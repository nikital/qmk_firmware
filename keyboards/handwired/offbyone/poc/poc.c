/* Copyright 2021 Nikita Leshenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "poc.h"

#include "i2c_master.h"

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
  PORTB &= ~_BV(PIN0);
  DDRB |= _BV(PIN0);
}

static void mcp23018_reset(void)
{
    // Assume device is in IOCON.BANK=0

    // Make sure writes increment pointer
    uint8_t enable_seqop[1] = {0};
    i2c_writeReg(MCP23018_ADDR, MCP23018_IOCON, enable_seqop, sizeof(enable_seqop), MCP23018_TIMEOUT);

    // First thing, flip direction to input
    uint8_t init1[MCP23018_IOCON - MCP23018_IODIRA] = {0xff, 0xff, 0};
    i2c_writeReg(MCP23018_ADDR, MCP23018_IODIRA, init1, sizeof(init1), MCP23018_TIMEOUT);

    // Skip IOCON

    // Zero the rest
    uint8_t init2[MCP23018_OLATB + 1 - MCP23018_GPPUA] = {0};
    i2c_writeReg(MCP23018_ADDR, MCP23018_GPPUA, init2, sizeof(init2), MCP23018_TIMEOUT);
}

static void mcp23018_write(uint8_t reg, uint8_t value)
{
    i2c_writeReg(MCP23018_ADDR, reg, &value, 1, MCP23018_TIMEOUT);
}

static uint8_t mcp23018_read(uint8_t reg)
{
    uint8_t value = 0;
    i2c_readReg(MCP23018_ADDR, reg, &value, 1, MCP23018_TIMEOUT);
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
    // COL0/COL1 are inputs with pullup
    DDRD &= ~(_BV(PIN2) | _BV(PIN3));
    PORTD |= _BV(PIN2) | _BV(PIN3);

    // ROW0/ROW1 are outputs pulled low
    DDRD |= _BV(PIN4) | _BV(PIN5);
    PORTD |= _BV(PIN4) | _BV(PIN5);

    mcp23018_write(MCP23018_GPPUB, 0b11000001); // Pullup on columns and LED
    mcp23018_write(MCP23018_IPOLB, 0b11000000); // 1 means ground
    mcp23018_write(MCP23018_GPIOA, 0b11); // Disconnect rows from ground
    mcp23018_write(MCP23018_IODIRA, ~0b11); // Output on rows
    mcp23018_write(MCP23018_IODIRB, ~0b1); // Output on LED

    mcp23018_write(MCP23018_GPIOB, 0b1);
}

static bool read_row(matrix_row_t * row)
{
    bool col0 = !(PIND & _BV(PIN2));
    bool col1 = !(PIND & _BV(PIN3));
    uint8_t mcp = mcp23018_read(MCP23018_GPIOB);
    bool col2 = mcp & 0b01000000;
    bool col3 = mcp & 0b10000000;

    matrix_row_t new_row = col0 | (col1 << 1) | (col2 << 2) | (col3 << 3);
    bool changed = new_row != *row;
    *row = new_row;
    return changed;
}

bool matrix_scan_custom(matrix_row_t matrix[])
{
    bool changed = false;

    static const int SCAN_DELAY = 1;

    // Scan ROW 0 and ROW 2
    PORTD &= ~_BV(PIN5);
    mcp23018_write(MCP23018_GPIOA, 0b01);
    _delay_ms(SCAN_DELAY);
    changed |= read_row(&matrix[0]);
    PORTD |= _BV(PIN5);

    // Scan ROW 1 and ROW 3
    PORTD &= ~_BV(PIN4);
    mcp23018_write(MCP23018_GPIOA, 0b10);
    _delay_ms(SCAN_DELAY);
    changed |= read_row(&matrix[1]);
    PORTD |= _BV(PIN4);

    return changed;
}
