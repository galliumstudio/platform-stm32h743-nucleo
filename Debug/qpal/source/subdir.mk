################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../qpal/source/qpal_hsm.cpp 

OBJS += \
./qpal/source/qpal_hsm.o 

CPP_DEPS += \
./qpal/source/qpal_hsm.d 


# Each subdirectory must supply rules for building sources it contributes
qpal/source/%.o: ../qpal/source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F746xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32746G-Discovery" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/ports/arm-cm/qxk/gnu -I../qpal/include -I../src/System -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


