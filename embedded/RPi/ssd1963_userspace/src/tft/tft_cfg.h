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
   #define TFT_WIDTH_UI16                   ((uint16)480U)
   #define TFT_HEIGHT_UI16                  ((uint16)272U)
#else
   #define TFT_WIDTH_UI16                   ((uint16)272U)
   #define TFT_HEIGHT_UI16                  ((uint16)480U)
#endif
#define TFT_ZERO_X                          ((uint16)0U)
#define TFT_ZERO_Y                          ((uint16)0U)
#define TFT_PIXELS_UI32                     ((uint32)130560U)

#define TFT_RS_PIN_UI8                      (DIO_CHANNEL_0)
#define TFT_WR_PIN_UI8                      (DIO_CHANNEL_1)
#define TFT_BACKLIGHT_PIN_UI8               (DIO_CHANNEL_3)
#define TFT_CS_PIN_UI8                      (DIO_CHANNEL_4)
#define TFT_RESET_PIN_UI8                   (DIO_CHANNEL_7)

#define tft_ChannelDB0                      (DIO_CHANNEL_18)
#define tft_ChannelDB1                      (DIO_CHANNEL_17)
#define tft_ChannelDB2                      (DIO_CHANNEL_20)
#define tft_ChannelDB3                      (DIO_CHANNEL_19)
#define tft_ChannelDB4                      (DIO_CHANNEL_2)
#define tft_ChannelDB5                      (DIO_CHANNEL_8)
#define tft_ChannelDB6                      (DIO_CHANNEL_10)
#define tft_ChannelDB7                      (DIO_CHANNEL_16)
#define tft_ChannelDB8                      (DIO_CHANNEL_9)
#define tft_ChannelDB9                      (DIO_CHANNEL_11)
#define tft_ChannelDB10                     (DIO_CHANNEL_12)
#define tft_ChannelDB11                     (DIO_CHANNEL_13)
#define tft_ChannelDB12                     (DIO_CHANNEL_14)
#define tft_ChannelDB13                     (DIO_CHANNEL_6)
#define tft_ChannelDB14                     (DIO_CHANNEL_15)
#define tft_ChannelDB15                     (DIO_CHANNEL_5)

#define HDP                                 (479U)           // 479
#define HT                                  (531U)           // 525
#define HPS                                 (43U)            // 40
#define LPS                                 (8U)             // 6
#define HPW                                 (10U)            // 39

#define VDP                                 (271U)           // 271
#define VT                                  (288U)           // 288
#define VPS                                 (12U)            // 12
#define FPS                                 (4U)             // 8
#define VPW                                 (10U)            // 11

/* TFT Controler Register defines */
#define TFT_RAM_REG_ADDR_UI16               ((uint16)0x002CU)
#define TFT_COL_START_ADDR2_REG_ADDR_UI16   ((uint16)0x002AU)
#define TFT_COL_START_ADDR1_REG_ADDR_UI16   ((uint16)0x0000U)
#define TFT_COL_END_ADDR2_REG_ADDR_UI16     ((uint16)0x0000U)
#define TFT_COL_END_ADDR1_REG_ADDR_UI16     ((uint16)0x0000U)
#define TFT_ROW_START_ADDR2_REG_ADDR_UI16   ((uint16)0x002BU)
#define TFT_ROW_START_ADDR1_REG_ADDR_UI16   ((uint16)0x0000U)
#define TFT_ROW_END_ADDR2_REG_ADDR_UI16     ((uint16)0x0000U)
#define TFT_ROW_END_ADDR1_REG_ADDR_UI16     ((uint16)0x0000U)

/* ***************************** enums ************************************** */

#endif /* TFT_CFG_H */
