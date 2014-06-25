#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#define PI 3.14159265

char lat[10];
char lon[11];
char tmp[9];
uint16_t deg_int;
double deg_dec;


char *create_lat(char *buffer)
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
    sprintf(lat, "%f", (double) (deg_int + deg_dec / 60));

    return lat;

}

char *create_lon(char *buffer)
{
    deg_int = 0;
    deg_dec = 0;
    uint8_t i;

    tmp[0] = buffer[0];
    tmp[1] = buffer[1];
    tmp[2] = buffer[2];
    tmp[3] = '\0';
    deg_int = atoi(tmp);
    for (i = 0; i < 9; i++)
        tmp[i] = buffer[i + 3];
    tmp[9] = '\0';
    deg_dec = atof(tmp);

    sprintf(lon, "%f", (double) (deg_int + deg_dec / 60));

    return lon;
}


float distance( float lat1, float lon1, float lat2, float lon2){
float f_dist;
//f_dist = 6378.388 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1));
f_dist = (6378.388*PI/180) * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1));

//f_dist =   acos(((sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon2-lon1))));
//f_dist *= 6378.137;
//printf("%f\n", lat1-lat2);
//printf("%f\n", lon1-lon2);

//f_dist = sqrt((lat1-lat2)*(lat1-lat2) + (lon1-lon2)*(lon1-lon2));

return f_dist;
}

int main(){
float f_dist;
float lat1;
float lon1;
float lat2;
float lon2;
lat2 = atof(create_lat("4927.95387"));
lon2 = atof(create_lon("01104.59936"));
lat1 = atof(create_lat("4928.30654"));
lon1 = atof(create_lon("01104.97525"));

/*lat2 = atof("4946.04470");
lon2 = atof("01120.74355");
lat1 = atof("4927.91714");
lon1 = atof("01104.72827");
*/
printf("%f, %f\n%f, %f\n", lat1, lon1, lat2, lon2);
//f_dist = distance(49.1234,11.056543,49.2345,11.056543);
//f_dist = distance(create_lat("4927.15410"),create_lon("01105.83103"),create_lat("4927.16295"),create_lon( "01105.82321"));
f_dist = distance(lat1,lon1, lat2, lon2);
printf("distance: %f\n", f_dist);

return 0;
}


