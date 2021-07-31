################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/DCFan/DCFan.c 

OBJS += \
./ECUAL/DCFan/DCFan.o 

C_DEPS += \
./ECUAL/DCFan/DCFan.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/DCFan/%.o: ../ECUAL/DCFan/%.c ECUAL/DCFan/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


