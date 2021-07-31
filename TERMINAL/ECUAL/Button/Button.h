#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../STD_TYPES.h"

typedef enum {BUTTON_ACTIVE_HIGH, BUTTON_ACTIVE_LOW} enuButtonConnectionType_t;
typedef enum {BUTTON_OFF, BUTTON_PRESSED, BUTTON_RELEASED, BUTTON_ON} enuButtonStates_t;

/*************************************************************************************************
* Parameters	: enuDIOPinNo, enuButtonConnectionType
* Return Value	: enuErrorStatus_t
* Description  : Initialize the button according to the configuration
*************************************************************************************************/
enuErrorStatus_t Button_Init(enuDIOPinNo_t enuDIOPinNo, enuButtonConnectionType_t enuButtonConnectionType);
/*************************************************************************************************
* Parameters	: enuDIOPinNo, penuButtonStates
* Return Value	: enuErrorStatus_t
* Description  : Read the current state of the button
*************************************************************************************************/
enuErrorStatus_t Button_GetState(uint8_t enuDIOPinNo_t, enuButtonStates_t* penuButtonStates);

#endif /* BUTTON_H_ */
