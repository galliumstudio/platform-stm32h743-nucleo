################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../qpcpp-5.9.5/src/qs/qs.cpp \
../qpcpp-5.9.5/src/qs/qs_64bit.cpp \
../qpcpp-5.9.5/src/qs/qs_fp.cpp \
../qpcpp-5.9.5/src/qs/qs_rx.cpp \
../qpcpp-5.9.5/src/qs/qutest.cpp 

OBJS += \
./qpcpp-5.9.5/src/qs/qs.o \
./qpcpp-5.9.5/src/qs/qs_64bit.o \
./qpcpp-5.9.5/src/qs/qs_fp.o \
./qpcpp-5.9.5/src/qs/qs_rx.o \
./qpcpp-5.9.5/src/qs/qutest.o 

CPP_DEPS += \
./qpcpp-5.9.5/src/qs/qs.d \
./qpcpp-5.9.5/src/qs/qs_64bit.d \
./qpcpp-5.9.5/src/qs/qs_fp.d \
./qpcpp-5.9.5/src/qs/qs_rx.d \
./qpcpp-5.9.5/src/qs/qutest.d 


# Each subdirectory must supply rules for building sources it contributes
qpcpp-5.9.5/src/qs/%.o: ../qpcpp-5.9.5/src/qs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F767xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32F7xx_Nucleo_144" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/ports/arm-cm/qxk/gnu -I../framework/include -I../src/System -I../src/Sample -I../src/Sample/SampleReg -I../src/UartAct -I../src/UartAct/UartIn -I../src/UartAct/UartOut -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

