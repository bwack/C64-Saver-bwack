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
#include <avr/eeprom.h>
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

enum { MEASURE_VAC=0, MEASURE_ACCUR=1, WRITE_VDC=2, WRITE_DCCUR=3 };
uint8_t state = 0;

struct config {
  uint8_t oc; // in amps*10
  uint8_t hold;
  uint8_t vtrip;
};
struct config conf;

uint8_t overcurrent_flag = 0;
uint8_t overvoltage_flag = 0;

uint8_t EEMEM EEOvercurrent;
uint8_t EEMEM EEHold;
uint8_t EEMEM EEVtrip;

void init(void) {
  conf.oc=12; // 1.2A
  conf.hold=1; // 1=hold, 0=autorecover
  conf.vtrip=55; // 5.5V

  uint8_t ee_oc=255, ee_hold=255, ee_vtrip=255;
  ee_oc = eeprom_read_byte(&EEOvercurrent);
  ee_hold = eeprom_read_byte(&EEHold);
  ee_vtrip = eeprom_read_byte(&EEVtrip);
  if (ee_oc<255) conf.oc = ee_oc;
  if (ee_hold<255) conf.hold = ee_hold;
  if (ee_vtrip<255) conf.vtrip = ee_vtrip;
  
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

void formatNumber(uint16_t value, char *buf, uint8_t maxlen, uint8_t decimals, uint8_t decimalpoint, char* unit) {
  memset(buf,0,maxlen);
  uint8_t offset=0;
  if (maxlen < 5+1+strlen(unit)+1) return; // 5 digits + 1 dot + string length of unit + zero terminator
  if (decimals>5) return;
  snprintf(buf,maxlen,"%5d",value);
  //printf("-%s-\n", buf);
  
  // align field by number of decimal  12.345uu
  offset = 5-decimals;
  int i;
  for(i=0; i<(decimals); i++)
    buf[i]=buf[i+offset];
  buf[decimals]=0;    
  //printf("-%s-\n", buf);

  // pad leading zeroes
  for(int i=0; i<decimals; i++) {
    if(buf[i]==' ' && i>=(decimals-decimalpoint-1)) buf[i]='0';
  }
  //printf("-%s-\n", buf);

  // add the dot
  if(decimalpoint>0) {
    for(int i=decimals; i>=decimals-decimalpoint; i--)   
      buf[i+1]=buf[i]; // move to right for dot
    buf[decimals-decimalpoint]='.';
  }
  //printf("-%s-\n", buf);
  
  // add unit
  char* ptr = buf + decimals+1; // decimals + dot
  snprintf(ptr, maxlen-5, "%s", unit);
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
  *buttondown=0;
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

uint8_t read_button(uint8_t buttondown) {
  static uint8_t cnt = 0;
  static uint8_t longpress=0;
  if (buttondown && longpress) return BUTTON_IDLE;
  longpress=0;
  if (buttondown) {
    cnt++;
    if (cnt>10) {
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

uint16_t recorded_overcurrent=0;

void main_screen(uint16_t adc_vac, uint16_t adc_accur, uint16_t busvoltage, uint16_t current, int _button) {
  char buf[8];

  const int decimals=5, decimalpoint=3;
  if (state==MEASURE_VAC) {
    formatNumber(adc_vac*19/100+adc_vac*2/100, buf, sizeof(buf), 3, 1, "V"); 
    //formatNumber(recorded_overcurrent, buf, sizeof(buf), 5, 3, "A"); 
    ssd1306_string_font8x16xy(0,0,buf);
  }
  else if (state==MEASURE_ACCUR) {
    formatNumber(adc_accur, buf, sizeof(buf), 4, 0, "A"); 
    ssd1306_string_font8x16xy(0,2,buf);
  }
  else if (state==WRITE_VDC) {
    formatNumber(busvoltage, buf, sizeof(buf), decimals, decimalpoint, "V"); 
    if (overvoltage_flag|| busvoltage>5500) {
      static uint8_t flash=0;
      flash++;
      if (flash>21) strcpy(buf,"       ");
      if (flash>25) flash=0;
    }
    ssd1306_string_font8x16xy(7*10,2,buf);
  }
  else if (state==WRITE_DCCUR) {
    formatNumber(current, buf, sizeof(buf), decimals, decimalpoint, "A"); 
    if (overcurrent_flag) {
      static uint8_t flash=0;
      flash++;
      formatNumber(recorded_overcurrent, buf, sizeof(buf), decimals, decimalpoint, "A"); 
      if (flash>21) strcpy(buf,"       ");
      if (flash>25) flash=0;
    }
    else 
      formatNumber(current, buf, sizeof(buf), decimals, decimalpoint, "A"); 
    ssd1306_string_font8x16xy(7*10,0,buf);
  }  
}

void overcurrent_screen(void) {
  char buf[8];
  if (state==MEASURE_VAC) {
    ssd1306_string_font8x16xy(0,0,"Overcurrent");
    formatNumber(conf.oc, buf, sizeof(buf), 2, 1, "A"); 
    ssd1306_string_font8x16xy(8*3,2,buf);
    ssd1306_string_font8x16xy(8*6,2,"A");
  }
}

uint8_t oc_temp=0;

void set_overcurrent_screen(uint8_t button) {
  if (button==BUTTON_LONG_PRESS) oc_temp = conf.oc;
  if (button==BUTTON_SHORT_PRESS) {
    oc_temp += 1; // +0.1A
    if (oc_temp>20) oc_temp=5;
  }
  if (state==WRITE_DCCUR)
    ssd1306_string_font8x16xy(8*3,2,"    ");
  else if (state==MEASURE_VAC) {
    char buf[8];
    formatNumber(oc_temp, buf, sizeof(buf), 2, 1, "A"); 
    ssd1306_string_font8x16xy(8*3,2,buf);
  }
    
}

void overvoltage_hold_screen(void) {
  ssd1306_string_font8x16xy(0,0,"Overvoltage Hold");
  if (conf.hold)
    ssd1306_string_font8x16xy(8*3,2,"HOLD       ");
  else
    ssd1306_string_font8x16xy(8*3,2,"AUTORECOVER");
}

uint8_t hold_temp = 0;

void set_overvoltage_hold_screen(uint8_t button) {
  if (button==BUTTON_LONG_PRESS) hold_temp = conf.hold;
  if (button==BUTTON_SHORT_PRESS) {
    hold_temp += 1;
    if (hold_temp>1) hold_temp=0;
  }
  if (state!=WRITE_DCCUR) {
    if (hold_temp)
      ssd1306_string_font8x16xy(8*3,2,"HOLD       ");
    else
      ssd1306_string_font8x16xy(8*3,2,"AUTORECOVER");
  }
  else
    ssd1306_string_font8x16xy(8*3,2,"           ");
}

void dc_volt_trippoint_screen(void) {
  char buf[8];
  ssd1306_string_font8x16xy(0,0,"Voltage Trippnt.");
  if (conf.vtrip==55)
    ssd1306_string_font8x16xy(8*2,2,"5.5V Hardware");
  else {
    formatNumber(conf.vtrip, buf, sizeof(buf), 2, 1, "V"); 
    ssd1306_string_font8x16xy(8*2,2,buf);
    ssd1306_string_font8x16xy(8*7,2,"Software");
  }
}

uint8_t ov_temp=0;

void set_dc_volt_trippoint_screen(uint8_t button) {
  char buf[8];
  if (button==BUTTON_LONG_PRESS) ov_temp = conf.vtrip;
  if (button==BUTTON_SHORT_PRESS) {
    ov_temp += 1; // +0.1V
    if (ov_temp>55) ov_temp=51;
  }
  if (state==MEASURE_VAC) {
    if (ov_temp==55)
      ssd1306_string_font8x16xy(8*2,2,"5.5V Hardware");
    else {
      formatNumber(ov_temp, buf, sizeof(buf), 2, 1, "V"); 
      ssd1306_string_font8x16xy(8*2,2,buf);
      ssd1306_string_font8x16xy(8*7,2,"Software");
    }
  }
  else if (state==WRITE_DCCUR)
    ssd1306_string_font8x16xy(8*2,2,"    ");
}


enum { MENUSCREEN=0, RECOVER,
DC_OVERCCURRENT,   SET_DC_OVERCURRENT,   STORE_DC_OVERCURRENT,
OVERVOLTAGE_HOLD,  SET_OVERVOLTAGE_HOLD, STORE_OVERVOLTAGE_HOLD,
DC_VOLT_TRIPPOINT, SET_DC_VOLT_TRIPPOINT, STORE_DC_VOLT_TRIPPOINT };

uint8_t next_screen_state(uint8_t presentstate, uint8_t button) {
  uint8_t nextstate=presentstate;
  switch(presentstate) {
    case MENUSCREEN:
      if (button==BUTTON_SHORT_PRESS) nextstate = DC_OVERCCURRENT;
      else if (button==BUTTON_LONG_PRESS) nextstate = RECOVER;
      break;
    case DC_OVERCCURRENT:
      if (button==BUTTON_SHORT_PRESS) nextstate = OVERVOLTAGE_HOLD;
      else if (button==BUTTON_LONG_PRESS) nextstate = SET_DC_OVERCURRENT;
      break;
    case OVERVOLTAGE_HOLD:
      if (button==BUTTON_SHORT_PRESS) nextstate = DC_VOLT_TRIPPOINT;
      else if (button==BUTTON_LONG_PRESS) nextstate = SET_OVERVOLTAGE_HOLD;
      break;
    case DC_VOLT_TRIPPOINT:
      if (button==BUTTON_SHORT_PRESS) nextstate = MENUSCREEN;
      else if (button==BUTTON_LONG_PRESS) nextstate = SET_DC_VOLT_TRIPPOINT;
      break;
      
    case SET_DC_OVERCURRENT:
      if (button==BUTTON_LONG_PRESS) nextstate = STORE_DC_OVERCURRENT;
      break;
    case SET_OVERVOLTAGE_HOLD:
      if (button==BUTTON_LONG_PRESS) nextstate = STORE_OVERVOLTAGE_HOLD;
      break;
    case SET_DC_VOLT_TRIPPOINT:
      if (button==BUTTON_LONG_PRESS) nextstate = STORE_DC_VOLT_TRIPPOINT;
      break;
      
    case STORE_DC_OVERCURRENT:
      nextstate = DC_OVERCCURRENT;
      break;
    case STORE_OVERVOLTAGE_HOLD:
      nextstate = OVERVOLTAGE_HOLD;
      break;
    case STORE_DC_VOLT_TRIPPOINT:
      nextstate = DC_VOLT_TRIPPOINT;
      break;

    case RECOVER:
      nextstate = MENUSCREEN;
      break;

    default:
      break;
  }
  return nextstate;
}

int main(void) {
//  int count = 0;
  init();
  ssd1306_clear();

  I2C_reset();
  _delay_ms(50); // ms loop
  setup_timer1(10);
  adc_setup(2);
  static int buttondown=0;
  uint16_t adc_vac=0,adc_accur=0;
  uint8_t button = BUTTON_IDLE;
  uint8_t present_screen_state=MENUSCREEN;
  uint16_t dcvoltage = 0;
  uint16_t dccurrent = 0;
  _delay_ms(100);

  while (1) {
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
      //adc_setup(2);
      //adc_vac = read_adc_vac(&buttondown);

      if (state==MEASURE_VAC) {
        button = read_button(buttondown);
        uint8_t old_state = present_screen_state;
        present_screen_state = next_screen_state(present_screen_state, button);
        if(old_state != present_screen_state) ssd1306_clear();
      }

      if (overcurrent_flag && !overvoltage_flag) {
        static uint16_t cnt=0;
        cnt++;
        if (cnt>500) {
          cnt=0;
          overcurrent_flag=0;
          HOLD_OFF;
          _delay_ms(20);
        }
      }
      dcvoltage = ina219_get_bus_voltage_mv();
      dccurrent = ina219_get_current_ma();
      if (overvoltage_flag && dcvoltage < (conf.vtrip*100)-100 && !conf.hold) {
        present_screen_state = RECOVER;
      }

      // handle limits

      if (dccurrent > conf.oc*100 && !overcurrent_flag) {
        recorded_overcurrent = dccurrent;
        overcurrent_flag = 1;
      }
      
//      if (conf.vtrip < 55 && dcvoltage >= conf.vtrip*100 && !overvoltage_flag) {
      if (dcvoltage >= conf.vtrip*100 && !overvoltage_flag) {
        overvoltage_flag = 1;
      }
      
      switch(present_screen_state) {
        case MENUSCREEN:            main_screen(adc_vac,adc_accur,dcvoltage,dccurrent,button); break;
        case DC_OVERCCURRENT:       overcurrent_screen(); break;
        case OVERVOLTAGE_HOLD:      overvoltage_hold_screen(); break;
        case DC_VOLT_TRIPPOINT:     dc_volt_trippoint_screen(); break;
        
        case SET_DC_OVERCURRENT:    set_overcurrent_screen(button); break;
        case SET_OVERVOLTAGE_HOLD:  set_overvoltage_hold_screen(button); break;
        case SET_DC_VOLT_TRIPPOINT: set_dc_volt_trippoint_screen(button); break;
        
        case STORE_DC_OVERCURRENT:
          conf.oc = oc_temp; eeprom_write_byte(&EEOvercurrent, conf.oc); break;
        case STORE_OVERVOLTAGE_HOLD:
          conf.hold = hold_temp; eeprom_write_byte(&EEHold, conf.hold); break;
        case STORE_DC_VOLT_TRIPPOINT:
          conf.vtrip = ov_temp; eeprom_write_byte(&EEVtrip, conf.vtrip); break;
        case RECOVER:
          HOLD_OFF; overcurrent_flag=0; overvoltage_flag=0; break;
      }

      if (overcurrent_flag || overvoltage_flag) HOLD_ON;
      else HOLD_OFF;
      
      // next state
      state++;
      state = state & 0x03;
      if (state==MEASURE_VAC || state == WRITE_VDC) {
        adc_setup(2);
      } else if (state==MEASURE_ACCUR || state == WRITE_DCCUR){
        adc_setup(3);
      }
      button = BUTTON_IDLE;
      //HOLD_OFF;
    }
  }
  return 0;
}

// ============================================================================
