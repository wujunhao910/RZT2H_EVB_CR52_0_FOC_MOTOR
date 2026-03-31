################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzt_gen/common_data.c \
../rzt_gen/elc_data.c \
../rzt_gen/hal_data.c \
../rzt_gen/main.c \
../rzt_gen/pin_data.c \
../rzt_gen/vector_data.c 

LST += \
common_data.lst \
elc_data.lst \
hal_data.lst \
main.lst \
pin_data.lst \
vector_data.lst 

C_DEPS += \
./rzt_gen/common_data.d \
./rzt_gen/elc_data.d \
./rzt_gen/hal_data.d \
./rzt_gen/main.d \
./rzt_gen/pin_data.d \
./rzt_gen/vector_data.d 

OBJS += \
./rzt_gen/common_data.o \
./rzt_gen/elc_data.o \
./rzt_gen/hal_data.o \
./rzt_gen/main.o \
./rzt_gen/pin_data.o \
./rzt_gen/vector_data.o 

MAP += \
RZT2H_EVB_CR52_0_FOC_MOTOR.map 


# Each subdirectory must supply rules for building sources it contributes
rzt_gen/%.o: ../rzt_gen/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wnull-dereference -g3 -gdwarf-4 -D_RENESAS_RZT_ -D_RZT_CORE=CR52_0 -D_RZT_ORDINAL=1 -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src" -I"C:\\Renesas\\rzt\\e2studio_v2024-10_fsp_v2.2.0\\toolchains\\gcc_arm\\arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi\\/arm-none-eabi/include" -I"D:/renesas_workspace/RZT2H_EVB_CR52_0_FOC_MOTOR/src" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\inc\\apl" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\encoder\\FACoder" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\src\\drv\\dsm" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\cg_src" -I"." -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\api" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\inc\\instances" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\fsp\\src\\bsp\\mcu\\all\\cr" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_gen" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg\\bsp" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\fsp_cfg" -I"D:\\renesas_workspace\\RZT2H_EVB_CR52_0_FOC_MOTOR\\rzt_cfg\\driver" -std=gnu99 -Wno-format-truncation -Wno-stringop-overflow --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@arm-none-eabi-gcc @"$@.in"

