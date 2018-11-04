/*
 * i2c.c
 */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define SCL	PB2
#define SDA	PB0

#define TICK		5.0
#define HALF_TICK	(TICK / 2.0)

#define DIGITAL_WRITE_HIGH(PORT, PAUSE)		{ PORTB |= (1 << PORT); if (PAUSE) { _delay_us(TICK); } }
#define DIGITAL_WRITE_LOW(PORT, PAUSE)		{ PORTB &= ~(1 << PORT); if (PAUSE) { _delay_us(TICK); } }

// When switching between tri-state ({DDxn, PORTxn} = 0b00) and output high ({DDxn, PORTxn} = 0b11),
// an intermediate state with either pull-up enabled {DDxn, PORTxn} = 0b01) or output
// low ({DDxn, PORTxn} = 0b10) must occur.
#define SET_SDA_INPUT() 		{ DDRB &= ~(1 << SDA); PORTB |= (1 << SDA); }
#define SET_SCL_INPUT() 		{ DDRB &= ~(1 << SCL); PORTB |= (1 << SCL); }
//#define SET_SDA_INPUT() 		{ DDRB &= ~(1 << SDA); PORTB &= ~(1 << SDA); }
//#define SET_SCL_INPUT() 		{ DDRB &= ~(1 << SCL); PORTB &= ~(1 << SCL); }
// Switching between input with pull-up and output low generates the same problem.
// The user must use either the tristate ({DDxn, PORTxn} = 0b00) or the output high
// state ({DDxn, PORTxn} = 0b10) as an intermediate step.
#define SET_SDA_OUTPUT()		{ DDRB |= (1 << SDA); }
#define SET_SCL_OUTPUT()		{ DDRB |= (1 << SCL); }
#define IS_INPUT(PORT)			(0 == (DDRB & (1 << PORT)))
#define IS_OUTPUT(PORT)			(0 != (DDRB & (1 << PORT)))

#define INA_CONFIG_REG	0b0001100110011111

void i2c_xfer_start(void) {
	SET_SCL_OUTPUT();
//	DIGITAL_WRITE_LOW(SCL, 1);
	SET_SDA_OUTPUT();
	DIGITAL_WRITE_HIGH(SDA, 1);
	DIGITAL_WRITE_HIGH(SCL, 1);
	DIGITAL_WRITE_LOW(SDA, 1);
	DIGITAL_WRITE_LOW(SCL, 1);
}

void i2c_xfer_stop(void) {
	SET_SDA_OUTPUT();
	DIGITAL_WRITE_LOW(SDA, 1);
	SET_SCL_OUTPUT();
	DIGITAL_WRITE_HIGH(SCL, 1);
	DIGITAL_WRITE_HIGH(SDA, 1);
//	DIGITAL_WRITE_LOW(SCL, 1);
	// INA has 28ms timeout after STOP
//	_delay_ms(30);
}

uint8_t i2c_send_byte(uint8_t byte) {
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
	uint8_t result = PINB & (1 << SDA);
	_delay_us(HALF_TICK);
	DIGITAL_WRITE_LOW(SCL, 0);
	SET_SDA_OUTPUT();
	DIGITAL_WRITE_LOW(SDA, 1);

	return result;
}

// FIXME val is always 0xff
uint8_t i2c_receive_byte(uint8_t last) {
	uint8_t i, val = 0;

	SET_SDA_INPUT();
	for (i = 0; i < 8; i++) {
		DIGITAL_WRITE_HIGH(SCL, 1);
		val <<= 1;
		val |= (PORTB & (1 << SDA)) ? 0x01 : 0x00;
//		if (0 != (PINB & (1 << SDA))) {
//			val |= 0x01;
//		}
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
