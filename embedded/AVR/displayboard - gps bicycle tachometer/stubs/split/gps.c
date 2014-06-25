#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gps.h"
#include "tools.h"
#include <inttypes.h>

void gps_split_data( char *buffer )
{
char *ptr;
char *save;
save = strtok_r(buffer, "$",&ptr);
while (save) {
   if (save[2] == 'R' && save[3] == 'M' && save[4] == 'C') {
	gps_split_rmc(save);
    }
   else if (save[2] == 'G' && save[3] == 'G' && save[4] == 'A') {
	gps_split_gga(save);
    }

   else if (save[2] == 'V' && save[3] == 'T' && save[4] == 'G') {
	gps_split_vtg(save);
    }/*else {
        }
    	*/
      save = strtok_r(NULL, "$",&ptr);
  }
}

void gps_init_mem(void)
{
	rmc = malloc(14 * sizeof(char *));
	gga = malloc(16 * sizeof(char *));
	vtg = malloc(11 * sizeof(char *));
	//RESERES 180 Bytes for temporary rmc, vtg and gga tokens
	gps_init_mem_rmc();
	gps_init_mem_vtg();
	gps_init_mem_gga();
}

//further information see link below page 43
//http://www.sander-electronic.de/datasheet/GPS/NL550_551/NL_u-blox5_Referenzmanual_06102008_571.pdf
void gps_init_mem_rmc(void)
{
	//RESERVES 69 bytes
	rmc[0] = (char*) malloc(sizeof(char) * 7);	//$GPRMC
	rmc[1] = (char*) malloc(sizeof(char) * 11);	//time: hhmmss
	rmc[2] = (char*) malloc(sizeof(char) * 2);	//status
	rmc[3] = (char*) malloc(sizeof(char) * 10);	//latitude: ddmm.mmmm
	rmc[4] = (char*) malloc(sizeof(char) * 2);	//nord, south
	rmc[5] = (char*) malloc(sizeof(char) * 11);	//latitude: dddmm.mmmm
	rmc[6] = (char*) malloc(sizeof(char) * 2);	//east, west
	rmc[7] = (char*) malloc(sizeof(char) * 7);	//velocity knots
	rmc[8] = (char*) malloc(sizeof(char) * 6);	//course
	rmc[9] = (char*) malloc(sizeof(char) * 7);	//date: ddmmyy
	rmc[10] =(char*) malloc(sizeof(char) * 1);	//magnetic variation value
	rmc[11] =(char*) malloc(sizeof(char) * 2);	//magnetic variation e/w indicator
	rmc[12] =(char*) malloc(sizeof(char) * 2);	//mode indicator
	rmc[13] =(char*) malloc(sizeof(char) * 5);	//checksum
}
void gps_init_mem_vtg(void)
{
	//RESERVRES 42 bytes
	vtg[0] = (char*) malloc(sizeof(char) * 7);	//$GPVTG
	vtg[1] = (char*) malloc(sizeof(char) * 7);	//course true
	vtg[2] = (char*) malloc(sizeof(char) * 2);	//fixed field: true
	vtg[3] = (char*) malloc(sizeof(char) * 1);	//course magnetic
	vtg[4] = (char*) malloc(sizeof(char) * 2);	//fixed field: magnetic
	vtg[5] = (char*) malloc(sizeof(char) * 7);	//speed over ground
	vtg[6] = (char*) malloc(sizeof(char) * 2);	//fixed field: knots
	vtg[7] = (char*) malloc(sizeof(char) * 7);	//speed over ground kmh
	vtg[8] = (char*) malloc(sizeof(char) * 2);	//fixed field: kilometers per hour
	vtg[9] = (char*) malloc(sizeof(char) * 2);	//mode indicator
	vtg[10] =(char*) malloc(sizeof(char) * 5);	//checksum
}
void gps_init_mem_gga(void)
{
	//RESERVES 88 bytes
	gga[0] = (char*) malloc(sizeof(char) * 7);	//$GPGGA
	gga[1] = (char*) malloc(sizeof(char) * 11);	//time: hhmmss.sss
	gga[2] = (char*) malloc(sizeof(char) * 10);	//latitude: ddmm.mmmm
	gga[3] = (char*) malloc(sizeof(char) * 2);	//N,S
	gga[4] = (char*) malloc(sizeof(char) * 11);	//longitude: dddmm.mmmm
	gga[5] = (char*)malloc(sizeof(char) * 2);	//E,W
	gga[6] = (char*) malloc(sizeof(char) * 2);	//position fix status indicator
	gga[7] = (char*) malloc(sizeof(char) * 3);	//satellites used
	gga[8] = (char*) malloc(sizeof(char) * 4);	//HDOP
	gga[9] = (char*) malloc(sizeof(char) * 6);	//msl altitude
	gga[10] =(char*) malloc(sizeof(char) * 2);	//fixed field: unit meters
	gga[11] =(char*) malloc(sizeof(char) * 6);	//geoid separation
	gga[12] =(char*) malloc(sizeof(char) * 7);	//fixed field: unit meters
	gga[13] =(char*) malloc(sizeof(char) * 6);	//diffage
	gga[14] =(char*) malloc(sizeof(char) * 6);	//diffsation
	gga[15] =(char*) malloc(sizeof(char) * 5);	//checksum
}

void gps_split_rmc(char *buffer)
{
    uint8_t i = 0;
    char *ptr;
    char *rmc_token;
    rmc_token = strtok_r_empty(buffer, ",*",&ptr);
    strcpy(rmc[i], rmc_token);
    while (rmc_token) {
	strcpy(rmc[i++], rmc_token);
	rmc_token = strtok_r_empty(NULL, ",*",&ptr);
    }
}

void gps_split_gga(char *buffer)
{

    char *ptr;
    uint8_t i = 0;
    char *gga_token;
    gga_token = strtok_r_empty(buffer, ",*",&ptr);
    strcpy(gga[i], gga_token);
    while (gga_token) {
	strcpy(gga[i++], gga_token);
	gga_token = strtok_r_empty(NULL, ",*",&ptr);
    }

}

void gps_split_vtg(char *buffer)
{
    char *ptr;
    uint8_t i = 0;
    char *vtg_token;
    vtg_token = strtok_r_empty(buffer, ",*",&ptr);
    strcpy(gga[i], vtg_token);
    while (vtg_token) {
	strcpy(vtg[i++], vtg_token);
	vtg_token = strtok_r_empty(NULL, ",*",&ptr);
   }
}

void gps_save_data(void)
{
    gps_data.date = (char *) malloc(sizeof(char) * 7);
    strcpy(gps_data.date, rmc[9]);

    gps_data.time = (char *) malloc(sizeof(char) * 7);
    strcpy(gps_data.time, rmc[1]);

    gps_data.longitude = (char *) malloc(sizeof(char) * 10);
    strcpy(gps_data.longitude, rmc[5]);

    gps_data.latitude = (char *) malloc(sizeof(char) * 10);
    strcpy(gps_data.latitude, rmc[3]);

    gps_data.longitude_we = (char *) malloc(sizeof(char) * 3);
    strcpy(gps_data.longitude_we, rmc[6]);

    gps_data.latitude_ns = (char *) malloc(sizeof(char) * 3);
    strcpy(gps_data.latitude_ns, rmc[4]);

    gps_data.sat_count = (char *) malloc(sizeof(char) * 4);
    strcpy(gps_data.sat_count, gga[7]);

    gps_data.height_sea = (char *) malloc(sizeof(char) * 6);
    strcpy(gps_data.height_sea, gga[9]);

    gps_data.speed_kmh = (char *) malloc(sizeof(char) * 6);
    strcpy(gps_data.speed_kmh, vtg[7]);

    gps_data.course = (char *) malloc(sizeof(char) * 5);
    strcpy(gps_data.course, vtg[1]);

//    strcpy(gps_data.date,             "test");

}



