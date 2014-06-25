
#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "spi_lcfg.h"
#include "spi_cfg.h"
#include "../dio/dio.h"

typedef void (*spi_callbackType);


typedef enum
{
	SPI_INTERRUPT_DISABLED = 0,
	SPI_INTERRUPT_ENABLED
}spi_spiInterruptControlType;

typedef enum
{
	SPI_MODULE_DISABLED = 0,
	SPI_MODULE_ENABLED
}spi_spiEnableControlType;

typedef enum
{
	SPI_LSB_FIRST = 0,
	SPI_MSB_FIRST
}spi_spiDataOrderControlType;

typedef enum
{
	SPI_SLAVE_MODE = 0,
	SPI_MASTER_MODE
}spi_spiMasterSlaveControlType;

typedef enum
{
	SPI_CPOL_0 = 0,
	SPI_CPOL_1
}spi_spiClockPolarityControlType;

typedef enum
{
	SPI_CPHA_0 = 0,
	SPI_CPHA_1
}spi_spiDataPhaseControlType;

typedef enum
{
	SPI_CLOCK_PRESCALER_DIV_4 = 0,
	SPI_CLOCK_PRESCALER_DIV_16,
	SPI_CLOCK_PRESCALER_DIV_64,
	SPI_CLOCK_PRESCALER_DIV_128
}spi_spiClockPrescalerControlType;

typedef enum
{
	SPI_DOUBLE_SPEED_DISABLED = 0,
	SPI_DOUBLE_SPEED_ENABLED
}spi_spiDoubleSpeedControlType;

typedef enum
{
	SPI_CS_ACTIVE_LOW = 0,
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

void spi_init();

void spi_sendData(uint8 data_ui8, dio_channelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e);


uint8 spi_receiveData(uint8 data_ui8, dio_channelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e);

static void spi_highCS(dio_channelType spi_chipSelect_e);

static void spi_lowCS(dio_channelType spi_chipSelect_e);


#endif
