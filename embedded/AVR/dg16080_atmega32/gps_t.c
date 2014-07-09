#include <stdio.h>
#include <stdlib.h>


#include "lc7981.h"
#include "graphics.h"
#include "touch.h"


int main()
{

lcd_graphics_init();
	
	
	print_welcome_screen();
	lcd_graphics_clear();
	
	while (1)
	{
		
		print_main_screen();
		
	}
		






return 0;
}