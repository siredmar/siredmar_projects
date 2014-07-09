#include <stdio.h>
#include <stdlib.h>


#include "lc7981.h"
#include "graphics.h"
#include "touch.h"
#include "images.h"
#include "windows.h"


void print_welcome_screen(){

	while (!touch_is_pressed())
		lcd_bmp(data_toteokopf,0 , 0, 160, 80);

lcd_graphics_clear(); // clear display
}

void print_main_screen(){

char str_koord[30];
char str_button_pressed[17];
	uint16_t x,y;
	str_koord[0] = '\0';
	str_button_pressed[0] = '\0';
	while(1){
	print_button(right_bmp,120, 24,0);
	print_button(left_bmp, 10,  24,0);
	print_button(up_bmp,   65,   5,0);
	print_button(down_bmp, 65,  52,0);	
	
	x = touch_readX();
	y = touch_readY();
			
			sprintf(str_koord, "x: %03d,\ty: %02d\n", x,y);
			g_draw_string(41, 40, str_koord); 
			
			if((x > 119 && x < 151) && (y > 23 && y < 48)){
				print_button(right_bmp,120, 24,1);
				_delay_ms(300);
				
				print_right_window();
			}
			if((x > 9 && x < 41) && (y > 23 && y < 48)){
				print_button(left_bmp, 10,  24,1);
				_delay_ms(300);
				
				print_left_window();
			}
			if((x > 64 && x < 96) && (y > 4 && y < 29)){
				print_button(up_bmp,   65,   5,1);
				_delay_ms(300);
					
				print_up_window();
			}	
			if((x > 64 && x < 96) && (y > 51 && y < 76)){
				print_button(down_bmp, 65,  52,1);
				_delay_ms(300);
				
				print_down_window();
			}
			
			
}
}

void print_left_window(){
lcd_graphics_clear();
	static int cnt = 0;
	char str_cnt[5];
	uint16_t x,y;
	
				
	
	
	

	while(1){
	x = touch_readX();
	y = touch_readY();
	
	
	sprintf(str_cnt, "%3d", cnt);
	g_draw_string(60, 35, str_cnt);
	
	
	print_button(plus_bmp,20, 10,0);
	print_button(minus_bmp,20, 40,0);
	print_button(right_bmp,120, 24,0);
	
	if((x > 19 && x < 41) && (y > 9 && y < 34)){
				print_button(plus_bmp,20, 10,1);
				_delay_ms(150);
				cnt++;
	}

	if((x > 19 && x < 41) && (y > 39 && y < 64)){
				print_button(minus_bmp,20, 40,1);
				_delay_ms(150);
				cnt--;
	}

	
	
	
	if((x > 119 && x < 151) && (y > 23 && y < 48)){
				print_button(right_bmp,120, 24,1);
				_delay_ms(300);
				lcd_graphics_clear();
				print_main_screen();
	}

	}
}

void print_right_window(){
lcd_graphics_clear();
	uint16_t x,y;
	while(1){
	lcd_bmp(tux_bmp, 40, 0,96,80);
	
	
	x = touch_readX();
	y = touch_readY();
	print_button(left_bmp, 10,  24,0);
	if((x > 9 && x < 41) && (y > 23 && y < 48)){
				print_button(left_bmp, 10,  24,1);
				_delay_ms(300);
				lcd_graphics_clear();
				print_main_screen();
	}
	}

}


void print_up_window(){
lcd_graphics_clear();
	uint16_t x,y;
	while(1){
	x = touch_readX();
	y = touch_readY();
	g_draw_string(0,0,"Bitte malen ...");
	lcd_graphics_plot_pixel(x, y, PIXEL_ON);
	
	
	
	print_button(down_bmp, 65,  52,0);	
			if((x > 64 && x < 96) && (y > 51 && y < 76)){
				print_button(down_bmp, 65,  52,1);
				_delay_ms(300);
				lcd_graphics_clear();
				print_main_screen();
	}

}

}

void print_down_window(){
lcd_graphics_clear();
	uint16_t x,y;
	while(1){
	g_draw_string(0,30,"Das ist eine kleine Demo,\nwas alles schönes mit\ndiesen Display machbar ist...");
	
	
	x = touch_readX();
	y = touch_readY();
	print_button(up_bmp,   65,   5,0);
	if((x > 64 && x < 96) && (y > 4 && y < 29)){
		print_button(up_bmp,   65,   5,1);
		_delay_ms(300);
		lcd_graphics_clear();
		print_main_screen();
		}
	}

}


