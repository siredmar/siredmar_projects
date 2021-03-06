/**
 * \file tools.h
 * \brief This file provides the interface to some useful routines.
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

#ifndef _TOOLS_H_
#define _TOOLS_H_

/*--- Includes -------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*--- Macros ---------------------------------------------------------*/

#define nop()  __asm__ __volatile__ ("nop" ::)

char *strtok_r_empty( char *p_str, const char *p_delim, char **pp_save );

#endif

