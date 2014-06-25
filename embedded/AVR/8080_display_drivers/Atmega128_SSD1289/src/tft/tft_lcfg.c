/*
 * tft_lcfg.c
 *
 *  Created on: Nov 10, 2012
 *      Author: armin
 */
#include "tft_lcfg.h"

const tft_initSequenceType tft_initialConfig3d2_s[] =
{

   {0x0000, 0x0001, 1, 1},		// Oscillator Control: OSC EN[0]
   {0x0003, 0xA8A4, 1, 1},		// Power Control (1):  DTC3[15], DTC1[13], BT2[11], DC3[7], DC1[5], AP1[2]: 1010 1000 1010 0100
   {0x000C, 0x0000, 1, 1},      // Power Control (2): none
   {0x000D, 0x080C, 1, 1},      // Power Control (3): none
   {0x000E, 0x2B00, 1, 1},      // Power Control (4): VCOMG[13], VDV3[11], VD1[9], VD0[8]: 0010 1011 0000 0000
   {0x001E, 0x00B0, 1, 1},      // Power Control (5): nOTP[7], VCM5[5], VCM4[4]: 0000 0000 1011 0000
   {0x0001, 0x2B3F, 1, 1},      // Driver Output Control: REV, BGR, TB, MUX8, MUX5, MUX4, MUX3, MUX2, MUX1, MUX0: 0010 1011 0011 1111
   {0x0002, 0x0600, 1, 1},      // LCD drive AC control: EOR, WSMD: 0000 0110 0000 0000
   {0x0010, 0x0000, 1, 1},      // Sleep mode: none
#if !ROTATE
   {0x0011, 0x6070, 1, 1},      // Entry mode: 0110 0000 0111 0000
#else
   {0x0011, 0x6078, 1, 1},      // Entry mode: 0110 0000 0111 0000
#endif
   {0x0005, 0x0000, 1, 1},      // Compare Register (1):
   {0x0006, 0x0000, 1, 1},      // Compare Register (2):
   {0x0016, 0xEF1C, 1, 1},      // Horizontal Porch:
   {0x0017, 0x0003, 1, 1},      // Vertical Porch:
   {0x0007, 0x0233, 1, 1},      // Display control:
   {0x000B, 0x0000, 1, 1},      // Frame cycle control:
   {0x000F, 0x0000, 1, 1},      // Gate scan start position:
   {0x0041, 0x0000, 1, 1},      // Vertical scroll control (1): none
   {0x0042, 0x0000, 1, 1},      // Vertical scroll control (2): none
   {0x0048, 0x0000, 1, 1},      // First window start:
   {0x0049, 0x013F, 1, 1},      // First window end:
   {0x004A, 0x0000, 1, 1},      // Second window start:
   {0x004B, 0x0000, 1, 1},      // Second window end:
   {0x0044, 0xEF00, 1, 1},      // Horizontal RAM address position:
   {0x0045, 0x0000, 1, 1},      // Vertical RAM adderss start position:
   {0x0046, 0x013F, 1, 1},      // Vertical RAM address end position:
   {0x0030, 0x0707, 1, 1},      // y Control (1):
   {0x0031, 0x0204, 1, 1},      // y Control (2):
   {0x0032, 0x0204, 1, 1},      // y Control (3):
   {0x0033, 0x0502, 1, 1},      // y Control (4):
   {0x0034, 0x0507, 1, 1},      // y Control (5):
   {0x0035, 0x0204, 1, 1},      // y Control (6):
   {0x0036, 0x0204, 1, 1},      // y Control (7):
   {0x0037, 0x0502, 1, 1},      // y Control (8):
   {0x003A, 0x0302, 1, 1},      // y Control (9):
   {0x003B, 0x0302, 1, 1},      // y Control (10):
   {0x0023, 0x0000, 1, 1},      // RAM write data mask (1):
   {0x0024, 0x0000, 1, 1},      // RAM write data mask (2):
   //{0x0025, 0x8000, 1, 1},      // THIS REGISTER DOES NOT EXIST!
   {0x004f, 0x0000, 1, 1},      // Set GDDRAM X address counter: 0
   {0x004e, 0x0000, 1, 1},      // Set GDDRAM Y address counter: 0




};

const tft_configType tft_initialConfigTft_s =
{
   tft_initialConfig3d2_s,
   40 /* Number of initial Sequences is 47 */
};

const void *tft_getLcfgData
(
   void
)
{
   return ((void*) &tft_initialConfigTft_s);
}

