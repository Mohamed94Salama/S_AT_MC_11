/*****************************************************************************
* Task       : External Interrupt driver
* File Name  : EXT_INT.h
* Description: header file for External Interrupt driver
* Author     : Kariman Karam
* Date       : 3/8/2021
******************************************************************************/

#ifndef MCAL_EXTERNAL_INTERRUPT_EXT_INT_H_
#define MCAL_EXTERNAL_INTERRUPT_EXT_INT_H_

/*- INCLUDES --------------------------------------------------*/
#include "STD_Types.h"
#include "BIT_MANIPULATE.h"
#include "EXT_INT_registers.h"

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	EXT_LOW_MODE =0,
	EXT_CHANGE_MODE,
	EXT_FAILLING_MODE,
	EXT_RAISING_MODE

}enuEXTINTSenseControl;

typedef enum
{
	EXTINT_INT0=0,
	EXTINT_INT1,
	EXTINT_INT2
}enuEXTINTNum;

typedef enum
{
	EXTINT_ERROR=0,
	EXTINT_OK
}enuEXTINTErrorStatus;


/*- FUNCTION PROTOTYPES ----------------------------------*/

/***********************************************************************************************
* Parameters (in) : enuInterruptNum
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to initialize External Interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_Init( enuEXTINTNum enuInterruptNum);

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, enuSenseMode
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_SetSenseMode(enuEXTINTSenseControl enuSenseMode, enuEXTINTNum enuInterruptNum);

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, pCallBack
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_SetCallBack(void(*pCallBack)(void), enuEXTINTNum enuInterruptNum);

#endif
