################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Utilities/CPU/cpu_utils.c 

OBJS += \
./system/Utilities/CPU/cpu_utils.o 

C_DEPS += \
./system/Utilities/CPU/cpu_utils.d 


# Each subdirectory must supply rules for building sources it contributes
system/Utilities/CPU/%.o: ../system/Utilities/CPU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F746xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -I"../system/BSP/STM32746G-Discovery" -I"../system/BSP/Components" -I"../system/Utilities/Log" -I"../system/Utilities/CPU" -I"../system/Utilities/Fonts" -I"../system/Utilities/JPEG" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


