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

/* ***************************** # defines ********************************** */
#define NOCMD     (0xFFFFU)
#define NOPARAM   (0U)
#define PARAM     (1U)
/* ***************************** modul global data ************************** */

/* ***************************** global data ******************************** */


const void *tft_getLcfgData
(
   void
);

