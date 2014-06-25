/**
 * \file uart.h
 * \brief This file contains the interface of the UART module.
 *
 * Copyright (C) 2011  Armin Schlegel, Christian Eismann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef _UART_H_
#define _UART_H_

/*--- Includes -------------------------------------------------------*/

#include <inttypes.h>
#include <avr/io.h>

/*--- External Function Prototypes -----------------------------------*/

extern void uart_init_low(uint8_t rxen, uint8_t txen, uint8_t rxcie);
extern void uart_init_high(uint8_t rxen, uint8_t txen, uint8_t rxcie);
extern uint8_t uart_getc(void);
extern void uart_putc(char byte);
extern void uart_send_byte(unsigned char byte);
extern void uart_puts(const char *s);
extern void uart_byte_s(unsigned char *s, uint8_t length);

#endif /* #ifndef _UART_H_ */

