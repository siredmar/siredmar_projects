/**
 * \file led.c
 * \brief This file contains all routines for using on-board LEDs.
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

#include "led.h"

/*--- External Function Definitions ----------------------------------*/

/**
 * \brief Initializing LEDs (DDR and PORT)
 */
void led_init(void)
{
    DDR_LED |= (1 << PDLED1) | (1 << PDLED2);
    PORTLED &= ~((1 << PDLED1) | (1 << PDLED2));
}

/**
 * \brief enable LED1 (GREEN)
 */
void led_led1_enable(void)
{
    PORTLED |= (1 << PDLED1);
}

/**
 * \brief disable LED1 (GREEN)
 */
void led_led1_disable(void)
{
    PORTLED &= ~(1 << PDLED1);
}

/**
 * \brief enable LED2 (RED)
 */
void led_led2_enable(void)
{
    PORTLED |= (1 << PDLED2);
}

/**
 * \brief disable LED2 (RED)
 */
void led_led2_disable(void)
{
    PORTLED &= ~(1 << PDLED2);
}

