/**
 * \file images.c
 * \brief This file provides some pictures.
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

#include "images.h"

/*--- External Data --------------------------------------------------*/

/** Byte code of a picture representing the initialization of SD card recording */
unsigned char record_init[] PROGMEM = { 112, 35,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFD, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xBF, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0xA0,
        0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00,
        0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x81,
        0x80, 0x84, 0x80, 0x02, 0x40, 0x08, 0x00, 0xA0, 0x05, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x80, 0x00, 0x40, 0x00,
        0x00, 0xA0, 0x05, 0xE7, 0xF0, 0x1C, 0xE7, 0x81, 0x9E, 0x8E,
        0x8E, 0x7A, 0xE7, 0xC8, 0x79, 0xA0, 0x05, 0x11, 0x19, 0x22,
        0x11, 0x81, 0xA2, 0x84, 0x90, 0x42, 0x48, 0x28, 0x8A, 0xA0,
        0x05, 0x11, 0x09, 0x22, 0x11, 0x81, 0xA2, 0x84, 0x90, 0x42,
        0x48, 0x28, 0x8A, 0xA0, 0x05, 0xF1, 0x09, 0x22, 0x11, 0x81,
        0xA2, 0x84, 0x9E, 0x22, 0x4F, 0x28, 0x8A, 0xA0, 0x05, 0x11,
        0x08, 0x22, 0x11, 0x81, 0xA2, 0x84, 0x92, 0x1A, 0x49, 0x28,
        0x8A, 0xA0, 0x05, 0x11, 0x19, 0x22, 0x11, 0x81, 0xA2, 0x84,
        0x92, 0x0A, 0x49, 0x28, 0x8A, 0xA0, 0x05, 0xE1, 0xF0, 0x1C,
        0xE1, 0x81, 0xA2, 0x98, 0x9E, 0x7A, 0x8F, 0xC9, 0x89, 0xA0,
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
        0xC5, 0xE1, 0x70, 0x38, 0x1C, 0x0E, 0x87, 0xC3, 0xE1, 0x70,
        0x1C, 0x0E, 0x87, 0xA3, 0xC5, 0xE1, 0x70, 0x38, 0x1C, 0x0E,
        0x87, 0xC3, 0xE1, 0x70, 0x1C, 0x0E, 0x87, 0xA3, 0xC5, 0xE1,
        0x70, 0x38, 0x1C, 0x0E, 0x87, 0xC3, 0xE1, 0x70, 0x1C, 0x0E,
        0x87, 0xA3, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xA0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xFD, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xBF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

/** Picture that shows that the SD card is locked */
unsigned char sd_locked[] PROGMEM = { 8, 9,
 0x00, 0x18, 0x24, 0x24, 0x7E, 0x7E, 0x76, 0x66, 0x7E
};

/** Picture that shows that the SD card is unlocked */
unsigned char sd_unlocked[] PROGMEM = { 10, 9,
       0x00, 0x00, 0x03, 0x12, 0x48, 0x7E, 0xF8, 0x61, 0x87, 0x19,
        0x7E, 0x00

};

/** Picture that shows that no lock is possible */
unsigned char no_lock[] PROGMEM = { 10, 9,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00
};

/** A picture of a satellite */
unsigned char satellit[] PROGMEM = { 11, 7,
      0x1F, 0x88, 0xA0, 0x02, 0x09, 0x4A, 0x50, 0xA2, 0x52, 0x15
};

/** A picture indicating that no SD card is inserted */
unsigned char no_sd_card[] PROGMEM = { 12, 11,
        0xFC, 0x2F, 0x80, 0x71, 0x18, 0x84, 0x71, 0x18, 0x81, 0x71,
        0x18, 0x80, 0x21, 0x18, 0x80, 0xFF, 0x0F
};

/** A picture indicating that a SD card is inserted */
unsigned char sd_card[] PROGMEM = { 12, 11,
        0xFC, 0x2F, 0x80, 0x01, 0xD8, 0x9D, 0x45, 0xDA, 0xA5, 0x51,
        0xDA, 0x9D, 0x01, 0x18, 0x80, 0xFF, 0x0F
};

/** A picture indicating that recording to SD card is currently running */
unsigned char sd_rec_on[] PROGMEM = { 7, 7,
        0x00, 0x8E, 0xCF, 0xE7, 0xE3, 0x00, 0x00
};

/** A picture indicating that recording to SD card is currently paused */
unsigned char sd_rec_pause[] PROGMEM = { 7, 7,
        0xBE, 0xF5, 0x7A, 0xBD, 0x5E, 0xFB, 0x00
};

/** A picture indicating that recording to SD card is currently stopped */
unsigned char sd_rec_stop[] PROGMEM = { 7, 7,
        0xBE, 0x71, 0x30, 0x18, 0x1C, 0xFB, 0x00
};

/** A picture representing a tacho */
unsigned char tacho[] PROGMEM = { 11, 8,
        0x70, 0x60, 0x8D, 0x80, 0x04, 0xD4, 0xD3, 0x00, 0x0A, 0x48,
        0x40
};

/** A picture that shall represent the height */
unsigned char height[] PROGMEM = { 11, 8,
        0x00, 0x00, 0x00, 0x01, 0x1D, 0x5C, 0x79, 0xE2, 0xD3, 0xFF,
        0xFF
};

/** A picture of a compass */
unsigned char compass[] PROGMEM = { 9, 9,
        0x10, 0x70, 0xE0, 0x30, 0x56, 0xD5, 0x18, 0x0E, 0x14, 0x10,
        0x00
};

/** A picture of pole */
unsigned char pole[] PROGMEM = { 9, 9,
        0x18, 0xF0, 0xE0, 0xC3, 0x81, 0x00, 0x01, 0x02, 0x0E, 0x3E,
        0x00
};

/** A picture of a simple cloud */
unsigned char cloud[] PROGMEM = { 11, 8,
        0x60, 0xC0, 0x0C, 0x92, 0x5C, 0x36, 0xC8, 0x42, 0x06, 0xD0,
        0x7F
};

unsigned char logo[] PROGMEM = { 128, 64,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x80, 0x19, 0xC0, 0x1F, 
	0x7F, 0xF0, 0x07, 0xFE, 0x1F, 0x00, 0x00, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x30, 0xF0, 0x7F, 0xFF, 0xFC, 0x0F, 0xFE, 
	0x1F, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 
	0xF0, 0x70, 0xE7, 0x1D, 0x0E, 0xE0, 0x00, 0x00, 0x00, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x20, 0xC0, 0x38, 0x00, 0xC7, 0x1F, 
	0x00, 0xE0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0xC0, 0x38, 0x00, 0xC7, 0x1F, 0x00, 0xE0, 0xE0, 0x0F, 
	0x3E, 0xFF, 0xF0, 0x03, 0x00, 0x00, 0x10, 0x60, 0x1C, 0x00, 
	0xC7, 0x3D, 0x00, 0xE0, 0xE0, 0x9F, 0x7F, 0xFF, 0xF9, 0x07, 
	0x00, 0x00, 0x08, 0x30, 0x1C, 0x00, 0xE7, 0xF9, 0x01, 0xE0, 
	0x60, 0x98, 0x63, 0xCF, 0x39, 0x0F, 0x00, 0x00, 0x04, 0x0C, 
	0x1C, 0x7F, 0xFF, 0xE0, 0xE7, 0xE7, 0x80, 0xDF, 0x01, 0xC7, 
	0x1D, 0x0E, 0x00, 0x00, 0x04, 0x06, 0x1C, 0x7F, 0x7F, 0x00, 
	0xEF, 0xE7, 0xE0, 0xDF, 0x01, 0x87, 0x1D, 0x0E, 0x00, 0x00, 
	0x19, 0x03, 0x38, 0x70, 0x07, 0x00, 0x0E, 0xE0, 0xF0, 0xD8, 
	0x01, 0x87, 0x1D, 0x0E, 0x00, 0xE0, 0xB3, 0x01, 0x38, 0x70, 
	0x07, 0x00, 0x0E, 0xE0, 0x70, 0xD8, 0x01, 0x87, 0x1D, 0x0E, 
	0x00, 0x30, 0xE6, 0x00, 0xF8, 0x70, 0x07, 0x0E, 0x0F, 0xE0, 
	0x70, 0x9C, 0x63, 0x87, 0x39, 0x0F, 0x00, 0x10, 0xEC, 0x07, 
	0xF0, 0x7F, 0x07, 0xFE, 0x07, 0xE0, 0xE0, 0x9F, 0x7F, 0x87, 
	0xF9, 0x07, 0x00, 0x08, 0xFC, 0x02, 0xC0, 0x1F, 0x07, 0xF8, 
	0x03, 0xE0, 0xC0, 0x1B, 0x3E, 0x87, 0xF1, 0x03, 0x00, 0x10, 
	0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xA2, 0x87, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xDD, 0xD7, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x40, 0xD8, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xF0, 
	0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x18, 0x78, 0x3C, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0x7C, 0x73, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xE6, 0x60, 0x00, 
	0x02, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x23, 0x00, 0x00, 0x82, 0x00, 0x00, 0xF0, 
	0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8C, 0x01, 
	0x00, 0x00, 0x81, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x41, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x78, 0x00, 0x00, 0x80, 0x40, 0x10, 0x00, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x40, 
	0x20, 0x10, 0x00, 0x70, 0x00, 0xF8, 0x7F, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x08, 0x00, 0x70, 
	0x00, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x30, 0x10, 0x08, 0x00, 0x30, 0x00, 0xE0, 0x0F, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x04, 
	0x00, 0xF8, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x08, 0x04, 0x00, 0xF8, 0xFF, 0xFF, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 
	0x06, 0x02, 0x00, 0xF8, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x01, 0x01, 0x00, 0x1C, 
	0x00, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xC0, 0x00, 0x01, 0x00, 0x3C, 0x00, 0xC0, 0x0F, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xC0, 0x80, 
	0xFF, 0x7E, 0x00, 0xE0, 0x1D, 0xFF, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0C, 0x20, 0xE0, 0xFF, 0xFF, 0x00, 0xE0, 
	0xF8, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0xF0, 0xFF, 0xEF, 0x01, 0xE0, 0xF8, 0xFF, 0x0F, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xFC, 0x00, 0xDF, 
	0x01, 0xF0, 0xF8, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0x01, 0x3C, 0x00, 0xBF, 0x03, 0x70, 0xFC, 0x00, 
	0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 
	0x00, 0x3F, 0x07, 0x70, 0xDE, 0x01, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x73, 0x0F, 0x70, 
	0xCE, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x80, 0xF3, 0x1E, 0x38, 0x8F, 0x03, 0xE0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0xC0, 0xE1, 
	0x3C, 0x38, 0x07, 0x07, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x03, 0xE0, 0xE0, 0x78, 0x3F, 0x07, 0x0E, 
	0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 
	0x70, 0xE0, 0xF0, 0x1F, 0x07, 0x1C, 0xC0, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x3C, 0xE0, 0xE1, 0x9F, 
	0x07, 0x3C, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x03, 0x1C, 0xE0, 0xC1, 0x9F, 0xF3, 0x3F, 0xC0, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x18, 0xE0, 
	0x81, 0xEF, 0xFF, 0x3F, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x03, 0x00, 0xE0, 0x00, 0xFF, 0xFF, 0x00, 
	0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 
	0x00, 0xE0, 0x00, 0xFF, 0x07, 0x00, 0xC0, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x00, 0x1F, 
	0x07, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x00, 0xF0, 0x00, 0x0E, 0x0F, 0x00, 0xE0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x78, 
	0x00, 0x0C, 0x1E, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1E, 0x00, 0x38, 0x00, 0x0C, 0x1C, 0x00, 
	0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 
	0x00, 0x3E, 0x00, 0x1C, 0x7C, 0x00, 0x3C, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x80, 0x1F, 0x00, 0x1C, 
	0xF8, 0x01, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xF0, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x0F, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x03, 
	0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0x01, 0x00, 0x00, 0x00

};
