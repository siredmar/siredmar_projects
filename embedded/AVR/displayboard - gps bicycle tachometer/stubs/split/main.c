#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "gps.h"

uint8_t uart_str_cnt = 0;
uint8_t uart_str_ready = 0;
uint8_t new_data = 0;
uint8_t cr_nl_det = 0;
char uart_str[190 + 1] = "";

uint8_t rmc_found = 0;
uint8_t vtg_found = 0;
uint8_t gga_found = 0;
uint8_t block_finished = 0;
uint8_t new_data_index = 0;


void func(char next_char)
{

	if(next_char == '$'){
		new_data = 1;
		new_data_index = uart_str_cnt;
		printf("new_data = 1\n");
		block_finished = 0;
	}
	if(block_finished == 0){
	uart_str[uart_str_cnt] = next_char;
		if(uart_str_cnt > 2){
			if(uart_str_cnt - new_data_index == 5){		//Absolute Position (cnt) - aktueller Datenindex (index) = 5 (z.b. $GPRMC um das erkannte C, M und R zu verarbeiten)
				if(uart_str[uart_str_cnt - 2] == 'R' && uart_str[uart_str_cnt - 1] == 'M' && uart_str[uart_str_cnt] == 'C'){
					rmc_found = 1;
					printf("rmc_found: %d\t ", rmc_found);
				}
				if(uart_str[uart_str_cnt - 2] == 'G' && uart_str[uart_str_cnt - 1] == 'G' && uart_str[uart_str_cnt] == 'A'){
					gga_found = 1;
					printf("gga_found: %d\t ", gga_found);
				}
				if(uart_str[uart_str_cnt - 2] == 'V' && uart_str[uart_str_cnt - 1] == 'T' && uart_str[uart_str_cnt] == 'G'){
					vtg_found = 1;
					printf("vtg_found: %d\t ", vtg_found);
				}
			}
		}

	}
	if(rmc_found && gga_found && vtg_found && uart_str[uart_str_cnt - 1] == '\r' && uart_str[uart_str_cnt] == '\n'){
		printf("cr_nl_det = 1\n");
		block_finished = 1;
	}
	uart_str_cnt++;

	if(block_finished == 1){
		uart_str[uart_str_cnt] = '\0';
		gps_split_data(uart_str);
		printf("block: %s\n", uart_str);
		uart_str_cnt = 0;
		block_finished = 0;
		new_data = 0;
		rmc_found = 0;
		gga_found = 0;
		vtg_found = 0;
		cr_nl_det = 0;
	}


}

int main()
{
char c;
FILE *filePointer;
gps_init_mem();

filePointer = fopen("in.txt", "r");

while(( c = fgetc(filePointer)) != EOF) {
//	printf("%c", c);
	func(c);
}
//gps_save_data();

int i;

for(i = 0; i<= 12; i++)
	printf("rmc[%d]: %s\n ", i, rmc[i]);
printf("\n");
for(i = 0; i<= 14; i++)
	printf("gga[%d]: %s\n", i, gga[i]);
printf("\n");
for(i = 0; i<= 9; i++)
	printf("vtg[%d]: %s\n ", i, vtg[i]);
printf("\n");


//printf("date: %s, time: %s, long: %s, lat: %s, heigth: %s\n", gps_data.date, gps_data.time, gps_data.longitude, gps_data.latitude, gps_data.height_sea);
fclose(filePointer);
return 0;
}

