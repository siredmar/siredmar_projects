/*
 * Set/Unset a single pixel on the display
 *
 * For choosing the correct entry within the data structure (disp_ram[])
 * first the concerning page of this pixel has to be determined. This
 * is done by dividing the Y coordinate by 8 (or better: do a right shift
 * of 3 bits). For choosing the entry in the array, the X coordinate multiplied
 * by 8 (or better: left shifted by 3) has to be added to the actual page number.
 * The exact bit that shall be set/unset is determined by using the bitmask
 * (y & 0x07). This selects the exact row of the respective memory page.
 *
 * Parameters:
 *   x  X coordinate of the pixel
 *   y  Y coordinate of the pixel
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