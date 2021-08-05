/*
 * EXINT_registers.h
 *
 *  Created on: Aug 3, 2021
 *      Author: Kariman
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EXT_INT_REGISTERS_H_
#define MCAL_EXTERNAL_INTERRUPT_EXT_INT_REGISTERS_H_

/*******************************************************************************
 *                           INTERRUPT Registers                               *
********************************************************************************/
#define GICR_R    *((volatile char*) 0x5B)
#define SREG_R    *((volatile char*) 0x5F)
#define SREG_I_B    7
#define INT0_B    6
#define INT1_B    7
#define INT2_B    5
#define MCUCR_R   *((volatile char*) 0x55)

#endif /* MCAL_EXTERNAL_INTERRUPT_EXT_INT_REGISTERS_H_ */
