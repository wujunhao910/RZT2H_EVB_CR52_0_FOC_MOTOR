################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/encoder/FACoder/subdir.mk
-include src/drv/dsm/subdir.mk
-include src/drv/subdir.mk
-include src/apl/subdir.mk
-include src/subdir.mk
-include rzt_gen/subdir.mk
-include rzt/fsp/src/r_xspi_ospi/subdir.mk
-include rzt/fsp/src/r_sci_uart/subdir.mk
-include rzt/fsp/src/r_poeg/subdir.mk
-include rzt/fsp/src/r_ioport/subdir.mk
-include rzt/fsp/src/r_gpt_three_phase/subdir.mk
-include rzt/fsp/src/r_gpt/subdir.mk
-include rzt/fsp/src/r_elc/subdir.mk
-include rzt/fsp/src/bsp/mcu/rzt2h/subdir.mk
-include rzt/fsp/src/bsp/mcu/all/cr/subdir.mk
-include rzt/fsp/src/bsp/mcu/all/subdir.mk
-include rzt/fsp/src/bsp/cmsis/Device/RENESAS/Source/cr/subdir.mk
-include rzt/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include rzt/board/rzt2h_evb/subdir.mk
-include cg_src/subdir.mk
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
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
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
RZT2H_EVB_CR52_0_FOC_MOTOR.srec \

SECONDARY_SIZE += \
RZT2H_EVB_CR52_0_FOC_MOTOR.siz \


# All Target
all: RZT2H_EVB_CR52_0_FOC_MOTOR.elf secondary-outputs

# Tool invocations
RZT2H_EVB_CR52_0_FOC_MOTOR.elf: $(OBJS) $(USER_OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(LINKER_SCRIPT)
	$(file > RZT2H_EVB_CR52_0_FOC_MOTOR.elf.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wnull-dereference -g3 -gdwarf-4 -o "RZT2H_EVB_CR52_0_FOC_MOTOR.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) -Wl,--end-group -T "fsp_ram_execution.ld" -L"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR/script" -Wl,--start-group -lgcc -lm -Wl,--end-group -nostartfiles -Xlinker --gc-sections -Wl,-Map,"RZT2H_EVB_CR52_0_FOC_MOTOR.map" --specs=nano.specs --specs=nosys.specs -Wl,-esystem_init)
	@echo Building target: $@ && arm-none-eabi-gcc @"RZT2H_EVB_CR52_0_FOC_MOTOR.elf.in"
RZT2H_EVB_CR52_0_FOC_MOTOR.srec: RZT2H_EVB_CR52_0_FOC_MOTOR.elf
	arm-none-eabi-objcopy -O srec "RZT2H_EVB_CR52_0_FOC_MOTOR.elf"  "RZT2H_EVB_CR52_0_FOC_MOTOR.srec"
RZT2H_EVB_CR52_0_FOC_MOTOR.siz: RZT2H_EVB_CR52_0_FOC_MOTOR.elf
	arm-none-eabi-size --format=berkeley "RZT2H_EVB_CR52_0_FOC_MOTOR.elf"
# Other Targets
clean:
	-$(file > clean_file.tmp,  $(JMP_DEPS)  $(FSY_DEPS)  $(C_UPPER_DEPS)  $(SECONDARY_SIZE)  $(SRC_UPPER_DEPS)  $(P_UPPER_DEPS)  $(S_DEPS)  $(LST)  $(PP_UPPER_DEPS)  $(P_DEPS)  $(FSY_UPPER_DEPS)  $(C_DEPS)  $(SRC_DEPS)  $(JMP_UPPER_DEPS)  $(PP_DEPS)  $(SX_DEPS)  $(ASM_UPPER_DEPS)  $(SX_UPPER_DEPS)  $(OBJS)  $(SECONDARY_FLASH)  $(ASM_DEPS)  $(S_UPPER_DEPS)  $(MAP) )
	-@ xargs -P 2 -s 32000 -t -a clean_file.tmp $(RM)
	-@$(RM) clean_file.tmp
	-$(RM)  RZT2H_EVB_CR52_0_FOC_MOTOR.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents 

-include ../makefile.targets
