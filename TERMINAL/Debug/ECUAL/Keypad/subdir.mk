################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/Keypad/Keypad.c 

OBJS += \
./ECUAL/Keypad/Keypad.o 

C_DEPS += \
./ECUAL/Keypad/Keypad.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/Keypad/%.o: ../ECUAL/Keypad/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


