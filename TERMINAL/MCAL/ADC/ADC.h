#ifndef ADC_H_
#define ADC_H_

#include "../../STD_TYPES.h"
#include "../../BIT_MANIPULATE.h"

typedef enum {ADC_AREF, ADC_AVCC, ADC_INTERNAL_VOLTAGE_REFERNECE = 3} enuADCReferenceSelectionBits_t;
typedef enum {ADC_DISABLE_LEFT_ADJUST_RESULT, ADC_ENABLE_LEFT_ADJUST_RESULT} enuADCLeftAdjustResult_t;
typedef enum {ADC_DIVISOR_FACTOR_IS_2 = 1, ADC_DIVISOR_FACTOR_IS_4, ADC_DIVISOR_FACTOR_IS_8, ADC_DIVISOR_FACTOR_IS_16,
				  ADC_DIVISOR_FACTOR_IS_32, ADC_DIVISOR_FACTOR_IS_64, ADC_DIVISOR_FACTOR_IS_128} enuADCPrescalerSelectBits_t;
typedef enum 
{
	ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7,
	ADC0_ADC0_10x, ADC1_ADC0_10x, ADC0_ADC0_200x, ADC1_ADC0_200x,
	ADC2_ADC2_10x, ADC3_ADC2_10x, ADC2_ADC2_200x, ADC3_ADC2_200x,
	ADC0_ADC1_1x, ADC1_ADC1_1x, ADC2_ADC1_1x, ADC3_ADC1_1x, ADC4_ADC1_1x, ADC5_ADC1_1x, ADC6_ADC1_1x, ADC7_ADC1_1x,
	ADC0_ADC2_1x, ADC1_ADC2_1x, ADC2_ADC2_1x, ADC3_ADC2_1x,ADC4_ADC2_1x,ADC5_ADC2_1x, 
	VBG, GND
} enuADCAnalogChannel_t;

/*************************************************************************************************
* Parameters	: enuADCReferenceSelectionBits, enuADCLeftAdjustResult, enuADCPrescalerSelectBits
* Return Value	: enuErrorStatus_t
* Description  : Initialize ADC module according to the configuration parameters
*************************************************************************************************/
enuErrorStatus_t ADC_Init(enuADCReferenceSelectionBits_t enuADCReferenceSelectionBits, enuADCLeftAdjustResult_t enuADCLeftAdjustResult, enuADCPrescalerSelectBits_t enuADCPrescalerSelectBits);
/*************************************************************************************************
* Parameters	: enuAnalogChannel, pu16Data
* Return Value	: enuErrorStatus_t
* Description  : Initiate an analog read from the selected channel
*************************************************************************************************/
enuErrorStatus_t ADC_ReadChannel(enuADCAnalogChannel_t enuAnalogChannel, uint16_t* pu16Data);

#endif /* ADC_H_ */
