################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../Buzzer.c \
../DC_DOOR.c \
../DC_MOTOR.c \
../DIO.c \
../GIE.c \
../I2C.c \
../TIMER.c \
../UART.c \
../main.c \
../timer2.c 

OBJS += \
./ADC.o \
./Buzzer.o \
./DC_DOOR.o \
./DC_MOTOR.o \
./DIO.o \
./GIE.o \
./I2C.o \
./TIMER.o \
./UART.o \
./main.o \
./timer2.o 

C_DEPS += \
./ADC.d \
./Buzzer.d \
./DC_DOOR.d \
./DC_MOTOR.d \
./DIO.d \
./GIE.d \
./I2C.d \
./TIMER.d \
./UART.d \
./main.d \
./timer2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


