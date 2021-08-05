
/*****************************************************************************
* Task: ATM Machine
* File Name: Card.c
* Description: File for the card application functions in the ATM machine project
* Author: Amr Mohamed
* Date: 29/7/2021
******************************************************************************/

/*- INCLUDES --------------------------------------------------*/
#include "APP/Card.h"

/*- MACROS --------------------------------------------------*/
#define PAN_SIZE				9
#define PIN_SIZE				4
#define NAME_SIZE				15
#define SPI_FRAME_SIZE		15

#define PAN_LOC		0
#define PIN_LOC		PAN_LOC+PAN_SIZE+1
#define NAME_LOC  	PIN_LOC+PIN_SIZE+2

uint8_t PAN[PAN_SIZE+1]={0};
uint8_t PIN[PIN_SIZE+1]={0};
uint8_t NAME[NAME_SIZE+1]={0};
uint8_t SPIFrame[SPI_FRAME_SIZE]={0};
uint8_t initialized=0;

/*- APIs IMPLEMENTATION --------------------------------------------------*/

/************************************************************************************
* Parameters (in): uint8_t *str1,uint8_t *str2
* Parameters (out): sint8_t
* Return value: 0= if strings are identical -- 1=str1>str2 -- -1=str1<str2
* Description: A function to compare two strings
************************************************************************************/
static sint8_t String_compare(uint8_t *str1,uint8_t *str2)
{
   uint16_t u16i;
   //Traverse both strings
   for(u16i=0;str1[u16i] || str2[u16i];u16i++)
   {
      // look for any difference
      if      (str1[u16i] < str2[u16i])     return -1;
      else if (str1[u16i] > str2[u16i])     return 1;
   }
   return 0;
}

/************************************************************************************
* Parameters (in): uint8_t * PAN, uint8_t * PIN, uint8_t * Frame
* Parameters (out): void
* Return value: void
* Description: A function to assemble the frame to be sent over SPI
************************************************************************************/
static void Frame_Assemble(uint8_t * PAN, uint8_t * PIN, uint8_t * Frame)
{
   uint8_t i,j;
   //copy each character from the PAN buffer into the SPI frame
   for (i=0,j=0;i<PAN_SIZE;i++,j++)
   {
      Frame[j]=PAN[i];
   }
   //put a boundary between PAN and PIN
   Frame[j++]='|';
   //copy each character from the PIN buffer into the SPI frame
   for (i=0;i<PIN_SIZE;i++,j++)
   {
      Frame[j]=PIN[i];
   }
   //put an ending character to the frame
   Frame[j]='\0';
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function that handles programming mode int the Card
************************************************************************************/
static void Programming_Mode (void)
{
   static uint8_t au8uartBuffer[20]={0};
   //DISABLE_UART_Interrupt
   UART_RX_Disable_Interrupt();
   if (initialized == 1)
   {
      //uart get string
      UART_ReceiveString(au8uartBuffer,20);
      
      if (String_compare(au8uartBuffer,(uint8_t *)"ADMIN") != 0)
      {
         
         UART_RX_Enable_Interrupt();
         return;
      }
   }
   //Get New Pan from user
   UART_SendString((uint8_t *)"\rEnter User Name:  ");
   UART_ReceiveString(NAME,NAME_SIZE);
   //Get New Pan from user
   UART_SendString((uint8_t *)"\rEnter PAN Number:  ");
   UART_ReceiveString(PAN,PAN_SIZE);
   //Get New Pin from user
   UART_SendString((uint8_t *)"\rEnter PIN Number:  ");
   UART_ReceiveString(PIN,PIN_SIZE);
   UART_SendString((uint8_t *)"\rDONE\r\r");
   //update pin and pan in EEPROM
   
   EEPROM_WriteString(PAN_LOC,PAN_SIZE,PAN);
   EEPROM_WriteString(PIN_LOC,PIN_SIZE,PIN);
   EEPROM_WriteString(NAME_LOC,NAME_SIZE,NAME);
   //Assemble the frame
   Frame_Assemble(PAN,PIN,SPIFrame);
   //ENABLE_UART_Interrupt
   UART_RX_Enable_Interrupt();
   
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function to Get the card data from the EEPROM
************************************************************************************/
static void GetCardData(void)
{
   uint8_t Programming_Flag=1;
   //while the data in the EEPROM is still corrupted
   while (Programming_Flag)
   {
      //read PAN from EEPROM
      EEPROM_ReadString(PAN_LOC,PAN_SIZE,PAN);
      //read PIN from EEPROM
      EEPROM_ReadString(PIN_LOC,PIN_SIZE,PIN);
      //perform checks on PAN and PIN
      for(uint8_t i=0;i<PAN_SIZE;i++)
      {
         //if data is invalid
         if ((!(PAN[i]>='0' && PAN[i]<='9')) || ((i<PIN_SIZE) && (!(PIN[i]>='0' && PIN[i]<='9'))))
         {
            //send a notification to the user
            UART_SendString("\n\rEEPROM Data Error .... Please Input User Data:\n\r");
            //enter EEPROM programming mode
            Programming_Mode();
            //enable programming mode
            Programming_Flag=1;
            //escape check sequence
            break;
         }
         //disable programming flag to end EEPROM programming
         Programming_Flag=0;
      }
   }
}




/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function to initialize application peripherals and devices
************************************************************************************/
void APP_Init(void)
{
   initialized=0;
   //initialize UART
   UART_Init();
   //Enable UART_Interrupt
   UART_RX_Enable_Interrupt();
   //Set UART Callback
   UART_RX_SetCallBack(Programming_Mode);
	//initialize SPI
   SPI_init();
   //initialize EEPROM
   EEPROM_Init();
   //Get the card data
   GetCardData();
   //assemble the card frame to be sent to the atm
   Frame_Assemble(PAN,PIN,SPIFrame);
   
   initialized=1;
   //start global interrupt
   sei();
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: A function to update the application status
************************************************************************************/
void APP_Update(void)
{
   //if communication started
   if(!GET_BIT(PINB_R,4))
   {
      //stop uart RX interrupt 
      UART_RX_Disable_Interrupt();
      //send the frame over SPI
      SPI_sendString(SPIFrame);
      //start uart RX interrupt 
		UART_RX_Enable_Interrupt();
      while(!GET_BIT(PINB_R,4));
   }
}