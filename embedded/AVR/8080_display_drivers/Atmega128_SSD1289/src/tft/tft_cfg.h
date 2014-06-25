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
   #define TFT_WIDTH_UI16                       (uint16)240
   #define TFT_HEIGHT_UI16                      (uint16)320
#else
   #define TFT_WIDTH_UI16                       (uint16)320
   #define TFT_HEIGHT_UI16                      (uint16)240
#endif
#define TFT_ZERO_X                           (uint16)0
#define TFT_ZERO_Y                           (uint16)0
#define TFT_PIXELS_UI16                     (uint16)38400

#define TFT_RS_PIN_UI8                       DIO_CHANNEL_PE7
#define TFT_WR_PIN_UI8                       DIO_CHANNEL_PE6
#define TFT_RD_PIN_UI8                       DIO_CHANNEL_PE5
#define TFT_CS_PIN_UI8                       DIO_CHANNEL_PE4
#define TFT_RESET_PIN_UI8                    DIO_CHANNEL_PE3

/* tft Controler Register defines */
#define TFT_START_WRITE_REG_UI16             (uint16)0x0022

#define TFT_HORIZONTAL_RAM_ADDR_UI16	     (uint16)0x0044
#define TFT_VERTICAL_RAM_START_ADDR_UI16     (uint16)0x0045
#define TFT_VERTICAL_RAM_END_ADDR_UI16	     (uint16)0x0046
#define TFT_SET_X_ADDR_COUNTER_UI16	         (uint16)0x004E
#define TFT_SET_Y_ADDR_COUNTER_UI16	         (uint16)0x004F

/* ***************************** enums ************************************** */

#endif /* TFT_CFG_H */
