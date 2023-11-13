@echo off

::��ʾ��ǰ�ı����ʽ
::chcp

::���õ�ǰ���ļ������ʽ
::chcp 936

@REM% loader ����ģʽ������bootloader�����ļ�������boot��¼ʱʹ��
@REM mpu ָ��MPUоƬ�ͺţ�������rzn2l/rzt2m/rzt2l
@REM mode ָ��bootģʽ����Ϊ�����������bootģʽ��ͬ���в�һ���������������Ҫָ������ѡxspi0/xspi1/bus(bus boot mode)
@REM src_addr ָ��Ҫ�洢���ⲿFLASH�еĵ�ַ(MCUоƬ��ַ�ռ�,8λʮ��������ֵ), ����xspi0�ռ�Ϊ6000004C֮��(ǰ���0x4C�ֽ����ڴ洢����), ����ò�������
@REM dest_addr ָ��Ҫ���ⲿFLASH�еĳ����Ƶ�RAM�е��ĸ���ַ(MCUоƬ��ַ�ռ�,8λʮ��������ֵ, �õ�ַӦ��Ҫ�ͳ����еĸ�λ������ַһ��)
@REM i ָ����Ҫ������ļ����ƣ��ļ�����Ҳ��Ҫд��
@REM o ָ�����������Ҫ������ļ����ƣ��ļ�����Ҳ��Ҫд��
@REM concat_loader ָ���Ƿ���Ҫ�������������-i�ļ��ϲ�������и����ʾ�ϲ������û�и����ʾ���ϲ�����-o������ļ��ǲ���
@REM help ����
@REM python parameter_generator.py loader --mpu rzn2l --mode xspi0 --src_addr 60000050 --dest_addr 00102000 -i RZN2L_bsp_led.bin -o RZN2L_bsp_led_xspi0.bin --concat_loader

@REM userapp ����ģʽ�������û�����app�������ڹ̼�����ʱ���ļ�ʹ��
@REM src_addr ָ��Ҫ�洢���ⲿFLASH�еĵ�ַ(MCUоƬ��ַ�ռ�,8λʮ��������ֵ), ����xspi0�ռ�Ϊ6000004C֮��(ǰ���0x4C�ֽ����ڴ洢����), ����ò�������
@REM dest_addr ָ��Ҫ���ⲿFLASH�еĳ����Ƶ�RAM�е��ĸ���ַ(MCUоƬ��ַ�ռ�,8λʮ��������ֵ, �õ�ַӦ��Ҫ�ͳ����еĸ�λ������ַһ��)
@REM i ָ����Ҫ������ļ����ƣ��ļ�����Ҳ��Ҫд��
@REM o ָ�����������Ҫ������ļ����ƣ��ļ�����Ҳ��Ҫд��
@REM help ����
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