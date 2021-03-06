/**
*  COPYRIGHT: Armin Schlegel
*  \file tft.h
*  \brief Display Graphic Driver
*
*  This header file contains all tft specific datatypes and defines.
*
*******************************************************************************/
#ifndef TFT_H
#define TFT_H

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "std_types.h"
#include "tft_cfg.h"


/* Function definitions */
/* TODO: Dio_WriteChannel() implementieren! */
#define tft_selectRS()             dio_writeChannel(TFT_RS_PIN_UI8, STD_HIGH)
#define tft_deSelectRS()           dio_writeChannel(TFT_RS_PIN_UI8, STD_LOW)

#define tft_selectCS()             dio_writeChannel(TFT_CS_PIN_UI8, STD_HIGH)
#define tft_deSelectCS()           dio_writeChannel(TFT_CS_PIN_UI8, STD_LOW)

#define tft_selectWR()             dio_writeChannel(TFT_WR_PIN_UI8, STD_HIGH)
#define tft_deSelectWR()           dio_writeChannel(TFT_WR_PIN_UI8, STD_LOW)

#define tft_selectRD()             dio_writeChannel(TFT_RD_PIN_UI8, STD_HIGH)
#define tft_deSelectRD()           dio_writeChannel(TFT_RD_PIN_UI8, STD_LOW)

#define tft_selectReset()          dio_writeChannel(TFT_RESET_PIN_UI8, STD_HIGH)
#define tft_deSelectReset()        dio_writeChannel(TFT_RESET_PIN_UI8, STD_LOW)

/* ***************************** typedefs *********************************** */
typedef uint16 tft_ColorType;

/* ***************************** enums ************************************** */


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
*  This type of data structure containing the initialization data for the PWM driver
*/
typedef struct
{
   tft_initSequenceType const    *tft_initSequence_ps;
   uint16                        tft_numberOfInitSeq_ui16;
}tft_configType;

/* ***************************** global data ******************************** */
extern const tft_configType tft_initialConfigTft_s;

/* ***************************** modul global prototypes ******************** */
/**  \brief Sets Register on tft Display Controller
*
*  \param [in]  tft_register_ui16 = tft Controler register address
*  \param [in]  tft_registerValue_ui16 = Register value to write
*  \param [in]  tft_registerParameters_ui16 = Parameters count to write
*  \param [out] ---
*  \return      ---
*/
static void tft_setDisplayRegister
(
   uint16 tft_register_ui16,
   uint16 tft_registerValue_ui16,
   uint16 tft_registerParameters_ui16
);


/**  \brief Waits x ms
*
*  \param [in]  waitTime_ui16 = Wait time in ms
*  \param [out] ---
*  \return      ---
*/
static void tft_waitXms
(
   uint16 waitTime_ui16
);

void tft_sendData
(
   uint16 data_ui16
);

/**  \brief Sends data
*
*  \param [in]  data_ui16 = Data to send
*  \param [out] ---
*  \return      ---
*/
void tft_sendCommand
(
   uint16 data_ui16
);

/**  \brief Set window with defined height and width window
*           will be drawn form top to bottom
*
*  \param [in]  startPositionX_ui16 = Top start X position window
*  \param [in]  startPositionY_ui16 = Top start Y position window
*  \param [in]  windowHeight_ui16 = Window height
*  \param [in]  windowWidth_ui16 = Window width
*  \param [out] ---
*  \return      ---
*/
static void tft_setWindow
(
   uint16 startPositionX_ui16,
   uint16 startPositionY_ui16,
   uint16 endPositionX_ui16,
   uint16 endPositionY_ui16
);


/* ***************************** global prototypes ************************** */
/**
*  \brief Function initialize the Display Graphic Driver and the tft Display
*
*  \param [in]  initSequence = Pointer to init Sequence
*  \param [out] ---
*  \return      ---
*/
void tft_init
(
	const tft_configType *ConfigPtr
);


/**
*  \brief Function clears whole screen with one color
*
*  \param [in]  color_ui16 =  Color Value
*  \param [out] ---
*  \return      ---
*/
void tft_clearScreen
(
   tft_ColorType color_ui16
);

/**
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
   uint16 xStartPosition_ui16,
   uint16 yStartPosition_ui16,
   uint16 rectangleWidth_ui16,
   uint16 rectangleHeight_ui16,
   tft_ColorType rectangleColor_ui16
);


static void tft_setPixelCoordinates
(
   uint16 positionX_ui16,
   uint16 positionY_ui16
);

#endif /* TFT_H */
