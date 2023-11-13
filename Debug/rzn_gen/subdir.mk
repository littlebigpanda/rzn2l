################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzn_gen/common_data.c \
../rzn_gen/hal_data.c \
../rzn_gen/main.c \
../rzn_gen/pin_data.c \
../rzn_gen/vector_data.c 

LST += \
common_data.lst \
hal_data.lst \
main.lst \
pin_data.lst \
vector_data.lst 

C_DEPS += \
./rzn_gen/common_data.d \
./rzn_gen/hal_data.d \
./rzn_gen/main.d \
./rzn_gen/pin_data.d \
./rzn_gen/vector_data.d 

OBJS += \
./rzn_gen/common_data.o \
./rzn_gen/hal_data.o \
./rzn_gen/main.o \
./rzn_gen/pin_data.o \
./rzn_gen/vector_data.o 

MAP += \
rzn2l_test.map 


# Each subdirectory must supply rules for building sources it contributes
rzn_gen/%.o: ../rzn_gen/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-r52 -mthumb -mfloat-abi=hard -mfpu=neon-fp-armv8 -fdiagnostics-parseable-fixits -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZN_ -D_RZN_CORE=CR52_0 -D_RZN_ORDINAL=1 -I"E:/workspace/e2 studio 202310/rzn2l_test/generate" -I"E:/workspace/e2 studio 202310/rzn2l_test/src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\api" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\inc\\instances" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\arm\\CMSIS_5\\CMSIS\\Core_R\\Include" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_gen" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\fsp_cfg\\bsp" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\hw" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver\\inc" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src\\driver" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\r_usb_basic\\src" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn\\fsp\\src\\rm_ethercat_ssc_port" -I"E:\\workspace\\e2 studio 202310\\rzn2l_test\\rzn_cfg\\driver" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

