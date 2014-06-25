#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

char lat[12];
char lon[12];
char tmp[12];
uint16_t deg_int;
double deg_dec;


char *create_lat (char *buffer);
char *create_lon(char *buffer);

int main ()
{

char lat_ori[] = "4717.112671";
char lon_ori[] = "00833.914843";
char *lat_a;
char *lon_a;

lat_a = create_lat(lat_ori);
printf("lat: %s\n", lat_a);
//	printf("deg_int: %d\n",deg_int);
//	printf("deg_dec: %f\n",deg_dec);

lon_a = create_lon(lon_ori);
printf("lon: %s\n", lon_a);

//	printf("deg_int: %d\n",deg_int);
//	printf("deg_dec: %f\n",(double)deg_dec);
//	printf("tmp: %s\n", tmp);
return 0;
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
	for(i = 0; i < 9; i++)
      tmp[i] = buffer[i+3];
	tmp[9] = '\0';
	deg_dec = atof(tmp);

sprintf(lon,"%f",(double)(deg_int + deg_dec/60));
//sprintf(lon,"%f",(deg_dec ));
//sprintf(lon,"%f",(deg_dec ));

return lon;
}



char *create_lat (char *buffer)
{
	uint8_t i;

	deg_int = 0;
	deg_dec = 0;

        tmp[0]=buffer[0];
        tmp[1]=buffer[1];
        tmp[2]='\0';
        deg_int = atoi(tmp);
	for(i = 0; i < 8; i++)
      tmp[i] = buffer[i+2];
        tmp[8]='\0';
        deg_dec = atof(tmp);
        sprintf(lat,"%f",(double)(deg_int + deg_dec/60));

return lat;

}
