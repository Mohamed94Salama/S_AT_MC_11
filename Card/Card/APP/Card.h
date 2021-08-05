/*****************************************************************************
* Task: ATM Machine
* File Name: Card.h
* Description: Header File for the card application in the ATM machine project
* Author: Amr Mohamed
* Date: 29/7/2021
******************************************************************************/

#ifndef CARD_H_
#define CARD_H_
/*- INCLUDES --------------------------------------------------*/
#include "MCAL/DIO/DIO.h"
#include "MCAL/UART/UART.h"
#include "MCAL/SPI/SPI.h"
#include "ECUAL/EEPROM/EEPROM.h"

/*- APIs PROTOTYPES -------------------------------------------*/


/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function to initialize application peripherals and devices
************************************************************************************/
void APP_Init(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function to update the application status
************************************************************************************/
void APP_Update(void);






#endif /* CARD_H_ */