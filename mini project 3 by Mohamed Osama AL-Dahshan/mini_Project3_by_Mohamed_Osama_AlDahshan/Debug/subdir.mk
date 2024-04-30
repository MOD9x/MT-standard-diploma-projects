################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DcMotor.c \
../LM35.c \
../MiniProject3.c \
../PWM.c \
../gpio.c \
../lcd.c 

OBJS += \
./ADC.o \
./DcMotor.o \
./LM35.o \
./MiniProject3.o \
./PWM.o \
./gpio.o \
./lcd.o 

C_DEPS += \
./ADC.d \
./DcMotor.d \
./LM35.d \
./MiniProject3.d \
./PWM.d \
./gpio.d \
./lcd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


