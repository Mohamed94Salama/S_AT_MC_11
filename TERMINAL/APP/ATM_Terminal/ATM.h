#ifndef ATM_ATM_H_
#define ATM_ATM_H_

#include <stdlib.h>
#include "BIT_MANIPULATE.h"
#include "STD_TYPES.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/I2C/I2C.h"
#include "MCAL/SPI/SPI.h"
#include "MCAL/UART/UART.h"
#include "MCAL/EXT_Int/EXT_INT.h"
#include "ECUAL/Button/Button.h"
#include "ECUAL/DCFan/DCFan.h"
#include "ECUAL/EEPROM/EEPROM.h"
#include "ECUAL/Keypad/Keypad.h"
#include "ECUAL/LCD/LCD.h"
#include "ECUAL/Sensor/LM35.h"


void APP_Init(void);
void APP_Update(void);

#endif /* ATM_ATM_H_ */
