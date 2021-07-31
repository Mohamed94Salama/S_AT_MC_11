#include "ATM/ATM.h"

/*
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
*/

int main(void)
{
//	uint8_t u8KeypadChar;
	APP_Init();

	while(1)
	{
		APP_Update();
//		LCD_SetCursorPosition(0, 0);
//		LCD_DisplayChar('b');
//		SPI_ReceiveChar(&u8KeypadChar);
//		LCD_DisplayChar(u8KeypadChar);
//		LCD_SetCursorPosition(0, 1);
//		LCD_DisplayChar('k');
	}
}


