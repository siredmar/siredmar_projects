
#include "spi.h"

static spi_configType		*lcfgConfigPtr_ps;
static spi_callbackType		 spi_callbackLocal_pv;
static spi_spiInterruptControlType  spi_interruptControlLocal_e;

volatile const spi_RegisterAddressType spi_RegisterAdress_as =
{
	(uint8*) SPI_SPCR_ADDRESS, 
    (uint8*) SPI_SPSR_ADDRESS, 
    (uint8*) SPI_SPDR_ADDRESS 
};

void spi_init(void)
{
   spi_spiEnableControlType         spi_spiControlLocal_e;
   spi_spiMasterSlaveControlType    spi_MasterSlaveControlLocal_e;
   spi_spiDataOrderControlType      spi_dataOrderControlLocal_e;
   spi_spiClockPolarityControlType  spi_cpolLocal_e;
   spi_spiDataPhaseControlType      spi_cphaLocal_e;
   spi_spiClockPrescalerControlType spi_clockPrescalerLocal_e;
   spi_spiDoubleSpeedControlType    spi_doubleSpeedLocal_e;
   
   
   lcfgConfigPtr_ps = (spi_configType*)spi_getlcfgdata();

   spi_spiControlLocal_e         = lcfgConfigPtr_ps->spi_spiControl_e;
   spi_MasterSlaveControlLocal_e = lcfgConfigPtr_ps->spi_MasterSlaveControl_e;
   spi_interruptControlLocal_e   = lcfgConfigPtr_ps->spi_interruptControl_e;
   spi_dataOrderControlLocal_e   = lcfgConfigPtr_ps->spi_dataOrderControl_e;
   spi_cpolLocal_e               = lcfgConfigPtr_ps->spi_cpol_e;
   spi_cphaLocal_e               = lcfgConfigPtr_ps->spi_cpha_e;
   spi_clockPrescalerLocal_e     = lcfgConfigPtr_ps->spi_clockPrescaler_e;
   spi_doubleSpeedLocal_e        = lcfgConfigPtr_ps->spi_doubleSpeed_e;
   spi_callbackLocal_pv          = lcfgConfigPtr_ps->spi_callback_pv;
   
   *(spi_RegisterAdress_as.spi_SpecialFunctionRegister_pui8)  = (spi_doubleSpeedLocal_e << SPI_SPR_BIT_POSITION_UI8);
   
   *(spi_RegisterAdress_as.spi_ControlRegister_pui8) =  ((spi_interruptControlLocal_e   << SPI_SPIE_BIT_POSITION_UI8) | \
																(spi_spiControlLocal_e         << SPI_SPE_BIT_POSITION_UI8)  | \
																(spi_dataOrderControlLocal_e   << SPI_DORD_BIT_POSITION_UI8) | \
																(spi_MasterSlaveControlLocal_e << SPI_MSTR_BIT_POSITION_UI8) | \
																(spi_cpolLocal_e               << SPI_CPOL_BIT_POSITION_UI8) | \
																(spi_cphaLocal_e               << SPI_CPHA_BIT_POSITION_UI8) | \
																(spi_clockPrescalerLocal_e     << SPI_SPR_BIT_POSITION_UI8));
}

uint8 spi_sendData(uint8 data_ui8, gpio_ChannelType spi_chipSelect_e, spi_csActiveLevelControlType spi_csLevel_e, uint8 start, uint8 stop)
{
	uint8 return_ui8;
	if(start){
		if(spi_csLevel_e == SPI_CS_ACTIVE_LOW)
		{
			spi_lowCS(spi_chipSelect_e);
		}
		else
		{
			spi_highCS(spi_chipSelect_e);
		}
	}
	
	/* send data */
	*(spi_RegisterAdress_as.spi_DataRegister_pui8) = data_ui8;

	if(spi_interruptControlLocal_e == SPI_INTERRUPT_DISABLED)
	{
		/* wait for transmission finished bit */
		while (!(*(spi_RegisterAdress_as.spi_SpecialFunctionRegister_pui8) & (1 << SPI_SPIF_BIT_POSITION_UI8)));
	}
	else
	{
		/* NOTE: SPI Interrupt and Callback MUST contain valid values in Linktime-Config! */
	}

	if(stop)
	{
		if(spi_csLevel_e == SPI_CS_ACTIVE_LOW)
		{
			spi_highCS(spi_chipSelect_e);
		}
		else
		{
			spi_lowCS(spi_chipSelect_e);
		}
	}	
	return_ui8 = *(spi_RegisterAdress_as.spi_DataRegister_pui8);
	return return_ui8;
}

static void spi_highCS(gpio_ChannelType spi_chipSelect_e)
{
	gpio_WriteChannel(spi_chipSelect_e, GPIO_HIGH);
}

static void spi_lowCS(gpio_ChannelType spi_chipSelect_e)
{
	gpio_WriteChannel(spi_chipSelect_e, GPIO_LOW);
}

ISR(SPI_STC_vect)
{
	if(spi_callbackLocal_pv != NULL)
	{
		spi_callbackLocal_pv();
	}
	else
	{
		/* do nothing */
	}
}
