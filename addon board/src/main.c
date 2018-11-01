/**
 * SSD1306xLED - Library/Driver for the SSD1306 based OLED/PLED 128x64 displays
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2018 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ============================================================================
// NOTE: About F_CPU - it should be set in either (1) Makefile; or (2) in the IDE.
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include "tinyavrlib/cpufreq.h"

//#include "font8x16.h"
//#include "ssd1306xled.h"
//#include "num2str.h"
#include "ina219.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+
//       (RST)---+ PB5  Vcc +---(+)--VCC--
// ---[OWOWOD]---+ PB3  PB2 +---[TWI/SCL]-
// --------------+ PB4  PB1 +-------------
// ---GND--(-)---+ GND  PB0 +---[TWI/SDA]-
//               +----------+
//              Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----------------------------------------------------------------------------

//#define F_CPU 8000000UL		// 8 MHz

#define SSD1306_SCL		PB2
#define SSD1306_SDA		PB0

#define SSD1306_SA		0x78	// Slave address

#define INA219_SA		0b1000000 // Slave address

// ----------------------------------------------------------------------------

#define STEPS_DELAY_SHORT 200
#define STEPS_DELAY 600
#define STEPS_DELAY_LONG 1000

void init(void) {
	// disable interrupts
	GIMSK = PCMSK = USICR = USISR = 0;
	cli();
	// enable global pullups
	MCUCR &= ~(1 << PUD);

	// set SDA and SCL to tri-state
	DDRB &= ~((1 << PB0) | (1 << PB2));
	PORTB &= ~((1 << PB0) | (1 << PB2));

	// wait a bit until everything stabilises
	_delay_ms(40);

//	ssd1306xled_font8x16 = ssd1306xled_font8x16data;
//	ssd1306_init();
//	ssd1306_clear();
//	ssd1306_string_font8x16xy(0, 0, "Init INA\0");

	initINA();

//	ssd1306_string_font8x16xy(0, 0, "Success\0");
	_delay_ms(2000);
}

int main(void) {
//	int count = 0;
//	char buf[1 + USINT2DECASCII_MAX_DIGITS];

	init();
//	memset(buf, 0, 1 + USINT2DECASCII_MAX_DIGITS);
	while (1) {
//		usint2decascii(count, buf);
//		count += 256;
//		ssd1306_string_font8x16xy(0, 0, buf);
//		ssd1306_string_font8x16xy(0, 2, buf);
	}

	return 0;
}

// ============================================================================
