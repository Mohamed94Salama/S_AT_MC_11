#include "DCFan.h"


/* Internal Macros */
#define DCFAN_MAX_NO																255u

typedef enum {DCFAN_INIT_UNDONE, DCFAN_INIT_DONE} enuDCFanState_t;
static enuDCFanState_t enuDCFanState[DCFAN_MAX_NO] = {DCFAN_INIT_UNDONE};


/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: void
* Description  : Initialize the DC Fan data pin
*************************************************************************************************/
void DCFan_Init(enuDIOPinNo_t enuDIOPinNo)
{	
	/* Initializing the DC Fan data pin as output */
	DIO_PinInit(enuDIOPinNo, OUTPUT, NO_CONNECTION);
	/* Stopping the DC Fan before the system starts */
	DIO_PinWrite(enuDIOPinNo, LOW);
	enuDCFanState[enuDIOPinNo] = DCFAN_INIT_DONE;
}

/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: enuErrorStatus_t
* Description  : Start the DC Fan to rotate
*************************************************************************************************/
enuErrorStatus_t DCFan_Start(enuDIOPinNo_t enuDIOPinNo)
{
	enuErrorStatus_t enuRetVar;
	
	if(enuDCFanState[enuDIOPinNo] == DCFAN_INIT_DONE)
	{
		/* Starting the DC Fan */
		DIO_PinWrite(enuDIOPinNo, HIGH);
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;
}

/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: enuErrorStatus_t
* Description  : Stop the DC Fan
*************************************************************************************************/
enuErrorStatus_t DCFan_Stop(enuDIOPinNo_t enuDIOPinNo)
{
	enuErrorStatus_t enuRetVar;
	
	if(enuDCFanState[enuDIOPinNo] == DCFAN_INIT_DONE)
	{
		/* Stopping the DC Fan */
		DIO_PinWrite(enuDIOPinNo, LOW);
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;	
}
