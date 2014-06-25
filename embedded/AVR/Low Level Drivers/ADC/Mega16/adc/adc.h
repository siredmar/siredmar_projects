
#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "adc_lcfg.h"
#include "adc_cfg.h"

#define ADC_CALLBACK_NULL_PTR ((void*)0)

typedef void (*adc_callbackType)(void);

typedef enum
{
	ADC_REFERENCE_AREF = 0U,
	ADC_REFERENCE_AVCC = 1U,
	ADC_REFERENCE_INTERNAL_2V56 = 3U
}adc_ReferenceSelectionType;

typedef enum
{
	ADC_CHANNEL_0 = 0U,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7
}adc_ChannelType;

typedef enum
{
	ADC_INTERRUPT_DISABLED = 0U,
	ADC_INTERRUPT_ENABLED
}adc_InterruptControlType;

typedef enum
{
	ADC_MODULE_DISABLED = 0U,
	ADC_MODULE_ENABLED
}adc_EnableControlType;

typedef enum
{
	ADC_SINGLE_SHOT						= 0xFFU,
	ADC_TRIGGER_FREE_RUNNING 			= 0U,
	ADC_TRIGGER_ANALOG_COMPERATOR 		= 0x01U,
	ADC_TRIGGER_EXT_INT0 				= 0x02U,
	ADC_TRIGGER_TIMER0_COMPARE_MATCH 	= 0x03U,
	ADC_TRIGGER_TIMER0_OVERFLOW 		= 0x04U,
	ADC_TRIGGER_TIMER1_OVERFLOW 		= 0x05U,
	ADC_TRIGGER_TIMER1_COMPARE_MATCH 	= 0x06U,
	ADC_TRIGGER_TIMER1_CAPTURE_EVENT 	= 0x07U
}adc_TriggerControlType;

typedef enum
{
	ADC_CLOCK_PRESCALER_2   = 1U,
	ADC_CLOCK_PRESCALER_4   = 2U,
	ADC_CLOCK_PRESCALER_8   = 3U,
	ADC_CLOCK_PRESCALER_16  = 4U,
	ADC_CLOCK_PRESCALER_32  = 5U,
	ADC_CLOCK_PRESCALER_64  = 6U,
	ADC_CLOCK_PRESCALER_128 = 7U
}adc_ClockPrescalerControlType;


typedef enum
{
	ADC_DATA_RIGHT_ADJUSTED = 0U,
	ADC_DATA_LEFT_ADJUSTED
}adc_DataAdjustmentControlType;

typedef enum
{
	ADC_AVERAGING_DISABLED 	= 1U,
	ADC_AVERAGE_5_SAMPLES	= 5U,
	ADC_AVERAGE_10_SAMPLES	= 10U,
	ADC_AVERAGE_20_SAMPLES	= 20U,
	ADC_AVERAGE_50_SAMPLES	= 50U,
}adc_AverageControlType_e;

typedef struct
{
	adc_EnableControlType 			adc_Control_e;
	adc_ReferenceSelectionType 		adc_ReferenceControl_e;
	adc_ClockPrescalerControlType 	adc_ClockPrescalerControl_e;
	adc_InterruptControlType		adc_InterruptControl_e;
	adc_TriggerControlType			adc_TriggerControl_e;
	adc_callbackType                adc_callback_pv;
	adc_DataAdjustmentControlType	adc_DataAdjustmentControl_e;
	adc_AverageControlType_e		adc_averageControl_e;
}adc_configType;

typedef struct
{
   uint8* adc_MuxRegister_pui8;
   uint8* adc_ControlAndStatusRegister_pui8;
   uint8* adc_DataRegisterHigh_pui8;
   uint8* adc_DataRegisterLow_pui8;
   uint8* adc_SpecialFunctionIoRegister_pui8;
}adc_RegisterAddressType;

#endif
