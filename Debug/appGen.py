########################################################################################################################
# DISCLAIMER
# This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
# other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
# applicable laws, including copyright laws.
# THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
# THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
# EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
# SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
# SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
# Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
# this software. By using this software, you agree to the additional terms and conditions found by accessing the
# following link:
# http://www.renesas.com/disclaimer
#
# Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
########################################################################################################################
# parameter_generator.py : Tool Version 1.20
import os
import re
import argparse
import operator
import time


# ctrl + k -> ctrl + 0 折叠全部代码
# ctrl + k -> ctrl + j 展开全部代码
# ctrl + k -> ctrl + [ 折叠本级及子节点
# ctrl + k -> ctrl + ] 展开本级及子节点
# ctrl + k -> ctrl + l 折叠本级

# Message print
ERRMSG = print
WARMSG = print

DEBUG_MSG = print

# Error / Warning Message
ERRMSG_OPENFAIL       = __file__ + ' : error: No such file : %s'
ERRMSG_ADDRFAIL       = __file__ + ' : error: The input value of the address is invalid : %s'
ERRMSG_SIZEFAIL       = __file__ + ' : error: The file size limit has been exceeded : %s'
WARMSG_UNITSIZE       = __file__ + ' : warning: The file size is not a multiple of the unit size : %s'

# Size
WORD_BYTES            = 4
WORD_BYTES_MAX_NUM    = 4294967295
SEC_IMAGE_UNIT_SIZE   = 16
LOADER_CERT_LEN       = 0x0800           # Certificate size for Loader
USERAPP_CERT_LEN      = 0x0200           # Certificate size for UserApp
LOADER_SIZE_MAX_RZT2M = 0x0000E000       # Maximum size of loader program: 56 KByte (for RZ/T2M)
LOADER_SIZE_MAX_RZT2L = 0x0000E000       # Maximum size of loader program: 56 KByte (for RZ/T2L)
LOADER_SIZE_MAX_RZN2L = 0x0001E000       # Maximum size of loader program: 120 KByte (for RZ/N2L)
LOADER_UNIT_SIZE      = 0x0200           # Unit size of loader program: 512 Byte
LOADER_BOOT_KEY_AREA  = 0x0200           # Key area size for image decryption during secure boot for Loader
USERAPP_BOOT_KEY_AREA = 0x0030           # Key area size for image decryption during secure boot for UserApp

# Endian string
ENDIAN_BIG            = 'big'
ENDIAN_LITTLE         = 'little'

# Fixed value included in parameter information for loader.
CACHE_FLG             = 0x00000001       # Cache enable flag during boot process : Enable
INIT_FLG              = 0x22360679       # Flag to initialize xSPI/Bus settings after boot process : Enable
CS0BCR                = 0x36DB0C00       # CS0 bus control register (CS0BCR) initial value
CS0WCR                = 0x00000500       # CS0 wait control register (CS0BCR) initial value
WRAPCFG               = 0x00000000       # Wrapper Configuration register (WRAPCFG) initial value
COMCFG                = 0x00000000       # Common Configuration register (COMCFG) initial value
BMCFG                 = 0x00000000       # Bridge Map Configuration register (BMCFG) initial value
CSSCTL                = 0x00000000       # CS Size Control register (CSSCTL) initial value
LIOCFGCS0             = 0x00070000       # link I/O Configuration Register CS0 (LIOCFGCS0) initial value
ACCESS_SPEED          = 0x00000606       # External memory access speed setting value

# Definition for padding
PADDING_VAL           = 'FF'             # Value at the time of padding
XSPI0_PRG_ADDR_BASE   = 0x6000004C       # Minimum address where the program is located when xspi0 mode is specified 
XSPI1_PRG_ADDR_BASE   = 0x6800004C       # Minimum address where the program is located when xspi1 mode is specified 
BUS_PRG_ADDR_BASE     = 0x7000004C       # Minimum address where the program is located when bus mode is specified 

# 编译生成的app固件bin文件中文件参数信息索引
POS_LOADER_TEXT_MEMERY	    = 0
POS_LOADER_DATA_MEMERY	    = 1
POS_FVECTOR_MEMERY          = 2
POS_RAM_CODE_MEMERY         = 3
POS_TEXT_MEMERY             = 4
POS_DATA_MEMERY             = 5
POS_FLASH_MEMERY_END        = 6
POS_FILL_BYTES		        = 4
POS_SRC_ADDR		        = 5
POS_SIZE                    = 6
POS_LOADER_TEXT_START       = 7
POS_LOADER_TEXT_END         = 8
POS_LOADER_DATA_START       = 9
POS_LOADER_DATA_END         = 10
POS_FVECTOR_START           = 11
POS_FVECTOR_END             = 12
POS_RAM_CODE_START          = 13
POS_RAM_CODE_END            = 14
POS_TEXT_START              = 15
POS_TEXT_END                = 16
POS_DATA_START              = 17
POS_DATA_END                = 18
POS_CHECK_SUM               = 19
LOADER_PARAMETER_LENGTH     = 0x50  # 原始生成的bin文件的参数区域字节数大小(同时也是目标要生成的bin文件的参数区域字节长度)

# 各个CRC校验值在CRC段的字位置
POS_LOADER_TEXT_CRC	        = 0
POS_LOADER_DATA_CRC	        = 1
POS_FVECTOR_CRC             = 2
POS_RAM_CODE_CRC            = 3
POS_TEXT_CRC                = 4
POS_DATA_CRC                = 5
POS_FW_CRC                  = 6


#boot参数位置
BOOT_PRM_LOADER_ADDR            = 0
BOOT_PRM_LENGTH                 = 1
BOOT_PRM_CRC                    = 2


#boot代码大小限制
CFG_BOOT_FW_SIZE_MAX_HX280025   = 0x0001E000    # 120KB
CFG_BOOT_FW_SIZE_MAX_RZN2L      = 0x00004800    # 18KB

#boot代码大小字典
bootFwSizeMax = {
    'hx280025':     CFG_BOOT_FW_SIZE_MAX_HX280025,
    'rzn2l':        CFG_BOOT_FW_SIZE_MAX_RZN2L
}

# APP代码大小限制
CFG_APP_FW_SIZE_MAX_HX280025   = 0x0003B000    # 236KB
CFG_APP_FW_SIZE_MAX_RZN2L      = 0x00400000    # 4096KB

#boot代码大小字典
bootFwSizeMax = {
    'hx280025':     CFG_APP_FW_SIZE_MAX_HX280025,
    'rzn2l':        CFG_APP_FW_SIZE_MAX_RZN2L
}

# hx280025 app固件中的参数位置
CFG_HX280025_APP_INFO_LENGTH         = 20   # app固件前面信息参数的字长度    
CFG_HX280025_APP_INFO_ENTRY_ADDR_POS = 0    # app入口点地址所在的Bin文件位置:字地址
CFG_HX280025_APP_INFO_LENGTH_POS     = 1
CFG_HX280025_APP_INFO_CRC_POS        = 2


# mpu型号
CFG_MPU_HX280025    = 'hx280025'
CFG_MPU_RZN2L       = 'rzn2l'

# xspi通道/单元
CFG_XSPI0           = 'xspi0'
CFG_XSPI1           = 'xspi1'

def main():
    """Main processing.
    
    Parsing command line arguments.
    Generates parameter information. 
    
    Args:
        None
    
    Returns:
        None
    
    """
    # Command line argument perse
    parser = set_cmdline_argparser()
    args = parser.parse_args()
    
    # Check whether required options are specified
    if False == os.path.exists(args.i_boot):
        ERRMSG(str.format(ERRMSG_OPENFAIL % (args.i_boot)))
        exit(1)

    if False == os.path.exists(args.i_app):
        ERRMSG(str.format(ERRMSG_OPENFAIL % (args.i_app)))
        exit(1)
    
    if re.match("^[0-9A-Fa-f]{8}$", args.boot_addr) is None:
        ERRMSG(str.format(ERRMSG_ADDRFAIL % (args.boot_addr)))
        exit(1)
    
    if re.match("^[0-9A-Fa-f]{8}$", args.app_addr) is None:
        ERRMSG(str.format(ERRMSG_ADDRFAIL % (args.app_addr)))
        exit(1)

    if re.match("^[0-9A-Fa-f]{2}$", args.fill) is None:
        ERRMSG(str.format(ERRMSG_ADDRFAIL % (args.fill)))
        exit(1)
    
    # Get the value from the option
    boot_file_len = os.path.getsize(args.i_boot)
    app_file_len = os.path.getsize(args.i_app)
    boot_addr = int(args.boot_addr, 16)
    app_addr = int(args.app_addr, 16)
    fill = int(args.fill, 16)

    if (args.xspi == CFG_XSPI1):
        xspi_unit = CFG_XSPI1
    else:
        xspi_unit = CFG_XSPI0

    if (fill > 0xFF) :
        ERRMSG("fill value need to less than 0xFF", end='\n')
        exit(1)

    # Delete files at output path
    if os.path.exists(args.o) is True:
        os.remove(args.o)
    
    # Generate Parameter
    if args.cmd == 'userapp':

        # 检查boot代码大小是否超过限制值
        if bootFwSizeMax[args.mpu] < boot_file_len:
            ERRMSG(str.format(__file__ + ' : error: The file size limit has been exceeded : %s' % (args.i)))
            exit(1)

        # 检查app代码大小是否超过限制值
        if bootFwSizeMax[args.mpu] < app_file_len:
            ERRMSG(str.format(__file__ + ' : error: The file size limit has been exceeded : %s' % (args.i)))
            exit(1)

        # 读取固件信息
        with open(args.i_boot, mode='rb') as f:
            bootBinFile = f.read()

        with open(args.i_app, mode='rb') as f:
            appBinFile = f.read()

        # boot代码添加参数
        bootBinFile = generate_boot_prm(bootBinFile, boot_addr, args.mpu, args.debug, xspi_unit)

        if (bootBinFile == None):
            ERRMSG("generate boot bin files is none.", end='\n')
            exit(1)

        if (args.debug == True):
            with open('bootInfo.bin', 'bw') as outfile:
                outfile.write(bootBinFile)
            ERRMSG("bootInfo.bin file generate ok.", end='\n')

        # app代码添加参数
        appBinFile = generate_app_prm(appBinFile, app_addr, args.mpu, args.debug, xspi_unit)

        if (appBinFile == None):
            ERRMSG("generate app bin files is none.", end='\n')
            exit(1)
            
        if (args.debug == True):
            with open('appInfo.bin', 'bw') as outfile:
                outfile.write(appBinFile)
            ERRMSG("appInfo.bin file generate ok.", end='\n')

        # boot和app代码合并
        if (args.concat is True):
            bin = bootBinFile + appBinFile
        else:
            bin = appBinFile

        # 将app写到输出文件
        with open(args.o, 'bw') as outfile:
            outfile.write(bin)

        DEBUG_MSG('generate bin file : %d / 0x%X'%(len(bin),len(bin)), end="\n")

        DEBUG_MSG(args.o + 'application firmware generate ok.', end='\n')

    else:  # args.cmd == 'userapp'
        None
        
    exit(0)

def set_cmdline_argparser():
    """Command line argument parsing settings.
    
    Set valid commands and options on the command line.
    
    Args:
        None
    
    Returns:
        parser - ArgumentParser object
    
    """
    DESC_TOOL       = 'Tool to generate parameter information'
    DESC_LOADER     = 'Generate Parameters for the Loader'
    DESC_USERAPP    = 'Generate Parameters for the User application'
    
    METAVER_ADDR    = '<Address>'
    METAVER_I       = '<ProgramFile>'
    METAVER_O       = '<ParamInfoFile>'
    METAVER_MODE    = '<BootMode>'
    METAVER_MPU     = '<Target>'
    
    HELP_CMD        = 'Specify the generation command'
    HELP_SADDR      = 'Specify the flash write destination address'
    HELP_DADDR      = 'Specify the RAM expansion destination address'
    HELP_MODE       = 'Specify the target boot mode (choose from xspi0, xspi1 or bus)'
    HELP_LOADERI    = 'Specify the path of the loader program file'
    HELP_USERI      = 'Specify the path of the user application program file'
    HELP_O          = 'Specify the path of the parameter information file to be output'
    HELP_ADD        = 'Specify when combining parameter information generation and program'
    HELP_SEC        = '(For secure boot) Specify when creating parameter information for secure'
    HELP_COMKEY4    = '(For secure boot) Specify this when using the key stored in the flash for image decryption'
    HELP_MPU        = 'Specify the target MPU'
    
    # Set command line parser
    parser = argparse.ArgumentParser(description=DESC_TOOL)
    subparsers = parser.add_subparsers(dest='cmd',required=True, help=HELP_CMD)
    # parser_loader = subparsers.add_parser('loader', description=DESC_LOADER)
    parser_userapp = subparsers.add_parser('userapp', description=DESC_USERAPP)
    
    # Set the argument of the "loader" command
    # parser_loader.add_argument('--mpu', choices=['rzt2m', 'rzt2l', 'rzn2l'], metavar=METAVER_MPU, required=True, help=HELP_MPU)
    # parser_loader.add_argument('--src_addr', metavar=METAVER_ADDR, required=True, help=HELP_SADDR)
    # parser_loader.add_argument('--dest_addr', metavar=METAVER_ADDR, required=True, help=HELP_DADDR)
    # parser_loader.add_argument('--mode', choices=['xspi0', 'xspi1', 'bus'], metavar=METAVER_MODE, required=True, help=HELP_MODE)
    # parser_loader.add_argument('-i', metavar=METAVER_I, required=True, help=HELP_LOADERI)
    # parser_loader.add_argument('-o', metavar=METAVER_O, required=True, help=HELP_O)
    # parser_loader.add_argument('--concat_loader', action='store_true', help=HELP_ADD)
    # parser_loader.add_argument('--secureboot', action='store_true', help=HELP_SEC)
    # parser_loader.add_argument('--use_commonkey4', action='store_true', help=HELP_COMKEY4)
    # parser_loader.add_argument('--format', action='store_true', help=HELP_ADD)
    
    # Set the argument of the "userapp" command
    # parser_userapp.add_argument('--src_addr',  metavar=METAVER_ADDR, required=True, help=HELP_SADDR)
    # parser_userapp.add_argument('--dest_addr',  metavar=METAVER_ADDR, required=True, help=HELP_DADDR)
    # parser_userapp.add_argument('-i', metavar=METAVER_I, required=True, help=HELP_USERI)
    # parser_userapp.add_argument('-o', metavar=METAVER_O, required=True, help=HELP_O)
    # parser_userapp.add_argument('--secureboot', action='store_true', help=HELP_SEC)
    # parser_userapp.add_argument('--use_commonkey4', action='store_true', help=HELP_COMKEY4)

    parser_userapp.add_argument('--boot_addr',  metavar=METAVER_ADDR, required=True, help=HELP_SADDR)
    parser_userapp.add_argument('--app_addr',  metavar=METAVER_ADDR, required=True, help=HELP_DADDR)
    parser_userapp.add_argument('-i_boot', metavar=METAVER_I, required=True, help=HELP_USERI)
    parser_userapp.add_argument('-i_app', metavar=METAVER_I, required=True, help=HELP_USERI)
    parser_userapp.add_argument('-o', metavar=METAVER_O, required=True, help=HELP_O)
    parser_userapp.add_argument('--fill', required=True, help=HELP_SEC)
    parser_userapp.add_argument('--concat', action='store_true', help=HELP_COMKEY4)
    parser_userapp.add_argument('--debug', action='store_true', help=HELP_COMKEY4)
    parser_userapp.add_argument('--mpu', choices=['hx280025', 'rzn2l'], metavar=METAVER_MPU, required=True, help=HELP_MPU)
    parser_userapp.add_argument('--xspi', choices=['xspi0', 'xspi1'], metavar=METAVER_MPU, required=False, help=HELP_MPU)

    return parser

def generate_loader_parameter(src_addr, dest_addr, prg_len, mode, sec_flg, comkey4_flg):
    """Generate Parameters for the Loader.
    
    Generates loader parameter information from the values
    specified in the command and internal constants.
    
    Args:
        src_addr (int) - Src address
        dest_addr (int) - Dest address
        prg_len (int) - Program size
        mode (str) - Boot mode
        sec_flg (bool) - Flag for secureboot
        comkey4_flg (bool) - Flag for commomkey4
    
    Returns:
        Parameters for the Loader (bytes)
    
    """
    loader_param = b''
    
    # Add a fixed value included in the parameter information for the loader
    loader_param += CACHE_FLG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    if mode == 'bus':
        # For Bus Boot Mode
        loader_param += CS0BCR.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += CS0WCR.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += bytes.fromhex('00' * 4)
        
    else:  # args.mode == 'xspi0' or 'xspi1'
        # For xSPI Boot Mode
        loader_param += WRAPCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += COMCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += BMCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
    loader_param += INIT_FLG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add flash write destination address
    loader_param += src_addr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add program file size
    if sec_flg == True:
        # Calculate secure boot image file size for secure
        if (prg_len % SEC_IMAGE_UNIT_SIZE) != 0:
            prg_len += SEC_IMAGE_UNIT_SIZE - (prg_len % SEC_IMAGE_UNIT_SIZE)
        
        prg_len += LOADER_CERT_LEN
        
        if comkey4_flg == True:
            prg_len += LOADER_BOOT_KEY_AREA
        
    loader_param += prg_len.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add RAM expansion destination address 
    loader_param += dest_addr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add a fixed value included in the parameter information for the loader
    if mode == 'bus':
        # For Bus Boot Mode
        loader_param += bytes.fromhex('00' * 40)
        
    else:  # args.mode == 'xspi0' or 'xspi1'
        # For xSPI Boot Mode
        loader_param += bytes.fromhex('00' * 8)
        loader_param += CSSCTL.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += LIOCFGCS0.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += bytes.fromhex('00' * 20)
        loader_param += ACCESS_SPEED.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Checksum
    mv = memoryview(loader_param).cast('H')
    sum = 0
    
    for item in mv:
        sum += item
    sum %= (WORD_BYTES_MAX_NUM + 1)
    
    loader_param += sum.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    return loader_param

def generate_userapp_parameter(src_addr, dest_addr, prg_len, sec_flg, comkey4_flg):
    """Generate Parameters for the User application.
    
    Generates userapp parameter information from the value
    specified in the command.
    
    Args:
        src_addr (int) - Src address
        dest_addr (int) - Dest address
        prg_len (int) - Program size
        sec_flg (bool) - Flag for secureboot
        comkey4_flg (bool) - Flag for commomkey4
    
    Returns:
        Parameters for the User application (bytes)
    
    """
    userapp_param = b''
    
    # Add flash write destination address
    userapp_param += src_addr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add program file size
    if sec_flg == True:
        if (prg_len % SEC_IMAGE_UNIT_SIZE) != 0:
            prg_len += SEC_IMAGE_UNIT_SIZE - (prg_len % SEC_IMAGE_UNIT_SIZE)
        
        prg_len += USERAPP_CERT_LEN
        
        if comkey4_flg == True:
            prg_len += USERAPP_BOOT_KEY_AREA
        
    
    userapp_param += prg_len.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Add RAM expansion destination address 
    userapp_param += dest_addr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    # Checksum
    mv = memoryview(userapp_param).cast('H')
    sum = 0
    
    for item in mv:
        sum += item
    sum %= (WORD_BYTES_MAX_NUM + 1)
    
    userapp_param += sum.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    
    return userapp_param

def combine_program_data(src_addr, mode, prg_path, param):
    """Combine program data.
    
    Combine program data with parameter information.
    
    Args:
        src_addr (int) - Src address
        mode (str) - Boot mode
        prg_path (str) - Program file path
        param (bytes) - Parameter info
    
    Returns:
        Parameter info + program data (bytes)
    
    """
    if mode == 'bus':
        padding_size = src_addr - BUS_PRG_ADDR_BASE
        
    elif mode == 'xspi0':
        padding_size = src_addr - XSPI0_PRG_ADDR_BASE
        
    else:  # mode == 'xspi1'
        padding_size = src_addr - XSPI1_PRG_ADDR_BASE
            
    # Check padding size
    if 0 > padding_size:
        return None
        
    param += bytes.fromhex(PADDING_VAL * padding_size)
    
    # Open input file and read data
    with open(prg_path, mode='rb') as f:
        file_data = f.read()
       
    # Add data read from file 
    param += file_data
    
    return param

def modbus_crc_calc(msg, length):
    counter = 0
    crc_data = 0xFFFF
    msg_data = 0

    for counter in range (0, length):
        msg_data = msg[counter:counter + 1]
        # print(type(msg_data))
        # ERRMSG(msg_data)

        # 字节数据转换为int类型数据，记得要使用，否则下面的异或运算直接不执行退出
        msg_int = int.from_bytes(msg_data, byteorder='big', signed=False)

        # print(type(msg_int))
        # ERRMSG(msg_int)

        crc_data = operator.xor(crc_data, msg_int)

        temp = 0
        index = 0
        for index in range (0, 8):
            temp = crc_data & 0x0001
            crc_data = crc_data >> 1
            if (temp != 0):
                crc_data = crc_data ^ 0xA001

    return (crc_data & 0xFFFF)

def ethernet_crc_calc(msg, length):
    counter = 0
    crc_data = 0xFFFFFFFF
    msg_data = 0

    for counter in range (0, length):
        msg_data = msg[counter:counter + 1]
        # print(type(msg_data))
        # ERRMSG(msg_data)

        # 字节数据转换为int类型数据，记得要使用，否则下面的异或运算直接不执行退出
        msg_int = int.from_bytes(msg_data, byteorder='big', signed=False)

        # print(type(msg_int))
        # ERRMSG(msg_int)

        crc_data = operator.xor(crc_data, msg_int)

        temp = 0
        index = 0
        for index in range (0, 8):
            temp = crc_data & 0x00000001
            crc_data = crc_data >> 1
            if (temp != 0):
                crc_data = crc_data ^ 0xEDB88320

    return (crc_data & 0xFFFFFFFF)

# 计算bin固件信息的crc校验值
def bin_crc_calc(data, length, method='ethernet'):
    
    if method == "ethernet":
        crc = ethernet_crc_calc(data, length)
    else:
        crc = modbus_crc_calc(data, length)
    return crc

# 获取bin文件中的特定字地址的数值
def get_bin_info(binFile, wordAddr):
    startAddr = wordAddr * 4
    val1  = int.from_bytes(binFile[startAddr:startAddr+1], byteorder='big', signed=False)
    startAddr += 1
    val2  = int.from_bytes(binFile[startAddr:startAddr+1], byteorder='big', signed=False)
    startAddr += 1
    val3  = int.from_bytes(binFile[startAddr:startAddr+1], byteorder='big', signed=False)
    startAddr += 1
    val4  = int.from_bytes(binFile[startAddr:startAddr+1], byteorder='big', signed=False)
    return ( (val4 << 24) + (val3 << 16) + (val2 << 8) + (val1 << 0) )

# 设置bin文件中特定字地址的数值
def set_bin_info(loader_prm, wordAddr, setVal):
    bin = bytearray(loader_prm)
    startAddr = wordAddr * 4
    bin[startAddr:startAddr+4] = setVal[0:4]
    return bin

# 固件loader_text段在QSPI FLASH的装载地址
def get_bin_info_loader_text_memery_addr(binFile):
    return get_bin_info(binFile, POS_LOADER_TEXT_MEMERY)

# 固件loader_data段在QSPI FLASH的装载地址
def get_bin_info_loader_data_memery_addr(binFile):
    return get_bin_info(binFile, POS_LOADER_DATA_MEMERY)

# 固件fvector段在QSPI FLASH的装载地址
def get_bin_info_fvector_memery_addr(binFile):
    return get_bin_info(binFile, POS_FVECTOR_MEMERY)

# 固件ram_code段在QSPI FLASH的装载地址
def get_bin_info_ramcode_memery_addr(binFile):
    return get_bin_info(binFile, POS_RAM_CODE_MEMERY)

# 固件text段在QSPI FLASH的装载地址
def get_bin_info_text_memery_addr(binFile):
    return get_bin_info(binFile, POS_TEXT_MEMERY)

# 固件data段在QSPI FLASH的装载地址
def get_bin_info_data_memery_addr(binFile):
    return get_bin_info(binFile, POS_DATA_MEMERY)

# 固件在QSPI FLASH的结束地址
def get_bin_info_flash_memery_end(binFile):
    return get_bin_info(binFile, POS_FLASH_MEMERY_END)

# 固件loader_text段在装载的运行首地址
def get_bin_info_loader_text_start(binFile):
    return get_bin_info(binFile, POS_LOADER_TEXT_START)

# 固件loader_text段在装载的运行结束地址
def get_bin_info_loader_text_end(binFile):
    return get_bin_info(binFile, POS_LOADER_TEXT_END)

# 固件loader_data段在装载的运行首地址
def get_bin_info_loader_data_start(binFile):
    return get_bin_info(binFile, POS_LOADER_DATA_START)

# 固件loader_data段在装载的运行结束地址
def get_bin_info_loader_data_end(binFile):
    return get_bin_info(binFile, POS_LOADER_DATA_END)

# 固件fvector段在装载的运行首地址
def get_bin_info_fvector_start(binFile):
    return get_bin_info(binFile, POS_FVECTOR_START)

# 固件fvector段在装载的运行结束地址
def get_bin_info_fvector_end(binFile):
    return get_bin_info(binFile, POS_FVECTOR_END)

# 固件ram_code段在装载的运行首地址
def get_bin_info_ram_code_start(binFile):
    return get_bin_info(binFile, POS_RAM_CODE_START)

# 固件ram_code段在装载的运行结束地址
def get_bin_info_ram_code_end(binFile):
    return get_bin_info(binFile, POS_RAM_CODE_END)

# 固件text段在装载的运行首地址
def get_bin_info_text_start(binFile):
    return get_bin_info(binFile, POS_TEXT_START)

# 固件text段在装载的运行结束地址
def get_bin_info_text_end(binFile):
    return get_bin_info(binFile, POS_TEXT_END)

# 固件data段在装载的运行首地址
def get_bin_info_data_start(binFile):
    return get_bin_info(binFile, POS_DATA_START)

# 固件data段在装载的运行结束地址
def get_bin_info_data_end(binFile):
    return get_bin_info(binFile, POS_DATA_END)

# 固件在QSPI FLASH的结束地址
def set_bin_info_loader_text(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_LOADER_TEXT_START, start)
    loader_prm = set_bin_info(loader_prm, POS_LOADER_TEXT_END, end)
    return loader_prm

def set_bin_info_loader_data(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_LOADER_DATA_START, start)
    loader_prm = set_bin_info(loader_prm, POS_LOADER_DATA_END, end)
    return loader_prm

def set_bin_info_fvector(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_FVECTOR_START, start)
    loader_prm = set_bin_info(loader_prm, POS_FVECTOR_END, end)
    return loader_prm

def set_bin_info_ram_code(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_RAM_CODE_START, start)
    loader_prm = set_bin_info(loader_prm, POS_RAM_CODE_END, end)
    return loader_prm

def set_bin_info_text(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_TEXT_START, start)
    loader_prm = set_bin_info(loader_prm, POS_TEXT_END, end)
    return loader_prm

def set_bin_info_data(loader_prm, start, end):
    loader_prm = set_bin_info(loader_prm, POS_DATA_START, start)
    loader_prm = set_bin_info(loader_prm, POS_DATA_END, end)
    return loader_prm

def set_bin_info_fill_bytes(loader_prm, val):
    loader_prm = set_bin_info(loader_prm, POS_FILL_BYTES, val)
    return loader_prm

def set_bin_info_src_addr(loader_prm, val):
    loader_prm = set_bin_info(loader_prm, POS_SRC_ADDR, val)
    return loader_prm

def set_bin_info_size(loader_prm, val):
    loader_prm = set_bin_info(loader_prm, POS_SIZE, val)
    return loader_prm

def set_bin_info_calc_check_sum(loader_prm):
    prm = bytearray(loader_prm)
    sum = 0
    startAddr = 0
    for item in range(0, (len(loader_prm)-4)):
        val1  = int.from_bytes(loader_prm[startAddr:startAddr+1], byteorder='big', signed=False)
        val2  = int.from_bytes(loader_prm[startAddr+1:startAddr+2], byteorder='big', signed=False)
        sum += ((val2 << 8) + val1)
        startAddr += 2
        # print('%d,%d'%(item, sum), end = '\n')
    sum %= (WORD_BYTES_MAX_NUM + 1)

    startAddr = POS_CHECK_SUM * 4
    prm[startAddr:startAddr+4] = sum.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
    return prm

def generate_loader_prm(binFile, enable_debug=0, xspi = CFG_XSPI0):

    loader_param = bytes.fromhex('00' * LOADER_PARAMETER_LENGTH)

    firmware_data = binFile[LOADER_PARAMETER_LENGTH:(len(binFile))]

    file_addr = 0

    # loader_text
    start = get_bin_info_loader_text_start(binFile)
    end = get_bin_info_loader_text_end(binFile)
    loader_param = set_bin_info_loader_text(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    loader_text_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('loader_text_section_info:', end="\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('loader_text.bin', 'bw') as outfile:
            outfile.write(loader_text_bin)

    # loader_data
    start = get_bin_info_loader_data_start(binFile)
    end = get_bin_info_loader_data_end(binFile)
    loader_param = set_bin_info_loader_data(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    loader_data_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('loader_data_section_info:', end="\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('loader_data.bin', 'bw') as outfile:
            outfile.write(loader_data_bin)

    # fvector
    start = get_bin_info_fvector_start(binFile)
    end = get_bin_info_fvector_end(binFile)
    loader_param = set_bin_info_fvector(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    fvector_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('fvector_section_info:', end="\t\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('fvector.bin', 'bw') as outfile:
            outfile.write(fvector_bin)

    # ram_code
    start = get_bin_info_ram_code_start(binFile)
    end = get_bin_info_ram_code_end(binFile)
    loader_param = set_bin_info_ram_code(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    ramcode_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('ramcode_section_info:', end="\t\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('ram_code.bin', 'bw') as outfile:
            outfile.write(ramcode_bin)

    # text
    start = get_bin_info_text_start(binFile)
    end = get_bin_info_text_end(binFile)
    loader_param = set_bin_info_text(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    text_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('text_section_info:', end="\t\t\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('text.bin', 'bw') as outfile:
            outfile.write(text_bin)

    # data
    start = get_bin_info_data_start(binFile)
    end = get_bin_info_data_end(binFile)
    loader_param = set_bin_info_data(loader_param, start.to_bytes(WORD_BYTES, ENDIAN_LITTLE), end.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    length = end - start
    data_bin = firmware_data[file_addr:(file_addr + length)]
    file_addr += length

    DEBUG_MSG('data_section_info:', end="\t\t\t")
    DEBUG_MSG('start -0x%08X   end -0x%08X length-0x%08X'%(start,end,length), end="\n")

    if enable_debug != 0:
        with open('data.bin', 'bw') as outfile:
            outfile.write(data_bin)

    # 对固件信息进行处理、判断

    loader_text_memery = get_bin_info_loader_text_memery_addr(binFile)
    loader_data_memery = get_bin_info_loader_data_memery_addr(binFile)
    fvector_memery = get_bin_info_fvector_memery_addr(binFile)
    ramcode_memery = get_bin_info_ramcode_memery_addr(binFile)
    text_memery = get_bin_info_text_memery_addr(binFile)
    data_memery = get_bin_info_data_memery_addr(binFile)
    flash_end_memery = get_bin_info_flash_memery_end(binFile)

    # DEBUG_MSG('\n')

    DEBUG_MSG('loader_text_memery:          0x%08X'%(loader_text_memery), end = '\n')
    DEBUG_MSG('loader_data_memery:          0x%08X'%(loader_data_memery), end = '\n')
    DEBUG_MSG('fvector_memery:              0x%08X'%(fvector_memery), end = '\n')
    DEBUG_MSG('ramcode_memery:              0x%08X'%(ramcode_memery), end = '\n')
    DEBUG_MSG('text_memery:                 0x%08X'%(text_memery), end = '\n')
    DEBUG_MSG('data_memery:                 0x%08X'%(data_memery), end = '\n')
    DEBUG_MSG('flash_end_memery:            0x%08X'%(flash_end_memery), end = '\n')

    # 判断QSPI FLASH的起始装载地址是否正确
    if (xspi == CFG_XSPI0):
        if loader_text_memery != 0x60100050 :
            DEBUG_MSG('loader_text_memery not fit. please check. over. current loader_text is 0x%08X'%(loader_text_memery), end='\n')
            return None
    else:
        if loader_text_memery != 0x68100050 :
            DEBUG_MSG('loader_text_memery not fit. please check. over. current loader_text is 0x%08X'%(loader_text_memery), end='\n')
            return None

    # 检查生成的bin文件是否连续
    loader_text_memery_len = loader_data_memery - loader_text_memery
    loader_data_memery_len = fvector_memery - loader_data_memery
    fvector_memery_len = ramcode_memery - fvector_memery
    ramcode_memery_len = text_memery - ramcode_memery
    text_memery_len = data_memery - text_memery
    data_memery_len = flash_end_memery - data_memery
    flash_memery_len = flash_end_memery - loader_text_memery

    if ( (loader_text_memery_len != len(loader_text_bin)) or \
        (loader_data_memery_len != len(loader_data_bin)) or \
        (fvector_memery_len != len(fvector_bin)) or \
        (ramcode_memery_len != len(ramcode_bin)) or \
        (text_memery_len != len(text_bin)) or \
        (data_memery_len != len(data_bin)) or \
        (flash_memery_len != len(firmware_data)) ):
        DEBUG_MSG('flash memery not fit. please check. over.', end='\n')
        return None
    
    return [loader_param, loader_text_bin, loader_data_bin, fvector_bin, ramcode_bin, text_bin, data_bin]

def print_bytes(bytes):
    Counter = 0
    Counter2 = 0
    Counter3 = 0
    ERRMSG('%04X: '%Counter3, end=" ")
    for Counter in range(0,len(bytes)):
        ERRMSG(bytes[Counter:Counter+1].hex(), end=" ")    # Jerome 使用空格替代换行符输出
        Counter2 = Counter2 + 1
        if (Counter2 >= 16):
            Counter2 = 0
            ERRMSG('\n')
            Counter3 += 16
            if (Counter < (len(bytes) - 1)):
                ERRMSG('%04X: '%Counter3, end=" ")
    ERRMSG('\n')

# 生成boot代码的参数,并和boot代码合并后返回
def generate_boot_prm(bootBin, loaderAddr, mpu = 'hx280025', debug = 'false', xspi = CFG_XSPI0):

    if (mpu == CFG_MPU_RZN2L):

        """Generate Parameters for the Loader.
        
        Generates loader parameter information from the values
        specified in the command and internal constants.
        
        Args:
            src_addr (int) - Src address
            dest_addr (int) - Dest address
            prg_len (int) - Program size
            mode (str) - Boot mode
            sec_flg (bool) - Flag for secureboot
            comkey4_flg (bool) - Flag for commomkey4
        
        Returns:
            Parameters for the Loader (bytes)
        
        """
        # boot装载到ram中的目的地址，这里固定位BTCM扇区，程序中的ld文件要和这个对应，否则五
        dest_addr = 0x00102000

        loader_param = b''
        
        # Add a fixed value included in the parameter information for the loader
        loader_param += CACHE_FLG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += WRAPCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += COMCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += BMCFG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += INIT_FLG.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
        # 固件在flash中的装载地址, 手册中，装载地址必须早0x6000004C之后, 因为参数占用0x4C字节
        if (xspi == CFG_XSPI0):
            if ( (loaderAddr < 0x6000004C) or (loaderAddr > 0x60FFFE00) ):
                print('loader address not correct. current address is 0x%x'%(loaderAddr), end='\n')
                return None
        else:
            if ( (loaderAddr < 0x6800004C) or (loaderAddr > 0x68FFFE00) ):
                print('loader address not correct. current address is 0x%d'%(loaderAddr), end='\n')
                return None
        loader_param += loaderAddr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
        # 固件的大小要求是512字节的整数倍
        fill_len = 0x200 - (len(bootBin) % 0x200)
        if (fill_len > 0):
            fillBin = bytes.fromhex('FF' * fill_len)

        # 固件的大小为原始固件大小+填充字节数
        bin_len = len(bootBin) + fill_len
        loader_param += bin_len.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
        # boot装载到ram中的目的地址
        loader_param += dest_addr.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
        # 8个字节的保留数据
        loader_param += bytes.fromhex('00' * 8)     

        loader_param += CSSCTL.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        loader_param += LIOCFGCS0.to_bytes(WORD_BYTES, ENDIAN_LITTLE)

        # 20个字节的保留数据
        loader_param += bytes.fromhex('00' * 20)

        loader_param += ACCESS_SPEED.to_bytes(WORD_BYTES, ENDIAN_LITTLE)
        
        # 计算参数校验和
        sum = 0
        startAddr = 0
        for item in range(0, (len(loader_param)-4)):
            val1  = int.from_bytes(loader_param[startAddr:startAddr+1], byteorder='big', signed=False)
            val2  = int.from_bytes(loader_param[startAddr+1:startAddr+2], byteorder='big', signed=False)
            sum += ((val2 << 8) + val1)
            startAddr += 2
        sum %= (WORD_BYTES_MAX_NUM + 1)

        # print('user sum: %d'%(sum), end='\n')

        # Checksum
        # mv = memoryview(loader_param).cast('H')
        # sum = 0
        
        # for item in mv:
        #     sum += item
        # sum %= (WORD_BYTES_MAX_NUM + 1)

        # print('renesas sum: %d'%(sum), end='\n')
        
        loader_param += sum.to_bytes(WORD_BYTES, ENDIAN_LITTLE)

        #需要填充的字节数据
        if (fill_len > 0):
            bootBin = bootBin + fillBin
        
        # 参数和起始装载地址之间的填充字节数
        if (xspi == CFG_XSPI0):
            fill = loaderAddr - XSPI0_PRG_ADDR_BASE
        else:
            fill = loaderAddr - XSPI1_PRG_ADDR_BASE
        if (fill > 0):
            loader_param = loader_param + bytes.fromhex('00' * fill)

        # print_bytes(loader_param)
        
        # 最终的加上参数后的boot固件
        bootBin = loader_param + bootBin

        # print_bytes(loader_param)

    elif (mpu == CFG_MPU_HX280025):
        if loaderAddr != 0x00600000:
            print('loader address not correct.', end='\n')
            return None

    # app信息扇区内容填充
    info = bytes.fromhex('00' * 0x50)

    # boot代码在FLASH中的装载地址
    info = set_bin_info(info, BOOT_PRM_LOADER_ADDR, loaderAddr.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    # boot代码的字节长度
    info = set_bin_info(info, BOOT_PRM_LENGTH, len(bootBin).to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    # boot代码的CRC校验值
    crc = bin_crc_calc(bootBin, len(bootBin), 'ethernet')
    info = set_bin_info(info, BOOT_PRM_CRC, crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

    # 调试打印输出
    # with open("bootInfo.bin", 'bw') as outfile:
    #     outfile.write(info)

    # with open("boot.bin", 'bw') as outfile:
    #     outfile.write(bootBin)

    return (info + bootBin)

# 生成app代码的参数,并和app代码合并后返回
def generate_app_prm(appBin, loadeAddr, mpu = 'hx280025', debug = 'false', xspi = CFG_XSPI0):

    if (mpu == CFG_MPU_HX280025):

        # app固件中的app装载地址
        binSetAppAddr = get_bin_info(appBin, CFG_HX280025_APP_INFO_ENTRY_ADDR_POS)

        if (debug) :
            print("App entry address is: %X"%(binSetAppAddr), end='\n')

        # app固件中的装载地址和设置的装载地址不一致，提示退出
        if (loadeAddr != binSetAppAddr) :
            print("app entry addr not equal. App actual entry address is: %X"%(binSetAppAddr), end='\n')
            return None
    
        # app固件信息的末尾要求是0x00000000
        if (get_bin_info(appBin, (CFG_HX280025_APP_INFO_LENGTH - 1)) != 0x00000000) :
            print("app bin iofo error.", end='\n')
            return None

        # 实际的app固件长度，需要减去前面80个字节的固件信息
        actualAppBinLen = len(appBin) - (CFG_HX280025_APP_INFO_LENGTH * 4)

        # 实际的app代码
        actualAppBin = appBin[(CFG_HX280025_APP_INFO_LENGTH * 4) : len(appBin)]

        if (len(actualAppBin) != actualAppBinLen):
            print("app bin length calc error.", end='\n')
            return None

        # 最后确认长度没有超过芯片FLASH扇区大小
        if ( (actualAppBinLen) > bootFwSizeMax['hx280025']) :
            print("firmware length more than flash lenth.", end='\n')
            return None

        # app信息扇区内容填充
        appInfo = bytes.fromhex('FF' * 0x800)
        # 装载地址
        appInfo = set_bin_info(appInfo, CFG_HX280025_APP_INFO_ENTRY_ADDR_POS, binSetAppAddr.to_bytes(WORD_BYTES, ENDIAN_LITTLE))
        # 固件字节长度
        appInfo = set_bin_info(appInfo, CFG_HX280025_APP_INFO_LENGTH_POS, actualAppBinLen.to_bytes(WORD_BYTES, ENDIAN_LITTLE))   
        # CRC
        appCrc = bin_crc_calc(actualAppBin, len(actualAppBin), 'ethernet')
        appInfo = set_bin_info(appInfo, CFG_HX280025_APP_INFO_CRC_POS, appCrc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # 编译生成的bin文件的前面0x50个字节是装载参数，需要去掉
        appBinFile = appInfo + actualAppBin

        # 保存文件
        # with open("appInfo.bin", 'bw') as outfile:
        #     outfile.write(appInfo)

        # with open("app.bin", 'bw') as outfile:
        #     outfile.write(appBin)

    else:
        # mpu = rzn2l         
        '''
        loader_text_start = get_bin_info_loader_text_start(appBin)
        loader_text_end = get_bin_info_loader_text_end(appBin)
        loader_data_start = get_bin_info_loader_data_start(appBin)
        loader_data_end = get_bin_info_loader_data_end(appBin)
        fvector_start = get_bin_info_fvector_start(appBin)
        fvector_end = get_bin_info_fvector_end(appBin)
        ram_code_start = get_bin_info_ram_code_start(appBin)
        ram_code_end = get_bin_info_ram_code_end(appBin)
        text_start = get_bin_info_text_start(appBin)
        text_end = get_bin_info_text_end(appBin)
        data_start = get_bin_info_data_start(appBin)
        data_end = get_bin_info_data_end(appBin)
        '''
        # 去掉参数部分的有效的bin文件
        firmware_len = len(appBin) - LOADER_PARAMETER_LENGTH

        # 先加上7个CRC的校验位置，位置排序是：loader_text_crc + loader_data_crc + fvector_crc + ram_code_crc + text_crc + data_crc + all_crc
        crc_len =  7 * 4

        # Jerome 需要填充的字节数据( (填充+CRC+fw)的大小要是LOADER_UNIT_SIZE字节对齐)
        fill_len = LOADER_UNIT_SIZE - ((firmware_len + crc_len) % LOADER_UNIT_SIZE)
        fill_prm = bytes.fromhex('FF' * fill_len)

        # 文件的长度变为：bin + fill + crc
        firmware_len += (fill_len + crc_len)

        # 将编译生成的bin原始文件分割成各个段
        bin_section_info = generate_loader_prm(appBin, 0, xspi)

        if bin_section_info is None:
            ERRMSG("bin section is none.", end='\n')
            return
        
        loader_prm_bin = bin_section_info[0]
        loader_text_bin = bin_section_info[1]
        loader_data_bin = bin_section_info[2]
        fvector_bin = bin_section_info[3]
        ramcode_bin = bin_section_info[4]
        text_bin = bin_section_info[5]
        data_bin = bin_section_info[6]

        '''
        with open('loader_prm.bin', 'bw') as outfile:
            outfile.write(loader_prm_bin)
        with open('loader_text.bin', 'bw') as outfile:
            outfile.write(loader_text_bin)
        with open('loader_data.bin', 'bw') as outfile:
            outfile.write(loader_data_bin)
        with open('fvector.bin', 'bw') as outfile:
            outfile.write(fvector_bin)
        with open('ramcode.bin', 'bw') as outfile:
            outfile.write(ramcode_bin)
        with open('text.bin', 'bw') as outfile:
            outfile.write(text_bin)
        with open('data.bin', 'bw') as outfile:
            outfile.write(data_bin)
        with open('generate.bin', 'bw') as outfile:
            generate_bin = (loader_prm_bin + loader_text_bin + loader_data_bin + fvector_bin + ramcode_bin + text_bin + data_bin)
            outfile.write(generate_bin)
        '''

        # print_bytes(loader_prm_bin)

        loader_prm_bin = set_bin_info_fill_bytes(loader_prm_bin, fill_len.to_bytes(WORD_BYTES, ENDIAN_LITTLE))
        loader_prm_bin = set_bin_info_src_addr(loader_prm_bin, get_bin_info_loader_text_memery_addr(appBin).to_bytes(WORD_BYTES, ENDIAN_LITTLE))
        loader_prm_bin = set_bin_info_size(loader_prm_bin, firmware_len.to_bytes(WORD_BYTES, ENDIAN_LITTLE))
        loader_prm_bin = set_bin_info_calc_check_sum(loader_prm_bin)
        
        # print_bytes(loader_prm_bin)

        crc_bin = bytes.fromhex('FF' * crc_len)

        '''
        with open('generate.bin', 'bw') as outfile:
            generate_bin = (loader_prm_bin + loader_text_bin + loader_data_bin + fvector_bin + ramcode_bin + text_bin + data_bin + fill_prm + crc_bin)
            outfile.write(generate_bin)
        '''

        # 计算各个section的crc校验值

        # loader_text段CRC校验值计算及设置
        loader_text_crc = bin_crc_calc(loader_text_bin, len(loader_text_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_LOADER_TEXT_CRC, loader_text_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # loader_data段CRC校验值计算及设置
        loader_data_crc = bin_crc_calc(loader_data_bin, len(loader_data_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_LOADER_DATA_CRC, loader_data_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # fvector段CRC校验值计算及设置
        fvector_crc = bin_crc_calc(fvector_bin, len(fvector_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_FVECTOR_CRC, fvector_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # ramcode段CRC校验值计算及设置
        ram_code_crc = bin_crc_calc(ramcode_bin, len(ramcode_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_RAM_CODE_CRC, ram_code_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))
        
        # text段CRC校验值计算及设置
        text_crc = bin_crc_calc(text_bin, len(text_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_TEXT_CRC, text_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # data段CRC校验值计算及设置
        data_crc = bin_crc_calc(data_bin, len(data_bin), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_DATA_CRC, data_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        # 各个段组合成的固件bin文件：计算固件crc时，不包含装载参数
        fw_bin_file = (loader_text_bin + loader_data_bin + fvector_bin + ramcode_bin + text_bin + data_bin + fill_prm + crc_bin)

        # 计算整个固件代码的CRC校验值
        bin_file_crc = bin_crc_calc(fw_bin_file, (len(fw_bin_file) - 4), 'ethernet')
        crc_bin = set_bin_info(crc_bin, POS_FW_CRC, bin_file_crc.to_bytes(WORD_BYTES, ENDIAN_LITTLE))

        appBinFile = (loader_prm_bin + loader_text_bin + loader_data_bin + fvector_bin + ramcode_bin + text_bin + data_bin + fill_prm + crc_bin)

    return appBinFile



if __name__=='__main__':
    main()

