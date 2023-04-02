/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <avr/io.h>

#include <avr/pgmspace.h>

#include "ssd1306xled.h"
#include "font16x16cn.h"

// ----------------------------------------------------------------------------

void ssd1306_char_font16x16cn(uint8_t x, uint8_t y, uint8_t N)
{
	uint8_t wm=0;
	unsigned int adder = 32 * N;
	ssd1306_setpos(x , y);
	ssd1306_send_data_start();
	for(wm = 0; wm < 16; wm++)
	{
		ssd1306_send_byte(pgm_read_byte(&ssd1306xled_font16x16cn[adder]));
		adder += 1;
	}
	ssd1306_send_data_stop();
	ssd1306_setpos(x,y + 1);
	ssd1306_send_data_start();
	for(wm = 0;wm < 16;wm++)
	{
		ssd1306_send_byte(pgm_read_byte(&ssd1306xled_font16x16cn[adder]));
		adder += 1;
	}
	ssd1306_send_data_stop();
}

// ----------------------------------------------------------------------------
