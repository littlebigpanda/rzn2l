/*
 * bsp_eeprom.c
 *
 *  Created on: Oct 25, 2023
 *      Author: xgj12
 */

#include "hal_data.h"
#include "bsp_eeprom.h"

#define ACCESS_SUCCESS      0
#define ACCESS_ERROR        1
#define ACCESS_BUSY         2
#define ACCESS_TIMEOUT      3


typedef struct
{
    uint32_t timeoutCnt;

} STR_EEPROM;

static STR_EEPROM strEeprom;

static void bsp_eeprom_iic_init(void)
{
    /* 按键及数码管显示使用的是IIC1外设 */
    R_IIC0_Type * regBase = ((R_IIC0_Type *) R_IIC1_BASE);
    uint8_t channel = 1;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_IIC, channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* 禁止GIC级中断 */
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC1_EEI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC1_RXI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC1_TXI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC1_TEI));

    /* ICCR1默认值(I2C引脚处于非激活状态) */
    regBase->ICCR1 = (uint8_t) 0x1FU;

    /* 复位I2C模块 */
    regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);

    /* I2C处于内部复位，引脚处于激活状态 */
    regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);

    R_BSP_SoftwareDelay(1000, BSP_DELAY_UNITS_MICROSECONDS);

    /* ICCR1默认值(I2C引脚处于非激活状态) */
    regBase->ICCR1 = (uint8_t) 0x1FU;

    /* 复位I2C模块 */
    regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);

    /* I2C处于内部复位，引脚处于激活状态 */
    regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);

    /* 20 - 大概是133KHz， 28 - 大概是100KHz， 9 - 大概是250KHz, 在8分频设定模式下 */
    /* 14 - 大概是350KHz, 在4分频设定模式下 */
    /* 14 - 大概是390KHz, 在4分频设定模式下 */
    /* 14 - 大概是367KHz, 在4分频设定模式下 */
    /* 低电平时间(波特率)，0xE0是保留位设定值 */
    regBase->ICBRL = (uint8_t) (0xE0 | 28);
    /* 高电平时间(波特率)，0xE0是保留位设定值 */
    regBase->ICBRH = (uint8_t) (0xE0 | 28);

    /* 选择I2C时钟分频系数，3-8分频(PCLKL/8，PCLKL=50MHz)， 2-4分频(PCLKL/4，PCLKL=50MHz) */
    regBase->ICMR1 = (uint8_t) (0x08 | ((0x02 & 0x07U) << 4U));

    /* 使能SCL L和H超时检测，短检测模式，禁止SDA输出延时 */
    regBase->ICMR2 = (0x06 | 0x00);

    /* 使能数字滤波，滤波为1级，I2C工作模式 */
    regBase->ICMR3 = 0x00;

    /* 使能超时检测功能，使能仲裁丢失检测及发送NACK，使能NACK接收暂停发送，使能滤波，禁止同步电路，禁止从机仲裁检测 */
    regBase->ICFER = 0x77;

    /* 禁止所有的设备地址(I2C模块完全工作在主机模式) */
    regBase->ICSER = 0x00;

    /* I2C模块中断使能(注：要使能外设级中断才可以使用DMA，否则DMA无法触发启动) */
    regBase->ICIER = 0xA0;  /* 使能接收满和发送空中断 */

    /* 使能GIC级中断 */
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC1_EEI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC1_RXI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC1_TXI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC1_TEI));

    /* I2C复位释放 */
    regBase->ICCR1 = (uint8_t) (0x80 | 0x1F);
}


void bsp_eeprom_init(void)
{
    memset(&strEeprom, 0x00, sizeof(strEeprom));

    /* 初始化Eeprom所用的iic外设 */
    bsp_eeprom_iic_init();
}


/*******************************************************************************************************************

* @param  DevAddress                device address
* @param  MemAddress                eeprom data address
* @param  MemAddSize                eeprom data address zise
* @param  pData                     Pointer to read data
*  @param  Size                     read data number
* @param  Timeout                   Timeout [ms]

* @return    ACCESS_ SUCCESS       0
* @return    ACCESS_ ERROR         1
* @return    ACCESS_ BUSY          2
* @return    ACCESS_ TIMEOUT       3
 **********************************************************************************************************************/

uint8_t I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,
        uint8_t * pData, uint16_t Size, uint32_t Timeout)
{
    return ACCESS_SUCCESS;
}

uint8_t I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,
        uint8_t * pData, uint16_t Size, uint32_t Timeout)
{
    return ACCESS_SUCCESS;
}
