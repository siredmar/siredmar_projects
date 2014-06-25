/*
* SSD1963 Framebuffer
*
*
* Copyright (c) 2013 Armin Schlegel <armin.schlegel@gmx.de>
* Original: Copyright (c) 2009 Jean-Christian de Rivaz
* Original: Copyright (c) 2012 Jeroen Domburg <jeroen@spritesmods.com>
*
* This is an adaption from the ili9325.c from Jeroen Domburg to work with
* the SSD1963 controller.
* Bits and pieces borrowed from the fsl-ili9325.c:
* Copyright (C) 2010-2011 Freescale Semiconductor, Inc. All Rights Reserved.
* Author: Alison Wang <b18965@freescale.com>
*         Jason Jin <Jason.jin@freescale.com>
*
* This file is subject to the terms and conditions of the GNU General Public
* License.  See the file "COPYING" in the main directory of this archive
* for more details.
*
* The Solomon Systech SSD1963 chip drive TFT screen with a resolution of 480x272.
*
* For direct I/O-mode:
*
* This driver expect the SSD1963 to be connected to a 16 bits local bus
* and to be set in the 16 bits parallel interface mode. To use it you must
* define in your board file a struct platform_device with a name set to
* "ssd1963" and a struct resource array with two IORESOURCE_MEM: the first
* for the control register; the second for the data register.
*
*/


#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/fb.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include "ssd1963.h"

#define SSD1963_GPIOSET(x)      writel((1<<x),  __io_address(GPIO_BASE+0x1C))
#define SSD1963_GPIORESET(x)    writel((1<<x),  __io_address(GPIO_BASE+0x28))


/*
Use direct GPIO reg access instead of the gpiolib framework: because we want to write
multiple bits at once to the (presumably connected over a slower bus) GPIO block,
this involves less writes and so will be faster.
*/

/* macros to get at IO space when running virtually */

#define GPIO_ALT_OFFSET(g) ((((g)/10))*4)
#define GPIO_ALT_VAL(a, g) ((a)<<(((g)%10)*3))


//#define GPIOSET(no, ishigh)   { if (ishigh) set|=(1<<no); else reset|=(1<<no); } while(0)



#define GPIOSET(no, ishigh) \
do {                        \
   if (ishigh)              \
      set |= (1 << (no));   \
   else                     \
      reset |= (1 << (no)); \
} while (0)


inline void ssd1963_write_byte(unsigned char data, int rs)
{
	unsigned int set=0;
	unsigned int reset=0;
	SSD1963_GPIORESET(LCD_NCS);
	//GPIOSET(LCD_NCS, 0);
	GPIOSET(LCD_NWR, 1);
	GPIOSET(LCD_RS, rs);
	GPIOSET(LCD_NRST, 1);
	GPIOSET(LCD_D0, (data&0x01));
	GPIOSET(LCD_D1, (data&0x02));
	GPIOSET(LCD_D2, (data&0x04));
	GPIOSET(LCD_D3, (data&0x08));
	GPIOSET(LCD_D4, (data&0x10));
	GPIOSET(LCD_D5, (data&0x20));
	GPIOSET(LCD_D6, (data&0x40));
	GPIOSET(LCD_D7, (data&0x80));

	writel(set, __io_address(GPIO_BASE+0x1C));
	writel(reset, __io_address(GPIO_BASE+0x28));

//Pulse /wr low
	SSD1963_GPIORESET(LCD_NWR);
	SSD1963_GPIORESET(0);
	SSD1963_GPIOSET(LCD_NWR);
	SSD1963_GPIOSET(LCD_NCS);
}
#undef GPIOSET


inline void ssd1963_set_output(int gpio)
{
	unsigned int v;
	v=readl(__io_address(GPIO_BASE+GPIO_ALT_OFFSET(gpio)));
	v&=~GPIO_ALT_VAL(0x7, gpio); //clear existing bits
	v|=GPIO_ALT_VAL(1, gpio); //output
	writel(v, __io_address(GPIO_BASE+GPIO_ALT_OFFSET(gpio)));
}

//#define GPIOSET(no, ishigh)   { if (ishigh) set|=(1<<no); else reset|=(1<<no); } while(0)


//#define GPIOSET(no, ishigh)   { if (ishigh) set|=(1<<no); else reset|=(1<<no); } while(0)



#define GPIOSET(no, ishigh) \
do {                        \
   if (ishigh)              \
      set |= (1 << (no));   \
   else                     \
      reset |= (1 << (no)); \
} while (0)


inline void ssd1963_writeword(unsigned int data, int rs)
{
   unsigned int set=0;
   unsigned int reset=0;
   //GPIOSET(LCD_NCS, 0);
   SSD1963_GPIORESET(LCD_NCS);
   GPIOSET(LCD_NWR, 1);
   GPIOSET(LCD_RS, rs);
   GPIOSET(LCD_NRST, 1);

   GPIOSET(LCD_D0,  (data&0x01));
   GPIOSET(LCD_D1,  (data&0x02));
   GPIOSET(LCD_D2,  (data&0x04));
   GPIOSET(LCD_D3,  (data&0x08));
   GPIOSET(LCD_D4,  (data&0x10));
   GPIOSET(LCD_D5,  (data&0x20));
   GPIOSET(LCD_D6,  (data&0x40));
   GPIOSET(LCD_D7,  (data&0x80));
   GPIOSET(LCD_D8,  (data&0x100));
   GPIOSET(LCD_D9,  (data&0x200));
   GPIOSET(LCD_D10, (data&0x400));
   GPIOSET(LCD_D11, (data&0x800));
   GPIOSET(LCD_D12, (data&0x1000));
   GPIOSET(LCD_D13, (data&0x2000));
   GPIOSET(LCD_D14, (data&0x4000));
   GPIOSET(LCD_D15, (data&0x8000));


   writel(set, __io_address(GPIO_BASE+0x1C));
   writel(reset, __io_address(GPIO_BASE+0x28));

   SSD1963_GPIORESET(LCD_NWR);
   SSD1963_GPIORESET(0);
   SSD1963_GPIOSET(LCD_NWR);
   SSD1963_GPIOSET(LCD_NCS);

   ////Pulse /wr low
//   writel((1<<LCD_NWR),  __io_address(GPIO_BASE+0x28));
//   writel(0,  __io_address(GPIO_BASE+0x28)); //used as a delay
//   writel((1<<LCD_NWR),  __io_address(GPIO_BASE+0x1C));
}

#undef GPIOSET

inline void ssd1963_gpio_init(void)
{
	ssd1963_set_output(LCD_NCS);
	ssd1963_set_output(LCD_BACKLIGHT);
	ssd1963_set_output(LCD_NWR);
	ssd1963_set_output(LCD_RS);
	ssd1963_set_output(LCD_NRST);
	ssd1963_set_output(LCD_D0);
	ssd1963_set_output(LCD_D1);
	ssd1963_set_output(LCD_D2);
	ssd1963_set_output(LCD_D3);
	ssd1963_set_output(LCD_D4);
	ssd1963_set_output(LCD_D5);
	ssd1963_set_output(LCD_D6);
	ssd1963_set_output(LCD_D7);
   ssd1963_set_output(LCD_D8);
   ssd1963_set_output(LCD_D9);
   ssd1963_set_output(LCD_D10);
   ssd1963_set_output(LCD_D11);
   ssd1963_set_output(LCD_D12);
   ssd1963_set_output(LCD_D13);
   ssd1963_set_output(LCD_D14);
   ssd1963_set_output(LCD_D15);
	ssd1963_writeword(0,0); //dummy
	ssd1963_writeword(0,0); //dummy
}

void ssd1963_setDisplayRegister
(
   unsigned short tft_register_ui16,
   unsigned short tft_registerValue_ui16,
   unsigned short tft_registerParameters_ui16
)
{
   /* First send Command if it is != NOCMD */
   if(tft_register_ui16 != NOCMD)
   {
      ssd1963_write_byte(tft_register_ui16, COMMAND);
   }
   /* Then send or continue sending Parameter to tft controler if needed */
   if(tft_registerParameters_ui16 != NOPARAM)
   {
      ssd1963_write_byte(tft_registerValue_ui16, DATA);
   }
}

void ssd1963_setWindow(unsigned short startPositionX_ui16, unsigned short startPositionY_ui16, unsigned short endPositionX_ui16, unsigned short endPositionY_ui16)
{
   SSD1963_GPIORESET(LCD_NCS);
   ssd1963_setDisplayRegister(TFT_COL_START_ADDR2_REG_ADDR_UI16,((startPositionX_ui16 & 0xFF00) >> 8U), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            (startPositionX_ui16 & 0x00FF), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            ((endPositionX_ui16 & 0xFF00) >> 8U), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            (endPositionX_ui16 & 0x00FF), 1U);
   ssd1963_setDisplayRegister(TFT_ROW_START_ADDR2_REG_ADDR_UI16,((startPositionY_ui16 & 0xFF00) >> 8U), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            (startPositionY_ui16 & 0x00FF), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            ((endPositionY_ui16 & 0xFF00) >> 8U), 1U);
   ssd1963_setDisplayRegister(NOCMD,                            (endPositionY_ui16 & 0x00FF), 1U);
   ssd1963_write_byte(TFT_RAM_REG_ADDR_UI16, COMMAND);
   SSD1963_GPIOSET(LCD_NCS);
}

void ssd1963_drawPixel
(
   unsigned short xPosition_ui16,
   unsigned short yPosition_ui16,
   unsigned short rectangleColor_ui16
)
{
   /* Set window size and position - modified for portrait view */
   ssd1963_setWindow(xPosition_ui16, yPosition_ui16, xPosition_ui16+1, yPosition_ui16+1);
   ssd1963_writeword(rectangleColor_ui16, DATA);
}

void ssd1963_copy(struct ssd1963 *item, unsigned int index)
{
	unsigned short x;
	unsigned short y;
	unsigned short *buffer;
	unsigned short *oldbuffer;
	unsigned int len;
	unsigned int count;
	int sendNewPos=1;
	int pageModified = 0;
	x = item->pages[index].x;
	y = item->pages[index].y;
	buffer = item->pages[index].buffer;
	oldbuffer = item->pages[index].oldbuffer;
	len = item->pages[index].len;
	dev_dbg(item->dev, "%s: page[%u]: x=%3hu y=%3hu buffer=0x%p len=%3hu\n", __func__, index, x, y, buffer, len);

	unsigned short x_pageend = 0;
	unsigned short y_pageend = 0;
	unsigned int   pixelsToThisPoint = index * len + len;

	x_pageend = (pixelsToThisPoint) % TFT_WIDTH_UI16 - 1;
	y_pageend = (pixelsToThisPoint) / TFT_WIDTH_UI16;
	if(x_pageend == 0)
	{
	   x_pageend = TFT_WIDTH_UI16 - 1;
	   y_pageend--;
	}
	printk(KERN_ALERT "ssd1963_copy(): Page changed! index: %d\n", index);

	for(count = 0; count < len; count++)
	{
	   if(oldbuffer[count] != buffer[count])
	   {
	      ssd1963_drawPixel(x, y, buffer[count]);
	      oldbuffer[count] = buffer[count];

	   }
	   x++;
	   if(x == TFT_WIDTH_UI16)
	   {
	      x = 0;
	      y++;
	   }

	}

//   //Only update changed pixels in the page.
//	for (count = 0; count < len; count++) {
//		if (buffer[count]==oldbuffer[count])
//		{
//		   pageModified=1;
//		   break;
//		}
//	}
//
//
//
//   if (pageModified)
//   {
//      ssd1963_setWindow(x, y, x_pageend, y_pageend);
//      sendNewPos=0;
//      pageModified = 0;
//      for (count = 0; count < len; count++)
//      {
//         ssd1963_writeword(buffer[count], DATA);
//         oldbuffer[count]=buffer[count];
//      }
//   }
//		x++;
//		if (x>=item->info->var.xres) {
//			y++;
//			x=0;
//		}

	//printk(KERN_ALERT "ssd1963_copy(): index: %u, len: %d, x: %d, y: %d\n", index, len, x, y);

   //msleep(100);
}

static void ssd1963_update_all(struct ssd1963 *item)
{
	unsigned short i;
	struct fb_deferred_io *fbdefio = item->info->fbdefio;
	for (i = 0; i < item->pages_count; i++) {
		item->pages[i].must_update=1;
	}
	printk(KERN_ALERT "ssd1963_update_all () occurred!\n");
	schedule_delayed_work(&item->info->deferred_work, fbdefio->delay);
}

static void ssd1963_update(struct fb_info *info, struct list_head *pagelist)
{
	struct ssd1963 *item = (struct ssd1963 *)info->par;
	struct page *page;
	int i;

	//We can be called because of pagefaults (mmap'ed framebuffer, pages
	//returned in *pagelist) or because of kernel activity
	//(pages[i]/must_update!=0). Add the former to the list of the latter.
	list_for_each_entry(page, pagelist, lru) {
		item->pages[page->index].must_update=1;
	}
	printk(KERN_ALERT "ssd1963_update() occurred!\n");
	//Copy changed pages.
	for (i=0; i<item->pages_count; i++) {
		//ToDo: Small race here between checking and setting must_update,
		//maybe lock?
		if (item->pages[i].must_update) {
			item->pages[i].must_update=0;
			ssd1963_copy(item, i);
		}
	}

}

//#define GPIOSET(no, ishigh)   { if (ishigh) set|=(1<<no); else reset|=(1<<no); } while(0)

//#define GPIOSET(no, ishigh)   { if (ishigh) set|=(1<<no); else reset|=(1<<no); } while(0)

#define GPIOSET(no, ishigh) \
do {                        \
   if (ishigh)              \
      set |= (1 << (no));   \
   else                     \
      reset |= (1 << (no)); \
} while (0)

// writel(set, __io_address(GPIO_BASE+0x1C));
// writel(reset, __io_address(GPIO_BASE+0x28));

static void __init ssd1963_setup(struct ssd1963 *item)
{
   unsigned int set=0;
   unsigned int reset=0;
 //  printk(KERN_ALERT "ssd1963_setup() called\n");

	int x;
	int y;
	dev_dbg(item->dev, "%s: item=0x%p\n", __func__,(void *)item);

	ssd1963_gpio_init();

	SSD1963_GPIOSET(LCD_NRST);

	msleep(50);
	SSD1963_GPIORESET(LCD_NRST);

	msleep(100);
	SSD1963_GPIOSET(LCD_NRST);
	SSD1963_GPIORESET(LCD_NCS);

	SSD1963_GPIOSET(LCD_BACKLIGHT);
	SSD1963_GPIOSET(LCD_NWR);

   msleep(20);

   ssd1963_setDisplayRegister(0x00E2, 0x002D,                 PARAM);               // PLL config
   ssd1963_setDisplayRegister(NOCMD,  0x0002,                 PARAM);
   ssd1963_setDisplayRegister(NOCMD,  0x0004,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x00E0, 0x0001,                 PARAM);   msleep(1U); // PLL config - continued
   ssd1963_setDisplayRegister(0x00E0, 0x0003,                 PARAM);   msleep(5U); // PLL config - continued
   ssd1963_setDisplayRegister(0x0001, 0x0000,                 NOPARAM); msleep(5U); // software reset
   ssd1963_setDisplayRegister(0x00E6, 0x0000,                 PARAM);               // LSHIFT freq
   ssd1963_setDisplayRegister(NOCMD,  0x00FF,                 PARAM);
   ssd1963_setDisplayRegister(NOCMD,  0x00BE,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x00B0, 0x0020,                 PARAM);   msleep(1U); // set lcd mode
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  ((HDP >> 8U) & 0x00FF), PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (HDP & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  ((HDP >> 8U) & 0x00FF), PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (VDP & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(5U);
   ssd1963_setDisplayRegister(0x00B4, ((HT >> 8U) & 0x00FF),  PARAM);   msleep(1U); // horizontal period
   ssd1963_setDisplayRegister(NOCMD,  (HT & 0x00FF),          PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  ((HPS >> 8U) & 0x00FF), PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (HPS & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  HPW,                    PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  ((LPS >> 8U) & 0x00FF), PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (LPS & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x00B6, ((VT >> 8U) & 0x00FF),  PARAM);   msleep(1U); // vertical period
   ssd1963_setDisplayRegister(NOCMD,  (VT & 0x00FF),          PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (VPS >> 8U) & 0x00FF,   PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (VPS & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  VPW,                    PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  ((FPS >> 8U) & 0x00FF), PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  (FPS & 0x00FF),         PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x0036, 0x0000,                 PARAM);   msleep(1U); // rotation - landscape
   ssd1963_setDisplayRegister(0x00F0, 0x0003,                 PARAM);   msleep(5U); // pixel data interface 16 bit    0b011 is 16 Bit
   ssd1963_setDisplayRegister(0x0029, 0x0000,                 NOPARAM); msleep(1U); // set display on
   ssd1963_setDisplayRegister(0x00BE, 0x0006,                 PARAM);   msleep(1U); // pwm config
   ssd1963_setDisplayRegister(NOCMD,  0x00F0,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x0001,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x00F0,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x00D0, 0x000D,                 PARAM);   msleep(1U); // pwm coffig continued
   ssd1963_setDisplayRegister(0x00B8, 0x0000,                 PARAM);   msleep(1U); // gpio config
   ssd1963_setDisplayRegister(NOCMD,  0x0000,                 PARAM);   msleep(1U);
   ssd1963_setDisplayRegister(0x00BA, 0x0000,                 PARAM);   msleep(1U); // gpio to 0x00


   //writel(1<<LCD_NCS, __io_address(GPIO_BASE+0x1C));

	ssd1963_setWindow(0,0, TFT_WIDTH_UI16-1, TFT_HEIGHT_UI16-1);
	for(x = 0; x < TFT_WIDTH_UI16*TFT_HEIGHT_UI16; x++)
	   ssd1963_writeword(0x5555, DATA);

	//printk(KERN_ALERT "ssd1963_setup() Screen cleared\n");

	ssd1963_setWindow(0,0, TFT_WIDTH_UI16-1, TFT_HEIGHT_UI16-1);
	for (y=0; y < item->pages_count; y++)
	{
	   for (x=0; x<item->pages[y].len; x++)
	   {
	      ssd1963_writeword(item->pages[y].buffer[x], DATA);
	   }
	}


	   SSD1963_GPIOSET(LCD_NCS);
	   //msleep(10000);
	//printk(KERN_ALERT "ssd1963_setup() end\n");
}
#undef GPIOSET


//This routine will allocate the buffer for the complete framebuffer. This
//is one continuous chunk of 16-bit pixel values; userspace programs
//will write here.
static int __init ssd1963_video_alloc(struct ssd1963 *item)
{
	unsigned int frame_size;

	dev_dbg(item->dev, "%s: item=0x%p\n", __func__, (void *)item);

	frame_size = item->info->fix.line_length * item->info->var.yres;
	dev_dbg(item->dev, "%s: item=0x%p frame_size=%u\n",
		__func__, (void *)item, frame_size);

	item->pages_count = frame_size / PAGE_SIZE;
	if ((item->pages_count * PAGE_SIZE) < frame_size) {
		item->pages_count++;
	}
	dev_dbg(item->dev, "%s: item=0x%p pages_count=%u\n",
		__func__, (void *)item, item->pages_count);

	item->info->fix.smem_len = item->pages_count * PAGE_SIZE;
	item->info->fix.smem_start =
	    (unsigned long)vmalloc(item->info->fix.smem_len);
	if (!item->info->fix.smem_start) {
		dev_err(item->dev, "%s: unable to vmalloc\n", __func__);
		return -ENOMEM;
	}
	memset((void *)item->info->fix.smem_start, 0, item->info->fix.smem_len);

	return 0;
}

static void ssd1963_video_free(struct ssd1963 *item)
{
	dev_dbg(item->dev, "%s: item=0x%p\n", __func__, (void *)item);

	kfree((void *)item->info->fix.smem_start);
}

//This routine will allocate a ssd1963_page struct for each vm page in the
//main framebuffer memory. Each struct will contain a pointer to the page
//start, an x- and y-offset, and the length of the pagebuffer which is in the framebuffer.
static int __init ssd1963_pages_alloc(struct ssd1963 *item)
{
	unsigned short pixels_per_page;
	unsigned short yoffset_per_page;
	unsigned short xoffset_per_page;
	unsigned int index;
	unsigned short x = 0;
	unsigned short y = 0;
	unsigned short *buffer;
	unsigned short *oldbuffer;
	unsigned int len;

	dev_dbg(item->dev, "%s: item=0x%p\n", __func__, (void *)item);

	item->pages = kmalloc(item->pages_count * sizeof(struct ssd1963_page),
			      GFP_KERNEL);
	if (!item->pages) {
		dev_err(item->dev, "%s: unable to kmalloc for ssd1963_page\n",
			__func__);
		return -ENOMEM;
	}

	pixels_per_page = PAGE_SIZE / (item->info->var.bits_per_pixel / 8);
	yoffset_per_page = pixels_per_page / item->info->var.xres;
	xoffset_per_page = pixels_per_page -
	    (yoffset_per_page * item->info->var.xres);
	dev_dbg(item->dev, "%s: item=0x%p pixels_per_page=%hu "
		"yoffset_per_page=%hu xoffset_per_page=%hu\n",
		__func__, (void *)item, pixels_per_page,
		yoffset_per_page, xoffset_per_page);

	oldbuffer = kmalloc(item->pages_count * pixels_per_page * 2,
			      GFP_KERNEL);
	if (!oldbuffer) {
		dev_err(item->dev, "%s: unable to kmalloc for ssd1963_page oldbuffer\n",
			__func__);
		return -ENOMEM;
	}

	buffer = (unsigned short *)item->info->fix.smem_start;
	for (index = 0; index < item->pages_count; index++) {
		len = (item->info->var.xres * item->info->var.yres) -
		    (index * pixels_per_page);
		if (len > pixels_per_page) {
			len = pixels_per_page;
		}
		dev_dbg(item->dev,
			"%s: page[%d]: x=%3hu y=%3hu buffer=0x%p len=%3hu\n",
			__func__, index, x, y, buffer, len);
		item->pages[index].x = x;
		item->pages[index].y = y;
		item->pages[index].buffer = buffer;
		item->pages[index].oldbuffer = oldbuffer;
		item->pages[index].len = len;

		x += xoffset_per_page;
		if (x >= item->info->var.xres) {
			y++;
			x -= item->info->var.xres;
		}
		y += yoffset_per_page;
		buffer += pixels_per_page;
		oldbuffer += pixels_per_page;
	}

	return 0;
}

static void ssd1963_pages_free(struct ssd1963 *item)
{
	dev_dbg(item->dev, "%s: item=0x%p\n", __func__, (void *)item);

	kfree(item->pages);
}

static inline __u32 CNVT_TOHW(__u32 val, __u32 width)
{
	return ((val<<width) + 0x7FFF - val)>>16;
}

//This routine is needed because the console driver won't work without it.
static int ssd1963_setcolreg(unsigned regno,
			       unsigned red, unsigned green, unsigned blue,
			       unsigned transp, struct fb_info *info)
{
	int ret = 1;

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	if (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
				      7471 * blue) >> 16;
	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			u32 *pal = info->pseudo_palette;
			u32 value;

			red = CNVT_TOHW(red, info->var.red.length);
			green = CNVT_TOHW(green, info->var.green.length);
			blue = CNVT_TOHW(blue, info->var.blue.length);
			transp = CNVT_TOHW(transp, info->var.transp.length);

			value = (red << info->var.red.offset) |
				(green << info->var.green.offset) |
				(blue << info->var.blue.offset) |
				(transp << info->var.transp.offset);

			pal[regno] = value;
			ret = 0;
		}
		break;
	case FB_VISUAL_STATIC_PSEUDOCOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		break;
	}
	return ret;
}

static int ssd1963_blank(int blank_mode, struct fb_info *info)
{
	struct ssd1963 *item = (struct ssd1963 *)info->par;
	if (blank_mode == FB_BLANK_UNBLANK)
		item->backlight=1;
	else
		item->backlight=0;
	//Item->backlight won't take effect until the LCD is written to. Force that
	//by dirty'ing a page.
	item->pages[0].must_update=1;
	printk(KERN_ALERT "ssd1963_blank() occurred!\n");
	schedule_delayed_work(&info->deferred_work, 0);
	return 0;
}

static void ssd1963_touch(struct fb_info *info, int x, int y, int w, int h)
{
	struct fb_deferred_io *fbdefio = info->fbdefio;
	struct ssd1963 *item = (struct ssd1963 *)info->par;
	int i, ystart, yend;
	if (fbdefio) {
		//Touch the pages the y-range hits, so the deferred io will update them.
		for (i=0; i<item->pages_count; i++) {
			ystart=item->pages[i].y;
			yend=item->pages[i].y+(item->pages[i].len/info->fix.line_length)+1;
			if (!((y+h)<ystart || y>yend)) {
				item->pages[i].must_update=1;
			}
		}
		//Schedule the deferred IO to kick in after a delay.
		schedule_delayed_work(&info->deferred_work, fbdefio->delay);
	}
}

static void ssd1963_fillrect(struct fb_info *p, const struct fb_fillrect *rect)
{
	sys_fillrect(p, rect);
	ssd1963_touch(p, rect->dx, rect->dy, rect->width, rect->height);
}

static void ssd1963_imageblit(struct fb_info *p, const struct fb_image *image)
{
	sys_imageblit(p, image);
	ssd1963_touch(p, image->dx, image->dy, image->width, image->height);
}

static void ssd1963_copyarea(struct fb_info *p, const struct fb_copyarea *area)
{
	sys_copyarea(p, area);
	ssd1963_touch(p, area->dx, area->dy, area->width, area->height);
}

static ssize_t ssd1963_write(struct fb_info *p, const char __user *buf,
				size_t count, loff_t *ppos)
{
	ssize_t res;
	res = fb_sys_write(p, buf, count, ppos);
	ssd1963_touch(p, 0, 0, p->var.xres, p->var.yres);
	return res;
}

static struct fb_ops ssd1963_fbops = {
	.owner        = THIS_MODULE,
	.fb_read      = fb_sys_read,
	.fb_write     = ssd1963_write,
	.fb_fillrect  = ssd1963_fillrect,
	.fb_copyarea  = ssd1963_copyarea,
	.fb_imageblit = ssd1963_imageblit,
	.fb_setcolreg = ssd1963_setcolreg,
	.fb_blank	  = ssd1963_blank,
};

static struct fb_fix_screeninfo ssd1963_fix __initdata = {
	.id          = "SSD1963",
	.type        = FB_TYPE_PACKED_PIXELS,
	.visual      = FB_VISUAL_TRUECOLOR,
	.accel       = FB_ACCEL_NONE,
	.line_length = 480 * 2,
};

static struct fb_var_screeninfo ssd1963_var __initdata = {
	.xres		         = 480,
	.yres		         = 272,
	.xres_virtual	   = 480,
	.yres_virtual	   = 272,
	.width		      = 480,
	.height		      = 272,
	.bits_per_pixel	= 16,
	.red		         = {11, 5, 0},
	.green		      = {5, 6, 0},
	.blue		         = {0, 5, 0},
	.activate	      = FB_ACTIVATE_NOW,
	.vmode		      = FB_VMODE_NONINTERLACED,
};

static struct fb_deferred_io ssd1963_defio = {
        .delay          = HZ,
        .deferred_io    = &ssd1963_update,
};

static int __init ssd1963_probe(struct platform_device *dev)
{
	int ret = 0;
	struct ssd1963 *item;
	struct fb_info *info;

	dev_dbg(&dev->dev, "%s\n", __func__);

	item = kzalloc(sizeof(struct ssd1963), GFP_KERNEL);
	if (!item) {
		dev_err(&dev->dev,
			"%s: unable to kzalloc for ssd1963\n", __func__);
		ret = -ENOMEM;
		goto out;
	}
	item->dev = &dev->dev;
	dev_set_drvdata(&dev->dev, item);
	item->backlight=1;


	info = framebuffer_alloc(sizeof(struct ssd1963), &dev->dev);
	if (!info) {
		ret = -ENOMEM;
		dev_err(&dev->dev,
			"%s: unable to framebuffer_alloc\n", __func__);
		goto out_item;
	}
	info->pseudo_palette = &item->pseudo_palette;
	item->info = info;
	info->par = item;
	info->dev = &dev->dev;
	info->fbops = &ssd1963_fbops;
	info->flags = FBINFO_FLAG_DEFAULT|FBINFO_VIRTFB;
	info->fix = ssd1963_fix;
	info->var = ssd1963_var;

	ret = ssd1963_video_alloc(item);
	if (ret) {
		dev_err(&dev->dev,
			"%s: unable to ssd1963_video_alloc\n", __func__);
		goto out_info;
	}
	info->screen_base = (char __iomem *)item->info->fix.smem_start;

	ret = ssd1963_pages_alloc(item);
	if (ret < 0) {
		dev_err(&dev->dev,
			"%s: unable to ssd1963_pages_init\n", __func__);
		goto out_video;
	}

	info->fbdefio = &ssd1963_defio;
	fb_deferred_io_init(info);

	ret = register_framebuffer(info);
	if (ret < 0) {
		dev_err(&dev->dev,
			"%s: unable to register_frambuffer\n", __func__);
		goto out_pages;
	}


	ssd1963_setup(item);
	ssd1963_update_all(item);

	return ret;

out_pages:
	ssd1963_pages_free(item);
out_video:
	ssd1963_video_free(item);
out_info:
	framebuffer_release(info);
out_item:
	kfree(item);
out:
	return ret;
}


static int ssd1963_remove(struct platform_device *dev)
{
	struct fb_info *info = dev_get_drvdata(&dev->dev);
	struct ssd1963 *item = (struct ssd1963 *)info->par;
	unregister_framebuffer(info);
	ssd1963_pages_free(item);
	ssd1963_video_free(item);
	framebuffer_release(info);
	kfree(item);
	return 0;
}

#ifdef CONFIG_PM
static int ssd1963_suspend(struct platform_device *dev, pm_message_t state)
{
//	struct fb_info *info = dev_get_drvdata(&spi->dev);
//	struct ssd1963 *item = (struct ssd1963 *)info->par;
	/* enter into sleep mode */
//	ssd1963_reg_set(item, SSD1963_REG_SLEEP_MODE, 0x0001);
	return 0;
}

static int ssd1963_resume(struct platform_device *dev)
{
//	struct fb_info *info = dev_get_drvdata(&spi->dev);
//	struct ssd1963 *item = (struct ssd1963 *)info->par;
	/* leave sleep mode */
//	ssd1963_reg_set(item, SSD1963_REG_SLEEP_MODE, 0x0000);
	return 0;
}
#else
#define ssd1963_suspend NULL
#define ssd1963_resume NULL
#endif

static struct platform_driver ssd1963_driver = {
	.probe = ssd1963_probe,
	.remove = ssd1963_remove,
	.driver = {
		   .name = "ssd1963",
		   },
};

static int __init ssd1963_init(void)
{
	int ret = 0;

	pr_debug("%s\n", __func__);

	ret = platform_driver_register(&ssd1963_driver);
	if (ret) {
		pr_err("%s: unable to platform_driver_register\n", __func__);
	}

	return ret;
}

module_init(ssd1963_init);
module_remove(ssd1963_remove);


MODULE_DESCRIPTION("SSD1963 LCD Driver");
MODULE_AUTHOR("Jeroen Domburg <jeroen@spritesmods.com>");
MODULE_AUTHOR("Armin Schlegel <armin.schlegel@gmx.de");
MODULE_LICENSE("GPL");
