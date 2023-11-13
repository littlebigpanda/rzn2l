################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_abs.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_access.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma_rz.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz_target.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_hostelectrical.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_abs.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_access.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_mcu.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_abs.c \
../rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_access.c 

LST += \
r_usb_creg_abs.lst \
r_usb_creg_access.lst \
r_usb_dma.lst \
r_usb_dma_rz.lst \
r_usb_dmaca_rz.lst \
r_usb_dmaca_rz_target.lst \
r_usb_hostelectrical.lst \
r_usb_hreg_abs.lst \
r_usb_hreg_access.lst \
r_usb_mcu.lst \
r_usb_preg_abs.lst \
r_usb_preg_access.lst 

C_DEPS += \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_abs.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_access.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma_rz.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz_target.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hostelectrical.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_abs.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_access.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_mcu.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_abs.d \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_access.d 

OBJS += \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_abs.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_creg_access.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dma_rz.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_dmaca_rz_target.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hostelectrical.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_abs.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_hreg_access.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_mcu.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_abs.o \
./rzn/fsp/src/r_usb_basic/src/hw/r_usb_preg_access.o 

MAP += \
rzn2l_test.map 


# Each subdirectory must supply rules for building sources it contributes
rzn/fsp/src/r_usb_basic/src/hw/%.o: ../rzn/fsp/src/r_usb_basic/src/hw/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZN_ -D_RZN_CORE=CR52_0 -D_RZN_ORDINAL=1 -I"E:/workspace/e2 studio 202310/rzn2l_test/generate" -I"E:/workspace/e2 studio 202310/rzn2l_test/src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\api" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\instances" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_gen" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg\\bsp" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\rm_ethercat_ssc_port" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\driver" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

