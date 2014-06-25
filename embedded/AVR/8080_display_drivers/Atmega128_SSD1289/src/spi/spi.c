
#include "spi.h"

static spi_configType* lcfgConfigPtr_ps;

void spi_init()
{
   spi_spiEnableControlType         spi_spiControlLocal_e;
   spi_spiMasterSlaveControlType    spi_MasterSlaveControlLocal_e;
   spi_spiInterruptControlType      spi_interruptControlLocal_e;
   spi_spiDataOrderControlType      spi_dataOrderControlLocal_e;
   spi_spiClockPolarityControlType  spi_cpolLocal_e;
   spi_spiDataPhaseControlType      spi_cphaLocal_e;
   spi_spiClockPrescalerControlType spi_clockPrescalerLocal_e;
   spi_spiDoubleSpeedControlType    spi_doubleSpeedLocal_e;

   spi_spiControlLocal_e         = lcfgConfigPtr_ps->spi_spiControl_e;
   spi_MasterSlaveControlLocal_e = lcfgConfigPtr_ps->spi_MasterSlaveControl_e;
   spi_interruptControlLocal_e   = lcfgConfigPtr_ps->spi_interruptControl_e;
   spi_dataOrderControlLocal_e   = lcfgConfigPtr_ps->spi_dataOrderControl_e;
   spi_cpolLocal_e               = lcfgConfigPtr_ps->spi_cpol_e;
   spi_cphaLocal_e               = lcfgConfigPtr_ps->spi_cpha_e;
   spi_clockPrescalerLocal_e     = lcfgConfigPtr_ps->spi_clockPrescaler_e;
   spi_doubleSpeedLocal_e        = lcfgConfigPtr_ps->spi_doubleSpeed_e;

	lcfgConfigPtr_ps = (spi_configType*)spi_getlcfgdata();

	DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_MISO)|(1<<DD_SS)|(1<<DD_SCK));

	DDR_SPI |= ((1<<DD_MOSI)|(1<<DD_SS)|(1<<DD_SCK));

	SPSR = (spi_doubleSpeedLocal_e << SPI_SPR_BIT_POSITION_UI8);

	SPCR = ((spi_interruptControlLocal_e   << SPI_SPIE_BIT_POSITION_UI8) | \
			  (spi_spiControlLocal_e         << SPI_SPE_BIT_POSITION_UI8)  | \
			  (spi_dataOrderControlLocal_e   << SPI_DORD_BIT_POSITION_UI8) | \
			  (spi_MasterSlaveControlLocal_e << SPI_MSTR_BIT_POSITION_UI8) | \
			  (spi_cpolLocal_e               << SPI_CPOL_BIT_POSITION_UI8) | \
			  (spi_cphaLocal_e               << SPI_CPHA_BIT_POSITION_UI8) | \
			  (spi_clockPrescalerLocal_e     << SPI_SPR_BIT_POSITION_UI8));

	sei();
}

void spi_sendData(uint8 data_ui8, dio_channelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e)
{

	if(spi_csLevel_e == SPI_CS_ACTIVE_LOW)
	{
		spi_lowCS(spi_chipSelect_e);
	}
	else
	{
		spi_highCS(spi_chipSelect_e);
	}

	/* send data */
	SPDR = data_ui8;

	/* wait for transmission finished bit */
	while (!(SPSR & (1 << SPIF)));


	data_ui8 = SPDR; // dummy readout

	//_delay_ms(1000);
	if(spi_csLevel_e == SPI_CS_ACTIVE_LOW)
	{
		spi_highCS(spi_chipSelect_e);
	}
	else
	{
		spi_lowCS(spi_chipSelect_e);
	}

}

uint8 spi_receiveData(uint8 data_ui8, dio_channelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e)
{
	/* send data */
	spi_sendData(data_ui8, spi_chipSelect_e, spi_csLevel_e);

	/* send dummy byte */
	spi_sendData((uint8)0xAA, spi_chipSelect_e, spi_csLevel_e);

	/* return reception data */
	return SPDR;
}

static void spi_highCS(dio_channelType spi_chipSelect_e)
{
	dio_writeChannel(spi_chipSelect_e, DIO_HIGH);
}

static void spi_lowCS(dio_channelType spi_chipSelect_e)
{
	dio_writeChannel(spi_chipSelect_e, DIO_LOW);
}

ISR(SPI_STC_vect)
{
	if(dio_readChannel(DIO_CHANNEL_PB7) == DIO_LOW)
		dio_writeChannel(DIO_CHANNEL_PB7, DIO_HIGH);
	else
		dio_writeChannel(DIO_CHANNEL_PB7, DIO_LOW);
}
