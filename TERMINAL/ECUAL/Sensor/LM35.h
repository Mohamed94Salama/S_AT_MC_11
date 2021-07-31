#ifndef LM35_H_
#define LM35_H_

#include "../../MCAL/ADC/ADC.h"
#include "LM35_Config.h"
#include "../../STD_TYPES.h"

/*************************************************************************************************
* Parameters	: void
* Return Value	: void
* Description  : Initialize the LM35 sensor with the ADC module
*************************************************************************************************/
void LM35_Init(void);
/*************************************************************************************************
* Parameters	: pu8Temperature
* Return Value	: enuErrorStatus_t
* Description  : Read the value of the sensor's temperature
*************************************************************************************************/
enuErrorStatus_t LM35_ReadTemperature(uint8_t* pu8Temperature);

#endif /* LM35_H_ */
