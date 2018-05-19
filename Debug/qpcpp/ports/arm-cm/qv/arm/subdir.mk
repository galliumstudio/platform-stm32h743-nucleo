################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../qpcpp/ports/arm-cm/qv/arm/qv_port.cpp 

OBJS += \
./qpcpp/ports/arm-cm/qv/arm/qv_port.o 

CPP_DEPS += \
./qpcpp/ports/arm-cm/qv/arm/qv_port.d 


# Each subdirectory must supply rules for building sources it contributes
qpcpp/ports/arm-cm/qv/arm/%.o: ../qpcpp/ports/arm-cm/qv/arm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F767xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32F7xx_Nucleo_144" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/source -I../qpcpp/ports/arm-cm/qxk/gnu -I../qpcpp/src -I../framework/include -I../src/System -I../src/Template/CompositeAct -I../src/Template/CompositeAct/CompositeReg -I../src/Template/SimpleAct -I../src/UartAct -I../src/UartAct/UartIn -I../src/UartAct/UartOut -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


