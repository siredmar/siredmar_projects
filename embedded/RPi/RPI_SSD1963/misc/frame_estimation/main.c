#include "../inc/std_types.h"

#include "dio/dio.h"
#include "tft/tft.h"
#include <time.h>

#define BENCHMARK FALSE
#define MAIN   4



#define CYCLES 250
int main()
{
#if BENCHMARK == TRUE
   struct timeval  start, stop;
   double start_mil;
   double stop_mil;
   double time_diff;
#endif
   //clock_t ticks; long count;


   printf("dio_init() called\n");
   dio_init();
   printf("dio_init() returned\n");


   printf("tft_init() called\n");
   tft_init(&tft_initialConfigTft_s);
   printf("tft_init() returned\n");

   tft_selectBacklight();
   tft_clearScreen(BLACK);




#if BENCHMARK == TRUE
   uint16 cmp = 0;
   uint16 cnt_ui16 = 0;
   //////
//   printf("tft_drawRectangle() called\n");
//   tft_drawRectangle(5, 5,   10, 10, (tft_stdColorsType)YELLOW);
//   printf("tft_drawRectangle() returned\n");
   //    tft_drawRectangle(50,  100, 300, 150, (tft_stdColorsType)BLUE);
//    tft_drawRectangle(10,  10,  50,  75,  (tft_stdColorsType)YELLOW);
//    tft_drawRectangle(90,  200, 100, 5,   (tft_stdColorsType)CYAN);
//    tft_drawRectangle(280, 30,  5,   200, (tft_stdColorsType)RED);


   //time(&start);
   gettimeofday(&start, NULL);
   while(cmp < CYCLES)
    {
       cmp++;
       tft_clearScreen(cmp);
    }
   gettimeofday(&stop, NULL);

   start_mil =  (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
   stop_mil =  (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
   time_diff = stop_mil - start_mil;

   printf("Finished in about %f seconds. \n", time_diff);
   printf("%d Frames sent in %f seconds. -> FPS: %f\n", cmp, time_diff, (cmp/(time_diff/1000)));
#endif

#if BENCHMARK == FALSE

   /* Use MAIN 1 for fullscreen updates! */
#if MAIN == 1
   uint16 buf_display[TFT_WIDTH_UI16 * TFT_HEIGHT_UI16 * 2];  // the current display content
   uint16 buf_source[TFT_WIDTH_UI16 * TFT_HEIGHT_UI16 * 2];   // the source framebuffer content
   FILE *fb;
 int i, j;

   fb = fopen("/dev/fb0", "rb");
      // run forever...
      while (1) {
      fseek(fb, 0, SEEK_SET);   // rewind source framebuffer
      fread(buf_source, 1, TFT_WIDTH_UI16 * TFT_HEIGHT_UI16 * 2, fb);  // read complete source framebuffer


                   tft_setWindow(0, 0, TFT_WIDTH_UI16-1, TFT_HEIGHT_UI16-1);
                   tft_drawStart();
                   // re-transmit the unchanged pixels of current row up to here
                   for (j = 0; j < TFT_WIDTH_UI16*TFT_HEIGHT_UI16; j++) {
                       tft_sendPixelData(buf_source[j]);
                   }




      usleep(5000L);     // sleep for 50ms
      }

      // actually we never get here
      fclose(fb);
#endif

/* Use MAIN 2 for line based update */
#if MAIN == 2
int y, x, j, i;

        // open the source framebuffer device
        FILE* fb=fopen("/dev/fb0","rb");

        // allocate two buffers for tracking the source framebuffer changes
        uint16 buf_display [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the current display content
        uint16 buf_source  [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the source framebuffer content

        // run forever...
        while(TRUE){
         fseek(fb, 0, SEEK_SET);         // rewind source framebuffer
         fread(buf_source, 1, TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2, fb);  // read complete source framebuffer

         // statistics
         uint32 changed=0; // how many pixels have changed since last refresh
         uint32  drawed=0; // how many pixel actualy where transmitted since last refresh

         // state for merging adjacent changes into one transmission
         uint32 i=0;           // current pixel index
         boolean drawing = FALSE;     // if pixels are currently transmitted
         uint32 lastChange=0;  // index of first pixel of this transmission

         // for all pixels on screen...
         for(y=0; y<TFT_HEIGHT_UI16; y++){
          for(x=0; x<TFT_WIDTH_UI16; x++){
            uint16 color=buf_source[i]; // get this pixels source color
            if (color!=buf_display[i]){
             // the pixel has changed
             changed++;
             lastChange=i; // store last change index
             if(!drawing){
              // whe are not drawing, so start a run here.
              // we only draw full rows:
              // set display area to the rest of the screen, including this row
              tft_setWindow(0,y,TFT_WIDTH_UI16-1,TFT_HEIGHT_UI16-1);
              tft_drawStart();
              // re-transmit the unchanged pixels of current row up to here
              for(j=0; j<x; j++)
               tft_sendPixelData(buf_display[y*TFT_WIDTH_UI16+j]);
              drawing=TRUE;
             }
            }

            if(drawing){
             // where in a transmission run.
             tft_sendPixelData(color);     // send pixel
             buf_display[i]=color;// store change
             drawed++;
             // end transmission, if the was no change for some time
             if(i>lastChange+400) {
              // stop drawing, lcd actually gets updated.
              tft_drawStop();
              drawing=FALSE;
             }
            }

            i++;
          }
         }
        // if(changed>0) printf("Pixels changed: %i, drawed: %i\n",changed,drawed);
         usleep(10000L); // sleep for 40ms
        }

        // actually we never get here
        fclose(fb);
#endif

/* this routine sends every pixel by itself */

#if MAIN == 3
        int y, x, j, i;

                // open the source framebuffer device
                FILE* fb=fopen("/dev/fb0","rb");

                // allocate two buffers for tracking the source framebuffer changes
                uint16 buf_display [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the current display content
                uint16 buf_source  [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the source framebuffer content

                // run forever...
                while(TRUE){
                 fseek(fb, 0, SEEK_SET);         // rewind source framebuffer
                 fread(buf_source, 1, TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2, fb);  // read complete source framebuffer

                 // statistics
                 uint32 changed=0; // how many pixels have changed since last refresh
                 uint32  drawed=0; // how many pixel actualy where transmitted since last refresh

                 // state for merging adjacent changes into one transmission
                 uint32 i=0;           // current pixel index
                 boolean drawing = FALSE;     // if pixels are currently transmitted
                 uint32 lastChange=0;  // index of first pixel of this transmission
                 uint16 color = 0;

                 // for all pixels on screen...
                 for(y=0; y<TFT_HEIGHT_UI16; y++)
                 {
                  for(x=0; x<TFT_WIDTH_UI16; x++)
                  {
                    color = buf_source[i];
                    if (color != buf_display[i])
                    {
                       buf_display[i] = color;
                       changed++;
                       tft_drawPixel(x, y, color);
                    }
                    i++;
                  }
                 }
                 printf("pixel changed: %d\n", changed);
                // if(changed>0) printf("Pixels changed: %i, drawed: %i\n",changed,drawed);
                 usleep(10000L); // sleep for 40ms
                }

                // actually we never get here
                fclose(fb);
#endif

#if MAIN == 4
#define RECTANGLE_WIDTH  8
#define RECTANGLE_HEIGHT 8
int i, j, changed, cnt, linecnt;
int xstart, xend, ystart, yend;

// open the source framebuffer device
FILE* fb=fopen("/dev/fb0","rb");

// allocate two buffers for tracking the source framebuffer changes
uint16 buf_display [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the current display content
uint16 buf_source  [TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2]; // the source framebuffer content

// run forever...
while(TRUE){
 fseek(fb, 0, SEEK_SET);         // rewind source framebuffer
 fread(buf_source, 1, TFT_WIDTH_UI16*TFT_HEIGHT_UI16*2, fb);  // read complete source framebuffer

uint16 x_rects = TFT_WIDTH_UI16/RECTANGLE_WIDTH;
uint16 y_rects = TFT_HEIGHT_UI16/RECTANGLE_HEIGHT;

uint16 display_rect[RECTANGLE_WIDTH*RECTANGLE_HEIGHT];
uint16 buffer_rect[RECTANGLE_WIDTH*RECTANGLE_HEIGHT];
uint16 buffer_rect2[RECTANGLE_WIDTH*RECTANGLE_HEIGHT];

for (j = 0; j < TFT_WIDTH_UI16*TFT_HEIGHT_UI16; j++) {
   if(buf_display[j] != buf_source[j])
   {
      changed++;
   }
}

for(i = 0; i < RECTANGLE_WIDTH; i = i + RECTANGLE_WIDTH)
{

   cnt = 0;
   j = 0;
   linecnt = 0;
   for(cnt = 0; cnt < RECTANGLE_HEIGHT; cnt++)
   {
      buffer_rect[j] = buf_source[i+linecnt+cnt*TFT_WIDTH_UI16];
      display_rect[j] = buf_display[i+linecnt+cnt*TFT_WIDTH_UI16];
      j++;
      linecnt++;
      if(linecnt > (RECTANGLE_WIDTH-1))
         linecnt = 0;
   }
   if()


//
//   buffer_rect2[0]  = buf_source[i+0+0*TFT_WIDTH_UI16];
//   buffer_rect2[1]  = buf_source[i+1+0*TFT_WIDTH_UI16];
//   buffer_rect2[2]  = buf_source[i+2+0*TFT_WIDTH_UI16];
//   buffer_rect2[3]  = buf_source[i+3+0*TFT_WIDTH_UI16];
//   buffer_rect2[4]  = buf_source[i+4+0*TFT_WIDTH_UI16];
//   buffer_rect2[5]  = buf_source[i+5+0*TFT_WIDTH_UI16];
//   buffer_rect2[6]  = buf_source[i+6+0*TFT_WIDTH_UI16];
//   buffer_rect2[7]  = buf_source[i+7+0*TFT_WIDTH_UI16];
//
//   buffer_rect2[8]  = buf_source[i+0+1*TFT_WIDTH_UI16];
//   buffer_rect2[9]  = buf_source[i+1+1*TFT_WIDTH_UI16];
//   buffer_rect2[10] = buf_source[i+2+1*TFT_WIDTH_UI16];
//   buffer_rect2[11] = buf_source[i+3+1*TFT_WIDTH_UI16];
//   buffer_rect2[12] = buf_source[i+4+1*TFT_WIDTH_UI16];
//   buffer_rect2[13] = buf_source[i+5+1*TFT_WIDTH_UI16];
//   buffer_rect2[14] = buf_source[i+6+1*TFT_WIDTH_UI16];
//   buffer_rect2[15] = buf_source[i+7+1*TFT_WIDTH_UI16];
//
//   buffer_rect2[16] = buf_source[i+0+2*TFT_WIDTH_UI16];
//   buffer_rect2[17] = buf_source[i+1+2*TFT_WIDTH_UI16];
//   buffer_rect2[18] = buf_source[i+2+2*TFT_WIDTH_UI16];
//   buffer_rect2[19] = buf_source[i+3+2*TFT_WIDTH_UI16];
//   buffer_rect2[20] = buf_source[i+4+2*TFT_WIDTH_UI16];
//   buffer_rect2[21] = buf_source[i+5+2*TFT_WIDTH_UI16];
//   buffer_rect2[22] = buf_source[i+6+2*TFT_WIDTH_UI16];
//   buffer_rect2[23] = buf_source[i+7+2*TFT_WIDTH_UI16];










}


#endif

#endif


      return 0;


}

