/**
 * \file main.c
 * \brief This file contains the implementation of the 'main' routine
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

#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "spi/spi.h"
#include "display/display.h"
#include "uart/uart.h"
#include "gps/gps.h"
#include "led/led.h"
#include "windows/windows.h"
#include "display/images.h"
#include "interrupts/interrupts.h"
#include "sdc/sdc.h"
#include "fat16/fat16.h"

/*--- External Function Definitions ----------------------------------*/

int main(void)
{
   led_init();

   /*
    * Initializing the SPI interface for communication with the graphical display.
    */
   spi_init();

   /*
    * Initializing the graphical display.
    */
   display_init();
   display_clear_screen();
   display_send_frame();

   gps_init_mem();

   /*
    * If the baudrate of the used GPS receiver is not modified, it is per default
    * at 38400UL. To change any configuration values of the GPS receiver, the
    * baudrate of the UART communication has to be set to this level, otherwise
    * no further communication would be possible
    */
   uart_init_high(0, 1, 0);

   /*
    * Initializing the GPS receiver by setting the baudrate, disabling unused
    * GPS data sets, ...
    */
   gps_init_stage1();
   gps_init_stage2();

   /*
    * After the initialization and configuration of the GPS receiver the baudrate
    * can be set to a lower level (here: 9800L).
    */
   uart_init_low(1, 0, 1);

   /* Enabling global Interrupts */
   sei();
   while (1){ }
}

