
#include "adc.h"

static adc_configType				*lcfgConfigPtr_ps;
static adc_callbackType         	adc_callback_pv;
static adc_InterruptControlType		adc_InterruptControlLocal_e;
static adc_AverageControlType_e 	adc_averageControlLocal_e;
static adc_ReferenceSelectionType 	adc_ReferenceControlLocal_e;

volatile const adc_RegisterAddressType adc_RegisterAdress_as =
{
	(uint8*) ADC_ADMUX_ADDRESS,
    (uint8*) ADC_ADCSRA_ADDRESS,
    (uint8*) ADC_ADCH_ADDRESS,
    (uint8*) ADC_ADCL_ADDRESS,
    (uint8*) ADC_SFIOR_ADDRESS
};

void adc_init(void)
{
   	uint8 adc_dummy_readout_ui8 = 0;
	adc_EnableControlType 			adc_ControlLocal_e;

	adc_ClockPrescalerControlType 	adc_ClockPrescalerControlLocal_e;
	adc_TriggerControlType			adc_TriggerControlLocal_e;
	adc_DataAdjustmentControlType	adc_DataAdjustmentControlLocal_e;
	adc_AverageControlType_e 		adc_averageControl_e;

	lcfgConfigPtr_ps = (adc_configType*)adc_getlcfgdata();

	adc_ControlLocal_e 					= lcfgConfigPtr_ps->adc_Control_e;
	adc_ReferenceControlLocal_e  		= lcfgConfigPtr_ps->adc_ReferenceControl_e;
	adc_ClockPrescalerControlLocal_e	= lcfgConfigPtr_ps->adc_ClockPrescalerControl_e;
	adc_TriggerControlLocal_e			= lcfgConfigPtr_ps->adc_TriggerControl_e;
	adc_DataAdjustmentControlLocal_e	= lcfgConfigPtr_ps->adc_DataAdjustmentControl_e;
	adc_InterruptControlLocal_e	 		= lcfgConfigPtr_ps->adc_InterruptControl_e;
	adc_callback_pv						= lcfgConfigPtr_ps->adc_callback_pv;
	adc_averageControlLocal_e 			= lcfgConfigPtr_ps->adc_averageControl_e;

	*(adc_RegisterAdress_as.adc_ControlAndStatusRegister_pui8) =	(adc_ControlLocal_e << ADC_ADEN_BIT_POSITION_UI8) | \
																	(adc_InterruptControlLocal_e << ADC_ADIE_BIT_POSITION_UI8) | \
																	(adc_ClockPrescalerControlLocal_e << ADC_ADPS0_BIT_POSITION_UI8);

	/* Dummy read out */
	*(adc_RegisterAdress_as.adc_ControlAndStatusRegister_pui8) |= (1 << ADC_ADSC_BIT_POSITION_UI8);
	*(adc_RegisterAdress_as.adc_MuxRegister_pui8) = (adc_ReferenceControlLocal_e << ADC_REFS0_BIT_POSITION_UI8);

	if(adc_TriggerControlLocal_e != ADC_SINGLE_SHOT)
	{
		*(adc_RegisterAdress_as.adc_ControlAndStatusRegister_pui8)  |=	(1 << ADC_ADATE_BIT_POSITION_UI8);
		*(adc_RegisterAdress_as.adc_SpecialFunctionIoRegister_pui8) |=  (adc_TriggerControlLocal_e << ADC_ADTS0_BIT_POSITION_UI8);
	}






}

static uint16 adc_getAdcResult()
{
	uint16 adc_result_ui16 = 0;

	uint8 adc_result_high_ui8 = 0;
	uint8 adc_result_low_ui8 = 0;

	adc_result_high_ui8 = *(adc_RegisterAdress_as.adc_DataRegisterHigh_pui8);
	adc_result_low_ui8 = *(adc_RegisterAdress_as.adc_DataRegisterLow_pui8);
	adc_result_ui16 += (adc_result_high_ui8 << 8) + adc_result_low_ui8;

	return adc_result_ui16;
}

uint16 adc_readChannel(adc_ChannelType channel_e)
{
	uint8 adc_average_cnt_ui8 = 0;
	uint16 adc_result_ui16 = 0;

	*(adc_RegisterAdress_as.adc_MuxRegister_pui8) = channel_e | (adc_ReferenceControlLocal_e << ADC_REFS0_BIT_POSITION_UI8);

	for(adc_average_cnt_ui8 = 0; adc_average_cnt_ui8 <= adc_averageControlLocal_e; adc_average_cnt_ui8++)
	{
		*(adc_RegisterAdress_as.adc_ControlAndStatusRegister_pui8) |= (1 << ADC_ADSC_BIT_POSITION_UI8);

		if(adc_InterruptControlLocal_e == ADC_INTERRUPT_DISABLED)
		{
			while(*(adc_RegisterAdress_as.adc_ControlAndStatusRegister_pui8) & (1 << ADC_ADIF_BIT_POSITION_UI8));
			adc_result_ui16 += adc_getAdcResult() / 2;
		}
		else
		{
			/* NOTE: Interrupts and Callback Function must be configured correctly! */
		}
	}
return adc_result_ui16;
}

ISR(ADC_vect)
{

	static uint8 adc_average_cnt_ui8 = 0;
	static uint16 adc_result_ui16 = 0;

	adc_result_ui16 += adc_getAdcResult() / 2;
	adc_average_cnt_ui8++;

	if(adc_average_cnt_ui8 == adc_averageControlLocal_e)
	{
		if(adc_callback_pv != NULL)
		{
			adc_callback_pv();
			adc_result_ui16 = 0;
		}
		else
		{
			/* do nothing */
		}
	}
}


