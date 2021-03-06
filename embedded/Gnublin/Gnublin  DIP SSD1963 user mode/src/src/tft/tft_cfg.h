/**
*  COPYRIGHT: Armin Schlegel
*  \file tft.h
*  \brief Display Graphic Driver
*
*  This header file contains all tft specific datatypes and defines.
*
*******************************************************************************/
#ifndef TFT_CFG_H
#define TFT_CFG_H
/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */

/* ***************************** typedefs *********************************** */
/* ***************************** defines ************************************ */
#define ROTATE 0

#if !ROTATE
   #define TFT_WIDTH_UI16                    (uint16)480
   #define TFT_HEIGHT_UI16                   (uint16)272
#else
   #define TFT_WIDTH_UI16                    (uint16)272
   #define TFT_HEIGHT_UI16                   (uint16)480
#endif
#define TFT_ZERO_X                           (uint16)0
#define TFT_ZERO_Y                           (uint16)0
#define TFT_PIXELS_UI32                      (uint32)130560

#define TFT_RS_PIN_UI8                       DIO_CHANNEL_18
#define TFT_WR_PIN_UI8                       DIO_CHANNEL_17
#if HARDWARE_BOARD_REV == 1
   #define TFT_BACKLIGHT_PIN_UI8             DIO_CHANNEL_20
#else
   #define TFT_RD_PIN_UI8                    DIO_CHANNEL_20
#endif
#define TFT_CS_PIN_UI8                       DIO_CHANNEL_1
#define TFT_RESET_PIN_UI8                    DIO_CHANNEL_0

#define HDP                         479           // 479
#define HT                          531           // 525
#define HPS                         43            // 40
#define LPS                         8             // 6
#define HPW                         10            // 39

#define VDP                         271           // 271
#define VT                          288           // 288
#define VPS                         12            // 12
#define FPS                         4             // 8
#define VPW                         10            // 11

/* TFT Controler Register defines */
#define TFT_RAM_REG_ADDR_UI16               (uint16)0x002C
#define TFT_COL_START_ADDR2_REG_ADDR_UI16   (uint16)0x002A
#define TFT_COL_START_ADDR1_REG_ADDR_UI16   (uint16)0x0000
#define TFT_COL_END_ADDR2_REG_ADDR_UI16     (uint16)0x0000
#define TFT_COL_END_ADDR1_REG_ADDR_UI16     (uint16)0x0000
#define TFT_ROW_START_ADDR2_REG_ADDR_UI16   (uint16)0x002B
#define TFT_ROW_START_ADDR1_REG_ADDR_UI16   (uint16)0x0000
#define TFT_ROW_END_ADDR2_REG_ADDR_UI16     (uint16)0x0000
#define TFT_ROW_END_ADDR1_REG_ADDR_UI16     (uint16)0x0000

/* ***************************** enums ************************************** */

#endif /* TFT_CFG_H */
