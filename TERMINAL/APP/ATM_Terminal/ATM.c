/*****************************************************************************
* Task		 : ATM Machine
* File Name	 : ATM.C
* Description: Source file for ATM Machine
* Author	 : TEAM2 (SAKE Team)
* Date		 : Jul 29, 2021
******************************************************************************/

/*- INCLUDES -----------------------------------------------*/
#include "ATM.h"

/*- MACROS -------------------------------------------------*/
#define APP_EEPROM_ADMIN_PASSWORD_ADDRESS						0x010
//#define APP_EEPROM_CARDS_NO									0x020
#define APP_EEPROM_MAX_AMOUNT_ADDRESS							0x030
#define APP_EEPROM_PAN_ADDRESS(CARDS_NO)						(0x100 + (0x10 * CARDS_NO))
#define APP_EEPROM_BALANCE_ADDRESS(CARDS_NO)					(0x500 + (0x10 * CARDS_NO))

/*- Static Global Functions --------------------------------*/
static void APP_Delay(void);
static void doubletostr (double num, char* str, int precision);

/*- Static Global Variables --------------------------------*/
static uint8_t gu8BTNFlag = 2;
static volatile uint8_t u8Flag = LOW;


static void Card(void)
{
	double dKeypadAmount;
	double dMaxAmount;
	double dBalance;
	uint8_t au8CardData[16];
	uint8_t au8PAN[10];
	uint8_t au8Balance[8];
	uint8_t au8MaxAmount[8];
	uint8_t au8KeypadAmount[7];
	uint8_t au8KeypadPIN[4];
	uint8_t u8LoopIndex;
	static uint8_t u8Flag = LOW;
	static uint8_t u8CardsNo=0;

	//admin mode and button is pressed
	if(gu8BTNFlag==1)
	{
		/* Clearing the LCD screen */
		LCD_Clear();
		/* Displaying "ADMIN MODE" on the LCD screen */
		LCD_SetCursorPosition(0, 0);
		LCD_DisplayString((uint8_t*)"Card not allowed");
		LCD_SetCursorPosition(0, 1);
		LCD_DisplayString((uint8_t*)"in ADMIN mode");
		APP_Delay();
		/* Clearing the LCD screen */
		LCD_Clear();
		/* Displaying "ADMIN MODE" on the LCD screen */
		LCD_DisplayString((uint8_t*)"   ADMIN MODE");
	}
	//user mode and button is pressed (card is inserted)
	else if(gu8BTNFlag==0)
	{
		gu8BTNFlag=2;

		{
			/* Clearing the SS pin to start reception */
			DIO_PinWrite(PB4, LOW);
			/* Reading from the CARD slave the card data */
			SPI_receiveString(au8CardData, 15);
			/* Clearing the SS pin to stop reception */
			DIO_PinWrite(PB4, HIGH);
			EEPROM_ReadByte(0x020, &u8CardsNo);
			/**/
			for(u8LoopIndex = 0; u8LoopIndex < u8CardsNo; u8LoopIndex++)
			{

				/* Reading the stored PAN from EEPROM */
				EEPROM_ReadString(0x100 + (0x10 * u8LoopIndex), 9, au8PAN);
				/* Checking if the PAN of the card is similar to the stored PAN in EEPROM */
				if((au8CardData[0] == au8PAN[0]) && (au8CardData[1] == au8PAN[1]) && (au8CardData[2] == au8PAN[2]) &&
				   (au8CardData[3] == au8PAN[3]) && (au8CardData[4] == au8PAN[4]) && (au8CardData[5] == au8PAN[5]) &&
				   (au8CardData[6] == au8PAN[6]) && (au8CardData[7] == au8PAN[7]) && (au8CardData[8] == au8PAN[8]))
				{
					break;
				}
				else
				{
				}
			}
			/* Checking if the card is present or not */
			if(u8LoopIndex < u8CardsNo)
			{
			/**/
				/* Clearing the LCD screen */
				LCD_Clear();
				/* Displaying "Enter PIN:" on the LCD screen */
				LCD_DisplayString((uint8_t*)"Enter PIN:");
				/* Setting the position of the cursor at the second row of the LCD screen */
				LCD_SetCursorPosition(0, 1);
				/* Getting the first PIN value from the keypad */
				Keypad_GetChar(&au8KeypadPIN[0]);
				/* Displaying '*' on the LCD screen */
				LCD_DisplayChar('*');
				/* Getting the second PIN value from the keypad */
				Keypad_GetChar(&au8KeypadPIN[1]);
				/* Displaying '*' on the LCD screen */
				LCD_DisplayChar('*');
				/* Getting the third PIN value from the keypad */
				Keypad_GetChar(&au8KeypadPIN[2]);
				/* Displaying '*' on the LCD screen */
				LCD_DisplayChar('*');
				/* Getting the forth PIN value from the keypad */
				Keypad_GetChar(&au8KeypadPIN[3]);
				/* Displaying '*' on the LCD screen */
				LCD_DisplayChar('*');
				/* Checking if the PIN of the card is similar to the entered PIN from the keypad */
				if((au8CardData[10] == au8KeypadPIN[0]) && (au8CardData[11] == au8KeypadPIN[1]) &&
				   (au8CardData[12] == au8KeypadPIN[2]) && (au8CardData[13] == au8KeypadPIN[3]))
				{
					/* Clearing the LCD screen */
					LCD_Clear();
					/* Displaying "Enter amount:" on the LCD screen */
					LCD_DisplayString((uint8_t*)"Enter amount:");
					/* Setting the position of the cursor at the second row of the LCD screen */
					LCD_SetCursorPosition(0, 1);
					/* Getting the thousands amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[0]);
					/* Displaying the thousands amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[0]);
					/* Getting the hundreds amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[1]);
					/* Displaying the hundreds amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[1]);
					/* Getting the tens amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[2]);
					/* Displaying the tens amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[2]);
					/* Getting the units amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[3]);
					/* Displaying the units amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[3]);
					/* Displaying the decimal point of amount value on the LCD screen */
					au8KeypadAmount[4]='.';
					/* Displaying the decimal point on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[4]);
					/* Getting the tenths amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[5]);
					/* Displaying the tenths amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[5]);
					/* Getting the hundredths amount value from the keypad */
					Keypad_GetChar(&au8KeypadAmount[6]);
					/* Displaying the hundredths amount value on the LCD screen */
					LCD_DisplayChar(au8KeypadAmount[6]);
					/* Converting the entered amount value from ASCII characters to double */
					dKeypadAmount = atof((char*)au8KeypadAmount);
					/* Reading the stored maximum amount value from EEPROM */
					EEPROM_ReadString(APP_EEPROM_MAX_AMOUNT_ADDRESS, 7, au8MaxAmount);
					/* Converting the stored maximum amount value from ASCII characters to double */
					dMaxAmount = atof((char*)au8MaxAmount);
					/* Reading the stored balance value from EEPROM */
					EEPROM_ReadString(0x500 + (0x10 * u8LoopIndex), 7, au8Balance);
					/* Converting the stored balance value from ASCII characters to double */
					dBalance = atof((char*)au8Balance);
					/* Clearing the LCD screen */
					LCD_Clear();
					/* Checking if the entered amount is greater than the stored maximum amount */
					if(dKeypadAmount > dMaxAmount)
					{
						/* Displaying "Maximum Amount" on the LCD screen */
						LCD_DisplayString((uint8_t*)" Maximum Amount");
						/* Setting the position of the cursor at the second row of the LCD screen */
						LCD_SetCursorPosition(0, 1);
						/* Displaying "Exceeded" on the LCD screen */
						LCD_DisplayString((uint8_t*)"    Exceeded");
						/* Giving a sufficient time delay to show the message on the LCD screen */
						APP_Delay();
						u8Flag = LOW;
					}
					/* Checking if the entered amount is greater than the stored balance */
					else if(dKeypadAmount > dBalance)
					{
						/* Displaying "Insufficient" on the LCD screen */
						LCD_DisplayString((uint8_t*)"  Insufficient");
						/* Setting the position of the cursor at the second row of the LCD screen */
						LCD_SetCursorPosition(0, 1);
						/* Displaying "Fund" on the LCD screen */
						LCD_DisplayString((uint8_t*)"      Fund");
						/* Giving a sufficient time delay to show the message on the LCD screen */
						APP_Delay();
						u8Flag = LOW;
					}
					else
					{
						/* Displaying "Transaction" on the LCD screen */
						LCD_DisplayString((uint8_t*)"  Transaction");
						/* Setting the position of the cursor at the second row of the LCD screen */
						LCD_SetCursorPosition(0, 1);
						/* Displaying "APPROVED" on the LCD screen */
						LCD_DisplayString((uint8_t*)"    Approved");
						/* Subtracting the withdrawn money after the transaction has successfully completed */
						dBalance -= dKeypadAmount;
						/* Converting the balance from double to ASCII characters */
						doubletostr(dBalance, (char*)au8Balance, 2);
						/* Writing the balance inside the EEPROM */
						EEPROM_WriteString(APP_EEPROM_BALANCE_ADDRESS(u8LoopIndex), 9, au8Balance);
						/* Starting the DC fan to run */
						DCFan_Start(PB1);
						/* Giving a sufficient time delay to make the DC fan run */
						APP_Delay();
						/* Stopping the DC Fan */
						DCFan_Stop(PB1);
						u8Flag = LOW;
					}
				}
				else
				{
					/* Clearing the LCD screen */
					LCD_Clear();
					/* Displaying "Incorrect PIN" on the LCD screen */
					LCD_DisplayString((uint8_t*)" Incorrect PIN");
					/* Setting the position of the cursor at the second row of the LCD screen */
					LCD_SetCursorPosition(0, 1);
					/* Displaying "Card is ejected" on the LCD screen */
					LCD_DisplayString((uint8_t*)"Card is ejected");
					/* Giving a sufficient time delay to show the message on the LCD screen */
					APP_Delay();
					u8Flag = LOW;
				}
			}
			else if (gu8BTNFlag==2)
			{
				/* Clearing the LCD screen */
				LCD_Clear();
				/* Displaying "Invalid Card" on the LCD screen */
				LCD_DisplayString((uint8_t*)"  Invalid Card");
				/* Setting the position of the cursor at the second row of the LCD screen */
				LCD_SetCursorPosition(0, 1);
				/* Displaying "Card is ejected" on the LCD screen */
				LCD_DisplayString((uint8_t*)"Card is ejected");
				/* Giving a sufficient time delay to show the message on the LCD screen */
				APP_Delay();
				u8Flag = LOW;
			}
		}

	}
	//in case no mode is entered and button pressed
	else
	{
		/* Clearing the LCD screen */
		LCD_Clear();
		LCD_SetCursorPosition(0, 0);
		LCD_DisplayString((uint8_t*)"Card ejected");
		LCD_SetCursorPosition(0, 1);
		LCD_DisplayString((uint8_t*)"Pls choose mode");
		APP_Delay();
		/* Clearing the LCD screen */
		LCD_Clear();
		/* Displaying "Welcome to" on the LCD screen */
		LCD_DisplayString((uint8_t*)"   Welcome to");
		/* Setting the position of the cursor at the second row of the LCD screen */
		LCD_SetCursorPosition(0, 1);
		/* Displaying "ATM System" on the LCD screen */
		LCD_DisplayString((uint8_t*)"   ATM System");
	}
}

/*************************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : A function to initialize the application
*************************************************************************************************/
void APP_Init(void)
{
	/* Initializing the UART MCAL driver */
	UART_Init();
	/* Initializing the SPI MCAL driver */
	SPI_init();
	/* Initializing the LCD ECUAL driver */
	LCD_Init(LCD_DATA_FOUR_BIT_MODE, LCD_CURSOR_OFF);
	/* Initializing the Keypad ECUAL driver */
	Keypad_Init(KEYPAD_4X3);
	/* Initializing the Button ECUAL driver */
	Button_Init(PB2, BUTTON_ACTIVE_HIGH);
	/* Initializing the DC Fan ECUAL driver */
	DCFan_Init(PB1);
	/* Initializing the LM35 ECUAL driver */
	LM35_Init();
	/* Initializing the EEPROM ECUAL driver */
	EEPROM_Init();
	/* Initializing the EXT interrupt MCUAL driver */
	EXTINT_Init(EXTINT_INT2);
	EXTINT_SetSenseMode(EXT_RAISING_MODE, EXTINT_INT2);

	/* Setting the SS pin to stop any incoming transmission/reception process */
	DIO_PinWrite(PB4, HIGH);
	/* Writing "admin" inside the EEPROM */
	EEPROM_WriteString(APP_EEPROM_ADMIN_PASSWORD_ADDRESS, 5, (uint8_t*)"admin");

	/* Setting callBack function for the EXT interrupt MCUAL driver */
	EXTINT_SetCallBack(Card, EXTINT_INT2);
}

/*************************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : A function to update the application
*************************************************************************************************/
void APP_Update()
{
	uint8_t au8PAN[10];
	uint8_t au8Balance[8];
	uint8_t au8MaxAmount[8];
	uint8_t au8Mode[6];
	uint8_t au8AdminPassword[6];
	uint8_t au8EEPROMAdminPassword[6];
	uint8_t au8Temperature[2];
	uint8_t u8KeypadChar;
	uint8_t u8Temperature = 0;
	uint8_t u8LoopIndex;
	static uint8_t u8Flag = LOW;
	static uint8_t u8CardsNo=0;
	/* Checking if the system is blocked or not */
	if(u8Flag == LOW)
	{
		/* Clearing the LCD screen */
		LCD_Clear();
		/* Displaying "Welcome to" on the LCD screen */
		LCD_DisplayString((uint8_t*)"   Welcome to");
		/* Setting the position of the cursor at the second row of the LCD screen */
		LCD_SetCursorPosition(0, 1);
		/* Displaying "ATM System" on the LCD screen */
		LCD_DisplayString((uint8_t*)"   ATM System");
		/* Sending "Enter the used mode (ADMIN - USER):" on the terminal by UART */
		UART_SendString((uint8_t*)"Enter the used mode (ADMIN - USER):\r");
		/* Receiving the entered mode from the terminal by UART */
		UART_ReceiveString(au8Mode, MAX_LEN);
		/* Sending new line on the terminal by UART */
		UART_SendData((uint8_t)'\r');
		/* Checking if the received mode is ADMIN mode */
		if((au8Mode[0] == 'A') && (au8Mode[1] == 'D') && (au8Mode[2] == 'M') &&
		   (au8Mode[3] == 'I') && (au8Mode[4] == 'N'))
		{
			gu8BTNFlag=1;
			/* Clearing the LCD screen */
			LCD_Clear();
			/* Displaying "ADMIN MODE" on the LCD screen */
			LCD_DisplayString((uint8_t*)"   ADMIN MODE");
			/* Sending "Enter Password:" on the terminal by UART */
			UART_SendString((uint8_t*)"Enter Password:\r");
			/* Receiving the entered admin password from the terminal by UART */
			UART_ReceiveString(au8AdminPassword, MAX_LEN);
			/* Reading the stored admin password "admin" from EEPROM */
			EEPROM_ReadString(APP_EEPROM_ADMIN_PASSWORD_ADDRESS, 5, au8EEPROMAdminPassword);
			/* Checking if the entered admin password is the same as the stored admin password in EEPROM */
			if((au8AdminPassword[0] == au8EEPROMAdminPassword[0]) && (au8AdminPassword[1] == au8EEPROMAdminPassword[1]) &&
			   (au8AdminPassword[2] == au8EEPROMAdminPassword[2]) && (au8AdminPassword[3] == au8EEPROMAdminPassword[3]) &&
			   (au8AdminPassword[4] == au8EEPROMAdminPassword[4]))
			{
				/* Breaking the loop process if Exit (3) is inserted */
				do
				{
					/* Sending new line on the terminal by UART */
					UART_SendData((uint8_t)'\r');
					/* Sending "Please select one of the following:" on the terminal by UART */
					UART_SendString((uint8_t*)"Please select one of the following:\r");
					/* Sending "1- Customer Data" on the terminal by UART */
					UART_SendString((uint8_t*)"1- Customer Data\r");
					/* Sending "2- Maximum Amount" on the terminal by UART */
					UART_SendString((uint8_t*)"2- Maximum Amount\r");
					/* Sending "3- Exit\r" on the terminal by UART */
					UART_SendString((uint8_t*)"3- Exit\r");
					/* Sending new line on the terminal by UART */
					UART_SendData((uint8_t)'\r');
					/* Getting the selected mode from the keypad */
					Keypad_GetChar(&u8KeypadChar);
					/* Checking if the selected mode is "Customer Data" */
					if(u8KeypadChar == '1')
					{
						UART_SendString((uint8_t*)"Pls enter number of cards: ");
						UART_ReceiveData((uint16_t*)&u8CardsNo);
						u8CardsNo=u8CardsNo-'0';
						EEPROM_WriteByte(0x020, u8CardsNo);
						UART_SendData('\r');
						for(u8LoopIndex=0;u8LoopIndex<u8CardsNo;u8LoopIndex++)
						{
							/* Sending "Please enter PAN:" on the terminal by UART */
							UART_SendString((uint8_t*)"Please enter PAN:\r");
							/* Receiving the entered PAN from the terminal by UART */
							UART_ReceiveString(au8PAN, MAX_LEN);
							/**/
							/* Writing the PAN inside the EEPROM */
							EEPROM_WriteString(0x100 + (0x10 * u8LoopIndex), 9, au8PAN);
							/* Sending "Please enter balance:" on the terminal by UART */
							UART_SendString((uint8_t*)"Please enter balance:\r");
							/* Receiving the entered balance from the terminal by UART */
							UART_ReceiveString(au8Balance, MAX_LEN);
							/* Writing the balance inside the EEPROM */
							EEPROM_WriteString(0x500 + (0x10 * u8LoopIndex), 7, au8Balance);
						}
					}
					/* Checking if the selected mode is "Maximum Amount" */
					else if(u8KeypadChar == '2')
					{
						/* Sending "Please enter maximum amount:" on the terminal by UART */
						UART_SendString((uint8_t*)"Please enter maximum amount:\r");
						/* Receiving the entered maximmum amount from the terminal by UART */
						UART_ReceiveString(au8MaxAmount, MAX_LEN);
						/* Writing the maximum amount inside the EEPROM */
						EEPROM_WriteString(APP_EEPROM_MAX_AMOUNT_ADDRESS, 7, au8MaxAmount);
					}
					else
					{
					}
				} while(u8KeypadChar != '3');
			}
			else
			{
				/* Sending "Invalid Password" on the terminal by UART if wrong admin password is inserted */
				UART_SendString((uint8_t*)"Invalid Password\r");
				/* Sending new line on the terminal by UART */
				UART_SendData((uint8_t)'\r');
			}
			u8Flag = LOW;
		}
		/* Checking if the received mode is USER mode */
		else if((au8Mode[0] == 'U') && (au8Mode[1] == 'S') &&
				(au8Mode[2] == 'E') && (au8Mode[3] == 'R'))
		{
			gu8BTNFlag=2;
			u8Flag = LOW;
			while(u8Flag == LOW)
			{
				/* Clearing the LCD screen */
				LCD_Clear();
				/* Displaying "1- Insert a Card" on the LCD screen */
				LCD_DisplayString((uint8_t*)"1- Insert a Card");
				/* Setting the position of the cursor at the second row of the LCD screen */
				LCD_SetCursorPosition(0, 1);
				/* Displaying "2- Display Temp" on the LCD screen */
				LCD_DisplayString((uint8_t*)"2- Display Temp");
				/* Getting the selected mode from the keypad */
				Keypad_GetChar(&u8KeypadChar);
				/* Checking if the selected mode is to use the ATM */
				if(u8KeypadChar == '1')
				{
					/* Clearing the LCD screen */
					LCD_Clear();
					/* Displaying "Please Enter" on the LCD screen */
					LCD_DisplayString((uint8_t*)"  Please Enter");
					/* Setting the position of the cursor at the second row of the LCD screen */
					LCD_SetCursorPosition(0, 1);
					/* Displaying "Your Card!" on the LCD screen */
					LCD_DisplayString((uint8_t*)"   Your Card!");
					gu8BTNFlag=0;
               UART_SendData(gu8BTNFlag);
					while(gu8BTNFlag!=2);
					u8Flag = LOW;
				}
				/* Checking if the selected mode is to display the temperature */
				else if(u8KeypadChar == '2')
				{
					u8Flag=HIGH;
					/* Reading the current temperature of the LM35 sensor */
					LM35_ReadTemperature(&u8Temperature);
					/* Clearing the LCD screen */
					LCD_Clear();
					/* Displaying "Current Temp: " on the LCD screen */
					LCD_DisplayString((uint8_t*)"Current Temp: ");
					/* Converting the temperature read from the LM35 sensor from integer to array of ASCII characters */
					itoa(u8Temperature, (char*)au8Temperature, 10);
					/* Displaying the temperature read from the LM35 sensor on the LCD screen */
					LCD_DisplayString(au8Temperature);
					/* Checking if the temperature read from the LM35 sensor is greater than 50 */
					if(u8Temperature > 50)
					{
						/* Clearing the LCD screen */
						LCD_Clear();
						/* Displaying "System blocked!" on the LCD screen */
						LCD_DisplayString((uint8_t*)"System blocked!");
						/* Setting the position of the cursor at the second row of the LCD screen */
						LCD_SetCursorPosition(0, 1);
						/* Displaying "Temp is above 50" on the LCD screen */
						LCD_DisplayString((uint8_t*)"Temp is above 50");
						/* Setting the system block flag to one to block the whole system */
						u8Flag = HIGH;
					}
					else
					{
						/* Setting the position of the cursor at the second row of the LCD screen */
						LCD_SetCursorPosition(0, 1);
						/* Displaying "Press any key" on the LCD screen */
						LCD_DisplayString((uint8_t*)"Press any key");
						/* Waiting for any key to be pressed from the keypad */
						Keypad_GetChar(&u8KeypadChar);
						u8Flag = LOW;
					}
				}
				else
				{
					/* Invalid keypad input, 1 or 2 must be inserted */
					u8Flag = LOW;
				}
			}
		}
		else
		{
			/* Sending "Invalid mode is inserted" on the terminal by UART */
			UART_SendString((uint8_t*)"Invalid mode is inserted\r");
			/* Sending new line on the terminal by UART */
			UART_SendData((uint8_t)'\r');
		}
	}
	else
	{
		/* System is blocked */
	}
}


static void APP_Delay(void)
{
	volatile uint32_t u32DelayValue;
	for(u32DelayValue = 0; u32DelayValue < 250000; u32DelayValue++);
}

static void doubletostr (double num,char *str, int precision)
{
    int int_exponent=1,frac_exponent=1;

    for (int temp=num/10;temp;temp/=10)
    {
        int_exponent*=10;
    }
    for (int i=0;i<precision;i++)
    {
        frac_exponent*=10;
    }
    long int integer=num;
    long int fraction=(num-integer)*frac_exponent;
    int i=0;
    for(i=0;int_exponent;i++)
    {
        str[i]=((integer/int_exponent)%10)+'0';
        int_exponent/=10;
    }
    str[i++]='.';
    frac_exponent/=10;
    for(;frac_exponent;i++)
    {
        str[i]=((fraction/frac_exponent)%10)+'0';
        frac_exponent/=10;
    }
    str[i++]=0;
}
