/**
 * \file spi.c
 * \brief This file contains the implementation of the SPI module.
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

/*--- Includes -------------------------------------------------------*/

#include <avr/io.h>
#define F_CPU 7372800UL
#include <util/delay.h>
#include "spi.h"

/*--- Macros ---------------------------------------------------------*/

#define nop() __asm volatile ("nop")

/*--- External Function Definitions ----------------------------------*/

/**
 * \brief Initializes spi communication
 */
void spi_init(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS) | (0 << DD_MISO);
    PORT_SPI |= (1<<PORT_MISO) | (1<<PORT_SS);

    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR)|(1<<SPR0)|(1<<SPR1); //fosc / 128
    SPSR |= (0 << SPI2X);
    _delay_ms(10);

}

/**
 * \brief Send one single byte via SPI
 *
 * \param cData byte to send via SPI
 */
uint8_t spi_send(uint8_t cData)
{
    SPDR = cData;
    while (!(SPSR & (1 << SPIF)));   //wait until sent
    cData = SPDR;
    return SPDR;
}

/**
 * \brief Read a single byte from SPI
 *
 * \returns the byte read from SPI
 */
uint8_t spi_read(void)
{
   uint8_t Byte = 0U;
   SPDR = 0xff;
   while(!(SPSR & (1<<SPIF))){};
   Byte = SPDR;
   return Byte;
}

/**
 * \brief empty dummy function - required for SDC library
 */
void SSC_ClearRxFifo(void)
{
   // enter your code here to clear the rx-fifo of the ssc.
}

