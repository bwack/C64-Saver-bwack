#ifndef I2C_H_
#define I2C_H_

void i2c_xfer_start(void);
void i2c_xfer_stop(void);
uint8_t i2c_send_byte(uint8_t byte);
uint8_t i2c_receive_byte(uint8_t last);

#endif /* I2C_H_ */
