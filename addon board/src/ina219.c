#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ina219.h"

//#define INA219_SLAVE_ADDRESS		0b1000000

#define INA219_SCL					PB2
#define INA219_SDA					PB0

enum {
	INA219_REG_ADDR_CONFIG,
	INA219_REG_ADDR_SHUNT_VOLTAGE,
	INA219_REG_ADDR_BUS_VOLTAGE,
	INA219_REG_ADDR_POWER,
	INA219_REG_ADDR_CURRENT,
	INA219_REG_ADDR_CALIBRATION
};


#define DIGITAL_WRITE_HIGH(PORT)				{ PORTB |= (1 << PORT); /*_delay_us(5);*/ }
#define DIGITAL_WRITE_LOW(PORT)					{ PORTB &= ~(1 << PORT); /*_delay_us(5);*/ }
#define DIGITAL_WRITE_BOTH_HIGH(PORT1, PORT2)	{ PORTB |= ((1 << PORT1) | (1 << PORT2)); /*_delay_us(5);*/ }
#define DIGITAL_WRITE_BOTH_LOW(PORT1, PORT2)	{ PORTB &= ~((1 << PORT1) | (1 << PORT2)); /*_delay_us(5);*/ }

#define INA219_SET_SDA_INPUT() 		{ DDRB &= ~(1 << INA219_SDA); }
#define INA219_SET_SDA_OUTPUT()		{ DDRB |= (1 << INA219_SDA); }
#define INA219_SET_SCL_INPUT() 		{ DDRB &= ~(1 << INA219_SCL); }
#define INA219_SET_SCL_OUTPUT()		{ DDRB |= (1 << INA219_SCL); }

#define INA_CONFIG_REG	0b0001100110011111

uint8_t ina219_slave_address;

void INA219_xfer_start(void) {
	DIGITAL_WRITE_BOTH_HIGH(INA219_SDA, INA219_SCL);	// Set to HIGH
	INA219_SET_SDA_OUTPUT();
	INA219_SET_SCL_OUTPUT();
	DIGITAL_WRITE_LOW(INA219_SDA);	// Set to LOW
	_delay_us(5);
	DIGITAL_WRITE_LOW(INA219_SCL);	// Set to LOW
}

void INA219_xfer_stop(void) {
	DIGITAL_WRITE_BOTH_LOW(INA219_SDA, INA219_SCL);	// Set to LOW
	INA219_SET_SDA_OUTPUT();
	INA219_SET_SCL_OUTPUT();
	DIGITAL_WRITE_HIGH(INA219_SCL);	// Set to HIGH
	_delay_us(5);
	DIGITAL_WRITE_HIGH(INA219_SDA);	// Set to HIGH
	INA219_SET_SDA_INPUT();
	INA219_SET_SCL_INPUT();
}

int INA219_send_byte(uint8_t byte) {
	uint8_t i;

	INA219_SET_SDA_OUTPUT();
	INA219_SET_SCL_OUTPUT();
	for (i = 0; i < 8; i++) {
		if ((byte << i) & 0x80) {
			DIGITAL_WRITE_HIGH(INA219_SDA);
		} else {
			DIGITAL_WRITE_LOW(INA219_SDA);
		}
		DIGITAL_WRITE_HIGH(INA219_SCL);
		_delay_us(1);
		DIGITAL_WRITE_LOW(INA219_SCL);
	}
	// wait for ACK after each byte
	_delay_us(5);
	DIGITAL_WRITE_HIGH(INA219_SCL);
	INA219_SET_SDA_INPUT();
//	while (!INA219_SDA);
	int count = 1000;
	while ((PORTB & (1 << INA219_SDA)) && 0 != --count);
	DIGITAL_WRITE_LOW(INA219_SCL);
	return count;
}

uint8_t INA219_receive_byte(uint8_t last) {
	uint8_t i, val = 0;

	INA219_SET_SDA_INPUT();
	for (i = 0; i < 8; i++) {
		DIGITAL_WRITE_HIGH(INA219_SCL);
		val |= (PORTB & (1 << INA219_SDA)) ? 0x01 : 0x00;
		val <<= 1;
		DIGITAL_WRITE_LOW(INA219_SCL);
	}
	INA219_SET_SDA_OUTPUT();
	if (last) {
		// send NACK
		DIGITAL_WRITE_HIGH(INA219_SDA);
	} else {
		// send ACK
		DIGITAL_WRITE_LOW(INA219_SDA);
	}
	DIGITAL_WRITE_HIGH(INA219_SCL);
	DIGITAL_WRITE_LOW(INA219_SCL);
	return val;
}

void INA219_write_register(uint8_t reg, uint16_t val) {
	INA219_xfer_start();
	INA219_send_byte((uint8_t)((ina219_slave_address << 1) & 0xfe));
	INA219_send_byte(reg);
	INA219_send_byte((uint8_t)((val >> 8) & 0xff));
	INA219_send_byte((uint8_t)(val & 0xff));
	INA219_xfer_stop();
}

void INA219_read_register(uint8_t reg, uint16_t *buf) {
	INA219_xfer_start();
	INA219_send_byte((uint8_t)((ina219_slave_address << 1) | 0x01));
	INA219_send_byte(reg);
	*buf++ = INA219_receive_byte(0);
	*buf++ = INA219_receive_byte(1);
	INA219_xfer_stop();
}

void INA219_I2C_reset(void) {
	// hold SDA or SCL low for at least 28ms
	DIGITAL_WRITE_BOTH_LOW(INA219_SDA, INA219_SCL);
	INA219_SET_SDA_OUTPUT();
	INA219_SET_SCL_OUTPUT();
	_delay_us(30000 / 8);
	// INA219 should be reset by now
	// bring both lines high
	// DIGITAL_WRITE_BOTH_HIGH(INA219_SDA, INA219_SCL);
	// pullups will take care of this
	INA219_SET_SDA_INPUT();
	INA219_SET_SCL_INPUT();
}

uint8_t INA219_I2C_autodetect_slave_address(void) {
	uint8_t current_address, found_address = 0;
	for (current_address = 0b1000000; current_address <= 0b1001111; current_address++) {
		INA219_xfer_start();
		if (INA219_send_byte((uint8_t) ((current_address << 1) | 0x01)) > 0) {
			// found it
			found_address = current_address;
		}
		INA219_xfer_stop();
		if (found_address) {
			break;
		}
		_delay_us(1000);
	}
	return found_address;
}

void INA219_init(void) {
	// there is a lot of garbage on i2c bus during power-on event, even without oled
	// reset INA219 interface (hold SDA or SCL low for at least 28ms)
	INA219_I2C_reset();

	// INA219 doesn't respond to slave address 0b1000000, try to autodetect the address
	ina219_slave_address = INA219_I2C_autodetect_slave_address();
	if (!ina219_slave_address) {
		// INA219 not found, nothing to do
		return;
	}

	// FIXME calculate proper values (16V, 2 amps)

	// VBUS_MAX = 32V             (can also be set to 16V)
	// VSHUNT_MAX = 0.32          (Assumes Gain 8, 320mV, can also be 0.16, 0.08, 0.04)
	// RSHUNT = 0.1               (Resistor value in ohms)

	// 1. Determine max possible current
	// MaxPossible_I = VSHUNT_MAX / RSHUNT
	// MaxPossible_I = 3.2A

	// 2. Determine max expected current
	// MaxExpected_I = 2.0A

	// 3. Calculate possible range of LSBs (Min = 15-bit, Max = 12-bit)
	// MinimumLSB = MaxExpected_I/32767
	// MinimumLSB = 0.000061              (61uA per bit)
	// MaximumLSB = MaxExpected_I/4096
	// MaximumLSB = 0,000488              (488uA per bit)

	// 4. Choose an LSB between the min and max values
	//    (Preferrably a roundish number close to MinLSB)
	// CurrentLSB = 0.0001 (100uA per bit)

	// 5. Compute the calibration register
	// Cal = trunc (0.04096 / (Current_LSB * RSHUNT))
	// Cal = 4096 (0x1000)

	uint16_t ina219_calValue = 4096;

	// 6. Calculate the power LSB
	// PowerLSB = 20 * CurrentLSB
	// PowerLSB = 0.002 (2mW per bit)

	// 7. Compute the maximum current and shunt voltage values before overflow
	//
	// Max_Current = Current_LSB * 32767
	// Max_Current = 3.2767A before overflow
	//
	// If Max_Current > Max_Possible_I then
	//    Max_Current_Before_Overflow = MaxPossible_I
	// Else
	//    Max_Current_Before_Overflow = Max_Current
	// End If
	//
	// Max_ShuntVoltage = Max_Current_Before_Overflow * RSHUNT
	// Max_ShuntVoltage = 0.32V
	//
	// If Max_ShuntVoltage >= VSHUNT_MAX
	//    Max_ShuntVoltage_Before_Overflow = VSHUNT_MAX
	// Else
	//    Max_ShuntVoltage_Before_Overflow = Max_ShuntVoltage
	// End If

	// 8. Compute the Maximum Power
	// MaximumPower = Max_Current_Before_Overflow * VBUS_MAX
	// MaximumPower = 3.2 * 32V
	// MaximumPower = 102.4W

	// Set multipliers to convert raw current/power values
//	uint16_t ina219_currentDivider_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
//	uint16_t ina219_powerMultiplier_mW = 2;     // Power LSB = 1mW per bit (2/1)

	// Set Config register to take into account the settings above
	uint16_t config = 0b0001100110011111;
	INA219_write_register(INA219_REG_ADDR_CONFIG, config);

	// Set Calibration register to 'Cal' calculated above
	INA219_write_register(INA219_REG_ADDR_CALIBRATION, ina219_calValue);
}
