/*
 * dio.h
 *
 *  Created on: Nov 6, 2012
 *      Author: armin
 */

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"
#include "dio_lcfg.h"
#include "dio_cfg.h"


#define NUMBER_OF_CONFIGURED_PINS    56
typedef uint8 dio_portValue_ui8;
typedef uint16 dio_portGroupValueType;

typedef enum
{
   DIO_CHANNEL_PA0 = 0x0000,
   DIO_CHANNEL_PA1 = 0x0001,
   DIO_CHANNEL_PA2 = 0x0002,
   DIO_CHANNEL_PA3 = 0x0003,
   DIO_CHANNEL_PA4 = 0x0004,
   DIO_CHANNEL_PA5 = 0x0005,
   DIO_CHANNEL_PA6 = 0x0006,
   DIO_CHANNEL_PA7 = 0x0007,

   DIO_CHANNEL_PB0 = 0x0100,
   DIO_CHANNEL_PB1 = 0x0101,
   DIO_CHANNEL_PB2 = 0x0102,
   DIO_CHANNEL_PB3 = 0x0103,
   DIO_CHANNEL_PB4 = 0x0104,
   DIO_CHANNEL_PB5 = 0x0105,
   DIO_CHANNEL_PB6 = 0x0106,
   DIO_CHANNEL_PB7 = 0x0107,

   DIO_CHANNEL_PC0 = 0x0200,
   DIO_CHANNEL_PC1 = 0x0201,
   DIO_CHANNEL_PC2 = 0x0202,
   DIO_CHANNEL_PC3 = 0x0203,
   DIO_CHANNEL_PC4 = 0x0204,
   DIO_CHANNEL_PC5 = 0x0205,
   DIO_CHANNEL_PC6 = 0x0206,
   DIO_CHANNEL_PC7 = 0x0207,

   DIO_CHANNEL_PD0 = 0x0300,
   DIO_CHANNEL_PD1 = 0x0301,
   DIO_CHANNEL_PD2 = 0x0302,
   DIO_CHANNEL_PD3 = 0x0303,
   DIO_CHANNEL_PD4 = 0x0304,
   DIO_CHANNEL_PD5 = 0x0305,
   DIO_CHANNEL_PD6 = 0x0306,
   DIO_CHANNEL_PD7 = 0x0307,
}dio_channelType;

typedef enum
{
   DIO_PORT_A = 0,
   DIO_PORT_B,
   DIO_PORT_C,
   DIO_PORT_D,
   DIO_NUMBER_OF_PORTS
}dio_portType;

typedef enum
{
   DIO_CHANNEL_0 = 0,
   DIO_CHANNEL_1,
   DIO_CHANNEL_2,
   DIO_CHANNEL_3,
   DIO_CHANNEL_4,
   DIO_CHANNEL_5,
   DIO_CHANNEL_6,
   DIO_CHANNEL_7
}dio_pinNumberType;

typedef enum
{
   DIO_PIN_INPUT = 0,
   DIO_PIN_OUTPUT
}dio_pinDirectionType;

typedef enum
{
   DIO_PIN_MODE_STANDARD = 0,
   DIO_PIN_MODE_ALTERNATIVE
}dio_pinModeType;

typedef enum
{
   DIO_PIN_INIT_LOW = 0,
   DIO_PIN_INIT_HIGH
}dio_pinInitialValueType;

typedef enum
{
   DIO_LOW = 0,
   DIO_HIGH
}dio_pinLevelType;

typedef enum
{
   DIO_PORTGROUP0 = 0,
   DIO_PORTGROUP1,
   DIO_PORTGROUP2
}dio_portGroupNoType;

typedef struct
{
   dio_portType               dio_pinPort_ui8;
   dio_pinNumberType          dio_pinNumber_ui8;
   dio_pinDirectionType       dio_pinDirection_ui8;
   dio_pinModeType            dio_pinMode_ui8;
   dio_pinInitialValueType    dio_pinInitialValue_ui8;
}dio_pinConfigType;

typedef struct
{
   uint8           dio_numberOfConfiguredPins_ui8;
   dio_channelType dio_portGroupChannel[DIO_MAX_NUMBER_OF_PORTS_PER_GROUP];
}dio_portPerGroupType;

typedef struct
{
   uint8                dio_numberOfConfiguredPortGroups_ui8;
	dio_portPerGroupType dio_portGroup[DIO_MAX_NUMBER_OF_PORT_GROUPS];
}dio_portGroupType;

typedef struct
{
   dio_pinConfigType  dio_pinConfig_s[NUMBER_OF_CONFIGURED_PINS];
   dio_portGroupType dio_portGroupConfig_s;
}dio_configType;

void dio_init(void);

void dio_writeChannel(dio_channelType dio_pin_ui8, dio_pinLevelType dio_output_ui8);
dio_pinLevelType dio_readChannel(dio_channelType dio_pin_ui8);

void dio_writePort(dio_portType dio_port_ui8, uint8 dio_data_ui8);
dio_portValue_ui8 dio_readPort(dio_portType dio_port_ui8);

void dio_writePortGroup(dio_portGroupNoType dio_portGroup_e, uint16 dio_data_ui16);

dio_portGroupValueType dio_readPortGroup(dio_portGroupNoType dio_portGroup_e);



#endif /* DIO_H_ */
