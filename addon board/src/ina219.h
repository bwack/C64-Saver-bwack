#ifndef _INA219_H_
#define _INA219_h_

void INA219_init(void);
void INA219_write_register(uint8_t reg, uint16_t val);
void INA219_read_register(uint8_t reg, uint16_t *buf);

#endif /* _INA219_H_ */
