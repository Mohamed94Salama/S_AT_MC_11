#include "APP/Card.h"

#define PAN_SIZE				9
#define PIN_SIZE				4
#define SPI_FRAME_SIZE		15

#define PAN_LOC		0
#define PIN_LOC		PAN_LOC+PAN_SIZE+1

uint8_t PAN[PAN_SIZE+1]={0};
uint8_t PIN[PIN_SIZE+1]={0};
uint8_t SPIFrame[SPI_FRAME_SIZE]={0};
uint8_t initialized=0;


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


static void Frame_Assemble(uint8_t * PAN, uint8_t * PIN, uint8_t * Frame)
{
   uint8_t i,j;
   for (i=0,j=0;i<PAN_SIZE;i++,j++)
   {
      Frame[j]=PAN[i];
   }
   Frame[j++]='|';
   for (i=0;i<PIN_SIZE;i++,j++)
   {
      Frame[j]=PIN[i];
   }
   //Frame[j]='\0';
}

void Programming_Mode (void)
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
   UART_SendString((uint8_t *)"\rEnter PAN Number:  ");
   UART_ReceiveString(PAN,PAN_SIZE);
   //Get New Pin from user
   UART_SendString((uint8_t *)"\rEnter PIN Number:  ");
   UART_ReceiveString(PIN,PIN_SIZE);
   UART_SendString((uint8_t *)"\rDONE\r\r");
   //update pin and pan in EEPROM
   EEPROM_WriteString(PAN_LOC,PAN_SIZE,PAN);
   EEPROM_WriteString(PIN_LOC,PIN_SIZE,PIN);
   //Assemble the frame
   Frame_Assemble(PAN,PIN,SPIFrame);
   //ENABLE_UART_Interrupt
   UART_RX_Enable_Interrupt();
   
}

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
   
   EEPROM_ReadString(PAN_LOC,PAN_SIZE,PAN);
   EEPROM_ReadString(PIN_LOC,PIN_SIZE,PIN);
   for(uint8_t i=0;i<PAN_SIZE;i++)
   {
      if ((!(PAN[i]>='0' && PAN[i]<='9')) || ((i<PIN_SIZE) && (!(PIN[i]>='0' && PIN[i]<='9'))))
      {
         Programming_Mode();
         break;
      }
   }
   Frame_Assemble(PAN,PIN,SPIFrame);
   
   initialized=1;
   sei();
}
void APP_Update(void)
{
   if(!GET_BIT(PINB_R,4))
   {
      UART_RX_Disable_Interrupt();
      SPI_sendString(SPIFrame);
		UART_RX_Enable_Interrupt();
      while(!GET_BIT(PINB_R,4));
   }
}