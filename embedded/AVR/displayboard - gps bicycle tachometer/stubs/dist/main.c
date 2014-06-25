#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

static char time[9];
static char date[9];
static char lat[11];
static char lat_new[11];
static char lat_hist[11];
static char lon[11];
static char lon_new[11];
static char lon_hist[11];
static char tmp[10];
static char speed[6];

static char dist_buffer[20];
static char air_buffer[20];

static float distance_complete;
static float distance_air;

static char start_lat[11];
static char start_lon[11];

volatile char buff[12];
static int8_t rec_pic_toggle = 1;
static uint16_t deg_int;
static float deg_dec;


static char *create_lat(const char *buffer)
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

static char *create_lon(const char *buffer)
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

static float distance(float curr_lat, float curr_lon, float old_lat, float old_lon)
{
   float distance = (6378.388*3.14/180)*acos(sin(old_lat)*sin(curr_lat)+cos(old_lat)*cos(curr_lat)*cos(curr_lon-old_lon));

   return distance;
}

static char *create_distance_complete()
{
   float curr_lat_f, curr_lon_f, old_lat_f, old_lon_f;
   float dist;


   printf("===================\n");

   curr_lon_f = atof(create_lon(lon));
   printf("%f\n", curr_lon_f);
   curr_lat_f = atof(create_lat(lat));
   printf("%f\n", curr_lat_f);

   old_lon_f = atof(create_lon(lon_hist));
   printf("%f\n", old_lon_f);

   old_lat_f = atof(create_lat(lat_hist));
   printf("%f\n", old_lat_f);


   printf("===================\n");
   /* set new history latitude / longitude */
   strcpy(lat_hist, lat);
   strcpy(lon_hist, lon);

   dist = distance(curr_lat_f, curr_lon_f, old_lat_f, old_lon_f);

   distance_complete += dist;

   sprintf(dist_buffer,"%.2f",distance_complete);


   return dist_buffer;
}

static char *create_distance_air()
{
   float curr_lat_f, curr_lon_f, old_lat_f, old_lon_f;
   float dist = 1;

   printf("===================\n");
   curr_lat_f = atof(create_lat(lat));
   printf("%f\n", curr_lat_f);
   curr_lon_f = atof(create_lon(lon));
   printf("%f\n", curr_lon_f);

   old_lat_f = atof(create_lat(start_lat));
   printf("%f\n", old_lat_f);
   old_lon_f = atof(create_lon(start_lon));
   printf("%f\n", old_lon_f);
   printf("===================\n");


   dist = distance(curr_lat_f, curr_lon_f, old_lat_f, old_lon_f);

   sprintf(air_buffer,"%.2f",dist);

   return air_buffer;
}


int main(void)
{
   float bla;

   strcpy(start_lat, "4928.11205");
   strcpy(start_lon, "01005.08243");

   strcpy(lat_hist, start_lat);
   strcpy(lon_hist, start_lon);

   strcpy(lat, "4929.83403");
   strcpy(lon, "01103.05309");


   printf("AIR: %s\n", create_distance_air());

   printf("COMPLETE: %s\n", create_distance_complete());
   printf("AIR: %s\n", create_distance_air());

   printf("COMPLETE: %s\n", create_distance_complete());

   return 0;
}


