################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzn/fsp/src/r_dsmif/r_dsmif.c 

LST += \
r_dsmif.lst 

C_DEPS += \
./rzn/fsp/src/r_dsmif/r_dsmif.d 

OBJS += \
./rzn/fsp/src/r_dsmif/r_dsmif.o 

MAP += \
rzn2l_test.map 


# Each subdirectory must supply rules for building sources it contributes
rzn/fsp/src/r_dsmif/%.o: ../rzn/fsp/src/r_dsmif/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZN_ -D_RZN_CORE=CR52_0 -I"E:/workspace/e2 studio/rzn2l_test/generate" -I"E:/workspace/e2 studio/rzn2l_test/src" -I"E:\\workspace\\e2 studio\\rzn2l_test\\src" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn\\fsp\\inc" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn\\fsp\\inc\\api" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn\\fsp\\inc\\instances" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn_gen" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn_cfg\\fsp_cfg" -I"E:\\workspace\\e2 studio\\rzn2l_test\\rzn_cfg\\fsp_cfg\\bsp" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"
