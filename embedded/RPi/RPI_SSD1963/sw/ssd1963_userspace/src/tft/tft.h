/**
*  COPYRIGHT: Armin Schlegel (armin.schlegel@gmx.de)
*
*******************************************************************************/
#ifndef TFT_H
#define TFT_H

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "../../inc/std_types.h"
#include "tft_cfg.h"
#include "tft_lcfg.h"


/* Function definitions */
#define tft_selectRS()             dio_writeChannel(TFT_RS_PIN_UI8, STD_HIGH)
#define tft_deSelectRS()           dio_writeChannel(TFT_RS_PIN_UI8, STD_LOW)

#define tft_selectCS()             dio_writeChannel(TFT_CS_PIN_UI8, STD_HIGH)
#define tft_deSelectCS()           dio_writeChannel(TFT_CS_PIN_UI8, STD_LOW)

#define tft_selectWR()             dio_writeChannel(TFT_WR_PIN_UI8, STD_HIGH)
#define tft_deSelectWR()           dio_writeChannel(TFT_WR_PIN_UI8, STD_LOW)

#define tft_selectBacklight()      dio_writeChannel(TFT_BACKLIGHT_PIN_UI8, STD_HIGH)
#define tft_deSelectBacklight()    dio_writeChannel(TFT_BACKLIGHT_PIN_UI8, STD_LOW)

#define tft_selectReset()          dio_writeChannel(TFT_RESET_PIN_UI8, STD_HIGH)
#define tft_deSelectReset()        dio_writeChannel(TFT_RESET_PIN_UI8, STD_LOW)



/* ***************************** typedefs *********************************** */
typedef uint16 tft_ColorType;

/* ***************************** enums ************************************** */
typedef enum
{
   WHITE       = (0xFFFFU),
   BLACK       = (0x0000U),
   BLUE        = (0x001FU),
   BRED        = (0xF81FU),
   GRED 		   = (0xFFE0U),
   GBLUE		   = (0x07FFU),
   RED         = (0xF800U),
   MAGENTA     = (0xF81FU),
   GREEN       = (0x07E0U),
   CYAN        = (0x7FFFU),
   YELLOW      = (0xFFE0U),
   BROWN 		= (0xBC40U),
   BRRED 		= (0xFC07U),
   GRAY  		= (0x8430U),
}tft_stdColorsType;

/* ***************************** macros ************************************* */
/* ***************************** structs ************************************ */

/**
*  \brief init sequence description type
*
*  Struct for postbuild init sequence description
*/
typedef struct
{
   uint16 tft_registerAddress_ui16;
   uint16 tft_registerValue_ui16;
   uint16 tft_waitTimeAfterSend_ui16;
   uint16 tft_registerParameters_ui16;
}tft_initSequenceType;


/**
*  \brief init container
*
*  This type of data structure containing the initialization data for the TFT driver
*/
typedef struct
{
   tft_initSequenceType const    *tft_initSequence_ps;
   uint16                         tft_numberOfInitSeq_ui16;
}tft_configType;

/* ***************************** global data ******************************** */
extern const tft_configType tft_initialConfigTft_s;


/* ***************************** modul global prototypes ******************** */
/* ***************************** global functions *************************** */
/*
*  \brief Function initialize the Display Graphic Driver and the tft Display
*
*  \param [in]  initSequence = Pointer to init Sequence
*  \param [out] ---
*  \return      ---
*/
Std_ReturnType tft_init
(
	const tft_configType *ConfigPtr
);



/*
*  \brief Function clears whole screen with one color
*
*  \param [in]  color_ui16 =  Color Value
*  \param [out] ---
*  \return      ---
*/
Std_ReturnType tft_clearScreen
(
   tft_ColorType color_ui16
);

//void tft_drawStart();
//
//void tft_drawStop();

/*
*  \brief Function draw a filled Rectangle at x/y position
*
*  \param [in]  xStartPosition_ui16 = X Start position of rectangle
*  \param [in]  yStartPosition_ui16 = Y Start position of rectangle
*  \param [in]  rectangleWidth_ui16 = Width of rectangle in pixel
*  \param [in]  rectangleHeight_ui16 = Height of rectangle in pixel
*  \param [in]  rectangleColor_ui16 = Color of rectangle

*  \param [out] ---
*  \return      E_OK = Rectangle draw successfull
*               E_NOT_OK = Rectangle draw not successfull
*/
Std_ReturnType tft_drawPixel
(
   uint16 xPosition_ui16,
   uint16 yPosition_ui16,
   tft_ColorType rectangleColor_ui16
);

/*
*  \brief Function draw a filled Rectangle at x/y position
*
*  \param [in]  xStartPosition_ui16 = X Start position of rectangle
*  \param [in]  yStartPosition_ui16 = Y Start position of rectangle
*  \param [in]  rectangleWidth_ui16 = Width of rectangle in pixel
*  \param [in]  rectangleHeight_ui16 = Height of rectangle in pixel
*  \param [in]  rectangleColor_ui16 = Color of rectangle

*  \param [out] ---
*  \return      E_OK = Rectangle draw successfull
*               E_NOT_OK = Rectangle draw not successfull
*/
Std_ReturnType tft_drawRectangle
(
   uint16 xPosition_ui16,
   uint16 yPosition_ui16,
   uint16 rectangleWidth_ui16,
   uint16 rectangleHeight_ui16,
   tft_ColorType rectangleColor_ui16
);

void tft_setWindow
(
   uint16 startPositionX_ui16,
   uint16 startPositionY_ui16,
   uint16 endPositionX_ui16,
   uint16 endPositionY_ui16
);

void tft_sendPixelData
(
   uint16 data_ui16
);

void tft_drawStart();

void tft_drawStop();

#endif
