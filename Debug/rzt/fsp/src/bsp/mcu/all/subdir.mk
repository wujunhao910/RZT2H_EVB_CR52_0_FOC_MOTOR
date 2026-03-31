################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzt/fsp/src/bsp/mcu/all/bsp_address_expander.c \
../rzt/fsp/src/bsp/mcu/all/bsp_cache.c \
../rzt/fsp/src/bsp/mcu/all/bsp_clocks.c \
../rzt/fsp/src/bsp/mcu/all/bsp_common.c \
../rzt/fsp/src/bsp/mcu/all/bsp_ddr.c \
../rzt/fsp/src/bsp/mcu/all/bsp_ddr_fw_param.c \
../rzt/fsp/src/bsp/mcu/all/bsp_delay.c \
../rzt/fsp/src/bsp/mcu/all/bsp_io.c \
../rzt/fsp/src/bsp/mcu/all/bsp_irq.c \
../rzt/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../rzt/fsp/src/bsp/mcu/all/bsp_reset.c \
../rzt/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../rzt/fsp/src/bsp/mcu/all/bsp_semaphore.c \
../rzt/fsp/src/bsp/mcu/all/bsp_slave_stop.c \
../rzt/fsp/src/bsp/mcu/all/bsp_tzc400.c 

LST += \
bsp_address_expander.lst \
bsp_cache.lst \
bsp_clocks.lst \
bsp_common.lst \
bsp_ddr.lst \
bsp_ddr_fw_param.lst \
bsp_delay.lst \
bsp_io.lst \
bsp_irq.lst \
bsp_register_protection.lst \
bsp_reset.lst \
bsp_sbrk.lst \
bsp_semaphore.lst \
bsp_slave_stop.lst \
bsp_tzc400.lst 

C_DEPS += \
./rzt/fsp/src/bsp/mcu/all/bsp_address_expander.d \
./rzt/fsp/src/bsp/mcu/all/bsp_cache.d \
./rzt/fsp/src/bsp/mcu/all/bsp_clocks.d \
./rzt/fsp/src/bsp/mcu/all/bsp_common.d \
./rzt/fsp/src/bsp/mcu/all/bsp_ddr.d \
./rzt/fsp/src/bsp/mcu/all/bsp_ddr_fw_param.d \
./rzt/fsp/src/bsp/mcu/all/bsp_delay.d \
./rzt/fsp/src/bsp/mcu/all/bsp_io.d \
./rzt/fsp/src/bsp/mcu/all/bsp_irq.d \
./rzt/fsp/src/bsp/mcu/all/bsp_register_protection.d \
./rzt/fsp/src/bsp/mcu/all/bsp_reset.d \
./rzt/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./rzt/fsp/src/bsp/mcu/all/bsp_semaphore.d \
./rzt/fsp/src/bsp/mcu/all/bsp_slave_stop.d \
./rzt/fsp/src/bsp/mcu/all/bsp_tzc400.d 

OBJS += \
./rzt/fsp/src/bsp/mcu/all/bsp_address_expander.o \
./rzt/fsp/src/bsp/mcu/all/bsp_cache.o \
./rzt/fsp/src/bsp/mcu/all/bsp_clocks.o \
./rzt/fsp/src/bsp/mcu/all/bsp_common.o \
./rzt/fsp/src/bsp/mcu/all/bsp_ddr.o \
./rzt/fsp/src/bsp/mcu/all/bsp_ddr_fw_param.o \
./rzt/fsp/src/bsp/mcu/all/bsp_delay.o \
./rzt/fsp/src/bsp/mcu/all/bsp_io.o \
./rzt/fsp/src/bsp/mcu/all/bsp_irq.o \
./rzt/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./rzt/fsp/src/bsp/mcu/all/bsp_reset.o \
./rzt/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./rzt/fsp/src/bsp/mcu/all/bsp_semaphore.o \
./rzt/fsp/src/bsp/mcu/all/bsp_slave_stop.o \
./rzt/fsp/src/bsp/mcu/all/bsp_tzc400.o 

MAP += \
RZT2H_EVB_CR52_0_FOC_MOTOR.map 


# Each subdirectory must supply rules for building sources it contributes
rzt/fsp/src/bsp/mcu/all/%.o: ../rzt/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wnull-dereference -g3 -gdwarf-4 -D_RENESAS_RZT_ -D_RZT_CORE=CR52_0 -D_RZT_ORDINAL=1 -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src" -I"C:\\Renesas\\rzt\\e2studio_v2024-10_fsp_v2.2.0\\toolchains\\gcc_arm\\arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi\\/arm-none-eabi/include" -I"D:/renesas_workspace/RZT2H_EVB_CR52_0_FOC_MOTOR/src" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\inc\\apl" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\encoder\\FACoder" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv\\dsm" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\cg_src" -I"." -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\api" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\instances" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\src\\bsp\\mcu\\all\\cr" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_gen" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg\\bsp" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\driver" -std=gnu99 -Wno-format-truncation -Wno-stringop-overflow --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@arm-none-eabi-gcc @"$@.in"

