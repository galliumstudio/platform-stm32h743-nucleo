################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sample/SampleReg/SampleReg.cpp 

OBJS += \
./src/Sample/SampleReg/SampleReg.o 

CPP_DEPS += \
./src/Sample/SampleReg/SampleReg.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sample/SampleReg/%.o: ../src/Sample/SampleReg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


