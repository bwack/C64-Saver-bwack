/*
 * oled.h
 */

#ifndef OLED_H_
#define OLED_H_

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_setpos(uint8_t x, uint8_t y);
void ssd1306_fill4(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4);
void ssd1306_fill2(uint8_t p1, uint8_t p2);
void ssd1306_fill(uint8_t p);
void ssd1306_string_font8x16xy(uint8_t x, uint8_t y, const char s[]);
void ssd1306_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]);

#endif /* OLED_H_ */
