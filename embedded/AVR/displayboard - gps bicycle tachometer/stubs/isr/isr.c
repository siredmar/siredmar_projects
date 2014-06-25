#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


void func(char next_char);

volatile uint8_t uart_str_cnt = 0;
volatile uint8_t uart_str_ready = 0;
volatile uint8_t new_data = 0;
volatile uint8_t uart_cr_found = 0;
volatile char uart_str[190 + 1] = "";

volatile uint8_t rmc_found = 0;
volatile uint8_t vtg_found = 0;
volatile uint8_t gga_found = 0;
volatile uint8_t block_finished = 0;
volatile uint8_t new_sentence_index = 0;



int main()
{
char c;
FILE *filePointer;
filePointer = fopen("in.txt", "r");

while(( c = fgetc(filePointer)) != EOF) {
//	printf("%c", c);
	func(c);
}
fclose(filePointer);
return 0;
}

void func(char next_char)
{
    if (next_char == '$'){
        new_data = 1;
        new_sentence_index = uart_str_cnt;
    }else{
	  new_data = 0;
    }
    if (next_char == '\r'){
        uart_cr_found = 1;
    }else{
        uart_cr_found = 0;
    }
    if ((uart_cr_found == 0) && (next_char != '\n') && (block_finished == 0)) {
        uart_str[uart_str_cnt] = next_char;
        uart_str_cnt++;
        uart_str_ready = 0;
        if((uart_str_cnt - new_sentence_index) == 6){
               if((uart_str[uart_str_cnt - 3] == 'R')  && (uart_str[uart_str_cnt - 2] == 'M')&& (uart_str[uart_str_cnt -1 ] == 'C')){

                        rmc_found = 1;
                	printf("rmc_found = 1\n");
                }
                if((uart_str[uart_str_cnt - 3] == 'G')  && (uart_str[uart_str_cnt - 2] == 'G')&& (uart_str[uart_str_cnt -1 ] == 'A')){
                        gga_found = 1;
                	printf("gga_found = 1\n");
                }
                if((uart_str[uart_str_cnt - 3] == 'V')  && (uart_str[uart_str_cnt - 2] == 'T')&& (uart_str[uart_str_cnt -1 ] == 'G')){
                	printf("vtg_found = 1\n");
                        vtg_found = 1;
		}
        }
    } else {
        if(rmc_found && gga_found && vtg_found){
                uart_str[uart_str_cnt] = '\0';
                uart_str_cnt = 0;
                uart_str_ready = 1;
                new_data = 1;
		printf("block:\n%s\n", uart_str);
//        display_clear_ram();
  //      display_string(0,0,uart_str);
    //    display_send_frame();
//        gps_split_data(uart_str);             //send received block to perform some split and play action
  //cleanup for next block to receive
        rmc_found = 0;
        gga_found = 0;
        vtg_found = 0;
        block_finished = 0;
        new_sentence_index = 0;
        }
    }
}
