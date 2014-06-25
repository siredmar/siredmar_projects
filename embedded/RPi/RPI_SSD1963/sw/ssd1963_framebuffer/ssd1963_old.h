/*
 * ssd1963.h
 *
 *  Created on: Aug 12, 2013
 *      Author: armin
 */

#ifndef SSD1963_H_
#define SSD1963_H_

#define DATA      1
#define COMMAND   0

#define LCD_RS          2
#define LCD_NWR         3
#define LCD_NCS         8
#define LCD_NRST        11
#define LCD_BACKLIGHT   7

//nrd is tied to 3.3V in hardware.
#define LCD_D0    29
#define LCD_D1    28
#define LCD_D2    31
#define LCD_D3    30
#define LCD_D4    4
#define LCD_D5    14
#define LCD_D6    17
#define LCD_D7    27
#define LCD_D8    15
#define LCD_D9    18
#define LCD_D10   22
#define LCD_D11   23
#define LCD_D12   24
#define LCD_D13   10
#define LCD_D14   25
#define LCD_D15   9

/* TFT Controler Register defines */
#define TFT_RAM_REG_ADDR_UI16               0x002C
#define TFT_COL_START_ADDR2_REG_ADDR_UI16   0x002A
#define TFT_COL_START_ADDR1_REG_ADDR_UI16   0x0000
#define TFT_COL_END_ADDR2_REG_ADDR_UI16     0x0000
#define TFT_COL_END_ADDR1_REG_ADDR_UI16     0x0000
#define TFT_ROW_START_ADDR2_REG_ADDR_UI16   0x002B
#define TFT_ROW_START_ADDR1_REG_ADDR_UI16   0x0000
#define TFT_ROW_END_ADDR2_REG_ADDR_UI16     0x0000
#define TFT_ROW_END_ADDR1_REG_ADDR_UI16     0x0000
#define NOCMD                               0xFFFF
#define NOPARAM                             0
#define PARAM                               1

#define TFT_WIDTH_UI16                      480
#define TFT_HEIGHT_UI16                     272

#define HDP                                  479        //479
#define HT                                   525        //531
#define HPS                                  40         //43
#define LPS                                  6           //8
#define HPW                                  39         //10
                                                        //
#define VDP                                  271        //271
#define VT                                   288        //288
#define VPS                                  12         //12
#define FPS                                  8          //4
#define VPW                                  11         //10


struct ssd1963_page {
   unsigned short x;
   unsigned short y;
   unsigned short *buffer;
   unsigned short *oldbuffer;
   unsigned short len;
   int must_update;
};

struct ssd1963 {
   struct device *dev;
   struct fb_info *info;
   unsigned int pages_count;
   struct ssd1963_page *pages;
   unsigned long pseudo_palette[17];
   int backlight;
};

typedef struct
{
   unsigned short tft_registerAddress_ui16;
   unsigned short tft_registerValue_ui16;
   unsigned short tft_waitTimeAfterSend_ui16;
   unsigned short tft_registerParameters_ui16;
}tft_initSequenceType;



#endif /* SSD1963_H_ */
