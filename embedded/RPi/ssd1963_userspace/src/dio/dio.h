/*
 * dio.h
 *
 *  Created on: Nov 6, 2012
 *      Author: armin
 */

#ifndef DIO_H_
#define DIO_H_

#include "../../inc/std_types.h"
#include "dio_lcfg.h"
#include "dio_cfg.h"


#define NUMBER_OF_CONFIGURED_PINS    (21U)
typedef uint8 dio_portValue_ui8;
typedef uint16 dio_portGroupValueType;


/* Physical to logical conversion of GPIO channels */
typedef enum
{
   DIO_CHANNEL_0  = (2U),
   DIO_CHANNEL_1  = (3U),
   DIO_CHANNEL_2  = (4U),
   DIO_CHANNEL_3  = (7U),
   DIO_CHANNEL_4  = (8U),
   DIO_CHANNEL_5  = (9U),
   DIO_CHANNEL_6  = (10U),
   DIO_CHANNEL_7  = (11U),
   DIO_CHANNEL_8  = (14U),
   DIO_CHANNEL_9  = (15U),
   DIO_CHANNEL_10 = (17U),
   DIO_CHANNEL_11 = (18U),
   DIO_CHANNEL_12 = (22U),
   DIO_CHANNEL_13 = (23U),
   DIO_CHANNEL_14 = (24U),
   DIO_CHANNEL_15 = (25U),
   DIO_CHANNEL_16 = (27U),
   DIO_CHANNEL_17 = (28U),
   DIO_CHANNEL_18 = (29U),
   DIO_CHANNEL_19 = (30U),
   DIO_CHANNEL_20 = (31U),
}dio_channelType;

typedef enum
{
   DIO_PIN_INPUT = (0U),
   DIO_PIN_OUTPUT
}dio_pinDirectionType;


typedef enum
{
   DIO_PIN_INIT_LOW = (0U),
   DIO_PIN_INIT_HIGH
}dio_pinInitialValueType;

typedef enum
{
   DIO_LOW = (0U),
   DIO_HIGH
}dio_pinLevelType;

typedef struct
{
   dio_channelType            dio_pinNumber_e;
   dio_pinDirectionType       dio_pinDirection_e;
   dio_pinInitialValueType    dio_pinInitialValue_e;
}dio_pinConfigType;

typedef struct
{
   dio_pinConfigType  dio_pinConfig_s[NUMBER_OF_CONFIGURED_PINS];
}dio_configType;

Std_ReturnType dio_init(void);

void dio_writeChannel(dio_channelType dio_pin_ui8, dio_pinLevelType dio_output_ui8);
void dio_writePortGroup(uint16 dio_data_ui16);
void dio_writePortGroup_8(uint8 dio_data_ui8);

#endif /* DIO_H_ */
