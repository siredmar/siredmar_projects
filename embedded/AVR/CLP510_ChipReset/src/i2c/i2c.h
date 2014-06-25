
#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "i2c_lcfg.h"
#include "i2c_cfg.h"
#include "../dio/dio.h"

typedef void (*i2c_callbackType);


typedef enum
{
	I2C_INTERRUPT_DISABLED = 0,
	I2C_INTERRUPT_ENABLED
}i2c_i2cInterruptControlType;

typedef enum
{
	I2C_MODULE_DISABLED = 0,
	I2C_MODULE_ENABLED
}i2c_i2cEnableControlType;

typedef enum
{
	I2C_LSB_FIRST = 0,
	I2C_MSB_FIRST
}i2c_i2cDataOrderControlType;

typedef enum
{
	I2C_SLAVE_MODE = 0,
	I2C_MASTER_MODE
}i2c_i2cMasterSlaveControlType;

typedef enum
{
	I2C_CPOL_0 = 0,
	I2C_CPOL_1
}i2c_i2cClockPolarityControlType;

typedef enum
{
	I2C_CPHA_0 = 0,
	I2C_CPHA_1
}i2c_i2cDataPhaseControlType;

typedef enum
{
	I2C_CLOCK_PRESCALER_DIV_4 = 0,
	I2C_CLOCK_PRESCALER_DIV_16,
	I2C_CLOCK_PRESCALER_DIV_64,
	I2C_CLOCK_PRESCALER_DIV_128
}i2c_i2cClockPrescalerControlType;

typedef enum
{
	I2C_DOUBLE_SPEED_DISABLED = 0,
	I2C_DOUBLE_SPEED_ENABLED
}i2c_i2cDoubleSpeedControlType;

typedef enum
{
	I2C_CS_ACTIVE_LOW = 0,
	I2C_CS_ACTIVE_HIGH
}i2c_csActiveLevelControlType;

typedef struct
{
	i2c_i2cEnableControlType         i2c_i2cControl_e;
	i2c_i2cMasterSlaveControlType    i2c_MasterSlaveControl_e;
	i2c_i2cInterruptControlType      i2c_interruptControl_e;
	i2c_callbackType                 i2c_callback_pv;
	i2c_i2cDataOrderControlType      i2c_dataOrderControl_e;
	i2c_i2cClockPolarityControlType  i2c_cpol_e;
	i2c_i2cDataPhaseControlType      i2c_cpha_e;
	i2c_i2cClockPrescalerControlType i2c_clockPrescaler_e;
	i2c_i2cDoubleSpeedControlType    i2c_doubleSpeed_e;
}i2c_configType;

void i2c_init();

void i2c_sendData(uint8 data_ui8, dio_channelType i2c_chipSelect_e, i2c_csActiveLevelControlType i2c_csLevel_e);


uint8 i2c_receiveData(uint8 data_ui8, dio_channelType i2c_chipSelect_e, i2c_csActiveLevelControlType i2c_csLevel_e);

static void i2c_highCS(dio_channelType i2c_chipSelect_e);

static void i2c_lowCS(dio_channelType i2c_chipSelect_e);


#endif
