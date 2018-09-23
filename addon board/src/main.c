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

//#include "tinyavrlib/cpufreq.h"

#include "font6x8.h"
#include "ssd1306xled.h"
#include "usi_i2c_master.h"

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

#define STEPS_DELAY_SHORT 200
#define STEPS_DELAY 600
#define STEPS_DELAY_LONG 1000

int main(void) {


	// ---- Initialization ----
	ssd1306xled_font6x8 = ssd1306xled_font6x8data;
	//_delay_ms(40);
	//ina_init();
	_delay_ms(40);
	ssd1306_init();

	int found=0;
	while(1) {
		ssd1306_clear();
		//_delay_ms(STEPS_DELAY_SHORT);
		//ssd1306_fill2(0x00, 0x00);
		//_delay_ms(STEPS_DELAY);
		ssd1306_setpos(0x00, 0x40);
		//_delay_ms(STEPS_DELAY);
		ssd1306_string_font6x8("Hello, World! Testing");
		_delay_ms(STEPS_DELAY);
        //
		//// ---- Fill out screen with patters ----
		//ssd1306_fill2(0x80, 0x00);
		//_delay_ms(STEPS_DELAY);
		////_delay_ms(STEPS_DELAY_LONG);
		//
		//ssd1306_fill2(0xff, 0xff);;
		//ssd1306_release();
		//_delay_ms(STEPS_DELAY);
		//ina_init();
		//_delay_ms(STEPS_DELAY_LONG);
	}

	return 0;
}

// ============================================================================