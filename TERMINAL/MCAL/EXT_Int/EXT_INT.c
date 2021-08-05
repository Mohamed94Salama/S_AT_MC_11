/*****************************************************************************
* Task       : External Interrupt driver
* File Name  : EXT_INT.c
* Description: Source file for External Interrupt driver
* Author     : Kariman Karam
* Date       : 3/8/2021
******************************************************************************/

/*- INCLUDES --------------------------------------------------*/
#include "EXT_INT.h"

/*- GLOBAL VARIABLES --------------------------------------------------*/
void(*pEXTINT0CallBack)(void);
void(*pEXTINT1CallBack)(void);
void(*pEXTINT2CallBack)(void);


/*- APIs IMPLEMENTATION-----------------------------------*/

/***********************************************************************************************
* Parameters (in) : enuInterruptNum
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to initialize External Interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_Init(enuEXTINTNum enuInterruptNum)
{
	enuEXTINTErrorStatus enuStatus = EXTINT_ERROR;

	//Enable peripheral interrupt enable
	switch(enuInterruptNum)
	{
	case EXTINT_INT0:
		SET_BIT(GICR_R, INT0_B);
		break;
	case EXTINT_INT1:
		SET_BIT(GICR_R, INT1_B);
		break;
	case EXTINT_INT2:
		SET_BIT(GICR_R, INT2_B);
		break;
	default:
		break;
	}
    //Enable GIE
	SET_BIT(SREG_R, SREG_I_B);

	enuStatus = EXTINT_OK;

	return enuStatus;
}

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, enuSenseMode
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_SetSenseMode(enuEXTINTSenseControl enuSenseMode, enuEXTINTNum enuInterruptNum)
{
	enuEXTINTErrorStatus enuStatus = EXTINT_ERROR;

    if (enuInterruptNum==EXTINT_INT0)
    {
		switch(enuSenseMode)
		{
		case EXT_LOW_MODE :
		  CLEAR_BIT(MCUCR_R,0);
		  CLEAR_BIT(MCUCR_R,1);
		  break;
		case EXT_RAISING_MODE :
		 SET_BIT(MCUCR_R,0);
		 SET_BIT(MCUCR_R,1);
		  break;
		case EXT_FAILLING_MODE :
		  CLEAR_BIT(MCUCR_R,0);
		  SET_BIT(MCUCR_R,1);
		  break;
		case EXT_CHANGE_MODE :
		  SET_BIT(MCUCR_R,0);
		  CLEAR_BIT(MCUCR_R,1);
		  break;
		default:
			break;
		}
    }
    else if (enuInterruptNum==EXTINT_INT1)
    {
		switch(enuSenseMode)
		{
		case EXT_LOW_MODE :
		  CLEAR_BIT(MCUCR_R,2);
	      CLEAR_BIT(MCUCR_R,3);
		  break;
		case EXT_RAISING_MODE :
		  SET_BIT(MCUCR_R,2);
		  SET_BIT(MCUCR_R,3);
		  break;
		case EXT_FAILLING_MODE :
		  CLEAR_BIT(MCUCR_R,2);
		  SET_BIT(MCUCR_R,3);
		  break;
		case EXT_CHANGE_MODE :
		  SET_BIT(MCUCR_R,2);
		  CLEAR_BIT(MCUCR_R,3);
		  break;
		default:
			break;
		}
    }
    else if (enuInterruptNum==EXTINT_INT2)
    {
		switch(enuSenseMode)
		{
		case EXT_RAISING_MODE :
			SET_BIT(MCUCR_R,6);
			break;
		case EXT_FAILLING_MODE :
			CLEAR_BIT(MCUCR_R,6);
			break;
		default:
			break;
		}
    }

	enuStatus = EXTINT_OK;

	return enuStatus;
}

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, pCallBack
* Parameters (out): None
* Return Value    : enuEXTINTErrorStatus - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuEXTINTErrorStatus EXTINT_SetCallBack(void(*pCallBack)(void), enuEXTINTNum enuInterruptNum)
{
   if (pCallBack==NULLPTR)
   {
      return EXTINT_ERROR;
   }
	if(enuInterruptNum==EXTINT_INT0)
		pEXTINT0CallBack = pCallBack;
	else if(enuInterruptNum==EXTINT_INT1)
		pEXTINT1CallBack = pCallBack;
	else if(enuInterruptNum==EXTINT_INT2)
		pEXTINT2CallBack = pCallBack;

	return EXTINT_OK;
}

/* ISR to handle the External Interrupt Request 0 */
void __vector_1(void) __attribute__ ((signal,used));
/* ISR to handle the External Interrupt Request 1 */
void __vector_2(void) __attribute__ ((signal,used));
/* ISR to handle the External Interrupt Request 2 */
void __vector_3(void) __attribute__ ((signal,used));

/* ISR to handle the External Interrupt Request 0 */
void __vector_1(void)
{
   if (pEXTINT0CallBack!=NULLPTR)
   {
      pEXTINT0CallBack();
   }
}

/* ISR to handle the External Interrupt Request 1 */
void __vector_2(void)
{
   if (pEXTINT1CallBack!=NULLPTR)
   {
      pEXTINT1CallBack();
   }
}

/* ISR to handle the External Interrupt Request 2 */
void __vector_3(void)
{
   if (pEXTINT2CallBack!=NULLPTR)
   {
      pEXTINT2CallBack();
   }
}
