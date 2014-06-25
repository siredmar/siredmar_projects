#include "std_types.h"

#include "dio/dio.h"
#include "uart/uart.h"
#include "tft/tft.h"
#include "spi/spi.h"



#define FCPU 20000000
#define BAUD 9600  //Baudrate
#define MYUBRR FCPU/16/BAUD-1  //Werte für UBRR Register

int main()
{
//   uint16 counter = 0x1000;
	static uint8 counter_ui8 = 0;

   USART_Init(MYUBRR);
   dio_init();
   spi_init();

   //tft_init(&tft_initialConfigTft_s);

   //tft_clearScreen(0xFFFF);

while(1)
{
	counter_ui8++;
	_delay_ms(1000);
	spi_sendData(counter_ui8, DIO_CHANNEL_PB0, SPI_CS_ACTIVE_LOW);

	//dio_writeChannel(DIO_CHANNEL_PB7, DIO_HIGH);
	//_delay_ms(1000);
	//dio_writeChannel(DIO_CHANNEL_PB7, DIO_LOW);
//	counter = counter + 0x5000;
//	tft_clearScreen(counter);
//	tft_drawRectangle(150, 150, 200, 200, 0xAAAA);
//
//	tft_drawPixel(50,150,0x0000);
//
//	tft_drawPixel(50,160,0xFFFF);

}

return 0;
}
