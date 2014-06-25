/**
 * \file led.h
 * \brief This file contains the interface to the LED module.
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


#ifndef _LED_H_
#define _LED_H_

/*--- Includes -------------------------------------------------------*/

#include <avr/io.h>

/*--- Macros ---------------------------------------------------------*/

#define DDR_LED DDRD
#define PDLED1 PD4
#define PDLED2 PD5
#define PORTLED PORTD

/*--- External Function Prototypes -----------------------------------*/

/* initialize the LEDs */
extern void led_init(void);

/* enables led1 */
extern void led_led1_enable(void);

/* disables led2 */
extern void led_led1_disable(void);

/* enables led2 */
extern void led_led2_enable(void);

/* disables led2 */
extern void led_led2_disable(void);

#endif /* #ifndef _LED_H_ */

