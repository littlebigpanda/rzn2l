################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzn/board/rzn2l_rsk/board_init.c \
../rzn/board/rzn2l_rsk/board_leds.c 

LST += \
board_init.lst \
board_leds.lst 

C_DEPS += \
./rzn/board/rzn2l_rsk/board_init.d \
./rzn/board/rzn2l_rsk/board_leds.d 

OBJS += \
./rzn/board/rzn2l_rsk/board_init.o \
./rzn/board/rzn2l_rsk/board_leds.o 

MAP += \
rzn2l_test.map 


# Each subdirectory must supply rules for building sources it contributes
rzn/board/rzn2l_rsk/%.o: ../rzn/board/rzn2l_rsk/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZN_ -D_RZN_CORE=CR52_0 -D_RZN_ORDINAL=1 -I"E:/workspace/e2 studio 202310/rzn2l_test/generate" -I"E:/workspace/e2 studio 202310/rzn2l_test/src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\api" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\instances" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_gen" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg\\bsp" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\rm_ethercat_ssc_port" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\driver" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

