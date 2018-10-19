#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ina219.h"
#include "usi_i2c_master.h"

#define INA_CONFIG_REG	0b0001100110011111

void ina_init(void) {
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
	uint16_t ina219_currentDivider_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
	uint16_t ina219_powerMultiplier_mW = 2;     // Power LSB = 1mW per bit (2/1)

	// Set Config register to take into account the settings above
	char *msg = "Init INA 1/2\0";
	ssd1306_string_font8x16xy(0, 0, msg);
//	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V
//			| INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT
//			| INA219_CONFIG_SADCRES_12BIT_1S_532US
//			| INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
	uint16_t config = 0b0001100110011111;
	// TODO	wireWriteRegister(INA_REG_ADDR_CONFIG, config);
	char buf[4];
	buf[0] = (INA_SLAVE_ADDR << 1) & 0xfe;
	buf[1] = INA_REG_ADDR_CONFIG;
	buf[2] = (config >> 8) & 0xff;
	buf[3] = config & 0xff;
	USI_I2C_Master_Start_Transmission(buf, 4);
	_delay_ms(10);

	// Set Calibration register to 'Cal' calculated above
	msg = "Init INA 2/2\0";
	ssd1306_string_font8x16xy(0, 0, msg);
	// TODO	wireWriteRegister(INA_REG_ADDR_CALIBRATION, ina219_calValue);
	buf[0] = (INA_SLAVE_ADDR << 1) & 0xfe;
	buf[1] = INA_REG_ADDR_CALIBRATION;
	buf[2] = (ina219_calValue >> 8) & 0xff;
	buf[3] = ina219_calValue & 0xff;
	USI_I2C_Master_Start_Transmission(buf, 4);
	_delay_ms(10);

	ssd1306_string_font8x16xy(0, 0, "INIT COMPLETED");
}
