#ifndef _GPS_H_
#define _GPS_H_

#include "tools.h"

typedef struct {
    char *time;			//rmc           
    char *date;
    char *longitude;	//rmc
    char *latitude;		//rmc
    char *longitude_we;	//rmc
    char *latitude_ns;	//rmc
    char *sat_count;		//gsv
    char *height_sea;	//gsv
    char *speed_kmh;		//vtg
    char *course;		//vtg
} GPS_DATA_TYPE;

// $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47 	//16 elements
// $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48				//10 elements
// $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A	//13 elements
/*
char *rmc[14];
char *gga[16];
char *vtg[11];
*/
char **rmc;
char **gga;
char **vtg;

//uint16_t get_rec(uint8_t no);

void gps_init_mem(void);
void gps_init_mem_rmc(void);
void gps_init_mem_vtg(void);
void gps_init_mem_gga(void);

volatile GPS_DATA_TYPE gps_data;

void gps_init(void);
void gps_split_data(char *buffer);
void gps_split_rmc(char *buffer);
void gps_split_gga(char *buffer);
void gps_split_vtg(char *buffer);
void gps_save_data(void);
#endif
