#include "ADC.h"


typedef volatile uint8_t* const pu8ADCRegisterAddress_t;

/* ADC Registers */
#define ADMUX_R																	*((pu8ADCRegisterAddress_t) 0x27)
#define ADCSRA_R																	*((pu8ADCRegisterAddress_t) 0x26)
#define ADCH_R																		*((pu8ADCRegisterAddress_t) 0x25)
#define ADCL_R																		*((pu8ADCRegisterAddress_t) 0x24)
#define SFIOR_R																	*((pu8ADCRegisterAddress_t) 0x50)

/* Internal Macros */
#define ADC_REFERENCE_SELECTION_BITS_MIN_VALUE							-1l
#define ADC_REFERENCE_SELECTION_BITS_MAX_VALUE							4u
#define ADC_REFERENCE_SELECTION_BITS_NOT_VALID_VALUE					2u
#define ADC_LEFT_ADJUST_RESULT_MIN_VALUE									-1l
#define ADC_LEFT_ADJUST_RESULT_MAX_VALUE									2u
#define ADC_PRESCALER_SELECT_BITS_MIN_VALUE								-1l
#define ADC_PRESCALER_SELECT_BITS_MAX_VALUE								8u
#define ADC_LEFT_ADJUST_RESULT_BIT											5u
#define ADC_REFERENCE_SELECT_START_BIT										6u
#define ADC_REFERENCE_SELECT_MASK											0x03
#define ADC_PRESCALER_SELECT_START_BIT										0u
#define ADC_PRESCALER_SELECT_VALUE(PRESCALER_SELECT)					(PRESCALER_SELECT + 1)					
#define ADC_PRESCALER_SELECT_MASK											0x07
#define ADC_MODULE_EN_BIT														7u
#define ADC_CHANNEL_SELECT_START_BIT										0u
#define ADC_CHANNEL_SELECT_MASK												0x1F
#define ADC_START_CONVERSION_EN_BIT											6u
#define ADC_CONVERSION_COMPLETE_FLAG_BIT									4u
#define ADC_VALUE_RIGHT_ADJUSTED												((ADCL_R) | ((ADCH_R & 0x03) << 8))
#define ADC_VALUE_LEFT_ADJUSTED												(((ADCL_R & 0xC0) >> 6) | (ADCH_R << 2))

typedef enum {ADC_INIT_UNDONE, ADC_INIT_DONE} enuADCState_t;
static enuADCState_t enuADCState = ADC_INIT_UNDONE;

static enuADCLeftAdjustResult_t enuADCLeftAdjustResultState;


/*************************************************************************************************
* Parameters	: enuADCReferenceSelectionBits, enuADCLeftAdjustResult, enuADCPrescalerSelectBits
* Return Value	: enuErrorStatus_t
* Description  : Initialize ADC module according to the configuration parameters
*************************************************************************************************/
enuErrorStatus_t ADC_Init(enuADCReferenceSelectionBits_t enuADCReferenceSelectionBits, enuADCLeftAdjustResult_t enuADCLeftAdjustResult, enuADCPrescalerSelectBits_t enuADCPrescalerSelectBits)
{
	enuErrorStatus_t enuRetVar;
    
	if((enuADCReferenceSelectionBits > ADC_REFERENCE_SELECTION_BITS_MIN_VALUE)				&& (enuADCReferenceSelectionBits < ADC_REFERENCE_SELECTION_BITS_MAX_VALUE) &&
		(enuADCReferenceSelectionBits != ADC_REFERENCE_SELECTION_BITS_NOT_VALID_VALUE)	&& (enuADCLeftAdjustResult > ADC_LEFT_ADJUST_RESULT_MIN_VALUE)					&& 
		(enuADCLeftAdjustResult < ADC_LEFT_ADJUST_RESULT_MAX_VALUE)								&& (enuADCPrescalerSelectBits > ADC_PRESCALER_SELECT_BITS_MIN_VALUE)			&& 
		(enuADCPrescalerSelectBits < ADC_PRESCALER_SELECT_BITS_MAX_VALUE))
	{	   
		/* Selecting whether the voltage reference is AREF, AVCC or Internal VREF */
		ASSIGN_BITS(ADMUX_R, ADC_REFERENCE_SELECT_START_BIT, enuADCReferenceSelectionBits, ADC_REFERENCE_SELECT_MASK);
		/* Selecting whether the output is right adjusted or left adjusted */
		ASSIGN_BIT(ADMUX_R, ADC_LEFT_ADJUST_RESULT_BIT, enuADCLeftAdjustResult);
		/* Saving the state of left adjust result into a temporary variable to be used in the other API */
		enuADCLeftAdjustResultState = enuADCLeftAdjustResult;
		/* Selecting the value of the prescaler divisor factor */
		ASSIGN_BITS(ADCSRA_R, ADC_PRESCALER_SELECT_START_BIT, ADC_PRESCALER_SELECT_VALUE(enuADCPrescalerSelectBits), ADC_PRESCALER_SELECT_MASK);
		/* Enabling the ADC module */
		SET_BIT(ADCSRA_R, ADC_MODULE_EN_BIT);
		enuADCState = ADC_INIT_DONE;
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;
}

/*************************************************************************************************
* Parameters	: enuAnalogChannel, pu16Data
* Return Value	: enuErrorStatus_t
* Description  : Initiate an analog read from the selected channel
*************************************************************************************************/
enuErrorStatus_t ADC_ReadChannel(enuADCAnalogChannel_t enuAnalogChannel, uint16_t* pu16Data)
{
	enuErrorStatus_t enuRetVar;
	
   if(enuADCState == ADC_INIT_DONE)
   {
	   /* Selecting the analog channel(s) used (Single or Differential Input) */
	   ASSIGN_BITS(ADMUX_R, ADC_CHANNEL_SELECT_START_BIT, enuAnalogChannel, ADC_CHANNEL_SELECT_MASK);
	   /* Starting the conversion process */
	   SET_BIT(ADCSRA_R, ADC_START_CONVERSION_EN_BIT);
		/* Waiting for the ADC conversion until it has successfully been completely */
		while(IS_BIT_CLEAR(ADCSRA_R, ADC_CONVERSION_COMPLETE_FLAG_BIT));
		/* Reading the value from the corresponding ADC channel */
		if(enuADCLeftAdjustResultState == ADC_DISABLE_LEFT_ADJUST_RESULT)
		{
			*pu16Data = ADC_VALUE_RIGHT_ADJUSTED;
		}
		else
		{
			*pu16Data = ADC_VALUE_LEFT_ADJUSTED;
		}
		/* Clearing the ADC conversion complete flag */
		CLEAR_BIT(ADCSRA_R, ADC_CONVERSION_COMPLETE_FLAG_BIT);
		/* Stopping the conversion process */
		CLEAR_BIT(ADCSRA_R, ADC_START_CONVERSION_EN_BIT);
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;	
} 



