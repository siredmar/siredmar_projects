#define GPS_RMC_BUFFER_SIZE 75

/* ... */

char * rmc[14] = { NULL };
static char gps_buffer_rmc[GPS_RMC_BUFFER_SIZE] = { '0' };

/* ... */

void gps_init_mem_rmc(void)
{
   rmc[0] = &(gps_buffer_rmc[0]);   /* $GPRMC */
   rmc[1] = &(gps_buffer_rmc[7]);   /* time: hhmmss.ssss */
   rmc[2] = &(gps_buffer_rmc[18]);  /* status */
   rmc[3] = &(gps_buffer_rmc[20]);  /* latitude: ddmm.mmmm */
   /* ... */
}