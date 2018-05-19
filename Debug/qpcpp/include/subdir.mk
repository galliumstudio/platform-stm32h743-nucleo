################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../qpcpp/include/qstamp.cpp 

OBJS += \
./qpcpp/include/qstamp.o 

CPP_DEPS += \
./qpcpp/include/qstamp.d 


# Each subdirectory must supply rules for building sources it contributes
qpcpp/include/%.o: ../qpcpp/include/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32H743xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32h7xx" -I"../system/BSP/STM32H7xx_Nucleo_144" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/source -I../qpcpp/ports/arm-cm/qxk/gnu -I../qpcpp/src -I../framework/include -I../src/System -I../src/Console -I../src/Console/CmdInput -I../src/Console/CmdParser -I../src/Template/CompositeAct -I../src/Template/CompositeAct/CompositeReg -I../src/Template/SimpleAct -I../src/UartAct -I../src/UartAct/UartIn -I../src/UartAct/UartOut -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


