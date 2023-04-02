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

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "tinyavrlib/cpufreq.h"

#include "ssd1306xled/ssd1306xled.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+   (-)--GND--
//       (RST)---+ PB5  Vcc +---(+)--VCC--
// ---[OWOWOD]---+ PB3  PB2 +---[TWI/SCL]-
// --------------+ PB4  PB1 +-------------
// --------(-)---+ GND  PB0 +---[TWI/SDA]-
//               +----------+
//              Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----------------------------------------------------------------------------

// -----(+)--------------->	// Vcc,	Pin 1 on SSD1306 Board
// -----(-)--------------->	// GND,	Pin 2 on SSD1306 Board
#define SSD1306_SCL		PB2	// SCL,	Pin 3 on SSD1306 Board
#define SSD1306_SDA		PB0	// SDA,	Pin 4 on SSD1306 Board

#define SSD1306_SA		0x78	// Slave address

// ----------------------------------------------------------------------------

int main(void) {

	// ---- Initialization ----
	
	// ---- CPU Frequency Setup ----
#if F_CPU == 1000000UL
#pragma message "F_CPU=1MHZ"
	CLKPR_SET(CLKPR_1MHZ);
#elif F_CPU == 8000000UL
#pragma message "F_CPU=8MHZ"
	CLKPR_SET(CLKPR_8MHZ);
#else
#pragma message "F_CPU=????"
#error "CPU frequency should be either 1 MHz or 8 MHz"
#endif

#define STEPS_DELAY_SHORT 200
#define STEPS_DELAY 800
#define STEPS_DELAY_LONG 2000

	// Small delay is necessary if ssd1306_init is the first operation in the application.
	_delay_ms(40);
	ssd1306_init();

	// ---- Main Loop ----
	for (;;) {
		ssd1306_clear(); _delay_ms(STEPS_DELAY_SHORT);

		// ---- Fill out screen with sequential bytes values ----
		ssd1306_setpos(0, 0);
		for (uint16_t i = 0; i < 128 * 8; i++) {
			ssd1306_byte(i);
		}
		_delay_ms(STEPS_DELAY);

		// ---- Fill out screen with rising stripes ----
		uint8_t p = 0xff;
		for (uint8_t i = 0; i < 8; i++) {
			p = (p >> 1);
			ssd1306_fill(~p);
		}
		_delay_ms(STEPS_DELAY);

		// ---- Fill out screen with patters ----
		ssd1306_fill(0xAA); _delay_ms(STEPS_DELAY);	// Horizontal lines
		ssd1306_fill2(0XFF, 0x00); _delay_ms(STEPS_DELAY);	// Vertical lines
		ssd1306_fill2(0x55, 0xAA); _delay_ms(STEPS_DELAY);	// Dots
		ssd1306_fill4(0xCC, 0xCC, 0x33, 0x33); _delay_ms(STEPS_DELAY);	// Small squares
		ssd1306_fill4(0xC0, 0x30, 0x0C, 0x03); _delay_ms(STEPS_DELAY);	// Slashes, sloping lines
		ssd1306_fill4(0x30, 0xC0, 0x03, 0x0C); _delay_ms(STEPS_DELAY);	// Slashes, sloping lines
		ssd1306_fill(0XFF); _delay_ms(STEPS_DELAY);	// Solid
		_delay_ms(STEPS_DELAY_LONG);		
	}

	return 0; // Return the mandatory result value. It is "0" for success.
}

// ============================================================================
