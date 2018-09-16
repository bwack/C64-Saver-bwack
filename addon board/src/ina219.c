#include <stdint.h>
#include <avr/io.h>
#include "ina219.h"
#include "usi_i2c_master.h"

void ina_init(void) {
	char msg[4];
	msg[0]=126;
	msg[1]=126;
	msg[2]=126;
	USI_I2C_Master_Start_Transmission(msg,3);
	return;
}
