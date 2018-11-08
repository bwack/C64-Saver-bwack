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

#include "ssd1306xled/font6x8.h"
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
	ssd1306xled_font6x8 = ssd1306xled_font6x8data;
	
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
#define STEPS_DELAY 600
#define STEPS_DELAY_LONG 1000

	// Small delay is necessary if ssd1306_init is the first operation in the application.
	_delay_ms(40);
	ssd1306_init();

	// ---- Main Loop ----
	for (;;) {
		ssd1306_clear(); _delay_ms(STEPS_DELAY_SHORT);

		// ---- Fill out screen with patters ----
		ssd1306_fill2(0x80, 0x00); _delay_ms(STEPS_DELAY);
		_delay_ms(STEPS_DELAY_LONG);
		
		// NOTE: Screen width - 128, that is 21 symbols per row.

		// ---- Print some small and large text on the screen ----
		ssd1306_setpos(0, 0); ssd1306_string_font6x8("Hello, World! Testing");
		ssd1306_setpos(7, 1); ssd1306_string_font6x8("SSD1306xLED Library");
		ssd1306_setpos(0, 2); ssd1306_string_font6x8("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[5]^_`abcdefghijklmnopqrstuvwxyz~");
		ssd1306_setpos(0, 6); ssd1306_string_font6x8(" This is the TINUSUR ");
		ssd1306_setpos(7, 7); ssd1306_string_font6x8("http://tinusaur.org");
		_delay_ms(STEPS_DELAY_LONG);	

		_delay_ms(STEPS_DELAY_LONG); _delay_ms(STEPS_DELAY_LONG); _delay_ms(STEPS_DELAY_LONG); 
	}

	return 0;	// Return the mandatory for the "main" function int value. It is "0" for success.
}

// ============================================================================
