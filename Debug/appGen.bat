@echo off

::显示当前的编码格式
::chcp

::设置当前的文件编码格式
::chcp 936

@REM% loader 命令模式：生成bootloader程序文件，用在boot烧录时使用
@REM mpu 指定MPU芯片型号，可以有rzn2l/rzt2m/rzt2l
@REM mode 指定boot模式，因为传输参数根据boot模式不同会有不一样的描述，因此需要指定，可选xspi0/xspi1/bus(bus boot mode)
@REM src_addr 指定要存储到外部FLASH中的地址(MCU芯片地址空间,8位十六进制数值), 比如xspi0空间为6000004C之后(前面的0x4C字节用于存储参数), 比如该参数可以
@REM dest_addr 指定要将外部FLASH中的程序复制到RAM中的哪个地址(MCU芯片地址空间,8位十六进制数值, 该地址应该要和程序中的复位向量地址一致)
@REM i 指定需要输入的文件名称，文件类型也需要写出
@REM o 指定经过处理后要输出的文件名称，文件类型也需要写出
@REM concat_loader 指定是否需要将参数和输入的-i文件合并，如果有该项表示合并，如果没有该项表示不合并，则-o输出的文件是参数
@REM help 帮助
@REM python parameter_generator.py loader --mpu rzn2l --mode xspi0 --src_addr 60000050 --dest_addr 00102000 -i RZN2L_bsp_led.bin -o RZN2L_bsp_led_xspi0.bin --concat_loader

@REM userapp 命令模式：生成用户程序app，用于在固件更新时的文件使用
@REM src_addr 指定要存储到外部FLASH中的地址(MCU芯片地址空间,8位十六进制数值), 比如xspi0空间为6000004C之后(前面的0x4C字节用于存储参数), 比如该参数可以
@REM dest_addr 指定要将外部FLASH中的程序复制到RAM中的哪个地址(MCU芯片地址空间,8位十六进制数值, 该地址应该要和程序中的复位向量地址一致)
@REM i 指定需要输入的文件名称，文件类型也需要写出
@REM o 指定经过处理后要输出的文件名称，文件类型也需要写出
@REM help 帮助
@REM python parameter_generator.py userapp --src_addr 60000050 --dest_addr 00102000 -i RZN2L_bsp_led.bin -o RZN2L_bsp_led_xspi0.bin

::%python parameter_generator.py loader --mpu rzn2l --mode xspi0 --src_addr 60000050 --dest_addr 00102000 -i RZN2L_bsp_led.bin -o RZN2L_bsp_led_xspi0.bin --concat_loader

@REM python parameter_generator.py loader --mpu rzn2l --mode xspi0 --src_addr 60000050 --dest_addr 00000000 -i CN032.bin -o CN032_crc.bin --concat_loader --format
@REM python bat\application_generator.py loader --mpu rzn2l --mode xspi0 --src_addr 60000050 --dest_addr 10000000 -i CN032.bin -o CN032_app.bin --concat_loader --format

@REM hx280025
@REM riscv32-haawking-elf-objcopy -O binary "ServoV4_HX280025.elf"  "ServoV4_HX280025.bin"
@REM python appGen.py userapp --mpu hx280025 -i_boot hx280025_boot.bin -i_app ServoV4_HX280025.bin --boot_addr 00600000 --app_addr 00605000 -o servo_hx280025.hex --fill FF --concat --debug

@REM rzn2l
@REM python appGen.py userapp --mpu rzn2l -i_boot CN032_SSBL.bin -i_app CN032.bin --boot_addr 60000050 --app_addr 10000000 -o cn032_app.bin --fill FF --concat --debug
python appGen.py userapp --mpu rzn2l --xspi xspi1 -i_boot servo_rzn2l_ssbl.bin -i_app rzn2l_test.bin --boot_addr 68000050 --app_addr 10000000 -o servo_rzn2l.bin --fill FF --concat --debug


@REM echo application firmware generate ok.

@REM pause

@echo on