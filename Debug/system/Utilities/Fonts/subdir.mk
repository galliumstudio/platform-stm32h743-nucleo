################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Utilities/Fonts/font12.c \
../system/Utilities/Fonts/font16.c \
../system/Utilities/Fonts/font20.c \
../system/Utilities/Fonts/font24.c \
../system/Utilities/Fonts/font8.c 

OBJS += \
./system/Utilities/Fonts/font12.o \
./system/Utilities/Fonts/font16.o \
./system/Utilities/Fonts/font20.o \
./system/Utilities/Fonts/font24.o \
./system/Utilities/Fonts/font8.o 

C_DEPS += \
./system/Utilities/Fonts/font12.d \
./system/Utilities/Fonts/font16.d \
./system/Utilities/Fonts/font20.d \
./system/Utilities/Fonts/font24.d \
./system/Utilities/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
system/Utilities/Fonts/%.o: ../system/Utilities/Fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F746xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32746G-Discovery" -I"../system/BSP/Components" -I"../system/Utilities/Log" -I"../system/Utilities/CPU" -I"../system/Utilities/Fonts" -I"../system/Utilities/JPEG" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


