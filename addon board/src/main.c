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

#include "font8x16.h"
#include "ssd1306xled.h"
#include "num2str.h"
#include "ina219.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//           ATtiny85
//         +----------+
//     (RST)---+ PB5  Vcc +---(+)--VCC--
// ---[OWOWOD]---+ PB3  PB2 +---[TWI/SCL]-
// --------------+ PB4  PB1 +-------------
// ---GND--(-)---+ GND  PB0 +---[TWI/SDA]-
//         +----------+
//        Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----------------------------------------------------------------------------

//#define F_CPU 8000000UL    // 8 MHz

#define SSD1306_SCL   PB2
#define SSD1306_SDA   PB0
#define HOLD_N        PB1

#define HOLD_ON       PORTB |= (1 << HOLD_N)
#define HOLD_OFF      PORTB &= ~(1 << HOLD_N)

#define SSD1306_SA    0x78  // Slave address

#define INA219_SA    0b1000000 // Slave address

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

  ssd1306xled_font8x16 = ssd1306xled_font8x16data;
  ssd1306_init();

  initINA();

  DDRB |= (1 << HOLD_N); 
  HOLD_OFF;
}

int main(void) {
//  int count = 0;

  init();
  ssd1306_clear();
  while (1) {
    char buf[USINT2DECASCII_MAX_DIGITS+1];
    uint16_t configval, currentval, shuntvoltage, busvoltage;
    I2C_reset();
    const int reg_addr_config = 0;
    const int shunt_voltage_reg = 1;
    const int bus_voltage_reg = 2;
    const int power_reg = 3;
    const int current_reg = 4;
    const int calibration_reg = 5;
    read_register(reg_addr_config, &configval);
    _delay_ms(40);
    read_register(current_reg, &currentval);
    read_register(shunt_voltage_reg, &shuntvoltage);
    read_register(bus_voltage_reg, &busvoltage);

    ssd1306_clear();
    memset(buf,0,sizeof(buf));
    usint2decascii(configval, buf);
    buf[sizeof(buf)-1]=0;
    ssd1306_string_font8x16xy(0,0,buf);

    memset(buf,0,sizeof(buf));
    usint2decascii(currentval, buf);
    ssd1306_string_font8x16xy(8*10,0,buf);

    memset(buf,0,sizeof(buf));
    usint2decascii(shuntvoltage, buf);
    ssd1306_string_font8x16xy(0,2,buf);

    memset(buf,0,sizeof(buf));
    usint2decascii(busvoltage, buf);
    ssd1306_string_font8x16xy(8*10,2,buf);
    HOLD_ON;
    _delay_ms(1000);
    HOLD_OFF;
  }
  return 0;
}

// ============================================================================
