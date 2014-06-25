/**
 * Send a new frame to th ST-7565R display RAM
 *
 * A frame consists of 8 Pages. Each page consists of 8x128bit storage.
 *    0                                             127
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D0 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D1 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D2 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * ...
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * D7 | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * The ST-7565R display controller provides a 64 * 132(!) bit RAM. But
 * the actual display resolution of the EA DOGL128-6 is 128x64 pixel.
 * Therefore only 128 columns are used within the internal RAM of the
 * display controller.
 * The virtual data representation is realized in linear order here.
 *    |- disp_ram[0]                disp_ram[1023] -|
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 *    | | | | | | | | | | | | | | | | | | | ... | | |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-...-+-+-+
 * To avoid a waste of memory the data structure is organized as follows:
 * ARRAY_ELEMENT = 8bit * COLUMN + PAGE --> maximum array size of 
 * 1024 elements
 *
 * Every 8 bit value stored in disp_ram array represents a single column 
 * of one page.
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