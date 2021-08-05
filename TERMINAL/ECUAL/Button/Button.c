#include "Button.h"


/* Internal Macros */
#define BUTTON_CONNECTION_TYPE_MIN_VALUE																-1l
#define BUTTON_CONNECTION_TYPE_MAX_VALUE																2u
#define BUTTON_MAX_NO																						255u

typedef enum {BUTTON_INIT_UNDONE, BUTTON_INIT_DONE} enuButtonState_t;
static enuButtonState_t enuButtonState[BUTTON_MAX_NO] = {BUTTON_INIT_UNDONE};

static enuButtonStates_t enuButtonStates[BUTTON_MAX_NO];

static enuButtonConnectionType_t enuButtonConnectionTypeState[BUTTON_MAX_NO];


/*************************************************************************************************
* Parameters	: enuDIOPinNo, enuButtonConnectionType
* Return Value	: enuErrorStatus_t
* Description  : Initialize the button according to the configuration
*************************************************************************************************/
enuErrorStatus_t Button_Init(enuDIOPinNo_t enuDIOPinNo, enuButtonConnectionType_t enuButtonConnectionType)
{
   enuErrorStatus_t enuRetVar;
   uint8_t u8Data;
   
	if((enuButtonConnectionType > BUTTON_CONNECTION_TYPE_MIN_VALUE) && (enuButtonConnectionType < BUTTON_CONNECTION_TYPE_MAX_VALUE))
	{
		/* Initialize the button with the connected DIO pin */
		DIO_PinInit(enuDIOPinNo, INPUT, enuButtonConnectionType);
		/* Reading the current state of the button */
		DIO_PinRead(enuDIOPinNo, &u8Data);
		/* Checking if the current state of the button according to the configuration is true */
		if(((u8Data == LOW) && (enuButtonConnectionType == BUTTON_ACTIVE_HIGH)) || ((u8Data == HIGH) && (enuButtonConnectionType == BUTTON_ACTIVE_LOW)))
		{
			enuButtonStates[enuDIOPinNo] = BUTTON_OFF;
		}
		else
		{
			enuButtonStates[enuDIOPinNo] = BUTTON_ON;
		}
		enuButtonConnectionTypeState[enuDIOPinNo] = enuButtonConnectionType;
		enuButtonState[enuDIOPinNo] = BUTTON_INIT_DONE;
		enuRetVar = E_OK;		
	}	
	else
	{
		enuRetVar = E_ERROR;
	}
   return enuRetVar;	
}

/*************************************************************************************************
* Parameters	: enuDIOPinNo, penuButtonStates
* Return Value	: enuErrorStatus_t
* Description  : Read the current state of the button
*************************************************************************************************/
enuErrorStatus_t Button_GetState(enuDIOPinNo_t enuDIOPinNo, enuButtonStates_t* penuButtonStates)
{
   enuErrorStatus_t enuRetVar;
   uint8_t u8Data;
    
   if(enuButtonState[enuDIOPinNo] == BUTTON_INIT_DONE)
   {
	   /* Reading the current state of the required BUTTON group */
	   DIO_PinRead(enuDIOPinNo, &u8Data);
	   /* Changing the current state of the required BUTTON group according to the action taken */
	   switch(enuButtonStates[enuDIOPinNo])
	   {
		   case BUTTON_OFF:
		   {
			   if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_PRESSED;
			   }
			   else
			   {
			   }
		   }
		   break;
		   case BUTTON_PRESSED:
		   {
			   if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_ON;
			   }
			   else if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_OFF;
			   }
			   else
			   {
			   }
		   }
		   break;
		   case BUTTON_RELEASED:
		   {
			   if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_ON;
			   }
			   else if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_OFF;
			   }
			   else
			   {
			   }
		   }
		   break;
		   case BUTTON_ON:
		   {
			   if(((u8Data == HIGH) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_LOW)) || ((u8Data == LOW) && (enuButtonConnectionTypeState[enuDIOPinNo] == BUTTON_ACTIVE_HIGH)))
			   {
				   enuButtonStates[enuDIOPinNo] = BUTTON_RELEASED;
			   }
			   else
			   {
			   }
		   }
		   break;
	   }
	   *penuButtonStates = enuButtonStates[enuDIOPinNo];
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;
}
