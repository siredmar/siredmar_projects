#include <stdio.h>
#include <stdlib.h>


#include "lc7981.h"
#include "graphics.h"
#include "touch.h"
#include "images.h"
#include "windows.h"

void print_button(unsigned const char *bitmap,unsigned char xpos , unsigned char ypos, int inverted)
{

 unsigned int i, x,y;
	
	unsigned char by;
	x = xpos;
	y = ypos;
	for(i = 0; i<= 95 ; i ++){
		if((i%4 == 0)){
			y++;
			x = xpos;
		}
		else{
			x = x + 8;
		}
		
		by=pgm_read_byte(bitmap);
		
		if(inverted == 0)
			lcd_graphics_plot_byte(x, y, msb_to_lsb(by));
		if(inverted == 1)
			lcd_graphics_plot_byte(x, y, msb_to_lsb(~by));
		bitmap++;	
		}
}