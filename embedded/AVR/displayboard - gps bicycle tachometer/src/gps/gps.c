/**
 * \file gps.c
 * \brief This file contains the implementation of the gps module.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/eeprom.h>

#include "../display/display.h"
#include "gps.h"
#include "../uart/uart.h"
#include "../tools/tools.h"
#include "../led/led.h"
#include "../touch/touch.h"
#include "../display/images.h"
#include "../fat16/fat16.h"
#include "../sdc/sdc.h"
#include "../windows/windows.h"

/*--- Macros ---------------------------------------------------------*/

#define GPS_BUFFER_SIZE 25      /**< buffer size for reading GPS receiver settings from EEPROM */
#define GPS_RMC_BUFFER_SIZE 75  /**< buffer size for GPS RMC data sets */
#define GPS_VTG_BUFFER_SIZE 44  /**< buffer size for GPS VTG data sets */
#define GPS_GGA_BUFFER_SIZE 90  /**< buffer size for GPS GGA data sets */

/*--- Internal Data --------------------------------------------------*/

/** The byte code for setting the baudrate of the GPS receiver */
static char EEMEM baud [] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,
                             0xD0,0x08,0x00,0x00,0x00,0x4B,0x00,0x00,0x03,0x00,
                             0x02,0x00,0x00,0x00,0x00,0x00,0x43,0x31};

static char EEMEM vtg_on[] = {"$PUBX,40,VTG,0,1,0,0*5F\r\n"};    /**< turn on VTG */
static char EEMEM rmc_on[] = {"$PUBX,40,RMC,0,1,0,0*46\r\n"};    /**< turn on RMC */
static char EEMEM gga_on[] = {"$PUBX,40,GGA,0,1,0,0*5B\r\n"};    /**< turn on GGA */
static char EEMEM gsa_off[] = {"$PUBX,40,GSA,0,0,0,0*4E\r\n"};   /**< turn off GSA */
static char EEMEM grs_off[] = {"$PUBX,40,GRS,0,0,0,0*5D\r\n"};   /**< turn off GRS */
static char EEMEM gsv_off[] = {"$PUBX,40,GSV,0,0,0,0*59\r\n"};   /**< turn off GSV */
static char EEMEM zda_off[] = {"$PUBX,40,ZDA,0,0,0,0*44\r\n"};   /**< turn off ZDA */
static char EEMEM gst_off[] = {"$PUBX,40,GST,0,0,0,0*5B\r\n"};   /**< turn off GST */
static char EEMEM gll_off[] = {"$PUBX,40,GLL,0,0,0,0*5C\r\n"};   /**< turn off GLL */

/** buffer for storing an entire RMC data set */
static char gps_buffer_rmc[GPS_RMC_BUFFER_SIZE] = { '0' };

/** buffer for storing an entire VTG data set */
static char gps_buffer_vtg[GPS_VTG_BUFFER_SIZE] = { '0' };

/** buffer for storing an entire GGA data set */
static char gps_buffer_gga[GPS_GGA_BUFFER_SIZE] = { '0' };

/*--- External Data --------------------------------------------------*/

char * rmc[14] = { NULL }; /**< pointer array providing access to RMC data */
char * gga[16] = { NULL }; /**< pointer array providing access to GGA data */
char * vtg[11] = { NULL }; /**< pointer array providing access to VTG data */

File *myfile;
char filename[11];
volatile char buff[12];


volatile uint8_t touchcnt = 0;

/** Status variable, indicating whether the system currently recording */
uint8_t recording = 0;

/** Status variable, indicating whether the recording has been started */
uint8_t start_recording = 0;

/** Status variable, indicating whether the recording has been stopped */
uint8_t stop_recording = 0;

/** Status variable, indicating whether the SD card has been initialized */
uint8_t sd_init = 0;

static void gps_init_mem_rmc(void);
static void gps_init_mem_vtg(void);
static void gps_init_mem_gga(void);


/*--- External Function Definitions ----------------------------------*/

/**
 * \brief Create a file name (based on a time stamp)
 *
 * \param gps_buffer pointer to a time stamp, represented in char
 *                   (should be data pointed to by rmc[1])
 * \return A string (including '\0') consisting of the current time stamp
 *         and the file ending '.nma'
 */
static char *create_filename(char *gps_buffer)
{
    filename[0] = gps_buffer[0];
    filename[1] = gps_buffer[1];
    filename[2] = gps_buffer[2];
    filename[3] = gps_buffer[3];
    filename[4] = gps_buffer[4];
    filename[5] = gps_buffer[5];
    filename[6] = '.';
    filename[7] = 'n';
    filename[8] = 'm';
    filename[9] = 'a';
    filename[10] = '\0';
    return filename;
}

/**
 * \brief Store a received data set to a provided SD card.
 *
 * \param gps_buffer the buffer containing GPS data (RMC, GGA and VTG data sets)
 */
void gps_save_data_sd(char *gps_buffer)
{
   if (touch_read(NULL, NULL) == valid) {
      touchcnt++;
      /* Pressed 3 cycles AND minimum of 3 Sattelites are in sight AND sd is detected and not locked */
      sd_check_detected();
      sd_check_writeable();
      if ( ((touchcnt > 2) && (atoi(gga[7]) >= 3) && sd_detected && sd_writeable) || (recording && touchcnt > 2)) {    //Press 3 cycles, TODO: #define TOUCHCNT 3
         touchcnt = 0;

         if (recording == 0) {
            start_recording = 1;    //if button pressed and not recording -> start recording
            recording = 0;
            stop_recording = 0;
         }
         if (recording == 1) {
            recording = 0;  //if button pressed and already recording -> stop recording
            stop_recording = 1;
            start_recording = 0;
         }
      }
   } else {
      touchcnt = 0;

      if (recording == 1) {
         recording = 1;
         start_recording = 0;
         stop_recording = 0;
      }
      if (recording == 0) {
         recording = 0;
         start_recording = 0;
         stop_recording = 0;
      }
   }

   if (start_recording == 1) {
      led_led2_enable();
      display_bmp_flash(10, 10, record_init);
      display_send_frame();

      if(InitFat16()){
         sprintf(buff, "%s", rmc[9]);
         mkdir_(buff);
         chdir_(buff);
         myfile = fopen_(create_filename(rmc[1]), 'a');
      }
      stop_recording = 0;
      //start_recording = 0;
      recording = 1;
   }
   if (recording == 1) {
      led_led2_enable();
      fputs_(myfile, gps_buffer);
   }
    if (stop_recording == 1) {
      led_led2_disable();
      //fclose_(myfile);      //Creates funny errors! DO NOT USE fclose()!!!!!
      fflush_(myfile);      //instead of fclose() use fflush() and FreeFilePointer()!!!!
      FreeFilePointer(myfile);   ///DO NOT CHANGE! (It's Magic!)
      recording = 0;
      start_recording = 0;
      stop_recording = 0;
   }
}

/**
 * \brief Sets the baudrate of the GPS receiver to 19200.
 */
void gps_init_stage1(void)
{
   char buffer_baud[28];
   led_led2_enable();
   uart_puts("$PUBX,41,0,3,3,9600,0*15\r\n");
   uart_puts("$PUBX,41,1,3,3,9600,0*14\r\n");
   uart_puts("$PUBX,41,2,3,3,9600,0*17\r\n");

   led_led2_disable();
   led_led2_enable();
   eeprom_read_block ((void *)&buffer_baud, (const void *)&baud,28);
   uart_puts(buffer_baud);
   led_led2_disable();
   _delay_ms(10);
}

/**
 * \brief Disables not needed GPS data sets.
 */
void gps_init_stage2(void)
{
   char gps_buffer[GPS_BUFFER_SIZE];
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&vtg_on,GPS_BUFFER_SIZE);
   display_bmp_flash(0,0,logo);
   display_send_frame();
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&rmc_on,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&gga_on,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&gsa_off,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&grs_off,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&gsv_off,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&zda_off,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&gst_off,GPS_BUFFER_SIZE);
   uart_puts(gps_buffer);
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   eeprom_read_block ((void *)&gps_buffer, (const void *)&gll_off,25);
   uart_puts(gps_buffer);
   led_led2_disable();
   led_led2_enable();
   led_led2_disable();
   _delay_ms(10);
   led_led2_enable();
   led_led2_disable();
   free(gps_buffer);
}

/**
 * \brief Split the received GPS data to its components.
 *
 * This function is called to split the received RMC, GGA and VTG data to
 * its single components, like date, time, speed, longitude, ..., etc.
 * Furthermore these components are stored in the respective data buffer
 * for additional processing.
 *
 * \param gps_buffer the received GPS data
 */
void gps_split_data( char *gps_buffer )
{
   char *ptr;
   char *save;

   save = strtok_r_empty(gps_buffer, "$",&ptr);

   while (save) {
      if (save[2] == 'R' && save[3] == 'M' && save[4] == 'C') {
         gps_split_rmc(save);
      }
      else if (save[2] == 'G' && save[3] == 'G' && save[4] == 'A') {
         gps_split_gga(save);
      }
      else if (save[2] == 'V' && save[3] == 'T' && save[4] == 'G') {
         gps_split_vtg(save);
      }
      save = strtok_r_empty(NULL, "$",&ptr);
   }
}

/**
 * \brief Initializes the internal data buffers for RMC, GGA and VTG data.
 *
 *
 */
void gps_init_mem(void)
{
   gps_init_mem_rmc();
   gps_init_mem_vtg();
   gps_init_mem_gga();
}

/**
 * \brief Initialization of the RMC data buffer
 *
 * further information see link below page 43
 * http://www.sander-electronic.de/datasheet/GPS/NL550_551/NL_u-blox5_Referenzmanual_06102008_571.pdf
 */
static void gps_init_mem_rmc(void)
{
   rmc[0] = &(gps_buffer_rmc[0]);   /* $GPRMC */
   rmc[1] = &(gps_buffer_rmc[7]);   /* time: hhmmss.ssss */
   rmc[2] = &(gps_buffer_rmc[18]);  /* status */
   rmc[3] = &(gps_buffer_rmc[20]);  /* latitude: ddmm.mmmm */
   rmc[4] = &(gps_buffer_rmc[30]);  /* nord, south */
   rmc[5] = &(gps_buffer_rmc[32]);  /* longitude: dddmm.mmmm */
   rmc[6] = &(gps_buffer_rmc[43]);  /* east, west */
   rmc[7] = &(gps_buffer_rmc[45]);  /* velocity knots */
   rmc[8] = &(gps_buffer_rmc[52]);  /* course */
   rmc[9] = &(gps_buffer_rmc[58]);  /* date: ddmmyy */
   rmc[10] = &(gps_buffer_rmc[65]); /* magnetic variation value */
   rmc[11] = &(gps_buffer_rmc[66]); /* magnetic variation e/w indicator */
   rmc[12] = &(gps_buffer_rmc[68]); /* mode indicator */
   rmc[13] = &(gps_buffer_rmc[70]); /* checksum */
}

/**
 * \brief Initialization of the VTG data buffer
 */
static void gps_init_mem_vtg(void)
{
   vtg[0] = &(gps_buffer_vtg[0]);   /* $GPVTG */
   vtg[1] = &(gps_buffer_vtg[7]);   /* course true */
   vtg[2] = &(gps_buffer_vtg[14]);  /* fixed field: true */
   vtg[3] = &(gps_buffer_vtg[16]);  /* course magnetic */
   vtg[4] = &(gps_buffer_vtg[17]);  /* fixed field: magnetic */
   vtg[5] = &(gps_buffer_vtg[19]);  /* speed over ground */
   vtg[6] = &(gps_buffer_vtg[26]);  /* fixed field: knots */
   vtg[7] = &(gps_buffer_vtg[28]);  /* speed over ground kmh */
   vtg[8] = &(gps_buffer_vtg[35]);  /* fixed field: kilometers per hour */
   vtg[9] = &(gps_buffer_vtg[37]);  /* mode indicator */
   vtg[10] = &(gps_buffer_vtg[39]); /* checksum */
}

/**
 * \brief Initialization of the GGA data buffer
 */
static void gps_init_mem_gga(void)
{
   gga[0] = &(gps_buffer_gga[0]);   /* $GPGGA */
   gga[1] = &(gps_buffer_gga[7]);   /* time: hhmmss.sss */
   gga[2] = &(gps_buffer_gga[18]);  /* latitude: ddmm.mmmm */
   gga[3] = &(gps_buffer_gga[28]);  /* N,S */
   gga[4] = &(gps_buffer_gga[30]);  /* longitude: dddmm.mmmm */
   gga[5] = &(gps_buffer_gga[41]);  /* E,W */
   gga[6] = &(gps_buffer_gga[43]);  /* position fix status indicator */
   gga[7] = &(gps_buffer_gga[45]);  /* satellites used */
   gga[8] = &(gps_buffer_gga[48]);  /* HDOP */
   gga[9] = &(gps_buffer_gga[52]);  /* msl altitude */
   gga[10] = &(gps_buffer_gga[58]); /* fixed field: unit meters */
   gga[11] = &(gps_buffer_gga[60]); /* geoid separation */
   gga[12] = &(gps_buffer_gga[66]); /* fixed field: unit meters */
   gga[13] = &(gps_buffer_gga[73]); /* diffage */
   gga[14] = &(gps_buffer_gga[79]); /* diffsation */
   gga[15] = &(gps_buffer_gga[85]); /* checksum */
}

/**
 * \brief Splits up a RMC GPS data set into its components
 *
 * \param gps_buffer buffer containing the entire GPS data set
 */
void gps_split_rmc(char *gps_buffer)
{
   uint8_t i = 0;
   char *ptr;
   char *rmc_token;
   rmc_token = strtok_r_empty(gps_buffer, ",*",&ptr);
   strcpy(rmc[i], rmc_token);
   while (rmc_token) {
      strcpy(rmc[i++], rmc_token);
      rmc_token = strtok_r_empty(NULL, ",*",&ptr);
   }
}

/**
 * \brief Splits up a GGA GPS data set into its components
 *
 * \param gps_buffer buffer containing the entire GPS data set
 */
void gps_split_gga(char *gps_buffer)
{
   char *ptr;
   uint8_t i = 0;
   char *gga_token;
   gga_token = strtok_r_empty(gps_buffer, ",*",&ptr);
   strcpy(gga[i], gga_token);
   while (gga_token) {
      strcpy(gga[i++], gga_token);
      gga_token = strtok_r_empty(NULL, ",*",&ptr);
   }
}

/**
 * \brief Splits up a VTG GPS data set into its components
 *
 * \param gps_buffer buffer containing the entire GPS data set
 */
void gps_split_vtg(char *gps_buffer)
{
   char *ptr;
   uint8_t i = 0;
   char *vtg_token;
   vtg_token = strtok_r_empty(gps_buffer, ",*",&ptr);
   strcpy(vtg[i], vtg_token);
   while (vtg_token) {
      strcpy(vtg[i++], vtg_token);
      vtg_token = strtok_r_empty(NULL, ",*",&ptr);
   }
}


