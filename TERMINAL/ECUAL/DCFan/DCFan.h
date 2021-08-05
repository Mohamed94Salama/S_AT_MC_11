#ifndef DCFAN_H_
#define DCFAN_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../STD_TYPES.h"

/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: void
* Description  : Initialize the DC Fan data pin
*************************************************************************************************/
void DCFan_Init(enuDIOPinNo_t enuDIOPinNo);
/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: enuErrorStatus_t
* Description  : Start the DC Fan to rotate
*************************************************************************************************/
enuErrorStatus_t DCFan_Start(enuDIOPinNo_t enuDIOPinNo);
/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: enuErrorStatus_t
* Description  : Stop the DC Fan
*************************************************************************************************/
enuErrorStatus_t DCFan_Stop(enuDIOPinNo_t enuDIOPinNo);

#endif /* DCFAN_H_ */
