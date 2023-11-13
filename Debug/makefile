################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include rzn_gen/subdir.mk
-include rzn/fsp/src/rm_ethercat_ssc_port/subdir.mk
-include rzn/fsp/src/r_xspi_qspi/subdir.mk
-include rzn/fsp/src/r_usb_pcdc/src/subdir.mk
-include rzn/fsp/src/r_usb_basic/src/hw/subdir.mk
-include rzn/fsp/src/r_usb_basic/src/driver/subdir.mk
-include rzn/fsp/src/r_usb_basic/subdir.mk
-include rzn/fsp/src/r_ioport/subdir.mk
-include rzn/fsp/src/r_ether_selector/subdir.mk
-include rzn/fsp/src/r_ether_phy/subdir.mk
-include rzn/fsp/src/r_dsmif/subdir.mk
-include rzn/fsp/src/r_dmac/subdir.mk
-include rzn/fsp/src/r_cmt/subdir.mk
-include rzn/fsp/src/bsp/mcu/rzn2l/subdir.mk
-include rzn/fsp/src/bsp/mcu/all/subdir.mk
-include rzn/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include rzn/board/rzn2l_rsk/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(P_UPPER_DEPS)),)
-include $(P_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(PP_UPPER_DEPS)),)
-include $(PP_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(FSY_UPPER_DEPS)),)
-include $(FSY_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_UPPER_DEPS)),)
-include $(JMP_UPPER_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
rzn2l_test.bin \

SECONDARY_SIZE += \
rzn2l_test.siz \


# All Target
all:
	$(MAKE) --no-print-directory main-build
	$(MAKE) --no-print-directory post-build

# Main-build Target
main-build: rzn2l_test.elf secondary-outputs

# Tool invocations
rzn2l_test.elf: $(OBJS) $(USER_OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(LINKER_SCRIPT)
	$(file > rzn2l_test.elf.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -o "rzn2l_test.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) -Wl,--end-group -T "E:\\workspace\\e2 studio 202310\\rzn2l_test\\script\\main.ld" -L"E:\\workspace\\e2 studio 202310\\rzn2l_test/script" -Wl,--start-group  -Wl,--end-group -nostartfiles -Xlinker --gc-sections -Wl,-Map,"rzn2l_test.map" --specs=nano.specs -Wl,-esystem_init --specs=rdimon.specs)
	@echo Building target: $@ && arm-none-eabi-gcc @"rzn2l_test.elf.in"
rzn2l_test.bin: rzn2l_test.elf
	arm-none-eabi-objcopy -O binary --gap-fill 0xff "rzn2l_test.elf"  "rzn2l_test.bin"
rzn2l_test.siz: rzn2l_test.elf
	arm-none-eabi-size --format=berkeley "rzn2l_test.elf"
# Other Targets
clean:
	-$(file > clean_file.tmp,  $(JMP_DEPS)  $(FSY_DEPS)  $(C_UPPER_DEPS)  $(SECONDARY_SIZE)  $(SRC_UPPER_DEPS)  $(P_UPPER_DEPS)  $(S_DEPS)  $(LST)  $(PP_UPPER_DEPS)  $(P_DEPS)  $(FSY_UPPER_DEPS)  $(C_DEPS)  $(SRC_DEPS)  $(JMP_UPPER_DEPS)  $(PP_DEPS)  $(ASM_UPPER_DEPS)  $(SX_DEPS)  $(SX_UPPER_DEPS)  $(OBJS)  $(SECONDARY_FLASH)  $(ASM_DEPS)  $(S_UPPER_DEPS)  $(MAP) )
	-@ xargs -P 2 -s 32000 -t -a clean_file.tmp $(RM)
	-@$(RM) clean_file.tmp
	-$(RM)  rzn2l_test.elf
	-@echo ' '

post-build:
	-appGen.bat
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents  post-build

-include ../makefile.targets
