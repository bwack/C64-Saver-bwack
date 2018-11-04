/*
 * oled.c
 *
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 */
#include <stdint.h>
#include <avr/pgmspace.h>
#include "oled.h"
#include "font8x16.h"
#include "i2c.h"

#define SSD1306_SLAVE_ADDRESS	0x3c

const uint8_t ssd1306_init_sequence[] PROGMEM = {	// Initialization Sequence
	0xAE,			// Display OFF (sleep mode)
	0x20, 0b00,		// Set Memory Addressing Mode
					// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
					// 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,			// Set COM Output Scan Direction
	0x00,			// ---set low column address
	0x10,			// ---set high column address
	0x40,			// --set start line address
	0x81, 0x3F,		// Set contrast control register
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x1F,		// Set multiplex ratio(1 to 64)
	0xA4,			// Output RAM to Display
					// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xD5,			// --set display clock divide ratio/oscillator frequency
	0xF0,			// --set divide ratio
	0xD9, 0x22,		// Set pre-charge period
	0xDA, 0x02,		// Set com pins hardware configuration
	0xDB,			// --set vcomh
	0x20,			// 0x20,0.77xVcc
	0x8D, 0x14,		// Set DC-DC enable
	0xAF			// Display ON in normal mode
};

const uint8_t *ssd1306xled_font8x16 = ssd1306xled_font8x16data;


void ssd1306_send_command_start(void) {
	i2c_xfer_start();
	i2c_send_byte(SSD1306_SLAVE_ADDRESS << 1);  // Slave address, SA0=0
	i2c_send_byte(0x00);	// write command
}

void ssd1306_send_command_stop(void) {
	i2c_xfer_stop();
}

void ssd1306_send_command(uint8_t command) {
	ssd1306_send_command_start();
	i2c_send_byte(command);
	ssd1306_send_command_stop();
}

void ssd1306_send_data_start(void) {
	i2c_xfer_start();
	i2c_send_byte(SSD1306_SLAVE_ADDRESS << 1);
	i2c_send_byte(0x40);	// write data
}

void ssd1306_send_data_stop(void) {
	i2c_xfer_stop();
}

void ssd1306_byte(uint8_t b) {
	ssd1306_send_data_start();
	i2c_send_byte(b);
	ssd1306_send_data_stop();
}

// ============================================================================

void ssd1306_init(void) {
	for (uint8_t i = 0; i < sizeof (ssd1306_init_sequence); i++) {
		ssd1306_send_command(pgm_read_byte(&ssd1306_init_sequence[i]));
	}
}

void ssd1306_setpos(uint8_t x, uint8_t y) {
	ssd1306_send_command_start();
	i2c_send_byte(0xb0 + y);
	i2c_send_byte(((x & 0xf0) >> 4) | 0x10); // | 0x10
	/* TODO: Verify correctness */
	i2c_send_byte((x & 0x0f)); // | 0x01
	ssd1306_send_command_stop();
}

void ssd1306_fill4(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
	ssd1306_setpos(0, 0);
	ssd1306_send_data_start();
	for (uint16_t i = 0; i < 128 * 8 / 4; i++) {
		i2c_send_byte(p1);
		i2c_send_byte(p2);
		i2c_send_byte(p3);
		i2c_send_byte(p4);
	}
	ssd1306_send_data_stop();
}

void ssd1306_fill2(uint8_t p1, uint8_t p2) {
	ssd1306_fill4(p1, p2, p1, p2);
}

void ssd1306_fill(uint8_t p) {
	ssd1306_fill4(p, p, p, p);
}

void ssd1306_clear(void) {
	ssd1306_fill(0);
}

void ssd1306_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]) {
	uint16_t j = 0;
	uint8_t y;
	if (y1 % 8 == 0) y = y1 / 8;
	else y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		ssd1306_setpos(x0,y);
		ssd1306_send_data_start();
		for (uint8_t x = x0; x < x1; x++)
		{
			i2c_send_byte(pgm_read_byte(&bitmap[j++]));
		}
		ssd1306_send_data_stop();
	}
}

void ssd1306_string_font8x16xy(uint8_t x, uint8_t y, const char s[]) {
	uint8_t ch, j = 0;
	while (s[j] != '\0') {
		ch = s[j] - 32; // Convert ASCII code to font data index.
//		if (x > 120) { x = 0; y++; }
		ssd1306_setpos(x, y);
		ssd1306_send_data_start();
		for (uint8_t i = 0; i < 8; i++) {
			i2c_send_byte(pgm_read_byte(&ssd1306xled_font8x16[ch * 16 + i]));
		}
		ssd1306_send_data_stop();
		ssd1306_setpos(x, y + 1);
		ssd1306_send_data_start();
		for (uint8_t i = 0; i < 8; i++) {
			i2c_send_byte(pgm_read_byte(&ssd1306xled_font8x16[ch * 16 + i + 8]));
		}
		ssd1306_send_data_stop();
		x += 8;
		j++;
	}
}
