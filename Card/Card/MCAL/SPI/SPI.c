/******************************************************************************
 *
 * Module: SPI
 * File Name: spi.c
 * Description: Source file for the SPI AVR driver
 * Author: Kariman Karam
 *
 *******************************************************************************/

/*******************************************************************************
 *                      INCLUDES			                                   *
 *******************************************************************************/
//#include "../DIO/DIO_registers.h"
//#include "../DIO/DIO_init.h"
#include "SPI_registers.h"
#include "SPI_Cfg.h"
#include "SPI.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to initialize the MCU as a master SPT
************************************************************************************************/
static void SPI_initMaster(void){

	/************************** Configure Master pins **************************
	 * SS(PB4) = outpout
	 * MOSI(PB5) = output
	 * MISO(PB6) = input
	 * SCK(PB7) = output
	 * **************************************************************************/

//	DDRB_R |= (1<<PB4) | (1<<PB5) | (1<<PB7);
//	DDRB_R &= ~(1<<PB6);

	//DIO_Init();
	DIO_PinInit(PB4, OUTPUT, NO_CONNECTION);	// SS
	DIO_PinInit(PB5, OUTPUT, NO_CONNECTION);	// MOSI
	DIO_PinInit(PB6, INPUT, NO_CONNECTION);	// MISO
	DIO_PinInit(PB7, OUTPUT, NO_CONNECTION);	// SCK
	/************************** SPCR Description **************************
	 * SPE = 1 ENABLE SPI
	 * DOPR = 0 Data Order is MSB first
	 * MSTR = 1 Enable Mater Mode
	 * CPOL = 0 The Leading Edge of SCK is the Rising Edge, SCK is LOW when idle
	 * CPHA = 0 Sample Data at the Rising Edge of SCK
	 * SPR1 = 0, SPR0 = 0 To Choose Clock = Fosc/4
	 ***********************************************************************/
	SPCR_R = (1<<SPE_B) | (1<<MSTR_B) | (1<<CPHA_B) | (1<<SPR0_B);
}

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to initialize the MCU as a slave SPT
************************************************************************************************/
static void SPI_initSlave(void){

	/************************** Configure Slave pins **************************
	 * SS(PB4) = input
	 * MOSI(PB5) = input
	 * MISO(PB6) = output
	 * SCK(PB7) = input
	 * **************************************************************************/
//	DDRB_R &= (~(1<<PB4)) & (~(1<<PB5)) & (~(1<<PB7));
//	DDRB_R |= (1<<PB6);
	//DIO_Init();
	DIO_PinInit(PB4, INPUT, NO_CONNECTION);	// SS
	DIO_PinInit(PB5, INPUT, NO_CONNECTION);	// MOSI
	DIO_PinInit(PB6, OUTPUT, NO_CONNECTION);	// MISO
	DIO_PinInit(PB7, INPUT, NO_CONNECTION);	// SCK
	/************************** SPCR Description **************************
	 * SPE = 1 ENABLE SPI
	 * SPR1 = 0, SPR0 = 0 To Choose Clock = Fosc/4
	 ***********************************************************************/
	SPCR_R = (1<<SPE_B)|(1<<CPHA_B)| (1<<SPR0_B);
}

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to initialize SPT
************************************************************************************************/
void SPI_init(void)
{
#if(SPI_CFG == MASTER)
	SPI_initMaster();
#elif (SPI_CFG == SLAVE)
	SPI_initSlave();
#endif
}

/***********************************************************************************************
* Parameters (in) : u8Data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to send Byte via SPI
************************************************************************************************/
void SPI_sendData(const uint8_t u8Data)
{
	SPDR_R = u8Data;	/*send data*/
	while(!GET_BIT(SPSR_R, SPIF_B));	/*wait until transfer is complete (SPIF=1)*/
}

/***********************************************************************************************
* Parameters (in) : u8Data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to receive Byte via SPI
************************************************************************************************/
void SPI_receiveData(uint8_t* pu8Data)
{
	DIO_PinWrite(PB4, LOW);
	//store the pointer contents in the SPI data register to initialize communication
	SPDR_R= *pu8Data;
	while(!GET_BIT(SPSR_R,SPIF_B));	/*wait until receive is complete (SPIF=1)*/
	*pu8Data = SPDR_R;	/*return the received data*/
	DIO_PinWrite(PB4, HIGH);
}

/***********************************************************************************************
* Parameters (in) : u8Data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to send String via SPI
************************************************************************************************/
void SPI_sendString(const uint8_t *pu8Data)
{
    uint8_t u8i;

    for (u8i=0;pu8Data[u8i];u8i++)
    {

    	SPI_sendData(*(pu8Data+u8i));
    }

    SPI_sendData('\0');
//    SPI_sendData('\n');
}

/***********************************************************************************************
* Parameters (in) : u8Data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to receive String via SPI
************************************************************************************************/
void SPI_receiveString(uint8_t *pu8Data, uint8_t u8BufferMaxSize)
{
	uint8_t u8i;
	for (u8i=0; u8i < u8BufferMaxSize;u8i++)
	{

		SPI_receiveData(&pu8Data[u8i]);
		if (*(pu8Data+u8i)==0)
		{
			break;
		}
	}
	//end the string with null
	//pu8Data[u8i]='\0';
}
