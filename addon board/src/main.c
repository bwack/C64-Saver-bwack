/**
 * main.c
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ina219.h"
#include "oled.h"

void init(void) {
//	// disable interrupts
//	GIMSK = PCMSK = USICR = USISR = 0;
//	cli();
//	// enable global pullups
//	//MCUCR &= ~(1 << PUD);
//	// disable global pullups
//	MCUCR |= (1 << PUD);

	// OLED needs some time to settle down otherwise the screen is filled with garbage
	_delay_ms(100);

  ina_init();
	ssd1306_init();
	ssd1306_clear();
}

int main(void) {
	char buf[17];
	memset(buf, 0, 17);

	init();
	for (;;) {
		// bus voltage
		sprintf(buf, "%1.4fmV", ina_get_bus_voltage());
		ssd1306_string_font8x16xy(0, 0, buf);

		// current
		sprintf(buf, "%1.4fmA", ina_get_current());
		ssd1306_string_font8x16xy(0, 2, buf);

		_delay_ms(500);
	}
	return 0;
}
