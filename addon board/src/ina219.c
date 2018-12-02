#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ina219.h"

//#define SLAVE_ADDRESS    0b1000000

#define SCL          PB2
#define SDA          PB0

#define TICK    5
#define HALF_TICK  (TICK / 2.0)

enum {
  REG_ADDR_CONFIG,
  REG_ADDR_SHUNT_VOLTAGE,
  REG_ADDR_BUS_VOLTAGE,
  REG_ADDR_POWER,
  REG_ADDR_CURRENT,
  REG_ADDR_CALIBRATION
};


#define DIGITAL_WRITE_HIGH(PORT, PAUSE)    { PORTB |= (1 << PORT); if (PAUSE) { _delay_us(TICK); } }
#define DIGITAL_WRITE_LOW(PORT, PAUSE)    { PORTB &= ~(1 << PORT); if (PAUSE) { _delay_us(TICK); } }
//#define DIGITAL_WRITE_BOTH_HIGH(PORT1, PORT2)  { PORTB |= ((1 << PORT1) | (1 << PORT2)); _delay_us(TICK); }
//#define DIGITAL_WRITE_BOTH_LOW(PORT1, PORT2)  { PORTB &= ~((1 << PORT1) | (1 << PORT2)); _delay_us(TICK); }

// When switching between tri-state ({DDxn, PORTxn} = 0b00) and output high ({DDxn, PORTxn} = 0b11),
// an intermediate state with either pull-up enabled {DDxn, PORTxn} = 0b01) or output
// low ({DDxn, PORTxn} = 0b10) must occur.
#define SET_SDA_INPUT()     { DDRB &= ~(1 << SDA); PORTB |= (1 << SDA); }
#define SET_SCL_INPUT()     { DDRB &= ~(1 << SCL); PORTB |= (1 << SCL); }
// Switching between input with pull-up and output low generates the same problem.
// The user must use either the tristate ({DDxn, PORTxn} = 0b00) or the output high
// state ({DDxn, PORTxn} = 0b10) as an intermediate step.
//#define SET_SDA_OUTPUT()    { DDRB &= ~(1 << SDA); PORTB &= ~(1 << SDA); DDRB |= (1 << SDA); }
//#define SET_SCL_OUTPUT()    { DDRB &= ~(1 << SCL); PORTB &= ~(1 << SCL); DDRB |= (1 << SCL); }
#define SET_SDA_OUTPUT()    { DDRB |= (1 << SDA); }
#define SET_SCL_OUTPUT()    { DDRB |= (1 << SCL); }
#define IS_INPUT(PORT)      (0 == (DDRB & (1 << PORT)))
#define IS_OUTPUT(PORT)      (0 != (DDRB & (1 << PORT)))

#define INA_CONFIG_REG  0b0001100110011111

uint8_t slave_address;

void xfer_start(void) {
  SET_SCL_OUTPUT();
  DIGITAL_WRITE_LOW(SCL, 1);
  SET_SDA_OUTPUT();
  DIGITAL_WRITE_HIGH(SDA, 1);
  DIGITAL_WRITE_HIGH(SCL, 1);
  DIGITAL_WRITE_LOW(SDA, 1);
  DIGITAL_WRITE_LOW(SCL, 1);
}

void xfer_stop(void) {
  SET_SDA_OUTPUT();
  DIGITAL_WRITE_LOW(SDA, 1);
  SET_SCL_OUTPUT();
  DIGITAL_WRITE_HIGH(SCL, 1);
  DIGITAL_WRITE_HIGH(SDA, 1);
  //DIGITAL_WRITE_LOW(SCL, 1);
  // INA has 28ms timeout after STOP
  //_delay_ms(30);
}

int send_byte(uint8_t byte) {
  uint8_t i;

  if (IS_INPUT(SDA)) {
    SET_SDA_OUTPUT();
  }
  if (IS_INPUT(SCL)) {
    SET_SCL_OUTPUT();
  }
  for (i = 0; i < 8; i++) {
    if ((byte << i) & 0x80) {
      DIGITAL_WRITE_HIGH(SDA, 0);
    } else {
      DIGITAL_WRITE_LOW(SDA, 0);
    }
    _delay_us(1);
    DIGITAL_WRITE_HIGH(SCL, 1);
    DIGITAL_WRITE_LOW(SCL, 0);
    _delay_us(4);
  }
  // wait for ACK after each byte
  _delay_us(TICK);
  SET_SDA_INPUT();
  _delay_us(1);
  DIGITAL_WRITE_HIGH(SCL, 0);
  _delay_us(HALF_TICK);
  int result = PORTB & (1 << SDA);
  _delay_us(HALF_TICK);
  DIGITAL_WRITE_LOW(SCL, 0);
  SET_SDA_OUTPUT();
  DIGITAL_WRITE_LOW(SDA, 1);

  return result;
}

uint8_t receive_byte(uint8_t last) {
  uint8_t i, val = 0;

  SET_SDA_INPUT();
  for (i = 0; i < 8; i++) {
    DIGITAL_WRITE_HIGH(SCL, 1);
    val <<= 1;
    val |= (PINB & (1 << SDA)) ? 0x01 : 0x00;
    DIGITAL_WRITE_LOW(SCL, 1);
  }
  SET_SDA_OUTPUT();
  if (last) {
    // send NACK
    DIGITAL_WRITE_HIGH(SDA, 1);
  } else {
    // send ACK
    DIGITAL_WRITE_LOW(SDA, 1);
  }
  DIGITAL_WRITE_HIGH(SCL, 1);
  DIGITAL_WRITE_LOW(SCL, 1);
  return val;
}

void write_register(uint8_t reg, uint16_t val) {
  xfer_start();
  send_byte((uint8_t)((slave_address << 1) & 0xfe));
  send_byte(reg);
  send_byte((uint8_t)((val >> 8) & 0xff));
  send_byte((uint8_t)(val & 0xff));
  xfer_stop();
}

void read_register(uint8_t reg, uint16_t *buf) {
  xfer_start();
  send_byte((slave_address << 1));
  send_byte(reg);
  xfer_stop();
  xfer_start();
  send_byte((uint8_t)((slave_address << 1) | 0x01));
  *buf = (receive_byte(0) << 8 ) | receive_byte(1);
  xfer_stop();
}

void I2C_reset(void) {
  // hold SDA or SCL low for at least 28ms
  SET_SDA_INPUT();
  SET_SCL_OUTPUT();
  DIGITAL_WRITE_LOW(SCL, 0);
  _delay_ms(30);
  SET_SCL_INPUT();
  // INA has 28ms timeout after STOP
  // this is not a STOP but let's wait anyway
  _delay_ms(30);
}

uint8_t I2C_autodetect_slave_address(void) {
  uint8_t current_address, found_address = 0;
  for (current_address = 0b1000000; current_address <= 0b1001111; current_address++) {
    // repeated start
    xfer_start();
    if (0 == send_byte((uint8_t) (current_address << 1))) {
      // found it
      found_address = current_address;
      break;
    }
    _delay_us(25);
  }
  xfer_stop();
  return found_address;
}

void initINA(void) {
  slave_address = 0b1000000;

  uint16_t calValue = 400;
  write_register(REG_ADDR_CALIBRATION, calValue);
  uint16_t config = 0b0011000111111111;
  write_register(REG_ADDR_CONFIG, config);
}

uint16_t ina219_get_bus_voltage_mv() {
  uint16_t busvoltage;
  initINA();
  read_register(REG_ADDR_BUS_VOLTAGE, &busvoltage);
  return (busvoltage>>1) + (busvoltage & 0x0001);
}

uint16_t ina219_get_current_ma(void) {
  uint16_t current;
  read_register(REG_ADDR_CURRENT, &current);
  return current;
}