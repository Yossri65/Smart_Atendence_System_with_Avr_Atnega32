################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/int_EEPROM/eeprom.c 

OBJS += \
./MCAL/int_EEPROM/eeprom.o 

C_DEPS += \
./MCAL/int_EEPROM/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/int_EEPROM/%.o: ../MCAL/int_EEPROM/%.c MCAL/int_EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


