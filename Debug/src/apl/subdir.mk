################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/apl/m_commands.c \
../src/apl/m_commutation.c \
../src/apl/m_control.c \
../src/apl/m_homing.c \
../src/apl/m_interlocks.c \
../src/apl/m_interpreter.c \
../src/apl/m_phasing.c \
../src/apl/m_pid_calc.c \
../src/apl/m_pos_read.c \
../src/apl/m_recorder.c \
../src/apl/m_vpg_trap.c 

LST += \
m_commands.lst \
m_commutation.lst \
m_control.lst \
m_homing.lst \
m_interlocks.lst \
m_interpreter.lst \
m_phasing.lst \
m_pid_calc.lst \
m_pos_read.lst \
m_recorder.lst \
m_vpg_trap.lst 

C_DEPS += \
./src/apl/m_commands.d \
./src/apl/m_commutation.d \
./src/apl/m_control.d \
./src/apl/m_homing.d \
./src/apl/m_interlocks.d \
./src/apl/m_interpreter.d \
./src/apl/m_phasing.d \
./src/apl/m_pid_calc.d \
./src/apl/m_pos_read.d \
./src/apl/m_recorder.d \
./src/apl/m_vpg_trap.d 

OBJS += \
./src/apl/m_commands.o \
./src/apl/m_commutation.o \
./src/apl/m_control.o \
./src/apl/m_homing.o \
./src/apl/m_interlocks.o \
./src/apl/m_interpreter.o \
./src/apl/m_phasing.o \
./src/apl/m_pid_calc.o \
./src/apl/m_pos_read.o \
./src/apl/m_recorder.o \
./src/apl/m_vpg_trap.o 

MAP += \
RZT2H_EVB_CR52_0_FOC_MOTOR.map 


# Each subdirectory must supply rules for building sources it contributes
src/apl/%.o: ../src/apl/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wnull-dereference -g3 -gdwarf-4 -D_RENESAS_RZT_ -D_RZT_CORE=CR52_0 -D_RZT_ORDINAL=1 -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src" -I"C:\\Renesas\\rzt\\e2studio_v2024-10_fsp_v2.2.0\\toolchains\\gcc_arm\\arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi\\/arm-none-eabi/include" -I"D:/renesas_workspace/RZT2H_EVB_CR52_0_FOC_MOTOR/src" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\inc\\apl" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\encoder\\FACoder" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv\\dsm" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\cg_src" -I"." -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\api" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\instances" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\src\\bsp\\mcu\\all\\cr" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_gen" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg\\bsp" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\driver" -std=gnu99 -Wno-format-truncation -Wno-stringop-overflow --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@arm-none-eabi-gcc @"$@.in"

