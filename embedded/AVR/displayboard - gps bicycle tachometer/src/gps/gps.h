/**
 * \file gps.h
 * \brief This file contains the interface of the gps module.
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

#ifndef _GPS_H_
#define _GPS_H_

/*--- Includes -------------------------------------------------------*/

#include "../tools/tools.h"

/*--- External Data --------------------------------------------------*/

extern char * rmc[14];
extern char * gga[16];
extern char * vtg[11];

extern uint8_t gps_write_rec;
extern uint8_t gps_write_init;
extern uint8_t gps_write_stop;
extern uint8_t recording;
extern uint8_t start_recording;
extern uint8_t stop_recording;

/*--- External Function Prototypes -----------------------------------*/

extern void gps_save_data_sd(char *gps_buffer);

extern void gps_init_stage1(void);
extern void gps_init_stage2(void);
extern void gps_init_mem(void);
extern void gps_split_data(char *gps_buffer);
extern void gps_split_rmc(char *gps_buffer);
extern void gps_split_gga(char *gps_buffer);
extern void gps_split_vtg(char *gps_buffer);
#endif /* #ifndef _GPS_H_ */

