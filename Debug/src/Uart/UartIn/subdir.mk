################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Uart/UartIn/UartIn.cpp 

OBJS += \
./src/Uart/UartIn/UartIn.o 

CPP_DEPS += \
./src/Uart/UartIn/UartIn.d 


# Each subdirectory must supply rules for building sources it contributes
src/Uart/UartIn/%.o: ../src/Uart/UartIn/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F746xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32746G-Discovery" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/ports/arm-cm/qxk/gnu -I../framework/include -I../src/System -I../src/Sample -I../src/Sample/SampleReg -I../src/Uart -I../src/Uart/UartIn -I../src/Uart/UartOut -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


