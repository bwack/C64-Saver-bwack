#ifndef _H_
#define _h_

void initINA(void);
void I2C_reset(void);
//void write_register(uint8_t reg, uint16_t val);
//void read_register(uint8_t reg, uint16_t *buf);
uint16_t ina219_get_bus_voltage_mv(void);
uint16_t ina219_get_current_ma(void);
#endif /* _H_ */
