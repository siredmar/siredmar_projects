/**
 * \file sdc.h
 * \brief This file contains the interface of the SPI module.
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

#ifndef _SPI_H_
#define _SPI_H_

/*--- Includes -------------------------------------------------------*/

#include <stdio.h>
#include <avr/io.h>

/*--- Macros ---------------------------------------------------------*/

/** SPI pin configuration */
#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_SCK DDB7
#define DD_MISO DDB6
#define DD_SS DDD4
#define PORT_SPI PORTB
#define PORT_MISO PORTB6
#define PORT_SS PORTB4

/*--- External Function Prototypes -----------------------------------*/

extern void spi_init(void);
extern uint8_t spi_send(uint8_t cData);
extern uint8_t spi_read(void);
extern void SSC_ClearRxFifo(void);

#endif /* #ifndef _SPI_H_ */

