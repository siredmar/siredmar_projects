/**
 * \file uart.c
 * \brief This file contains the implementation of the UART module.
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

#include "uart.h"

/*--- Macros ---------------------------------------------------------*/

#define F_CPU 7372800UL
#define BAUD_HIGH 38400UL      /**< the high baudrate */
#define BAUD_LOW 9600UL        /**< the alternative low baudrate */

/** Calculated UBRR value for high baud rate */
#define UBRR_VAL_HIGH ((F_CPU+BAUD_HIGH*8)/(BAUD_HIGH*16)-1)

/** Calculated UBRR value for low baud rate */
#define UBRR_VAL_LOW ((F_CPU+BAUD_LOW*8)/(BAUD_LOW*16)-1)

/*--- External Function Definitions ----------------------------------*/

/**
 * \brief Initialize UART communication with given parameters rxen, txen, rxcie and BAUD_VAL_LOW
 *
 * \param rxen   enable receiving
 * \param txen   enable transmitting
 * \param rxcie  enable receiving interrupts
 */
void uart_init_low(uint8_t rxen, uint8_t txen, uint8_t rxcie)
{
    UCSR0B = 0x00;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B |= (rxen << RXEN0) | (rxcie << RXCIE0) | (txen << TXEN0);
    UBRR0H = UBRR_VAL_LOW >> 8;
    UBRR0L = UBRR_VAL_LOW & 0xFF;
}

/**
 * \brief Initialize UART communication with given parameters rxen, txen, rxcie and BAUD_VAL_HIGH
 *
 * \param rxen   enable receiving
 * \param txen   enable transmitting
 * \param rxcie  enable receiving interrupts
 */
void uart_init_high(uint8_t rxen, uint8_t txen, uint8_t rxcie)
{
    UCSR0B = 0x00;
    UCSR0B |= (rxen << RXEN0) | (rxcie << RXCIE0) | (txen << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0H = UBRR_VAL_HIGH >> 8;
    UBRR0L = UBRR_VAL_HIGH & 0xFF;
}

/**
 * \brief receive byte and store it in UDR
 *
 * \returns the received byte
 */
uint8_t uart_getc(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;         // Zeichen aus UDR an Aufrufer zurueckgeben
}

/**
 * \brief Send a single character via UART
 *
 * \param c byte to send
 */
void uart_putc(char byte)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = byte;         /* sende Zeichen */
}

/**
 * \brief Send a single byte via UART
 *
 * \param byte the byte to send
 */
void uart_send_byte(unsigned char byte)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = byte;         /* sende Byte */
}

/**
 * \brief Transmit string
 *
 * \param s pointer to string to send
 */
void uart_puts(const char *s) {
   while (*s ) {
      uart_putc(*s);
      s++;
   }
}

/**
 * \brief Transmit a byte stream (terminated with '\0') with a defined length
 *
 * \param s the bytestream the shall be send
 * \param length the length of the bytestream
 */
void uart_byte_s(unsigned char *s, uint8_t length) {
   uint8_t cnt = 0;
   while (cnt < length ) {
      uart_send_byte(s[cnt]);
      cnt++;
   }
}

