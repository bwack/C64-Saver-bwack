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
#include <stdio.h>
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

#define MEASURE_VAC 0
#define MEASURE_ACCUR 1
#define WRITE_VDC 2
#define WRITE_DCCUR 3

uint8_t state = 0;

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

void formatNumber(uint16_t value, char *buf, uint8_t maxlen, uint8_t decimals, uint8_t decimalpoint) {
  uint8_t offset=0;
  sprintf(buf,"%7d",value);

  // align field by number of decimal
  offset = 7-decimals;
  for(int i=0; i<decimals; i++)
    buf[i]=buf[i+offset];
  buf[decimals]=0;    

  // pad leading zeroes
  for(int i=0; i<decimals; i++) {
    if(buf[i]==' ' && i>=(decimals-decimalpoint-1)) buf[i]='0';
  }

  // add the dot
  if(decimalpoint>0) {
    for(int i=decimals; i>=decimals-decimalpoint; i--)   
      buf[i+1]=buf[i];
    buf[decimals-decimalpoint]='.';
  }
}

void adc_setup(uint8_t channel) {
  ADMUX = (1<<ADLAR) | channel; // SENSE_VAC
  //ADMUX = (1<<ADLAR) | (1<<MUX1) | (1<<MUX0); // SENSE_ACCUR
  //ADMUX = (1<<REFS1)|(1<<ADLAR)|(1<<REFS2)|(1<<MUX1);
}

uint16_t read_adc(void) {
  ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS1) | (1<<ADPS0); // conversion start
  while(ADCSRA & (1<<ADSC)); // wait for conversion
  uint8_t adl = ADCL;
  uint8_t adh = ADCH;
  return (adh<<2) | (adl>>6);
}

uint16_t read_adc_vac(int *buttondown) {
  static uint16_t adc_present_value;
  static uint16_t i=0;
  static uint16_t adchigh=0x0000, adclow=0xffff;
  uint16_t adcval = read_adc();
  if (adcval<100) {
    *buttondown=1;
    return adc_present_value;
  }
  buttondown=0;
  i++;
  if (i>3000) {
    adc_present_value = adchigh-adclow;
    i=0;
    adchigh=0;
    adclow=0xffff;
  } else {
    if(adcval>adchigh) adchigh=adcval;
    if(adcval<adclow) adclow=adcval;
  }
  return adc_present_value;
}

uint16_t read_adc_accur(void) {
  static uint16_t adc_present_value;
  static uint16_t i=0;
  static uint16_t adchigh=0x0000, adclow=0xffff;
  uint16_t adcval = read_adc();
  i++;
  if (i>3000) {
    adc_present_value = adchigh-adclow;
    i=0;
    adchigh=0;
    adclow=0xffff;
  } else {
    if(adcval>adchigh) adchigh=adcval;
    if(adcval<adclow) adclow=adcval;
  }
  return adc_present_value;
}

void setup_timer1(uint8_t delay) {
  TCCR1 = (0b1110<<CS10);
  OCR1A = delay;	
  TCNT1 = 0;
  TIFR |= (1<<OCF1A);
}

uint8_t has_timed_out(void) {
  return ((TIFR & (1<<OCF1A))>0)  ? 1 : 0;

}

void reset_timer1(void) {
    TIFR |= (1<<OCF1A);
    TCNT1 = 0;		
}

enum buttonpress {BUTTON_IDLE=0, BUTTON_SHORT_PRESS=1, BUTTON_LONG_PRESS=2};

int read_button(int buttondown) {
  static uint8_t cnt = 0;
  static uint8_t longpress=0;
  if (buttondown && longpress) return BUTTON_IDLE;
  longpress=0;
  if (buttondown) {
    cnt++;
    if (cnt>15) {
      cnt=0;
      longpress=1; // remember it
      return BUTTON_LONG_PRESS;
    }
  }
  else {
    if(cnt>1) {
      cnt=0;
      return BUTTON_SHORT_PRESS;
    }
    cnt=0;
  }
  return BUTTON_IDLE;
}

int main(void) {
//  int count = 0;

  init();
  ssd1306_clear();

  I2C_reset();
  _delay_ms(50); // ms loop
  uint8_t overcurrent_flag=0;
  setup_timer1(15);
  adc_setup(2);
  int buttondown=0;
  int button=BUTTON_IDLE;
  uint16_t adc_vac=0,adc_accur=0;
  while (1) {
    char buf[USINT2DECASCII_MAX_DIGITS+1];
    uint16_t busvoltage, current;
    //uint16_t configval, shuntvoltage;
    //const int reg_addr_config = 0;
    //const int shunt_voltage_reg = 1;
    //const int bus_voltage_reg = 2;
    //const int power_reg = 3;
    //const int current_reg = 4;
    //const int calibration_reg = 5;

    if (state==MEASURE_VAC || state==WRITE_VDC) {
      buttondown=0;
      adc_vac = read_adc_vac(&buttondown);
  
    } else if (state==MEASURE_ACCUR || state==WRITE_DCCUR) {
      adc_accur = read_adc_accur();
    }
    if ( has_timed_out() ) {
      reset_timer1();
      //HOLD_ON;
      //read_register(reg_addr_config, &configval);
      //read_register(shunt_voltage_reg, &shuntvoltage);
      busvoltage = ina219_get_bus_voltage_mv();
      current = ina219_get_current_ma();

      const int decimals=5, decimalpoint=3;
      if (state==MEASURE_VAC) {
        button = read_button(buttondown);
        formatNumber(adc_vac*19/100+adc_vac*2/100, buf, USINT2DECASCII_MAX_DIGITS, 3, 1); 
        formatNumber(button, buf, USINT2DECASCII_MAX_DIGITS, 3, 0); 
        ssd1306_string_font8x16xy(0,0,buf);
      }
      else if (state==MEASURE_ACCUR) {
        formatNumber(adc_accur, buf, USINT2DECASCII_MAX_DIGITS, 4, 0); 
        ssd1306_string_font8x16xy(0,2,buf);
      }
      else if (state==WRITE_VDC) {
        formatNumber(busvoltage, buf, USINT2DECASCII_MAX_DIGITS, decimals, decimalpoint); 
        ssd1306_string_font8x16xy(8*10,2,buf);
      }
      else if (state==WRITE_DCCUR) {
        formatNumber(current, buf, USINT2DECASCII_MAX_DIGITS, decimals, decimalpoint); 
        if (current > 1200) {
          overcurrent_flag = 1;
          HOLD_ON;
        }
        if (overcurrent_flag)
          strcpy(buf, "OVERCU");
        formatNumber(button, buf, USINT2DECASCII_MAX_DIGITS, decimals, decimalpoint); 
        ssd1306_string_font8x16xy(8*10,0,buf);
      }
  
      state++; // next state
      state = state & 0x03;
      if (state==MEASURE_VAC || state == WRITE_VDC) {
        adc_setup(2);
      } else if (state==MEASURE_ACCUR || state == WRITE_DCCUR){
        adc_setup(3);
      }
      //HOLD_OFF;
    }
  }
  return 0;
}

// ============================================================================
