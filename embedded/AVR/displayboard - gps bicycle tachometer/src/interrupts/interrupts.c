/**
 * \file interrupts.c
 * \brief This file contains all interrupt routines used in this project.
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

#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "interrupts.h"
#include "../led/led.h"
#include "../windows/windows.h"
#include "../gps/gps.h"


/** Counter variable used for determining the type and the end of the received data set */
uint8_t uart_str_cnt = 0;

/** Status variable, indicating whether a new data set is incoming (1) or not (0) */
uint8_t new_data = 0;

/** Buffer holding the received data set */
char uart_str[MAXUARTSTR] = "";

/** Status variable, indicating whether a RMC data set has been received (1) or not (0) */
uint8_t rmc_found = 0;

/** Status variable, indicating whether a VTG data set has been received (1) or not (0) */
uint8_t vtg_found = 0;

/** Status variable, indicating whether a GGA data set has been received (1) or not (0) */
uint8_t gga_found = 0;

/** Status variable, indicating whether the end of a data set has been found (\n\r) */
uint8_t block_finished = 0;

/** Index of the beginning of a new data set within the UART buffer */
uint8_t new_data_index = 0;

/**
 * \brief Is called every time a byte is received by UART interrupt.
 *
 * Every time this routine is called it reads one byte sent by the GPS module.
 * The current byte is attached to the end of the read buffer until:
 *   - RMC data set was received
 *   - VTG data set was received
 *   - GGA data set was received
 */
ISR(SIG_USART_RECV)
{
   unsigned char next_char;

   led_led1_enable();

   /* buffer received character */
   next_char = UDR0;

   /* data block not finished yet - collecting further byte */
   if(next_char == '$'){
             new_data = 1;
             new_data_index = uart_str_cnt;
             block_finished = 0;
   }
   if(block_finished == 0){
      uart_str[uart_str_cnt] = next_char;
      if(uart_str_cnt > 2){
         if(uart_str_cnt - new_data_index == 5){         //Absolute Position (cnt) - aktueller Datenindex (index) = 5 (z.b. $GPRMC um das erkannte C, M und R zu verarbeiten)
            if(uart_str[uart_str_cnt - 2] == 'R' && uart_str[uart_str_cnt - 1] == 'M' && uart_str[uart_str_cnt] == 'C'){
               rmc_found = 1;
            }
            if(uart_str[uart_str_cnt - 2] == 'G' && uart_str[uart_str_cnt - 1] == 'G' && uart_str[uart_str_cnt] == 'A'){
               gga_found = 1;
            }
            if(uart_str[uart_str_cnt - 2] == 'V' && uart_str[uart_str_cnt - 1] == 'T' && uart_str[uart_str_cnt] == 'G'){
               vtg_found = 1;
            }
         }
      }
   }

   /* data block finished - continuing processing of received data */
   if(rmc_found && gga_found && vtg_found && uart_str[uart_str_cnt - 1] == '\r' && uart_str[uart_str_cnt] == '\n'){
      block_finished = 1;
   }

   uart_str_cnt++;

   /* buffer is finished - processing data */
   if(block_finished == 1){
      uart_str[uart_str_cnt] = '\0';
      uart_str_cnt = 0;
      block_finished = 0;
      new_data = 0;
      rmc_found = 0;
      gga_found = 0;
      vtg_found = 0;

      /* save data buffer to sd card */
      gps_save_data_sd(uart_str);
      /* split buffer to it's tokens*/
      gps_split_data(uart_str);
      /* print split data on the screen*/
      window1();
   }

   led_led1_disable();
}

