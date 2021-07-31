/***************************************************************
* Task       : SPI Driver
* File Name	 : SPI_registers.h
* Description: header file for SPI memory mapped registers
* Author     : Kariman
* Date       : 14/7/2021
***************************************************************/

#ifndef MCAL_SPI_SPI_REGISTERS_H_
#define MCAL_SPI_SPI_REGISTERS_H_


/*- SPI Registers----------------------------------------*/

/*- SPI Control Register –SPCR---------------------------*/
#define SPCR_R    (*(volatile unsigned char*) 0x2D)
#define SPIE_B    7
#define SPE_B     6
#define DORD_B    5
#define MSTR_B    4
#define CPOL_B    3
#define CPHA_B    2
#define SPR1_B    1
#define SPR0_B    0

/*- SPI Status Register –SPSR---------------------------*/
#define SPSR_R    (*(volatile unsigned char*) 0x2E)
#define SPIF_B    7
#define WCOL_B    6
#define SPI2X_B   0

/*- SPI Data Register –SPDR---------------------------*/
#define SPDR_R    (*(volatile unsigned char*) 0x2F)



#endif /* MCAL_SPI_SPI_REGISTERS_H_ */
