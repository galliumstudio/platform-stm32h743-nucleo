################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../qpcpp-5.9.5/src/qf/qep_hsm.cpp \
../qpcpp-5.9.5/src/qf/qep_msm.cpp \
../qpcpp-5.9.5/src/qf/qf_act.cpp \
../qpcpp-5.9.5/src/qf/qf_actq.cpp \
../qpcpp-5.9.5/src/qf/qf_defer.cpp \
../qpcpp-5.9.5/src/qf/qf_dyn.cpp \
../qpcpp-5.9.5/src/qf/qf_mem.cpp \
../qpcpp-5.9.5/src/qf/qf_ps.cpp \
../qpcpp-5.9.5/src/qf/qf_qact.cpp \
../qpcpp-5.9.5/src/qf/qf_qeq.cpp \
../qpcpp-5.9.5/src/qf/qf_qmact.cpp \
../qpcpp-5.9.5/src/qf/qf_time.cpp 

OBJS += \
./qpcpp-5.9.5/src/qf/qep_hsm.o \
./qpcpp-5.9.5/src/qf/qep_msm.o \
./qpcpp-5.9.5/src/qf/qf_act.o \
./qpcpp-5.9.5/src/qf/qf_actq.o \
./qpcpp-5.9.5/src/qf/qf_defer.o \
./qpcpp-5.9.5/src/qf/qf_dyn.o \
./qpcpp-5.9.5/src/qf/qf_mem.o \
./qpcpp-5.9.5/src/qf/qf_ps.o \
./qpcpp-5.9.5/src/qf/qf_qact.o \
./qpcpp-5.9.5/src/qf/qf_qeq.o \
./qpcpp-5.9.5/src/qf/qf_qmact.o \
./qpcpp-5.9.5/src/qf/qf_time.o 

CPP_DEPS += \
./qpcpp-5.9.5/src/qf/qep_hsm.d \
./qpcpp-5.9.5/src/qf/qep_msm.d \
./qpcpp-5.9.5/src/qf/qf_act.d \
./qpcpp-5.9.5/src/qf/qf_actq.d \
./qpcpp-5.9.5/src/qf/qf_defer.d \
./qpcpp-5.9.5/src/qf/qf_dyn.d \
./qpcpp-5.9.5/src/qf/qf_mem.d \
./qpcpp-5.9.5/src/qf/qf_ps.d \
./qpcpp-5.9.5/src/qf/qf_qact.d \
./qpcpp-5.9.5/src/qf/qf_qeq.d \
./qpcpp-5.9.5/src/qf/qf_qmact.d \
./qpcpp-5.9.5/src/qf/qf_time.d 


# Each subdirectory must supply rules for building sources it contributes
qpcpp-5.9.5/src/qf/%.o: ../qpcpp-5.9.5/src/qf/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F767xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32F7xx_Nucleo_144" -I"../system/BSP/Components" -I../qpcpp/include -I../qpcpp/ports/arm-cm/qxk/gnu -I../framework/include -I../src/System -I../src/Sample -I../src/Sample/SampleReg -I../src/UartAct -I../src/UartAct/UartIn -I../src/UartAct/UartOut -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


