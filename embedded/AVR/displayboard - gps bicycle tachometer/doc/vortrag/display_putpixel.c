void display_putpixel(unsigned char x, unsigned char y, uint8_t pixel_status)
{
   if (x < DISP_WIDTH && y < DISP_HEIGHT) {
      if (pixel_status == PIXEL_ON)
         disp_ram[(y >> 3) + (x << 3)] |= (1 << (y & 0x07));
      else
         disp_ram[(y >> 3) + (x << 3)] &= ~(1 << (y & 0x07));
    }
}