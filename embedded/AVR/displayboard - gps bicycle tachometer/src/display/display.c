/**
 * \file display.c
 * \brief This file contains the implementation of the display module.
 *
 * Copyright (C) 2011  Armin Schlegel, Christian Eismann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*--- Includes -------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "display.h"

/*--- Macros ---------------------------------------------------------*/

/** turn display on */
#define DISPLAY_ON 0xAF

/** the display RAM address SEG output correspondence (reverse) */
#define DISPLAY_ADC_SELECT_REVERSE 0xA1

/** COM output scan direction (reverse direction) */
#define DISPLAY_COMMON_OUTPUT_MODE 0xC0

/** the display RAM display start line address */
#define DISPLAY_START_LINE 0x40

/** 'normal' display view */
#define DISPLAY_VIEW_NORMAL 0xA6

/** the LCD drive voltage bias ration (1/9 bias) */
#define DISPLAY_BIAS 0xA2

/** internal power supply operating mode (booster, regulator and follower on) */
#define DISPLAY_POWER_CONTROL 0x2F

/** select booster ratio */
#define DISPLAY_BOOSTER_RATIO_SELECT 0xF8

/** set booster ratio to 4x */
#define DISPLAY_BOOSTER_RATIO_SET 0x00

/** internal resistor ratio (Rb/Ra) mode */
#define DISPLAY_INTERNAL_RESISTOR_RATIO 0x27

/** electronic volume mode set */
#define DISPLAY_ELEC_VOLUME_MODE 0x81

/** electronic volume register set */
#define DISPLAY_ELEC_VOLUME_REGISTER 0x10

/** set static indicator OFF */
#define DISPLAY_STATIC_INDICATOR_ON 0xAC

/** set static register */
#define DISPLAY_STATIC_REGISTER_SET 0x00

/** display RAM size */
#define DISPLAY_RAM_SIZE 1024U

/*--- Internal Constants ---------------------------------------------*/

/** The byte code array for the used font */
static const unsigned char Font5x7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,   // (space)
    0x00, 0x00, 0x5F, 0x00, 0x00,   // !
    0x00, 0x07, 0x00, 0x07, 0x00,   // "
    0x14, 0x7F, 0x14, 0x7F, 0x14,   // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12,   // $
    0x23, 0x13, 0x08, 0x64, 0x62,   // %
    0x36, 0x49, 0x55, 0x22, 0x50,   // &
    0x00, 0x05, 0x03, 0x00, 0x00,   // '
    0x00, 0x1C, 0x22, 0x41, 0x00,   // (
    0x00, 0x41, 0x22, 0x1C, 0x00,   // )
    0x08, 0x2A, 0x1C, 0x2A, 0x08,   // *
    0x08, 0x08, 0x3E, 0x08, 0x08,   // +
    0x00, 0x50, 0x30, 0x00, 0x00,   // ,
    0x08, 0x08, 0x08, 0x08, 0x08,   // -
    0x00, 0x60, 0x60, 0x00, 0x00,   // .
    0x20, 0x10, 0x08, 0x04, 0x02,   // /
    0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
    0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
    0x42, 0x61, 0x51, 0x49, 0x46,   // 2
    0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
    0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
    0x27, 0x45, 0x45, 0x45, 0x39,   // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
    0x01, 0x71, 0x09, 0x05, 0x03,   // 7
    0x36, 0x49, 0x49, 0x49, 0x36,   // 8
    0x06, 0x49, 0x49, 0x29, 0x1E,   // 9
    0x00, 0x36, 0x36, 0x00, 0x00,   // :
    0x00, 0x56, 0x36, 0x00, 0x00,   // ;
    0x00, 0x08, 0x14, 0x22, 0x41,   // <
    0x14, 0x14, 0x14, 0x14, 0x14,   // =
    0x41, 0x22, 0x14, 0x08, 0x00,   // >
    0x02, 0x01, 0x51, 0x09, 0x06,   // ?
    0x32, 0x49, 0x79, 0x41, 0x3E,   // @
    0x7E, 0x11, 0x11, 0x11, 0x7E,   // A
    0x7F, 0x49, 0x49, 0x49, 0x36,   // B
    0x3E, 0x41, 0x41, 0x41, 0x22,   // C
    0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
    0x7F, 0x49, 0x49, 0x49, 0x41,   // E
    0x7F, 0x09, 0x09, 0x01, 0x01,   // F
    0x3E, 0x41, 0x41, 0x51, 0x32,   // G
    0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
    0x00, 0x41, 0x7F, 0x41, 0x00,   // I
    0x20, 0x40, 0x41, 0x3F, 0x01,   // J
    0x7F, 0x08, 0x14, 0x22, 0x41,   // K
    0x7F, 0x40, 0x40, 0x40, 0x40,   // L
    0x7F, 0x02, 0x04, 0x02, 0x7F,   // M
    0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
    0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
    0x7F, 0x09, 0x09, 0x09, 0x06,   // P
    0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
    0x7F, 0x09, 0x19, 0x29, 0x46,   // R
    0x46, 0x49, 0x49, 0x49, 0x31,   // S
    0x01, 0x01, 0x7F, 0x01, 0x01,   // T
    0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
    0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
    0x7F, 0x20, 0x18, 0x20, 0x7F,   // W
    0x63, 0x14, 0x08, 0x14, 0x63,   // X
    0x03, 0x04, 0x78, 0x04, 0x03,   // Y
    0x61, 0x51, 0x49, 0x45, 0x43,   // Z
    0x00, 0x00, 0x7F, 0x41, 0x41,   // [
    0x02, 0x04, 0x08, 0x10, 0x20,   // "\"
    0x41, 0x41, 0x7F, 0x00, 0x00,   // ]
    0x04, 0x02, 0x01, 0x02, 0x04,   // ^
    0x40, 0x40, 0x40, 0x40, 0x40,   // _
    0x00, 0x01, 0x02, 0x04, 0x00,   // `
    0x20, 0x54, 0x54, 0x54, 0x78,   // a
    0x7F, 0x48, 0x44, 0x44, 0x38,   // b
    0x38, 0x44, 0x44, 0x44, 0x20,   // c
    0x38, 0x44, 0x44, 0x48, 0x7F,   // d
    0x38, 0x54, 0x54, 0x54, 0x18,   // e
    0x08, 0x7E, 0x09, 0x01, 0x02,   // f
    0x08, 0x14, 0x54, 0x54, 0x3C,   // g
    0x7F, 0x08, 0x04, 0x04, 0x78,   // h
    0x00, 0x44, 0x7D, 0x40, 0x00,   // i
    0x20, 0x40, 0x44, 0x3D, 0x00,   // j
    0x00, 0x7F, 0x10, 0x28, 0x44,   // k
    0x00, 0x41, 0x7F, 0x40, 0x00,   // l
    0x7C, 0x04, 0x18, 0x04, 0x78,   // m
    0x7C, 0x08, 0x04, 0x04, 0x78,   // n
    0x38, 0x44, 0x44, 0x44, 0x38,   // o
    0x7C, 0x14, 0x14, 0x14, 0x08,   // p
    0x08, 0x14, 0x14, 0x18, 0x7C,   // q
    0x7C, 0x08, 0x04, 0x04, 0x08,   // r
    0x48, 0x54, 0x54, 0x54, 0x20,   // s
    0x04, 0x3F, 0x44, 0x40, 0x20,   // t
    0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
    0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
    0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
    0x44, 0x28, 0x10, 0x28, 0x44,   // x
    0x0C, 0x50, 0x50, 0x50, 0x3C,   // y
    0x44, 0x64, 0x54, 0x4C, 0x44,   // z
    0x00, 0x08, 0x36, 0x41, 0x00,   // {
    0x00, 0x00, 0x7F, 0x00, 0x00,   // |
    0x00, 0x41, 0x36, 0x08, 0x00,   // }
    0x08, 0x08, 0x2A, 0x1C, 0x08,   // ->
    0x08, 0x1C, 0x2A, 0x08, 0x08   // <-
};

/*--- Internal Data --------------------------------------------------*/

static uint8_t disp_ram[1024];

/*--- External Function Definitions ----------------------------------*/

/**
 * \brief Reset the graphic display.
 */
void display_reset(void)
{
   /* set data direction of reset pin to output */
   DDR_RESET_DSP |= (1 << DD_RESET_DSP);

   /* set low active Reset to low -> Display reset */
   PORT_RESET_DSP &= ~(1 << RESET_DSP);
   _delay_ms(100);

   /* set low active Reset to high -> no Display reset */
   PORT_RESET_DSP |= (1 << RESET_DSP);
}

/**
 * \brief Deselect the chip select pin for the graphic display.
 */
void display_cs_unselect(void)
{
   /* CS_DSP is output */
   DDR_CS_DSP |= (1 << DD_CS_DSP);
   /* CS_DSP high */
   PORT_CS_DSP |= (1 << CS_DSP);
}

/**
 * \brief Activate the chip select pin for the graphic display.
 */
void display_cs_select(void)
{
   /* CS_DSP is output */
   DDR_CS_DSP |= (1 << DD_CS_DSP);
   /* CS_DSP low */
   PORT_CS_DSP &= ~(1 << CS_DSP);
}

/**
 * \brief Set the display SPI communication to data mode.
 */
void display_data_mode(void)
{
   /* A0 is output */
   DDR_A0_DSP |= (1 << DD_A0_DSP);
   /* A0 high -> data mode */
   PORT_A0_DSP |= (1 << A0_DSP);

}

/**
 * \brief Set the display SPI communication to command mode.
 */
void display_command_mode(void)
{
   /* A0 is output */
   DDR_A0_DSP |= (1 << DD_A0_DSP);

   /* A0 low -> command mode */
   PORT_A0_DSP &= ~(1 << A0_DSP);
}

/**
 * \brief Sends a 8 bit command to the display controller.
 */
void display_send_command(unsigned char cData)
{
   display_cs_select();
   display_command_mode();
   spi_send(cData);
   display_cs_unselect();
}

/**
 * \brief Sends a 8 bit data block the display controller.
 */
void display_send_data(unsigned char cData)
{
   display_cs_select();
   display_data_mode();
   spi_send(cData);
   display_cs_unselect();
}

/**
 * \brief Initializes the graphical display
 *
 * Within this function the EA DOGL-128-6 is initialized for single power
 * supply +3.3V
 */
void display_init(void)
{
   display_reset();

   /* (2) display start line 0 */
   display_send_command(DISPLAY_START_LINE);

   /* (8) ADC reverse */
   display_send_command(DISPLAY_ADC_SELECT_REVERSE);

   /* (15) normal COM0~COM63 */
   display_send_command(DISPLAY_COMMON_OUTPUT_MODE);

   /* (9)  display view: normal */
   display_send_command(DISPLAY_VIEW_NORMAL);

   /* (11) lcd bias set 1/9 (duty 1/65) */
   display_send_command(DISPLAY_BIAS);

   /* (16) booster, regulator and follower on */
   display_send_command(DISPLAY_POWER_CONTROL);

   /* (20) booster ration 4x */
   display_send_command(DISPLAY_BOOSTER_RATIO_SELECT);
   display_send_command(DISPLAY_BOOSTER_RATIO_SET);

   /* (17) V0 voltage regulator set */
   display_send_command(DISPLAY_INTERNAL_RESISTOR_RATIO);

   /* (18) electronic volume mode set */
   display_send_command(DISPLAY_ELEC_VOLUME_MODE);
   display_send_command(DISPLAY_ELEC_VOLUME_REGISTER);

   /* (19) no indicator */
   display_send_command(DISPLAY_STATIC_INDICATOR_ON);
   display_send_command(DISPLAY_STATIC_REGISTER_SET);

   /* (1) Display On */
   display_send_command(DISPLAY_ON);
}

/**
 * \brief Send a new frame to th ST-7565R display RAM
 *
 * A frame consists of 8 Pages. Each page consists of 8x128bit storage.
 * \code
 *    0                                             127
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D0 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D1 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D2 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D3 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D4 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D5 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D6 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D7 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * \endcode
 * \note The ST-7565R display controller provides a 64 * 132(!) bit RAM. But the
 *       actual display resolution of the EA DOGL128-6 is 128x64 pixel. Therefore
 *       only 128 columns are used within the internal RAM of the display controller.
 *
 * The virtual data representation is realized in linear order here.
 * \code
 *    |- disp_ram[0]                disp_ram[1023] -|
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 *    | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * \endcode
 * To avoid a waste of memory the data structure is organized as follows:
 * ARRAY_ELEMENT = 8bit * COLUMN + PAGE --> maximum array size of 1024 elements
 *
 * Every 8 bit value stored in disp_ram array represents a single column of one
 * page.
 */
void display_send_frame()
{
   uint8_t page;
   uint8_t column;

   for (page = 0U; page < 8U; page++) {
      display_go_to(0U, page);
      for (column = 0U; column < 128U; column++)
         display_send_data(disp_ram[page + (column << 3U)]);
   }
}

/**
 * \brief Set/Unset a single pixel on the display
 *
 * For choosing the correct entry within the data structure (disp_ram[])
 * first the concerning page of this pixel has to be determined. This
 * is done by dividing the Y coordinate by 8 (or better: do a right shift
 * of 3 bits). For choosing the entry in the array, the X coordinate multiplied
 * by 8 (or better: left shifted by 3) has to be added to the actual page number.
 * The exact bit that shall be set/unset is determined by using the bitmask
 * (y & 0x07). This selects the exact row of the respective memory page.
 *
 * \param x  X coordinate of the pixel
 * \param y  Y coordinate of the pixel
 */
void display_putpixel(unsigned char x, unsigned char y, int pixel_status)
{
   if (x < DISP_WIDTH && y < DISP_HEIGHT) {
      if (pixel_status == PIXEL_ON)
         disp_ram[(y >> 3) + (x << 3)] |= (1 << (y & 0x07));
      else
         disp_ram[(y >> 3) + (x << 3)] &= ~(1 << (y & 0x07));
    }
}

/**
 * \brief Turn every pixel off
 */
void display_clear_ram(void)
{
   /* clears the local RAM but don't send it */
   uint16_t d;
   for (d = 0U; d < DISPLAY_RAM_SIZE; d++) {
      disp_ram[d] = 0x00;
   }
}

/**
 * \brief Clear the graphical display screen
 */
void display_clear_screen(void)
{
   display_clear_ram();
   display_send_frame();
}

/**
 * \brief Positioning of the cursor at the provided column and page
 *
 * \param col the column at which the curser shall be positioned
 * \param page the RAM page at which the cursor shall be positioned
 */
void display_go_to(unsigned char col, unsigned char page)
{
   display_send_command(DISPLAY_PAGE_ADDRESS | ((page) & 0x0F));
   display_send_command(DISPLAY_COL_ADDRESS_MSB | ((col >> 4) & 0x0F));
   display_send_command(DISPLAY_COL_ADDRESS_LSB | ((col) & 0x0F));
   return;
}

/**
 * \brief Draw a provided character at a specific position on the graphical display
 *
 * \param x the x coordinate where the character shall be placed
 * \param y the y coordinate where the character shall be placed
 * \param character the actual character that shall be printed
 */
void display_draw_char_5x7(unsigned short x, unsigned short y,
            char character)
{
   unsigned char fontIndex, i, j;
   const unsigned char *addr = Font5x7;
   /* The 5x7 character set starts at the '!' character (ASCII index
    * number 33) so we subtract 32 from the ASCII character to find the
    * index in the 5x7 font table. */
   fontIndex = character - 32;
   /* If the index is out of bounds, bail out */
   if (fontIndex > 94)
      return;

   for (i = 0; i < FONT_WIDTH; i++) {
      for (j = 0; j < FONT_HEIGHT; j++) {
      /* Check if the bit/pixel is set, paint accoringly to
       * the screen */
    if (pgm_read_byte(addr + FONT_WIDTH * fontIndex + i) & (1 << j))
   display_putpixel(x, y + j, PIXEL_ON);
    else
   display_putpixel(x, y + j, PIXEL_OFF);
   }
   /* Move the LCD cursor through the font width as well */
   x++;
   }
}

/**
 * \brief Draw an entire string at a specific position on the graphical display
 *
 * \param x the x coordinate where the string shall be placed
 * \param y the y coordinate where the string shall be placed
 * \param str the pointer to the string that shall be printed, terminated by
 *            '\0'
 */
void display_string(unsigned short x, unsigned short y, const char *str)
{
   unsigned short origin_X;

   origin_X = x;      //alte X Position beibehalten

   /* Continue through the string until we encounter a null character */

   while (*str != '\0') {
      /* If the character is a newline, then prepare our x and y
      * coordinates for the next character on the new line. */
      if (*str == '\n') {
         /* Reset x to its origin */
         x = origin_X;

         /* Move y one character down */
         y += FONT_HEIGHT + 1;

         str++;
         continue;
      }

      display_draw_char_5x7(x, y, *str++);

      /* Add a 1-pixel spacing between the characters */
      x += FONT_WIDTH + 1;

      /* In case we are putting this character out of bounds,
      * move the character to the next line on the display */
      if ((x + FONT_WIDTH) > DISP_WIDTH) {
       /* Reset x to its origin */
       x = origin_X;

       /* Move y one character down */
       y += FONT_HEIGHT + 1;
      }
   }
}

/**
 * \brief Draw a bitmap picture to the graphical display.
 * \note The picture has to be stored within the interal EEPROM!
 * \param x the x coordinate where the picture shall be placed (upper left corner)
 * \param y the y coordinate where the string shall be placed (upper left corner)
 * \param str the address where the picture is stored (in internal EEPROM)
 */
void display_bmp_flash(unsigned char x, unsigned char y, unsigned char *addr)
{
    uint8_t width = pgm_read_byte(addr++);
    uint8_t heigth = pgm_read_byte(addr++);
    uint16_t bitcnt;
    uint8_t _x = 0;
    uint8_t _y = 0;

   for (bitcnt = 0; bitcnt < (uint16_t) (heigth * width); bitcnt++) {
      if ((bitcnt % (width)) == 0) {
         _y++;
         _x = 0;
      } else {
         _x++;
      }
      if (pgm_read_byte(addr + bitcnt / 8) & (1 << (bitcnt % 8)))
         display_putpixel(_x + x, _y + y, PIXEL_ON);
      else
         display_putpixel(_x + x, _y + y, PIXEL_OFF);
   }
}

/**
 * \brief Print a line on the graphical display.
 *
 * \param x0 the starting point x-coordinate
 * \param y0 the starting point y-coordinate
 * \param x1 the ending point x-coordinate
 * \param y1 the ending point y-coordinate
 */
void display_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
   int8_t dy = y1 - y0;
   int8_t dx = x1 - x0;
   int8_t stepx, stepy;

   if (dy < 0) {
      dy = -dy;
   stepy = -1;
   } else {
      stepy = 1;
   }
   if (dx < 0) {
      dx = -dx;
      stepx = -1;
   } else {
      stepx = 1;
   }
   dy <<= 1;
   dx <<= 1;

   display_putpixel(x0, y0, 1);

   if (dx > dy) {
      int fraction = dy - (dx >> 1);

      while (x0 != x1) {
         if (fraction >= 0) {
            y0 += stepy;
            fraction -= dx;
         }
         x0 += stepx;
         fraction += dy;
         display_putpixel(x0, y0, PIXEL_ON);
      }
   } else {
      int fraction = dx - (dy >> PIXEL_ON);
      while (y0 != y1) {
         if (fraction >= 0) {
            x0 += stepx;
            fraction -= dy;
         }
         y0 += stepy;
         fraction += dx;
         display_putpixel(x0, y0, PIXEL_ON);
      }
   }
}

/**
 * \brief Print a horizontal line on the graphical display.
 *
 * \param x0 the starting point x-coordinate
 * \param y0 the starting point y-coordinate
 * \param length the length of the horizontal line
 * \param pixel_status defines whether the line shall be printed by enabling
 *                     (PIXEL_ON) or disabling (PIXEL_OFF) single pixels
 */
void display_hline(uint8_t x0, uint8_t y0, uint8_t length, uint8_t pixel_status)
{
   uint8_t cnt;

   for (cnt = x0; cnt <= length + x0; cnt++)
      display_putpixel(cnt, y0, pixel_status);
}

