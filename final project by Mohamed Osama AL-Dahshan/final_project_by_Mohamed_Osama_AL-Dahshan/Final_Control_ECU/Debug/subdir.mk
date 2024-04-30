################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BUZZER.c \
../Control.c \
../DcMotor.c \
../EEPROM.c \
../I2C.c \
../PWM.c \
../TIMER1.c \
../UART.c \
../gpio.c 

OBJS += \
./BUZZER.o \
./Control.o \
./DcMotor.o \
./EEPROM.o \
./I2C.o \
./PWM.o \
./TIMER1.o \
./UART.o \
./gpio.o 

C_DEPS += \
./BUZZER.d \
./Control.d \
./DcMotor.d \
./EEPROM.d \
./I2C.d \
./PWM.d \
./TIMER1.d \
./UART.d \
./gpio.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


