//#define _MMIO_BYTE(mem_addr) (mem_addr))
//#define __SFR_OFFSET 0x20
//#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
//
//
#include "../inc/std_types.h"

#ifndef GPIO_H
#define GPIO_H

#define MAX_NUM_OF_PORTS (7U)
#define MAX_NUM_OF_PINS  (8U)

typedef enum
{
   GPIO_CHANNEL_PA0 = 0x0000,
   GPIO_CHANNEL_PA1 = 0x0001,
   GPIO_CHANNEL_PA2 = 0x0002,
   GPIO_CHANNEL_PA3 = 0x0003,
   GPIO_CHANNEL_PA4 = 0x0004,
   GPIO_CHANNEL_PA5 = 0x0005,
   GPIO_CHANNEL_PA6 = 0x0006,
   GPIO_CHANNEL_PA7 = 0x0007,

   GPIO_CHANNEL_PB0 = 0x0100,
   GPIO_CHANNEL_PB1 = 0x0101,
   GPIO_CHANNEL_PB2 = 0x0102,
   GPIO_CHANNEL_PB3 = 0x0103,
   GPIO_CHANNEL_PB4 = 0x0104,
   GPIO_CHANNEL_PB5 = 0x0105,
   GPIO_CHANNEL_PB6 = 0x0106,
   GPIO_CHANNEL_PB7 = 0x0107,

   GPIO_CHANNEL_PC0 = 0x0200,
   GPIO_CHANNEL_PC1 = 0x0201,
   GPIO_CHANNEL_PC2 = 0x0202,
   GPIO_CHANNEL_PC3 = 0x0203,
   GPIO_CHANNEL_PC4 = 0x0204,
   GPIO_CHANNEL_PC5 = 0x0205,
   GPIO_CHANNEL_PC6 = 0x0206,
   GPIO_CHANNEL_PC7 = 0x0207,

   GPIO_CHANNEL_PD0 = 0x0300,
   GPIO_CHANNEL_PD1 = 0x0301,
   GPIO_CHANNEL_PD2 = 0x0302,
   GPIO_CHANNEL_PD3 = 0x0303,
   GPIO_CHANNEL_PD4 = 0x0304,
   GPIO_CHANNEL_PD5 = 0x0305,
   GPIO_CHANNEL_PD6 = 0x0306,
   GPIO_CHANNEL_PD7 = 0x0307,

   GPIO_CHANNEL_PE0 = 0x0400,
   GPIO_CHANNEL_PE1 = 0x0401,
   GPIO_CHANNEL_PE2 = 0x0402,
   GPIO_CHANNEL_PE3 = 0x0403,
   GPIO_CHANNEL_PE4 = 0x0404,
   GPIO_CHANNEL_PE5 = 0x0405,
   GPIO_CHANNEL_PE6 = 0x0406,
   GPIO_CHANNEL_PE7 = 0x0407,

   GPIO_CHANNEL_PF0 = 0x0500,
   GPIO_CHANNEL_PF1 = 0x0501,
   GPIO_CHANNEL_PF2 = 0x0502,
   GPIO_CHANNEL_PF3 = 0x0503,
   GPIO_CHANNEL_PF4 = 0x0504,
   GPIO_CHANNEL_PF5 = 0x0505,
   GPIO_CHANNEL_PF6 = 0x0506,
   GPIO_CHANNEL_PF7 = 0x0507,

   GPIO_CHANNEL_PG0 = 0x0600,
   GPIO_CHANNEL_PG1 = 0x0601,
   GPIO_CHANNEL_PG2 = 0x0602,
   GPIO_CHANNEL_PG3 = 0x0603,
   GPIO_CHANNEL_PG4 = 0x0604,
   GPIO_CHANNEL_PG5 = 0x0605,
   GPIO_CHANNEL_PG6 = 0x0606,
   GPIO_CHANNEL_PG7 = 0x0607
}gpio_ChannelType;


typedef enum
{
   GPIO_PORTA = (0U),
   GPIO_PORTB,
   GPIO_PORTC,
   GPIO_PORTD,
   GPIO_PORTE,
   GPIO_PORTF,
   GPIO_PORTG
}gpio_PortType;

typedef enum
{
   GPIO_PIN0 = (0U),
   GPIO_PIN1,
   GPIO_PIN2,
   GPIO_PIN3,
   GPIO_PIN4,
   GPIO_PIN5,
   GPIO_PIN6,
   GPIO_PIN7
}gpio_PinType;

typedef enum
{
   GPIO_FALSE = (0U),
   GPIO_TRUE
}gpio_ConfigureAllowedType;

typedef enum
{
   GPIO_PIN_INITIAL_LOW = (0U),
   GPIO_PIN_INITIAL_HIGH
}gpio_PinInitialType;

typedef enum
{
   GPIO_LOW = (0U),
   GPIO_HIGH
}gpio_PinState;

typedef enum
{
   GPIO_INPUT = (0U),
   GPIO_OUTPUT
}gpio_PinInOutType;

typedef struct
{
   gpio_ConfigureAllowedType  gpio_ConfireAllowed;
   gpio_ChannelType           gpio_Pin;
   gpio_PinInOutType          gpio_PinInOut;
   gpio_PinInitialType        gpio_PinInitial;
}gpio_PinConfigType;

//typedef struct
//{
//   gpio_PinConfigType   gpio_PinConfig[MAX_NUM_OF_PINS];
//}gpio_PortConfigType;


typedef struct
{
   gpio_PinConfigType gpio_PinConfig[MAX_NUM_OF_PINS * MAX_NUM_OF_PORTS];
   //gpio_PortConfigType  gpio_PortConfig[MAX_NUM_OF_PORTS];
}gpio_ConfigType;


typedef struct
{
   uint8*       gpio_PortRegister_pui8;
   uint8*       gpio_DirectionRegister_pui8;
   uint8*       gpio_InputRgister_pui8;
} gpio_RegisterAddresstype;

void gpio_WriteChannel(gpio_ChannelType channel, gpio_PinState state);
gpio_PinState gpio_ReadChannel(gpio_ChannelType channel);
void gpio_ToggleChannel(gpio_ChannelType channel);


#endif

