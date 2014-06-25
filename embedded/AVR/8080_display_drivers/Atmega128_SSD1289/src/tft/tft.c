/**
*  COPYRIGHT: Armin Schlegel
*  \file tft.h
*  \brief Display Graphic Driver
*
*  This header file contains all tft specific datatypes and defines.
*
*******************************************************************************/

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "tft.h"
#include "tft_lcfg.h"
#include "../dio/dio.h"
#include <avr/delay.h>


/* ***************************** # defines ********************************** */

/* ***************************** modul global data ************************** */

/* ***************************** modul global functions ********************* */
/**  \brief Sends data
*
*  \param [in]  data_ui16 = Data to send
*  \param [out] ---
*  \return      ---
*/
void tft_sendData
(
   uint16 data_ui16
)
{
	tft_selectRS();
	tft_deSelectCS();
	//dio_writePortGroup(DIO_PORTGROUP0, (uint16)data_ui16);
    dio_writePort(DIO_PORT_A, data_ui16);
    dio_writePort(DIO_PORT_B, data_ui16 >> 8);

	tft_deSelectWR();
    tft_selectWR();
    tft_selectCS();
}

/**  \brief Sends data
*
*  \param [in]  data_ui16 = Data to send
*  \param [out] ---
*  \return      ---
*/
void tft_sendCommand
(
   uint16 data_ui16
)
{

	tft_deSelectRS();
	tft_deSelectCS();

    dio_writePort(DIO_PORT_A, data_ui16);
    dio_writePort(DIO_PORT_B, data_ui16 >> 8);
	//dio_writePortGroup(DIO_PORTGROUP0, (uint16)data_ui16);
    tft_deSelectWR();
    tft_selectWR();
    tft_selectCS();
}

/**  \brief Sends data
*
*  \param [in]  data_ui16 = Data to send
*  \param [out] ---
*  \return      ---
*/
void tft_writeCommandData
(
   uint16 command_ui16,
   uint16 data_ui16
)
{
	tft_sendCommand(command_ui16);
	tft_sendData(data_ui16);
}

/*  \brief Sets Register on tft Display Controller
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
)
{
   /* First send Command if it is != 0xFFFF */
   if(tft_register_ui16 != 0xFFFF)
   {
      tft_sendCommand(tft_register_ui16);
   }
   /* Then send or continue sending Parameter to tft controler if needed */
   if(tft_registerParameters_ui16 != 0)
   {
      tft_sendData(tft_registerValue_ui16);
   }
}

/*  \brief Waits x ms
*
*  \param [in]  waitTime_ui16 = Wait time in ms
*  \param [out] ---
*  \return      ---
*/
static void tft_waitXms
(
   uint16 waitTime_ui16
)
{
	uint16 tmp_ui16 = 0;
	for(tmp_ui16 = 0; tmp_ui16 < waitTime_ui16; tmp_ui16++)
	{
		_delay_ms(1);
	}
}


/*  \brief Set window with defined height and width window
*          will be drawn form top to bottom
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
)
{
   /* secure border of display */
   if((startPositionX_ui16 + endPositionX_ui16) > (TFT_WIDTH_UI16 - 1))
   {
	   endPositionX_ui16 = TFT_WIDTH_UI16 - 1;
   }
   else if((startPositionX_ui16 + endPositionY_ui16) > (TFT_HEIGHT_UI16 - 1))
   {
	   endPositionY_ui16 = TFT_HEIGHT_UI16 - 1;
   }
   else
   {
      // do nothing
   }

   tft_setDisplayRegister(TFT_HORIZONTAL_RAM_ADDR_UI16,(uint16)((endPositionX_ui16 << 8) + startPositionX_ui16), 1);
   tft_setDisplayRegister(TFT_VERTICAL_RAM_START_ADDR_UI16, startPositionY_ui16, 1);
   tft_setDisplayRegister(TFT_VERTICAL_RAM_END_ADDR_UI16, endPositionY_ui16, 1);
   tft_setDisplayRegister(TFT_SET_X_ADDR_COUNTER_UI16, startPositionX_ui16, 1);
   tft_setDisplayRegister(TFT_SET_Y_ADDR_COUNTER_UI16, startPositionY_ui16, 1);
   tft_sendCommand(TFT_START_WRITE_REG_UI16);
}


static void tft_setPixelCoordinates
(
   uint16 positionX_ui16,
   uint16 positionY_ui16
)
{
   /* secure border of display */
   if(positionX_ui16 > (TFT_WIDTH_UI16 - 1))
   {
	   positionX_ui16 = TFT_WIDTH_UI16 - 1;
   }
   else if(positionY_ui16 > (TFT_HEIGHT_UI16 - 1))
   {
	   positionY_ui16 = TFT_HEIGHT_UI16 - 1;
   }
   else
   {
      // do nothing
   }

   tft_setDisplayRegister(TFT_SET_X_ADDR_COUNTER_UI16, positionX_ui16, 1);
   tft_setDisplayRegister(TFT_SET_Y_ADDR_COUNTER_UI16, positionY_ui16, 1);
   tft_sendCommand(TFT_START_WRITE_REG_UI16);
}
/* ***************************** global functions *************************** */
/*
*  \brief Function initialize the Display Graphic Driver and the tft Display
*
*  \param [in]  initSequence = Pointer to init Sequence
*  \param [out] ---
*  \return      ---
*/
void tft_init
(
	const tft_configType *ConfigPtr
)
{

   tft_initSequenceType const *tmpInitSequence_ps;
   tmpInitSequence_ps = ConfigPtr->tft_initSequence_ps;


   uint16 forCounter_ui16;

   /* Reset Display */
   tft_selectReset();
   /* Wait 50ms */
   tft_waitXms(5);

   tft_deSelectReset();

   /* Wait 100ms */
   tft_waitXms(10);

   /* Reset Display done */
   tft_selectReset();

   /* Pull CS Pin high */
   tft_selectCS();

   /* Pull RD Pin high */
   tft_selectRD();
   //dio_writeChannel((dio_channelType)TFT_RD_PIN_UI8, (dio_pinLevelType)STD_HIGH);

   /* Pull WR Pin high */
   tft_selectWR();
   //dio_writeChannel((dio_channelType)TFT_WR_PIN_UI8, (dio_pinLevelType)STD_HIGH);

   tft_waitXms(20);

   /* Init Sequence */
   for(forCounter_ui16 = 0; forCounter_ui16 < ConfigPtr->tft_numberOfInitSeq_ui16; forCounter_ui16++)
   {
      /* Send Sequence */
      tft_setDisplayRegister((tmpInitSequence_ps + forCounter_ui16)->tft_registerAddress_ui16,
                             (tmpInitSequence_ps + forCounter_ui16)->tft_registerValue_ui16,
                             (tmpInitSequence_ps + forCounter_ui16)->tft_registerParameters_ui16);

      /* Wait X ms */
      tft_waitXms((tmpInitSequence_ps + forCounter_ui16)->tft_waitTimeAfterSend_ui16);

   }
}



/*
*  \brief Function clears whole screen with one color
*
*  \param [in]  color_ui16 =  Color Value
*  \param [out] ---
*  \return      ---
*/
void tft_clearScreen
(
   tft_ColorType color_ui16
)
{
   uint32 forCounter_ui16;

   tft_setWindow(TFT_ZERO_X, TFT_ZERO_Y, TFT_WIDTH_UI16 - 1, TFT_HEIGHT_UI16 - 1);


     for(forCounter_ui16 = 0; forCounter_ui16 < TFT_PIXELS_UI16; forCounter_ui16++)
      {
        tft_sendData(color_ui16);
        tft_sendData(color_ui16);
      }

}


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
)
{
   Std_ReturnType returnValue;
   uint32 forCounter_ui32;
   uint32 pixelSizeOfRectangle_ui32;

   returnValue = E_NOT_OK;

      /* calculate pixel size */


      /* Set window size and position - modified for portrait view */
   tft_setPixelCoordinates(xPosition_ui16, yPosition_ui16);


         tft_sendData(rectangleColor_ui16);


      returnValue = E_OK;

   return returnValue;
}

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
   uint16 xStartPosition_ui16,
   uint16 yStartPosition_ui16,
   uint16 xEndPosition_ui16,
   uint16 yEndPosition_ui16,
   tft_ColorType rectangleColor_ui16
)
{
   Std_ReturnType returnValue;
   uint16 forCounter_ui16;
   uint16 forCounter2_ui16;

   returnValue = E_NOT_OK;

      /* send pixel (for faster transmission, two for loop used) */
      for(forCounter_ui16 = yStartPosition_ui16; forCounter_ui16 < yEndPosition_ui16; forCounter_ui16++)
      {
    	  for(forCounter2_ui16 = xStartPosition_ui16; forCounter2_ui16 < xEndPosition_ui16; forCounter2_ui16++)
    	  {
    		  tft_drawPixel(forCounter_ui16, forCounter2_ui16, rectangleColor_ui16);
    	  }
       }

      returnValue = E_OK;

   return returnValue;
}



