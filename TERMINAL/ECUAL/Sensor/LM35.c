#include "LM35.h"

/* Internal Macros */
#define LM35_CALCULATE_TEMPERATURE(ADC_VALUE)										(((5000.0 / 1024) * ADC_VALUE) / 10) 	

typedef enum {LM35_INIT_UNDONE, LM35_INIT_DONE} enuLM35State_t;
static enuLM35State_t enuLM35State = LM35_INIT_UNDONE;


/*************************************************************************************************
* Parameters	: void
* Return Value	: void
* Description  : Initialize the LM35 sensor with the ADC module
*************************************************************************************************/
void LM35_Init(void)
{
	/* Initializing the ADC module to start reading from the LM35 sensor */
	ADC_Init(ADC_AVCC, ADC_DISABLE_LEFT_ADJUST_RESULT, ADC_DIVISOR_FACTOR_IS_128);
	enuLM35State = LM35_INIT_DONE;
}

/*************************************************************************************************
* Parameters	: pu8Temperature
* Return Value	: enuErrorStatus_t
* Description  : Read the value of the sensor's temperature
*************************************************************************************************/
enuErrorStatus_t LM35_ReadTemperature(uint8_t* pu8Temperature)
{
	enuErrorStatus_t enuRetVar;
	uint16_t u16ADCData;
	
	if(enuLM35State == LM35_INIT_DONE)
	{
		/* Reading the value of the ADC channel connected to the LM35 sensor */
		ADC_ReadChannel(LM35_ANALOG_DATA_PIN_NO, &u16ADCData);
		/* Converting the ADC value from voltage to Celsius */
		*pu8Temperature = LM35_CALCULATE_TEMPERATURE(u16ADCData);
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;
}
