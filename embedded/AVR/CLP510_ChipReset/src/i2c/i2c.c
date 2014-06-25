
#include "i2c.h"

static i2c_configType* lcfgConfigPtr_ps;

void i2c_init()
{
   i2c_i2cEnableControlType         i2c_i2cControlLocal_e;
   i2c_i2cMasterSlaveControlType    i2c_MasterSlaveControlLocal_e;
   i2c_i2cInterruptControlType      i2c_interruptControlLocal_e;
   i2c_i2cDataOrderControlType      i2c_dataOrderControlLocal_e;
   i2c_i2cClockPolarityControlType  i2c_cpolLocal_e;
   i2c_i2cDataPhaseControlType      i2c_cphaLocal_e;
   i2c_i2cClockPrescalerControlType i2c_clockPrescalerLocal_e;
   i2c_i2cDoubleSpeedControlType    i2c_doubleSpeedLocal_e;

   i2c_i2cControlLocal_e         = lcfgConfigPtr_ps->i2c_i2cControl_e;
   i2c_MasterSlaveControlLocal_e = lcfgConfigPtr_ps->i2c_MasterSlaveControl_e;
   i2c_interruptControlLocal_e   = lcfgConfigPtr_ps->i2c_interruptControl_e;
   i2c_dataOrderControlLocal_e   = lcfgConfigPtr_ps->i2c_dataOrderControl_e;
   i2c_cpolLocal_e               = lcfgConfigPtr_ps->i2c_cpol_e;
   i2c_cphaLocal_e               = lcfgConfigPtr_ps->i2c_cpha_e;
   i2c_clockPrescalerLocal_e     = lcfgConfigPtr_ps->i2c_clockPrescaler_e;
   i2c_doubleSpeedLocal_e        = lcfgConfigPtr_ps->i2c_doubleSpeed_e;

	lcfgConfigPtr_ps = (i2c_configType*)i2c_getlcfgdata();

	DDR_I2C &= ~((1<<DD_MOSI)|(1<<DD_MISO)|(1<<DD_SS)|(1<<DD_SCK));

	DDR_I2C |= ((1<<DD_MOSI)|(1<<DD_SS)|(1<<DD_SCK));

	SPCR = ((i2c_interruptControlLocal_e   << I2C_I2CE_BIT_POSITION_UI8) | \
			  (i2c_i2cControlLocal_e         << I2C_SPE_BIT_POSITION_UI8)  | \
			  (i2c_dataOrderControlLocal_e   << I2C_DORD_BIT_POSITION_UI8) | \
			  (i2c_MasterSlaveControlLocal_e << I2C_MSTR_BIT_POSITION_UI8) | \
			  (i2c_cpolLocal_e               << I2C_CPOL_BIT_POSITION_UI8) | \
			  (i2c_cphaLocal_e               << I2C_CPHA_BIT_POSITION_UI8) | \
			  (i2c_clockPrescalerLocal_e     << I2C_SPR_BIT_POSITION_UI8));

	SPSR = (i2c_doubleSpeedLocal_e << I2C_SPR_BIT_POSITION_UI8);
	sei();
}

void i2c_sendData(uint8 data_ui8, dio_channelType i2c_chipSelect_e, i2c_csActiveLevelControlType i2c_csLevel_e)
{

	if(i2c_csLevel_e == I2C_CS_ACTIVE_LOW)
	{
		i2c_lowCS(i2c_chipSelect_e);
	}
	else
	{
		i2c_highCS(i2c_chipSelect_e);
	}

	/* send data */
	SPDR = data_ui8;

	/* wait for transmission finished bit */
	while (!(SPSR & (1 << I2CF)));


	data_ui8 = SPDR; // dummy readout

	//_delay_ms(1000);
	if(i2c_csLevel_e == I2C_CS_ACTIVE_LOW)
	{
		i2c_highCS(i2c_chipSelect_e);
	}
	else
	{
		i2c_lowCS(i2c_chipSelect_e);
	}

}

uint8 i2c_receiveData(uint8 data_ui8, dio_channelType i2c_chipSelect_e, i2c_csActiveLevelControlType i2c_csLevel_e)
{
	/* send data */
	i2c_sendData(data_ui8, i2c_chipSelect_e, i2c_csLevel_e);

	/* send dummy byte */
	i2c_sendData((uint8)0xAA, i2c_chipSelect_e, i2c_csLevel_e);

	/* return reception data */
	return SPDR;
}

static void i2c_highCS(dio_channelType i2c_chipSelect_e)
{
	dio_writeChannel(i2c_chipSelect_e, DIO_HIGH);
}

static void i2c_lowCS(dio_channelType i2c_chipSelect_e)
{
	dio_writeChannel(i2c_chipSelect_e, DIO_LOW);
}

ISR(I2C_STC_vect)
{
	if(dio_readChannel(DIO_CHANNEL_PB7) == DIO_LOW)
		dio_writeChannel(DIO_CHANNEL_PB7, DIO_HIGH);
	else
		dio_writeChannel(DIO_CHANNEL_PB7, DIO_LOW);
}
