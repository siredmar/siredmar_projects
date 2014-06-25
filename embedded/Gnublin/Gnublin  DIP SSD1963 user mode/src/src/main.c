#include "../inc/std_types.h"

#include "dio/dio.h"
#include "tft/tft.h"

#include <time.h>
#include <stdlib.h>


/* LPC3131 UM chapter 15 */
#define IOCONFIG    0x13003000
#define CLK_REG		0x1300442C
#define wh  160560


#define BENCHMARK 0

//#if BENCHMARK == TRUE
#include <time.h>
#define CYCLES 250
//#endif
//
//#define w TFT_WIDTH_UI16
//#define h TFT_HEIGHT_UI16
//#define FBLO_GPIO   0x1C0	/* GPIO functional block */
//
//int memory_fd;
//char *memory;


int main(sint32 argc, uint8 *argv[])
{

   if(argc < 2){
      printf("usage: \ngnublin_ssd1963 device [benchmark]\n");
   }

  // uint16 buf_display[TFT_HEIGHT_UI16][TFT_WIDTH_UI16];  // the current display content
  // uint16 buf_source[TFT_HEIGHT_UI16][TFT_WIDTH_UI16];   // the source framebuffer content


  // srand(time(NULL));
  // uint16 color = rand() % 0xFFFF;


   dio_init();
   tft_init(&tft_initialConfigTft_s);
   tft_selectBacklight();
   tft_clearScreen(BLACK);

#if BENCHMARK == 1
   if(!strcmp(argv[2], "benchmark"))
   {
      //#if BENCHMARK == 1

      struct timeval start, stop;
      double start_mil;
      double stop_mil;
      double time_diff;

      uint16 cmp = 0;

      gettimeofday (&start, NULL);
      while (cmp < CYCLES)
      {
         cmp++;
         tft_clearScreen (cmp);
      }
      gettimeofday (&stop, NULL);

      start_mil = (start.tv_sec) * 1000 + (start.tv_usec) / 1000; // convert tv_sec & tv_usec to millisecond
      stop_mil = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000; // convert tv_sec & tv_usec to millisecond
      time_diff = stop_mil - start_mil;

      printf ("Finished in about %f seconds. \n", time_diff);
      printf ("%d Frames sent in %f seconds. -> FPS: %f\n", cmp, time_diff,
            (cmp / (time_diff / 1000)));
      //#endif
   }
   else
   {
#endif
#define PIXELGROUPLEN 40
      int y, x, j, i, xend;

      // open the source framebuffer device
      FILE *fb = fopen (argv[1], "rb");

      // allocate two buffers for tracking the source framebuffer changes
      uint16 buf_display[TFT_HEIGHT_UI16][TFT_WIDTH_UI16];  // the current display content
      uint16 buf_source[TFT_HEIGHT_UI16][TFT_WIDTH_UI16];   // the source framebuffer content

      for (i = 0; i < TFT_HEIGHT_UI16; i++)
      {
         for (j = 0; j < TFT_WIDTH_UI16; j++)
         {
            buf_display[i][j] = 0;
         }
      }

      // run forever...
      while (TRUE)
      {

         /* This can be speed up a little by using DMA or memcopy */
         fseek (fb, 0, SEEK_SET);   // rewind source framebuffer
         //for (i = 0; i < TFT_HEIGHT_UI16; i++){

            //fread(buf_source[i], 2, TFT_WIDTH_UI16, fb);  // read complete source framebuffer

        // }

         for (y = 0; y < TFT_HEIGHT_UI16; y++)
         {
            uint32 changed = 0;  // how many pixels have changed since last refresh
            uint32 drawed = 0;   // how many pixel actualy where transmitted since last refresh
            xend = 0;

            //fread(buf_source[y], 1, TFT_WIDTH_UI16 * 2, fb);  // read complete source framebuffer
            fread(buf_source[y], TFT_WIDTH_UI16 * 2, 1, fb);  // read complete source framebuffer

            for (x = 0; x < TFT_WIDTH_UI16; x++)
            {

               //x = i ;//% TFT_WIDTH_UI16;
               //y = lines;

               if (buf_source[y][x] != buf_display[y][x])
               {

                  changed++;
                  if ((x + PIXELGROUPLEN) > TFT_WIDTH_UI16)
                  {
                     xend = TFT_WIDTH_UI16 - 1;
                     //printf("x: %d\n", x);
                  }
                  else
                  {
                     xend = x + PIXELGROUPLEN;
                  }
                  tft_setWindow (x, y, xend, y);
                  tft_drawStart ();

                  //for(j = tmpx; j < tmpx+xend; j++)
                  for (j = x; j <= xend; j++)
                  {
                     tft_sendPixelData (buf_source[y][j]);
                     buf_display[y][j] = buf_source[y][j];
                     drawed++;
                     //   x++;
                  }
                  x = xend;
               }
            }
         }
         usleep (50000L);     // sleep for 15ms
      }
      fclose (fb);

#if BENCHMARK == 1
      }
#endif
   return 0;



}
