// Copyright 2022 Nikita Leshenko (@nikital)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>

#include "i2c_master.h"
#include "quantum.h"

#define MCP23018_ADDR (0x20 << 1)
#define MCP23018_TIMEOUT I2C_TIMEOUT_INFINITE

#define MCP23018_IODIRA 0x00
#define MCP23018_IODIRB 0x01
#define MCP23018_IPOLA 0x02
#define MCP23018_IPOLB 0x03
#define MCP23018_IOCON 0x0a
#define MCP23018_GPPUA 0x0c
#define MCP23018_GPPUB 0x0d
#define MCP23018_GPIOA 0x12
#define MCP23018_GPIOB 0x13
#define MCP23018_OLATB 0x15

static void led_init(void)
{
    DDRB |= _BV(PIN7); // Output
    PORTB |= _BV(PIN7); // On by default
}

static void mcp23018_reset(void)
{
    // Assume device is in IOCON.BANK=0

    // Make sure writes increment pointer
    uint8_t enable_seqop[1] = {0};
    i2c_write_register(MCP23018_ADDR, MCP23018_IOCON, enable_seqop, sizeof(enable_seqop), MCP23018_TIMEOUT);

    // First thing, flip direction to input
    uint8_t init1[MCP23018_IOCON - MCP23018_IODIRA] = {0xff, 0xff, 0};
    i2c_write_register(MCP23018_ADDR, MCP23018_IODIRA, init1, sizeof(init1), MCP23018_TIMEOUT);

    // Skip IOCON

    // Zero the rest
    uint8_t init2[MCP23018_OLATB + 1 - MCP23018_GPPUA] = {0};
    i2c_write_register(MCP23018_ADDR, MCP23018_GPPUA, init2, sizeof(init2), MCP23018_TIMEOUT);
}

static void mcp23018_write(uint8_t reg, uint8_t value)
{
    i2c_write_register(MCP23018_ADDR, reg, &value, 1, MCP23018_TIMEOUT);
}

static uint8_t mcp23018_read(uint8_t reg)
{
    uint8_t value = 0;
    i2c_read_register(MCP23018_ADDR, reg, &value, 1, MCP23018_TIMEOUT);
    return value;
}

void keyboard_pre_init_kb(void)
{
    led_init();

    i2c_init();
    mcp23018_reset();
}

void matrix_init_custom(void)
{
    // cols are inputs with pullup
    static const uint8_t COLB = (_BV(PIN1)|_BV(PIN2)|_BV(PIN3)|_BV(PIN4)|_BV(PIN5)|_BV(PIN6));
    DDRB &= ~COLB;
    PORTB |= COLB;
    static const uint8_t COLC = (_BV(PIN6));
    DDRC &= ~COLC;
    PORTC |= COLC;
    static const uint8_t COLD = (_BV(PIN2)|_BV(PIN3)|_BV(PIN4)|_BV(PIN5)|_BV(PIN6)|_BV(PIN7));
    DDRD &= ~COLD;
    PORTD |= COLD;
    static const uint8_t COLF = (_BV(PIN0)|_BV(PIN1)|_BV(PIN2)|_BV(PIN3)|_BV(PIN4)|_BV(PIN5)|_BV(PIN6)|_BV(PIN7));
    DDRF &= (uint8_t)~COLF;
    PORTF |= COLF;

    // rows are outputs pulled high
    // [Temp] But now I don't have diodes on all buttons, so they are inputs without pullup
    static const uint8_t ROWB = (_BV(PIN0));
    DDRB &= ~ROWB;
    PORTB &= ~ROWB;
    static const uint8_t ROWC = (_BV(PIN7));
    DDRC &= ~ROWC;
    PORTC &= ~ROWC;
    static const uint8_t ROWE = (_BV(PIN6));
    DDRE &= ~ROWE;
    PORTE &= ~ROWE;

    // rows and led are output, pulled high (led pulled low)
    static const uint8_t ROWB2 = (_BV(PIN0)|_BV(PIN1)|_BV(PIN2));
    // cols are input, with pullup
    static const uint8_t COLA2 = (_BV(PIN0)|_BV(PIN1)|_BV(PIN2)|_BV(PIN3)|_BV(PIN4)|_BV(PIN5)|_BV(PIN6)|_BV(PIN7));
    static const uint8_t COLB2 = (_BV(PIN3)|_BV(PIN4)|_BV(PIN5)|_BV(PIN6));

    // Pullup on columns
    mcp23018_write(MCP23018_GPPUA, COLA2);
    mcp23018_write(MCP23018_GPPUB, COLB2);
    // Disconnect rows
    mcp23018_write(MCP23018_OLATB, ROWB2);
    // Only cols are inputs
    mcp23018_write(MCP23018_IODIRA, COLA2);
    mcp23018_write(MCP23018_IODIRB, COLB2);

}

static bool read_row(matrix_row_t * row)
{
    uint8_t B = PINB;
    uint8_t C = PINC;
    uint8_t D = PIND;
    uint8_t F = PINF;

    uint8_t A_ = mcp23018_read(MCP23018_GPIOA);
    uint8_t B_ = mcp23018_read(MCP23018_GPIOB);

#ifdef _COL
#error "_COL is already defined"
#endif
#define _COL(col, reg, offset) (((matrix_row_t)!(((reg) >> (offset)) & 1)) << col)
    matrix_row_t right_row =
        _COL( 0, D, 2) |
        _COL( 1, D, 3) |
        _COL( 2, D, 5) |
        _COL( 3, D, 4) |
        _COL( 4, D, 6) |
        _COL( 5, D, 7) |
        _COL( 6, B, 4) |
        _COL( 7, B, 5) |
        _COL( 8, B, 6) |
        _COL( 9, C, 6) |
        _COL(10, F, 7) |
        _COL(11, F, 6) |
        _COL(12, F, 5) |
        _COL(13, F, 4) |
        _COL(14, F, 1) |
        _COL(15, F, 0) |
        _COL(16, B, 1) |
        _COL(17, B, 2) |
        _COL(18, B, 3) |
        0;

    matrix_row_t left_row =
        _COL( 0, B_, 3) |
        _COL( 1, B_, 4) |
        _COL( 2, B_, 5) |
        _COL( 3, B_, 6) |
        _COL( 4, A_, 7) |
        _COL( 5, A_, 0) |
        _COL( 6, A_, 6) |
        _COL( 7, A_, 5) |
        _COL( 8, A_, 4) |
        _COL( 9, A_, 3) |
        _COL(10, A_, 2) |
        _COL(11, A_, 1) |
        0;
#undef _COL

    matrix_row_t new_row = right_row | (left_row << 19);
    bool changed = new_row != *row;
    *row = new_row;
    return changed;
}

bool matrix_scan_custom(matrix_row_t matrix[])
{
    bool changed = false;

    static const int SCAN_DELAY = 1;

    // Scan ROW 0
    DDRE |= _BV(PIN6);
    mcp23018_write(MCP23018_OLATB, _BV(PIN1)|_BV(PIN2));
    _delay_ms(SCAN_DELAY);
    changed |= read_row(&matrix[0]);
    DDRE &= ~_BV(PIN6);
    _delay_ms(1); // Be absolutely sure row becomes high impedance

    // Scan ROW 1
    DDRC |= _BV(PIN7);
    mcp23018_write(MCP23018_OLATB, _BV(PIN0)|_BV(PIN2));
    _delay_ms(SCAN_DELAY);
    changed |= read_row(&matrix[1]);
    DDRC &= ~_BV(PIN7);
    _delay_ms(1); // Be absolutely sure row becomes high impedance

    // Scan ROW 2
    DDRB |= _BV(PIN0);
    mcp23018_write(MCP23018_OLATB, _BV(PIN0)|_BV(PIN1));
    _delay_ms(SCAN_DELAY);
    changed |= read_row(&matrix[2]);
    DDRB &= ~_BV(PIN0);
    _delay_ms(1); // Be absolutely sure row becomes high impedance

    return changed;
}
