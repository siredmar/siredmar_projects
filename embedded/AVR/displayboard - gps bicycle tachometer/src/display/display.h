/**
 * \file display.h
 * \brief This file contains the interface of the display module.
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

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*--- Includes -------------------------------------------------------*/

#include <stdio.h>
#include <inttypes.h>

/* F_CPU has to be defined before including util/delay.h */
#define F_CPU 7372800UL
#include <util/delay.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "../spi/spi.h"
#include "../gps/gps.h"
#include "../tools/tools.h"


/*--- Macros ---------------------------------------------------------*/

/* A0 */
#define DDR_A0_DSP DDRD
#define DD_A0_DSP DDD2
#define PORT_A0_DSP PORTD
#define A0_DSP PD2

/* RESET_DSP */
#define DDR_RESET_DSP DDRD
#define DD_RESET_DSP DDD3
#define PORT_RESET_DSP PORTD
#define RESET_DSP PD3

/* CS_DSP */
#define DDR_CS_DSP DDRB
#define DD_CS_DSP DDB4
#define PORT_CS_DSP PORTB
#define CS_DSP PB4

#define PAGES 7
#define LINES 8
#define COLUMS 128

#define DISPLAY_PAGE_ADDRESS      0xB0
#define DISPLAY_COL_ADDRESS_MSB   0x10
#define DISPLAY_COL_ADDRESS_LSB   0x00
#define DISP_WIDTH   128L
#define DISP_HEIGHT  64L
#define PIXEL_ON 1
#define PIXEL_OFF 0
#define FONT_WIDTH   5
#define FONT_HEIGHT   7

/*--- External Function Prototypes -----------------------------------*/

extern void display_reset(void);
extern void display_cs_select(void);
extern void display_cs_unselect(void);
extern void display_command_mode(void);
extern void display_data_mode(void);
extern void display_init(void);
extern void display_send_data(unsigned char cData);
extern void display_send_command(unsigned char cData);

extern void display_clear_screen(void);
extern void display_clear_ram(void);
extern void display_putpixel(unsigned char x, unsigned char y, int pixel_status);
extern void display_send_frame(void);
extern void display_go_to(unsigned char col, unsigned char page);
extern void display_draw_char_5x7(unsigned short x, unsigned short y,char character);
extern void display_string(unsigned short x, unsigned short y, const char *str);
extern void display_bmp_flash(unsigned char x, unsigned char y, unsigned char *addr);
extern void display_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
extern void display_hline(uint8_t x0, uint8_t y0, uint8_t length, uint8_t pixel_status);

#endif /* #ifndef _DISPLAY_H_ */

