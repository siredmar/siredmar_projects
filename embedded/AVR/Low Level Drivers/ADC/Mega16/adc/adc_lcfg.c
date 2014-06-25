#include "adc_lcfg.h"
#include "adc.h"

extern void adc_Callback();

const adc_configType adc_initialConfiguration_s =
{
		ADC_MODULE_ENABLED,
		ADC_REFERENCE_AVCC,
		ADC_CLOCK_PRESCALER_128,
		ADC_INTERRUPT_DISABLED,
		ADC_TRIGGER_FREE_RUNNING,
		NULL,
		ADC_DATA_RIGHT_ADJUSTED,
		ADC_AVERAGE_20_SAMPLES

};

const void *adc_getlcfgdata(void)
{
   return ((void*) &adc_initialConfiguration_s);
}
