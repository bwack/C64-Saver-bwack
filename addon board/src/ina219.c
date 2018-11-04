#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "ina219.h"

#define INA_SLAVE_ADDRESS	0x40

enum {
	REG_ADDR_CONFIG,
	REG_ADDR_SHUNT_VOLTAGE,
	REG_ADDR_BUS_VOLTAGE,
	REG_ADDR_POWER,
	REG_ADDR_CURRENT,
	REG_ADDR_CALIBRATION
};

void write_register(uint8_t reg, uint16_t val) {
	i2c_xfer_start();
	i2c_send_byte((uint8_t)((INA_SLAVE_ADDRESS << 1) & 0xfe));
	i2c_send_byte(reg);
	i2c_send_byte((uint8_t)((val >> 8) & 0xff));
	i2c_send_byte((uint8_t)(val & 0xff));
	i2c_xfer_stop();
}

void read_register(uint8_t reg, uint16_t *buf) {
	i2c_xfer_start();
	i2c_send_byte((INA_SLAVE_ADDRESS << 1));
	i2c_send_byte(reg);
	i2c_xfer_stop();
	i2c_xfer_start();
	i2c_send_byte((uint8_t)((INA_SLAVE_ADDRESS << 1) | 0x01));
//	*buf = (receive_byte(0) << 8) | receive_byte(1);
	uint8_t hi = i2c_receive_byte(0);
	uint8_t lo = i2c_receive_byte(1);
	*buf = (hi << 8) | lo;
	i2c_xfer_stop();
}

void ina_init(void) {
	write_register(REG_ADDR_CALIBRATION, 4096);
	write_register(REG_ADDR_CONFIG, 0b0001100110011111);
}

// volts
float ina_get_bus_voltage(void) {
	uint16_t raw;
	read_register(REG_ADDR_BUS_VOLTAGE, &raw);
	// FIXME raw value is 9930, it should return around 4.964V but we're getting 32.6360V
	return (float)(((raw >> 3) << 2) / 1000.0);
}

// amps
float ina_get_current(void) {
	uint16_t raw;
	// uncomment this line if you notice INA outputting weird values after load is switched on
	//write_register(REG_ADDR_CALIBRATION, 4096);
	read_register(REG_ADDR_CURRENT, &raw);
	float val = (float)((int16_t)raw);
	val /= (10 * 1000); // 10 uA per bit, mA to A
	return val;
}
