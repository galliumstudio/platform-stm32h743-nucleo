################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/BSP/STM32746G-Discovery/stm32746g_discovery.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_audio.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_camera.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_eeprom.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_qspi.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_sd.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_sdram.c \
../system/BSP/STM32746G-Discovery/stm32746g_discovery_ts.c 

OBJS += \
./system/BSP/STM32746G-Discovery/stm32746g_discovery.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_audio.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_camera.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_eeprom.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_qspi.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_sd.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_sdram.o \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_ts.o 

C_DEPS += \
./system/BSP/STM32746G-Discovery/stm32746g_discovery.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_audio.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_camera.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_eeprom.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_qspi.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_sd.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_sdram.d \
./system/BSP/STM32746G-Discovery/stm32746g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
system/BSP/STM32746G-Discovery/%.o: ../system/BSP/STM32746G-Discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


