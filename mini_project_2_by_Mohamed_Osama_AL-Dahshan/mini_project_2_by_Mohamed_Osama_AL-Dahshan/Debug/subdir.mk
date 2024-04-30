################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD.c \
../TIMER1.c \
../gpio.c \
../mini_project_2_by_Mohamed_Osama_AL-Dahshan.c 

OBJS += \
./LCD.o \
./TIMER1.o \
./gpio.o \
./mini_project_2_by_Mohamed_Osama_AL-Dahshan.o 

C_DEPS += \
./LCD.d \
./TIMER1.d \
./gpio.d \
./mini_project_2_by_Mohamed_Osama_AL-Dahshan.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


