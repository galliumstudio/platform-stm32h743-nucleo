################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/src/stm32h7xx/subdir.mk
-include system/src/newlib/subdir.mk
-include system/src/diag/subdir.mk
-include system/src/cortexm/subdir.mk
-include system/src/cmsis/subdir.mk
-include system/BSP/STM32H7xx_Nucleo_144/subdir.mk
-include src/UartAct/UartOut/subdir.mk
-include src/UartAct/UartIn/subdir.mk
-include src/UartAct/subdir.mk
-include src/Template/SimpleReg/subdir.mk
-include src/Template/SimpleAct/subdir.mk
-include src/Template/CompositeAct/CompositeReg/subdir.mk
-include src/Template/CompositeAct/subdir.mk
-include src/System/subdir.mk
-include src/Console/CmdParser/subdir.mk
-include src/Console/CmdInput/subdir.mk
-include src/Console/subdir.mk
-include src/subdir.mk
-include qpcpp/src/qxk/subdir.mk
-include qpcpp/src/qf/subdir.mk
-include qpcpp/ports/arm-cm/qxk/gnu/subdir.mk
-include qpcpp/include/subdir.mk
-include framework/source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
platform-stm32h743-nucleo.hex \

SECONDARY_SIZE += \
platform-stm32h743-nucleo.siz \


# All Target
all: platform-stm32h743-nucleo.elf secondary-outputs

# Tool invocations
platform-stm32h743-nucleo.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"platform-stm32h743-nucleo.map" --specs=nano.specs -o "platform-stm32h743-nucleo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

platform-stm32h743-nucleo.hex: platform-stm32h743-nucleo.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "platform-stm32h743-nucleo.elf"  "platform-stm32h743-nucleo.hex"
	@echo 'Finished building: $@'
	@echo ' '

platform-stm32h743-nucleo.siz: platform-stm32h743-nucleo.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "platform-stm32h743-nucleo.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) platform-stm32h743-nucleo.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
