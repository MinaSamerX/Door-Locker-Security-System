################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_ctrl.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main.c \
../timer1.c \
../uart.c 

OBJS += \
./HMI_ctrl.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main.o \
./timer1.o \
./uart.o 

C_DEPS += \
./HMI_ctrl.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


