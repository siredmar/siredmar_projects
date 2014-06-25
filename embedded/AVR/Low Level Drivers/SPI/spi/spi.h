
#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "spi_lcfg.h"
#include "spi_cfg.h"
#include "../gpio/gpio.h"

#define SPI_CALLBACK_NULL_PTR ((void*)0)

typedef void (*spi_callbackType)(void);

typedef enum
{
	SPI_INTERRUPT_DISABLED = 0U,
	SPI_INTERRUPT_ENABLED
}spi_spiInterruptControlType;

typedef enum
{
	SPI_MODULE_DISABLED = 0U,
	SPI_MODULE_ENABLED
}spi_spiEnableControlType;

typedef enum
{
	SPI_LSB_FIRST = 0U,
	SPI_MSB_FIRST
}spi_spiDataOrderControlType;

typedef enum
{
	SPI_SLAVE_MODE = 0U,
	SPI_MASTER_MODE
}spi_spiMasterSlaveControlType;

typedef enum
{
	SPI_CPOL_0 = 0U,
	SPI_CPOL_1
}spi_spiClockPolarityControlType;

typedef enum
{
	SPI_CPHA_0 = 0U,
	SPI_CPHA_1
}spi_spiDataPhaseControlType;

/*
* CKP: 0, DAP: 0
* Clock Idle: High
* Data Phase: Latch on Trailing Edge
* ________     ___     ___     ___     ___     ___     ___     ___     ___     _____
*         |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|
* __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
* __________/ D7\___/ D6\___/ D5\___/ D4\___/ D4\___/ D3\___/ D2\___/ D1\___/ D0\___
*             ^       ^       ^       ^       ^       ^       ^       ^       ^
*             |       |       |       |       |       |       |       |       |
*___________________________________________________________________________________
* CKP: 0, DAP: 1
* Clock Idle: High
* Data Phase: Latch on Leading Edge
* ________     ___     ___     ___     ___     ___     ___     ___     ___     _____
*         |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|  
* ______ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ _______
* ______/ D7\___/ D6\___/ D5\___/ D4\___/ D4\___/ D3\___/ D2\___/ D1\___/ D0\_______
*         ^       ^       ^       ^       ^       ^       ^       ^       ^
*         |       |       |       |       |       |       |       |       |
*____________________________________________________________________________________
* CKP: 1, DAP: 0
* Clock Idle: Low
* Data Phase: Latch on Trailing Edge
*          ___     ___     ___     ___     ___     ___     ___     ___     ___
* ________|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |_____
* __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
* __________/ D7\___/ D6\___/ D5\___/ D4\___/ D4\___/ D3\___/ D2\___/ D1\___/ D0\___
*             ^       ^       ^       ^       ^       ^       ^       ^       ^
*             |       |       |       |       |       |       |       |       |
*___________________________________________________________________________________
* CKP: 1, DAP: 1
* Clock Idle: Low
* Data Phase: Latch on Leading Edge
*          ___     ___     ___     ___     ___     ___     ___     ___     ___  
* ________|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |______
* ______ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ________
* ______/ D7\___/ D6\___/ D5\___/ D4\___/ D4\___/ D3\___/ D2\___/ D1\___/ D0\________
*         ^       ^       ^       ^       ^       ^       ^       ^       ^
*         |       |       |       |       |       |       |       |       |
*____________________________________________________________________________________
*/

typedef enum
{
	SPI_CLOCK_PRESCALER_DIV_4 = 0U,
	SPI_CLOCK_PRESCALER_DIV_16,
	SPI_CLOCK_PRESCALER_DIV_64,
	SPI_CLOCK_PRESCALER_DIV_128
}spi_spiClockPrescalerControlType;

typedef enum
{
	SPI_DOUBLE_SPEED_DISABLED = 0U,
	SPI_DOUBLE_SPEED_ENABLED
}spi_spiDoubleSpeedControlType;

typedef enum
{
	SPI_CS_ACTIVE_LOW = 0U,
	SPI_CS_ACTIVE_HIGH
}spi_csActiveLevelControlType;

typedef struct
{
	spi_spiEnableControlType         spi_spiControl_e;
	spi_spiMasterSlaveControlType    spi_MasterSlaveControl_e;
	spi_spiInterruptControlType      spi_interruptControl_e;
	spi_callbackType                 spi_callback_pv;
	spi_spiDataOrderControlType      spi_dataOrderControl_e;
	spi_spiClockPolarityControlType  spi_cpol_e;
	spi_spiDataPhaseControlType      spi_cpha_e;
	spi_spiClockPrescalerControlType spi_clockPrescaler_e;
	spi_spiDoubleSpeedControlType    spi_doubleSpeed_e;
}spi_configType;

typedef struct
{
   uint8* spi_ControlRegister_pui8;
   uint8* spi_SpecialFunctionRegister_pui8;
   uint8* spi_DataRegister_pui8;
}spi_RegisterAddressType;


void spi_init(void);
uint8 spi_sendData(uint8 data_ui8, gpio_ChannelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e, uint8 start, uint8 stop);
static void spi_highCS(gpio_ChannelType spi_chipSelect_e);
static void spi_lowCS(gpio_ChannelType spi_chipSelect_e);


#endif
