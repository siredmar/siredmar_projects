#include "std_types.h"

#include "dio/dio.h"
//#include "spi/spi.h"



int main()
{
   dio_init();
   //spi_init();


while(1)
{

   dio_writeChannel(BLACK_LED   , STD_HIGH);
   dio_writeChannel(CYAN_LED    , STD_LOW);
   dio_writeChannel(MAGENTA_LED , STD_HIGH);
   dio_writeChannel(YELLOW_LED  , STD_LOW);
   dio_writeChannel(WORKING_LED , STD_HIGH);
   dio_writeChannel(FINISHED_LED, STD_LOW);

	_delay_ms(100);
   dio_writeChannel(BLACK_LED   , STD_LOW);
   dio_writeChannel(CYAN_LED    , STD_HIGH);
   dio_writeChannel(MAGENTA_LED , STD_LOW);
   dio_writeChannel(YELLOW_LED  , STD_HIGH);
   dio_writeChannel(WORKING_LED , STD_LOW);
   dio_writeChannel(FINISHED_LED, STD_HIGH);
   _delay_ms(400);

}

return 0;
}
