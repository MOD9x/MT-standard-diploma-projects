################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ICU.c \
../LCD.c \
../Mini_Project4.c \
../Ultrasonic.c \
../gpio.c 

OBJS += \
./ICU.o \
./LCD.o \
./Mini_Project4.o \
./Ultrasonic.o \
./gpio.o 

C_DEPS += \
./ICU.d \
./LCD.d \
./Mini_Project4.d \
./Ultrasonic.d \
./gpio.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


