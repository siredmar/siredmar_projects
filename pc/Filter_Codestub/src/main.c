#include "../inc/std_types.h"
#include "../inc/filter_types.h"
#include "draw_handler.h"
#include "event_handler.h"

#define SCREENWIDTH     480
#define SCREENHEIGHT    572
#define SCREENDEPTH     16

#define IMAGEHEIGHT 272
#define IMAGEWIDTH  480

#define ORG_X_OFFSET 0
#define ORG_Y_OFFSET 0

#define MOD_X_OFFSET 0
#define MOD_Y_OFFSET 300



image_rgb888float_type
convert565to888float (uint16 pixel)
{
   image_rgb888float_type returnvalue;
   returnvalue.R = (float)((pixel & 0xF800) >> 8);
   returnvalue.G = (float)((pixel & 0x07E0) >> 3);
   returnvalue.B = (float)((pixel & 0x001F) << 3);

   return returnvalue;
}

image_rgb888int_type
convert565to888int (uint16 pixel)
{
   image_rgb888int_type returnvalue;
   returnvalue.R = (uint8)((pixel & 0xF800) >> 8);
   returnvalue.G = (uint8)((pixel & 0x07E0) >> 3);
   returnvalue.B = (uint8)((pixel & 0x001F) << 3);

   return returnvalue;
}

uint16
convert888floatto565 (image_rgb888float_type pixel)
{
   uint16 returnvalue;

   //returnvalue = (uint16)((((uint16)pixel.R << 8) & 0xF800)) | (uint16)(((uint16)pixel.G << 3) & 0x07E0) | (uint16)(((uint16)pixel.B >> 3) & 0x001F);
   returnvalue = (uint16)((((((uint16)pixel.R) << 8) & 0xF800)) | ((((uint16)pixel.G) << 3) & 0x07E0) | ((((uint16)pixel.B) >> 3) & 0x001F));
   //  printf("Float: R: %f, G: %f, B: %f, RGB565: %d\n", pixel.R, pixel.B, pixel.G, returnvalue);
   return returnvalue;

}


void
drawFramebuffer (SDL_Surface * screen, framebuffer_type fb, uint16 xpos, uint16 ypos)
{
   uint16 x, y;
   for (y = 0; y < fb.yres; y++)
   {
      for (x = 0; x < fb.xres; x++)
      {
         drawPixel (screen, x + xpos, y + ypos,
               convert565to888int (fb.content[y * IMAGEWIDTH + x]));
      }
   }
}



image_rgb888float_type multiplyRGB888(image_rgb888float_type a, float b)
{
   image_rgb888float_type returnvalue;

   returnvalue.R = a.R * b;
   returnvalue.G = a.G * b;
   returnvalue.B = a.B * b;
   return returnvalue;
}
image_rgb888float_type normalizeRGB888(image_rgb888float_type a, float normalize)
{
   image_rgb888float_type returnvalue;
   returnvalue.R = a.R / (normalize);
   returnvalue.G = a.G / (normalize);
   returnvalue.B = a.B / (normalize);
   return returnvalue;
}

void
printFilterCoeffs(filter_type filter)
{
   int cnt1, cnt2;
   printf("Filter Koeffizienten von: %s\n", filter.name);
   for(cnt1 = 0; cnt1 < filter.y_dimension; cnt1++)
   {
      for(cnt2 = 0; cnt2 < filter.x_dimension; cnt2++)
      {
         printf("%f\t", filter.coeff[cnt1*filter.y_dimension + cnt2]);
      }
      printf("\n");
   }
   printf("\n");
};


framebuffer_type filterFramebuffer(framebuffer_type source_framebuffer, filter_type filter)
{
   framebuffer_type filtered_framebuffer;
   uint16 *pixel_to_be_filtered = (uint16*) malloc(sizeof(uint16) * filter.x_dimension * filter.y_dimension);

   uint16 *content = (uint16*) malloc(sizeof(uint16) * source_framebuffer.xres * source_framebuffer.yres );
   filtered_framebuffer.content = content;
   uint16 xres, yres, pixelx, pixely, filter_element;//, filterx, filtery;
   sint16 filterx, filtery;
   uint32 pixel;
   xres = source_framebuffer.xres;
   yres = source_framebuffer.yres;
   printf("xres: %d, yres: %d\n", xres, yres);
   filtered_framebuffer.xres = source_framebuffer.xres;
   filtered_framebuffer.yres = source_framebuffer.yres;
   filtered_framebuffer.x_offset = 0;
   filtered_framebuffer.y_offset = 300;

   image_rgb888float_type tempRGBPoint, tempRGBPoint2;


   /* For every pixel on the screen... */
   for(pixel = 0; pixel < (yres*xres); pixel++)
   {
      /* Set initial value of filtered pixel to 0 */
      filtered_framebuffer.content[pixel] = 0;
      /* ... and every pixel on the filtermask */
      pixelx = pixel % xres;
      pixely = pixel / xres;
      filterx = -filter.x_dimension / 2;
      filtery = -filter.y_dimension / 2;

      for(filter_element = 0; filter_element < (filter.x_dimension*filter.y_dimension); filter_element++)
      {

         if(filterx < filter.x_dimension / 2)
            filterx++;
         else
            filterx = -filter.x_dimension / 2;

         if(filtery < filter.y_dimension / 2)
            filtery++;
         else
            filtery = -filter.y_dimension / 2;


         if((pixelx + filterx) >= 0 && (pixely + filtery) >= 0 &&
               (pixelx + filterx) <= xres && (pixely + filtery) <= yres)
            pixel_to_be_filtered[filter_element] = source_framebuffer.content[pixelx + filterx + (pixely + filtery) * xres];
         else
            pixel_to_be_filtered[filter_element] = 0;

         /* do the Filtering */
         /* multiply and accumulate (MAC) every pixel of the image with overlaying mask */
         tempRGBPoint2 = convert565to888float(pixel_to_be_filtered[filter_element]);
         tempRGBPoint.R += tempRGBPoint2.R * filter.coeff[filter_element];
         tempRGBPoint.G += tempRGBPoint2.G * filter.coeff[filter_element];
         tempRGBPoint.B += tempRGBPoint2.B * filter.coeff[filter_element];
      }

      /* Normalize the pixel */
      if(tempRGBPoint.R <= 0)
         tempRGBPoint.R = 0;
      if(tempRGBPoint.G <= 0)
         tempRGBPoint.G = 0;
      if(tempRGBPoint.B <= 0)
         tempRGBPoint.B = 0;
      if(filter.inv_normalization > 0.0)
      {
         tempRGBPoint.R = tempRGBPoint.R / filter.inv_normalization;
         tempRGBPoint.G = tempRGBPoint.G / filter.inv_normalization;
         tempRGBPoint.B = tempRGBPoint.B / filter.inv_normalization;
      }
      filtered_framebuffer.content[pixel] = convert888floatto565(tempRGBPoint);
   }
   return filtered_framebuffer;
}

filter_type initFilter(uint16 xdim, uint16 ydim, float* coeff, char *name)
{
   filter_type filter;
   uint16 row, line;
   filter.x_dimension = xdim;
   filter.y_dimension = ydim;
   filter.inv_normalization = 0;
   filter.name = (char*) malloc(sizeof(char) * strlen(name) + 1);
   filter.name = name;
   filter.coeff = (float*) malloc(sizeof(float) * xdim * ydim);
   filter.coeff = coeff;
   for(line = 0; line < ydim; line++){
      for(row = 0; row < xdim; row++){
         filter.inv_normalization += filter.coeff[row*xdim + line];
      }
   }
   //
   //      filter.inv_normalization = 1.0;
   return filter;
}

framebuffer_type initFramebuffer(uint16* content, uint16 xres, uint16 yres, uint16 xoffset, uint16 yoffset)
{
   framebuffer_type framebuffer;
   framebuffer.xres = xres;
   framebuffer.yres = yres;
   framebuffer.x_offset = xoffset;
   framebuffer.y_offset = yoffset;
   framebuffer.content = content;
   return framebuffer;
}

int
main (int  argc, char * argv[])
{
   boolean quit = FALSE;
   SDL_Surface *screen;
   FILE *fb;

   if(argc < 2)
   {
      printf("Error: Need framebuffer output as argument!\n");
      printf("%s framebufferoutput \n",*argv);
      exit(1);
   }

   if (SDL_Init (SDL_INIT_VIDEO) < 0)
   {
      fprintf (stderr, "Konnte SDL nicht initialisieren: %s\n",
            SDL_GetError ());
      exit (-1);
   }
   screen = SDL_SetVideoMode (SCREENWIDTH, SCREENHEIGHT, SCREENDEPTH,
         SDL_SWSURFACE);

   if (screen < 0)
   {
      fprintf (stderr, "Konnte video mode nicht setzen: %s\n",
            SDL_GetError ());
   }
   atexit (SDL_Quit);
   // Algorithm start

   fb = fopen (argv[1], "rb");
   if (fb == NULL)
   {
      fprintf (stderr, "Konnte Bild nicht laden\n");
      exit (-1);
   }

   /* Init Framebuffer */
   framebuffer_type source_framebuffer;
   uint16 buf_source[IMAGEHEIGHT * IMAGEWIDTH * sizeof(uint16)];
   fseek (fb, 0, SEEK_SET);
   fread (buf_source, 1, IMAGEWIDTH * IMAGEHEIGHT * sizeof(uint16), fb);
   source_framebuffer = initFramebuffer(buf_source, IMAGEWIDTH, IMAGEHEIGHT, ORG_X_OFFSET, ORG_Y_OFFSET);
   fclose(fb);
   /* Init Gauss Filter */
   filter_type filter;

   //      float filter_coeff[5][5] = {
   //            {1, 4,  7,  4,  1},
   //            {4, 16, 26, 16, 4},
   //            {7, 26, 41, 26, 7},
   //            {4, 16, 26, 16, 4},
   //            {1, 4,  7,  4,  1}};
   //      filter = initFilter(5, 5, filter_coeff, "Gauss-Filter");

            float filter_coeff[5][5] = {
                  {1, 4,  6,  4,  1},
                  {4, 16, 24, 16, 4},
                  {6, 24, 36, 24, 6},
                  {4, 16, 24, 16, 4},
                  {1, 4,  6,  4,  1}};
            filter = initFilter(5, 5, filter_coeff, "Gauss-Filter");

   //      float filter_coeff[3][3] = {
   //            {1, 2, 1},
   //            {2, 4, 2},
   //            {1, 2, 1}};
   //      filter = initFilter(3, 3, filter_coeff, "Gauss-Filter");

   //   float filter_coeff[3][3] = {
   //         {-3, -6, -3},
   //         {-6, 50, -6},
   //         {-3, -6, -3}};
   //   filter = initFilter(3, 3, filter_coeff, "Hochpass-Filter");

   //      float filter_coeff[3][3] = {
   //            {1.0, 1.0, 1.0},
   //            {1.0, 1.0, 1.0},
   //            {1.0, 1.0, 1.0}};
   //      filter = initFilter(3, 3, filter_coeff, "Mittelwert-Filter");

   //         float filter_coeff[3][3] = {
   //               {-1, -2, -1},
   //               {0, 0, 0},
   //               {1, 2, 1}};
   //         filter = initFilter(3, 3, filter_coeff, "Soebel-Filter");

   //            float filter_coeff[3][3] = {
   //                  {0, -1, 0},
   //                  {-1, 4, -1},
   //                  {0, -1, 0}};
   //            filter = initFilter(3, 3, filter_coeff, "Laplace-Operator-Filter");

//         float filter_coeff[3][3] = {
//               {-1.0, -1.0, -1.0},
//               {-1.0, 9.0, -1.0},
//               {-1.0, -1.0, -1.0}};
//         filter = initFilter(3, 3, filter_coeff, "Hochpass-Filter");

//   float filter_coeff[3][3] = {
//         {0, -0.25, 0},
//         {-0.25, 2.0, -0.25},
//         {0, -0.25, 0}};
//   filter = initFilter(3, 3, filter_coeff, "Laplace-Operator-Filter");

//         float filter_coeff[3][3] = {
//               {0.11, 0.11, 0.11},
//               {0.11, 0.11, 0.11},
//               {0.11, 0.11, 0.11}};
//         filter = initFilter(3, 3, filter_coeff, "Mittelwert-Filter");


   printf("%s: xdim: %d, ydim: %d, norm: %f\n", filter.name, filter.x_dimension, filter.y_dimension, filter.inv_normalization);
   printFilterCoeffs(filter);
   framebuffer_type filtered_framebuffer;

   filtered_framebuffer = filterFramebuffer(source_framebuffer, filter);

   drawFramebuffer (screen, source_framebuffer, 0, 0);
   drawFramebuffer (screen, filtered_framebuffer, 0, 300);


   // SDL_BlitSurface(image, 0, screen, 0);
   SDL_UpdateRect (screen, 0, 0, 0, 0);

   // Algorithm stop
   while (quit == FALSE)
   {
      quit = main_loop_handle();

   }
   exit (0);
}
