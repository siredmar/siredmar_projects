/**
 * \file windows.c
 * \brief Within this file all functions are defined that manipulate the display screen.
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

#include <avr/interrupt.h>
#include "windows.h"
#include "../gps/gps.h"
#include "../display/images.h"
#include "../display/display.h"
#include "../touch/touch.h"
#include "../sdc/sdc.h"
#include <math.h>

/*--- Internal Data --------------------------------------------------*/

/** internal buffer used for storing the current time */
static char time[9];

/** internal buffer used for storing the current date */
static char date[9];

/** internal buffer used for interchange of the new latitude */
static char lat_new[14];

/** internal buffer used for storing the previous received latitude */
static char lat_hist[14];

/** internal buffer used for interchange of the new longitude */
static char lon_new[14];

/** internal buffer used for storing the previous received longitude */
static char lon_hist[14];

/** internal helper buffer */
static char tmp[10];

/** internal buffer containing the current speed */
static char speed[6];

/** internal buffer containing the complete distance */
static char dist_buffer[20] = {'\0'};

/** internal buffer containing the air distance*/
static char air_buffer[20] = {'\0'};

/** the accumulated complete distance from start- to ending-point */
static float distance_complete = 0;

/** the air distance from start- to ending-point*/
static float distance_air = 0;

/** internal buffer containing the latitude of the starting point */
static char start_lat[14];

/** internal buffer containing the longitude of the ending point */
static char start_lon[14];

/** status variable, indicating whether the recording-picture shall be shown (1) or not (-1) */
static int8_t rec_pic_toggle = 1;

/** degree values for calcluating the latitude/longitude */
static float deg_int;
static float deg_dec;

/*--- Internal Function Prototypes -----------------------------------*/

static char *create_time(char *buffer);
static char *create_date(char *buffer);
static char *create_lat(char *buffer);
static char *create_lon(char *buffer);
static char *create_speed(char *buffer);
static float distance(float curr_lat, float curr_lon, float old_lat, float old_lon);
static char *create_distance_complete(void);
static char *create_distance_air(void);
static float create_distance_air_f(void);

/*--- External Function Definitions ----------------------------------*/

/**
 * \brief The actual application
 *
 * This function handles the display presentation, including general layout,
 * provided GPS data and static information.
 */
void window1()
{
   char buff[14];

   display_clear_ram();
   display_bmp_flash(0, 1, satellit);

   sd_init_status();
   sd_check_detected();
   sd_check_writeable();

   if(sd_detected == 1){
      display_bmp_flash(22, 0, sd_card);
      display_bmp_flash(12,0,no_lock);

      if(!sd_writeable)
         display_bmp_flash(12,0,sd_locked);
      else
         display_bmp_flash(12,0, sd_unlocked);
      }

      if(sd_detected == 0){
         sd_writeable = 0;
         display_bmp_flash(22,0,no_sd_card);
         display_bmp_flash(12,0,no_lock);
      }

      display_string(0, 11, gga[7]);
      display_string(76, 56, create_time(rmc[1]));
      display_string(5, 56, create_date(rmc[9]));
      display_string(39, 1, "La:");
      display_string(39, 9, "Lo:");
      display_string(58, 1, create_lat(rmc[3]));
      display_string(58, 9, create_lon(rmc[5]));
      display_string(115, 1, rmc[4]);
      display_string(115, 9, rmc[6]);

      display_bmp_flash(5,20,tacho);
      if(atof(vtg[7]) >= 1)
          sprintf(buff,"%skm/h", create_speed(vtg[7]));
      else
          strcpy(buff, "0.0km/h");

      display_string(18,22,buff);
      display_bmp_flash(5,32,height);
      sprintf(buff,"%sm", create_speed(gga[9]));
      display_string(18, 34, buff);
      display_bmp_flash(7,44,compass);
      sprintf(buff,"%s", create_speed(vtg[1]));
      display_string(18, 46, buff);

   if(start_recording) {
      distance_complete = 0;
      distance_air = 0;
      display_bmp_flash(10,10,record_init);
      strcpy(lat_hist, create_lat(rmc[3]));
      strcpy(lon_hist, create_lon(rmc[5]));
      strcpy(start_lat, create_lat(rmc[3]));
      strcpy(start_lon, create_lon(rmc[5]));
      start_recording=0;
   }

   if(recording) {
      if(rec_pic_toggle == 1)
         display_bmp_flash(12,10,sd_rec_on);

      //if min. 3 satellites in view AND speed is >= 2 km/h
      if(atoi(gga[7]) >= 3 && atof(vtg[7]) >= 1.4){
         create_distance_complete();
         create_distance_air();
      }

      display_bmp_flash(77,19,pole);
      display_string(88, 22, dist_buffer);
      display_bmp_flash(75,32,cloud);
      display_string(88, 34, air_buffer);
   }

   if(rec_pic_toggle == -1)
      display_bmp_flash(12,10,sd_rec_stop);
   if(!recording)
      display_bmp_flash(12,10,sd_rec_pause);

   rec_pic_toggle = rec_pic_toggle * -1;

   display_send_frame();
}

/*--- Internal Function Definitions ----------------------------------*/

/**
 * \brief Determines the date from the provided GPS data
 *
 * \param buffer the buffer containing the date in NMEA format
 * \returns the date in general string format ( DD.MM.YY, terminated by '\0')
 */
static char *create_date(char *buffer)
{
   date[0] = buffer[0];
   date[1] = buffer[1];
   date[2] = '.';
   date[3] = buffer[2];
   date[4] = buffer[3];
   date[5] = '.';
   date[6] = buffer[4];
   date[7] = buffer[5];
   date[8] = '\0';
   return date;
}

/**
 * \brief Determines the time from the provided GPS data
 *
 * \param buffer the buffer containing the time in NMEA format
 * \returns the time in general string format ( HH:MM:SS, terminated by '\0')
 */
static char *create_time(char *buffer)
{
   time[0] = buffer[0];
   time[1] = buffer[1];
   time[2] = ':';
   time[3] = buffer[2];
   time[4] = buffer[3];
   time[5] = ':';
   time[6] = buffer[4];
   time[7] = buffer[5];
   time[8] = '\0';
   return time;
}

/**
 * \brief Determines the speed from the provided GPS data
 *
 * \param buffer the buffer containing the speed in NMEA format
 * \returns the speed in general string format (one decimal place, terminated by '\0')
 */
static char *create_speed(char *buffer)
{
   float speed_f;
   speed_f = atof(buffer);
   sprintf(speed, "%.1f", speed_f);
   return speed;
}


/**
 * \brief Determines the latitude from the provided GPS data
 *
 * \param buffer the buffer containing the latitude in NMEA format
 * \returns the latitude in general string format (terminated by '\0')
 */
static char *create_lat(char *buffer)
{
   uint8_t i;

   deg_int = 0;
   deg_dec = 0;

   tmp[0] = buffer[0];
   tmp[1] = buffer[1];
   tmp[2] = '\0';
   deg_int = atoi(tmp);
   for (i = 0; i < 8; i++)
   tmp[i] = buffer[i + 2];
   tmp[8] = '\0';
   deg_dec = atof(tmp);
   sprintf(lat_new, "%f", (float) (deg_int + deg_dec / 60));

   return lat_new;
}

/**
 * \brief Determines the longitude from the provided GPS data
 *
 * \param buffer the buffer containing the longitude in NMEA format
 * \returns the longitude in general string format (terminated by '\0')
 */
static char *create_lon(char *buffer)
{
   uint8_t i;

   deg_int = 0;
   deg_dec = 0;

   tmp[0] = buffer[0];
   tmp[1] = buffer[1];
   tmp[2] = buffer[2];
   tmp[3] = '\0';
   deg_int = atoi(tmp);
   for (i = 0; i < 9; i++)
      tmp[i] = buffer[i + 3];
   tmp[9] = '\0';
   deg_dec = atof(tmp);

   sprintf(lon_new, "%f", (float) (deg_int + deg_dec / 60));

   return lon_new;
}

/**
 * \brief Calculates distance between two coordination points
 *
 * \param curr_lat the current latitude
 * \param curr_lon the current longitude
 * \param old_lat the latitude of the starting point the distance shall be calculated for
 * \param old_lon the longitutde of the starting point the distance shall be calculated for
 * \returns the calculated distance between the provided coordinates
 */
static float distance(float curr_lat, float curr_lon, float old_lat, float old_lon)
{
   float dist = acos(sin(curr_lat/180*3.14)*sin(old_lat/180*3.14)+cos(curr_lat/180*3.14)*cos(old_lat/180*3.14)*cos(curr_lon/180*3.14 - old_lon/180*3.14))*6.378137;

   return dist;
}

/**
 * \brief Calculates the complete distance since the start of recording
 *
 * \returns the created string, containing the complete distance to the starting point
 *          (terminated by '\0')
 */
static char *create_distance_complete(void)
{
   float curr_lat_f, curr_lon_f, old_lat_f, old_lon_f;
   float dist = 0.0;

   curr_lat_f = atof(create_lat(rmc[3]));
   curr_lon_f = atof(create_lon(rmc[5]));

   old_lat_f = atof(lat_hist);
   old_lon_f = atof(lon_hist);

   dist = distance(curr_lat_f, curr_lon_f, old_lat_f, old_lon_f);

   distance_complete += dist;

   sprintf(dist_buffer,"%.2f",distance_complete);
   strcpy(lat_hist, create_lat(rmc[3]));
   strcpy(lon_hist, create_lon(rmc[5]));

   return dist_buffer;
}

/**
 * \brief Calculate air distance between the record starting point and the current position
 *
 * \returns the created string, containing the total air distance to the starting point
 *          (terminated by '\0')
 */
static char *create_distance_air(void)
{
   float curr_lat_f, curr_lon_f, old_lat_f, old_lon_f;
   float dist = 0.0;

   curr_lat_f = atof(create_lat(rmc[3]));
   curr_lon_f = atof(create_lon(rmc[5]));
   old_lat_f = atof(start_lat);
   old_lon_f = atof(start_lon);

   dist = distance(curr_lat_f, curr_lon_f, old_lat_f, old_lon_f);

   sprintf(air_buffer,"%.2f",dist);

   return air_buffer;
}

