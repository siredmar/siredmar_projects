/*
 * dio_lcfg.c
 *
 *  Created on: Nov 10, 2012
 *      Author: armin
 */
#include "dio.h"
#include "dio_lcfg.h"
const dio_configType dio_initialConfiguration_s = {
  /* configure single pins used for input or output */
  {
     {
        DIO_CHANNEL_0,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_1,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_2,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_3,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_4,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_5,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_6,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_7,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_8,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_9,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_10,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_11,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_12,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_13,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_14,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_15,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_16,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_17,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_18,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_19,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     },
     {
        DIO_CHANNEL_20,
        DIO_PIN_OUTPUT,
        DIO_PIN_INIT_LOW
     }
  }
};

const void *
dio_getlcfgdata (void)
{
  return ((void *) &dio_initialConfiguration_s);
}
