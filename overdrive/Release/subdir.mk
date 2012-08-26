################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Overdrive_neutrino.cpp 

OBJS += \
./Overdrive_neutrino.o 

CPP_DEPS += \
./Overdrive_neutrino.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/wojtek/Downloads/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Users/wojtek/Downloads/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/mega" -I"/Users/wojtek/Google Drive/Atominho/Arduino-Playground/overdrive" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


