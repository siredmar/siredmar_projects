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
#include "tft_cfg.h"
#include "../../inc/platform_types.h"

#define TFT_COLOR_WORKAROUND  6000

/* ***************************** # defines ********************************** */

/* ***************************** modul global data ************************** */

/* ***************************** modul global functions ********************* */
void tft_sendData
(
   uint16 data_ui16
)
{
	tft_selectRS();
	//tft_deSelectCS();
	//printk(KERN_ALERT "tft_sendData: 0x%x\n", data_ui16);
	dio_writePortGroup((uint8)data_ui16);

	tft_deSelectWR();
	tft_selectWR();
	//tft_deSelectWR();
    //tft_selectWR();
    //tft_selectCS();
}

void tft_sendPixelData
(
   uint16 data_ui16
)
{
   data_ui16 = data_ui16 * TFT_COLOR_WORKAROUND;
   tft_selectRS();
	//tft_deSelectCS();
	//printk(KERN_ALERT "tft_sendPixelData: 0x%x\n", data_ui16);
	//printk(KERN_ALERT "tft_sendPixelData RED: 0x%x\n", (data_ui16 >> 8) & 0xF8);
	dio_writePortGroup((uint8)((data_ui16 >> 9) & 0xF8));
	tft_deSelectWR();
	tft_selectWR();

	//printk(KERN_ALERT "tft_sendPixelData GREEN: 0x%x\n", (data_ui16 >> 3) & 0xFC);
	dio_writePortGroup((uint8)((data_ui16 >> 3) & 0xFC));
	tft_deSelectWR();
	tft_selectWR();

	//printk(KERN_ALERT "tft_sendPixelData BLUE: 0x%x\n", (data_ui16 << 3) & 0xF8);
	dio_writePortGroup((uint8)((data_ui16 << 3) & 0xF8));
	tft_deSelectWR();
	tft_selectWR();
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
	//tft_deSelectRS();
	//tft_deSelectCS();
	tft_deSelectRS();
	//printk(KERN_ALERT "tft_sendCommand: 0x%x\n", data_ui16);
	dio_writePortGroup((uint8)data_ui16);
	tft_deSelectWR();
	tft_selectWR();
	// tft_deSelectWR();
   // tft_selectWR();
   // tft_selectCS();
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
   /* First send Command if it is != NOCMD */
   if(tft_register_ui16 != NOCMD)
   {
      tft_sendCommand(tft_register_ui16);
   }
   /* Then send or continue sending Parameter to tft controler if needed */
   if(tft_registerParameters_ui16 != NOPARAM)
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
		usleep(1000);
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
void tft_setWindow
(
   uint16 startPositionX_ui16,
   uint16 startPositionY_ui16,
   uint16 endPositionX_ui16,
   uint16 endPositionY_ui16
)
{

   tft_deSelectCS();
   tft_setDisplayRegister(TFT_COL_START_ADDR2_REG_ADDR_UI16,((startPositionX_ui16 & 0xFF00) >> 8), 1);
   tft_setDisplayRegister(NOCMD,                            (startPositionX_ui16 & 0x00FF), 1);
   tft_setDisplayRegister(NOCMD,                            ((endPositionX_ui16 & 0xFF00) >> 8), 1);
   tft_setDisplayRegister(NOCMD,                            (endPositionX_ui16 & 0x00FF), 1);
   tft_setDisplayRegister(TFT_ROW_START_ADDR2_REG_ADDR_UI16,((startPositionY_ui16 & 0xFF00) >> 8), 1);
   tft_setDisplayRegister(NOCMD,                            (startPositionY_ui16 & 0x00FF), 1);
   tft_setDisplayRegister(NOCMD,                            ((endPositionY_ui16 & 0xFF00) >> 8), 1);
   tft_setDisplayRegister(NOCMD,                            (endPositionY_ui16 & 0x00FF), 1);
   tft_selectCS();
   //tft_sendCommand(TFT_RAM_REG_ADDR_UI16);
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

   uint16 forCounter_ui16;
   tft_initSequenceType const *tmpInitSequence_ps;
   tmpInitSequence_ps = ConfigPtr->tft_initSequence_ps;

   /* Reset Display */
   tft_selectReset();
   /* Wait 50ms */
   tft_waitXms(5);

   tft_deSelectReset();

   /* Wait 100ms */
   tft_waitXms(10);

   /* Reset Display done */
   tft_selectReset();

   /* activate CS */
   tft_deSelectCS();

#if HARDWARE_BOARD_REV == 1
  /* Enable Backlight */
   tft_selectBacklight();
#else
   /* Pull RD Pin high */
   tft_selectRD();
#endif
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
   /* deactivate CS */
   tft_selectCS();
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
   uint32 forCounter_ui32;
   tft_drawRectangle(0, 0, 480, 272, color_ui16);
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

   returnValue = E_NOT_OK;

      /* calculate pixel size */

   /*
    *
    tft_deSelectRS();
	dio_writePortGroup((uint8)data_ui16);
	tft_deSelectWR();
	tft_selectWR();
    *
    */

      /* Set window size and position - modified for portrait view */
      tft_setWindow(xPosition_ui16, yPosition_ui16, ++xPosition_ui16, ++yPosition_ui16);

      tft_deSelectCS();

      tft_sendCommand(TFT_RAM_REG_ADDR_UI16);

     // tft_selectRS();

      tft_sendPixelData(rectangleColor_ui16);
      //tft_sendData16(rectangleColor_ui16);
      tft_selectCS();

      returnValue = E_OK;

   return returnValue;
}

void tft_drawStart()
{

    tft_deSelectCS();

    tft_sendCommand(TFT_RAM_REG_ADDR_UI16);
}

void tft_drawStop()
{

    tft_selectCS();

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
   uint16 xPosition_ui16,
   uint16 yPosition_ui16,
   uint16 rectangleWidth_ui16,
   uint16 rectangleHeight_ui16,
   tft_ColorType rectangleColor_ui16
)
{
   Std_ReturnType returnValue;
   uint32 forCounter_ui32;
   uint16 endPositionX_ui16;
   uint16 endPositionY_ui16;
   uint32 pixelSizeOfRectangle_ui32;

   returnValue = E_NOT_OK;
   endPositionX_ui16 = xPosition_ui16 + rectangleWidth_ui16;
   endPositionY_ui16 = yPosition_ui16 + rectangleHeight_ui16;

   /* secure border of display */
   if(endPositionX_ui16 > (TFT_WIDTH_UI16 - 1))
   {
	   endPositionX_ui16 = TFT_WIDTH_UI16 - 1;
   }
   else if(endPositionY_ui16 > (TFT_HEIGHT_UI16 - 1))
   {
	   endPositionY_ui16 = TFT_HEIGHT_UI16 - 1;
   }
   else
   {
      // do nothing
   }
   /* calculate pixel size */
    pixelSizeOfRectangle_ui32 = rectangleWidth_ui16 * rectangleHeight_ui16;

   tft_setWindow(xPosition_ui16, yPosition_ui16, endPositionX_ui16, endPositionY_ui16);

   /* activate CS */
     tft_deSelectCS();

     tft_deSelectRS();

     tft_sendCommand(TFT_RAM_REG_ADDR_UI16);

     tft_selectRS();
  // tft_setWindow(TFT_ZERO_X, TFT_ZERO_Y, TFT_WIDTH_UI16 - 1, TFT_HEIGHT_UI16 - 1);


     for(forCounter_ui32 = 0; forCounter_ui32 < pixelSizeOfRectangle_ui32; ++forCounter_ui32)
      {
    	 tft_sendPixelData(rectangleColor_ui16);
    	 //tft_sendData(rectangleColor_ui16);
      }
     tft_selectCS();


      returnValue = E_OK;

   return returnValue;
}
