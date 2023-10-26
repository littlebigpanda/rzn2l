/*
 * bsp_led.c
 *
 *  Created on: Oct 25, 2023
 *      Author: xgj12
 */


#include "hal_data.h"
#include "bsp_led.h"

struct TCA6424A_t TCA6424A[1];
unsigned char led_buffer[5] = {0xFD,0xFD,0xFD,0xFD,0xFD};
unsigned char DisplayCommStatus = 0;

const unsigned char TCA6424_Command_Output[3] = {TCA6424A_CMD_OUT0_AI, PCA9535_CMD_OUT0, PCA9535_CMD_OUT0};
const unsigned char TCA6424_Command_Input[3] = {TCA6424A_CMD_IN0_AI, PCA9535_CMD_IN0, PCA9535_CMD_IN0};
const unsigned char TCA6424_Command_Config[3] = {TCA6424A_CMD_CONF0_AI, PCA9535_CMD_CONF0, PCA9535_CMD_CONF0};
const unsigned char TCA6424_Command_ConfigData[3][3] = { {0x00,0x00,0xFF}, {0x00,0x1F,0xFF}, {0x00,0x1F,0xFF} };
const unsigned char TCA6424_Command_ConfigDataLength[3] = { 3, 2, 2 };
const unsigned char TCA6424_Input_Position[3] = {2, 1, 1};
const uint8_t TCA6424_slaveAddr[2] = {0x23/*TCA6424A*/, 0x24/*PCA9535*/};
const uint8_t TCA6424_chipType[2] = {CHIP_TYPE_TCA6424/*TCA6424A*/, CHIP_TYPE_PCA9535/*PCA9535*/};

static uint8_t SendDataBuf[10];

//************************************************
//   __     __     __     __     __
//  |__|   |__|   |__|   |__|   |__|
//  |__|   |__|   |__|   |__|   |__|
//
//   0      1      2      3      4
//
//  0xEF   0xFE   0xF7   0xFD   0xFB    -  TCA6424A
//
//  0x80   0x00   0x60   0x20   0x40    -  PCA9535
//
//************************************************
const unsigned char Segment[3][5] = { {0xEF,0xFE,0xF7,0xFD,0xFB}, {0x80,0x00,0x60,0x20,0x40}, {0x80,0x00,0x60,0x20,0x40} };


static void bsp_led_iic_init(void)
{
    /* 按键及数码管显示使用的是IIC2外设 */
    R_IIC0_Type * regBase = ((R_IIC0_Type *) R_IIC2_BASE);
    uint8_t channel = 2;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_IIC, channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* 禁止GIC级中断 */
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC2_EEI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC2_RXI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC2_TXI));
    R_BSP_IrqDisable(((IRQn_Type) VECTOR_NUMBER_IIC2_TEI));

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
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC2_EEI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC2_RXI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC2_TXI));
    //R_BSP_IrqEnable(((IRQn_Type) VECTOR_NUMBER_IIC2_TEI));

    /* I2C复位释放 */
    regBase->ICCR1 = (uint8_t) (0x80 | 0x1F);

    /* 按键及LED需要DMA传输时的目的寄存器 */
    g_iic_led_tx_dma.p_cfg->p_info->p_dest = (void *)(&regBase->ICDRT);
    /* 按键及LED需要DMA传输时的源寄存器 */
    g_iic_led_tx_dma.p_cfg->p_info->p_src = (void *)(&SendDataBuf[0]);
}

static void bsp_led_reconfig_dma(uint32_t length)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *)g_iic_led_tx_dma.p_ctrl;

    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *)g_iic_led_tx_dma.p_cfg->p_extend;

    R_DMAC0_Type * regBase = p_ctrl->p_reg;

    uint8_t channel = p_extend->channel;

    /* 失能DMA */
    regBase->GRP[0].CH[channel].CHCTRL = (1U << 0x01);
    /* 等待DMA传输停止 */
    FSP_HARDWARE_REGISTER_WAIT(regBase->GRP[0].CH[channel].CHSTAT_b.TACT, 0);
    /* DMA软件复位 */
    regBase->GRP[0].CH[channel].CHCTRL = (1U << 0x03);
    /* 屏蔽发送完成中断 */
    regBase->GRP[0].CH[channel].CHCFG |= (1U << 24);

    /* 设置发送长度 */
    regBase->GRP[0].CH[channel].N[0].TB = length;

    /* DMA Software Reset. */
    regBase->GRP[0].CH[channel].CHCTRL = (1U << 3U);
    /* Does not mask DMA transfer end interrupt */
    regBase->GRP[0].CH[channel].CHCFG &= (~((uint32_t) (1U << 24U)));
    /* Enable transfer. */
    regBase->GRP[0].CH[channel].CHCTRL = (1U << 0U);
}

static uint8_t bsp_led_get_dma_status(void)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *)g_iic_led_tx_dma.p_ctrl;

    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *)g_iic_led_tx_dma.p_cfg->p_extend;

    R_DMAC0_Type * regBase = p_ctrl->p_reg;

    uint8_t channel = p_extend->channel;

    /* 注：只有使能中断后才可以有TEND中断标志位 */
    return ((regBase->GRP[0].DSTAT_END & (0x01UL << channel)) ? 1 : 0);
}

void bsp_led_init(void)
{
    memset(&TCA6424A[0], 0x00, sizeof(TCA6424A[0]));

    memset(&SendDataBuf[0], 0x00, sizeof(SendDataBuf));

    /* 初始化按键及LED所用的IIC外设，同时配置使用的DMA的目的地址，源地址 */
    bsp_led_iic_init();

    /* 初始化IIC2发送DMA */
    g_iic_led_tx_dma.p_api->open(g_iic_led_tx_dma.p_ctrl, g_iic_led_tx_dma.p_cfg);
}

void bsp_led_handle(void)
{
    static uint8_t sendLength = 0;
    static uint8_t sendCount = 0;
    static uint8_t SendRestart = 0;
    static uint8_t testAddrCnt = 0;

    struct TCA6424A_t *tca6424a = &TCA6424A[0];
    R_IIC0_Type * regBase = ((R_IIC0_Type *) R_IIC2_BASE);

TCA6242A_RESTART_QUICK:

    switch(tca6424a->HandleState)
    {
    case TCA6424A_HANDLE_STATE_TEST_ADDR_INIT:
    case TCA6424A_HANDLE_STATE_TEST_ADDR_START:
    case TCA6424A_HANDLE_STATE_TEST_ADDR_END:

        tca6424a->Addr = TCA6424_slaveAddr[testAddrCnt];
        tca6424a->ChipType = TCA6424_chipType[testAddrCnt];

        testAddrCnt++;
        if (testAddrCnt >= sizeof(TCA6424_slaveAddr))
        {
            testAddrCnt = 0;
        }

        #if(CFG_TCA6424A_REFRESH_MODE==1)
        tca6424a->sendCfgValCnt = CFG_TCA6424A_CONFIG_INTERVAL;
        #endif

        tca6424a->HandleState = TCA6424A_HANDLE_STATE_INIT;
        break;

    case TCA6424A_HANDLE_STATE_INIT:

        if (TCA6424A[0].EepromControlFlag == 2)
        {
            /* 0xFF - 数码管段码全部点亮 */
            led_buffer[0] = 0xFF;
            led_buffer[1] = 0xFF;
            led_buffer[2] = 0xFF;
            led_buffer[3] = 0xFF;
            led_buffer[4] = 0xFF;
        }

        #if(CFG_TCA6424A_REFRESH_MODE==1)
        tca6424a->sendCfgValCnt ++;
        if (tca6424a->sendCfgValCnt >= CFG_TCA6424A_CONFIG_INTERVAL)
        {
            tca6424a->sendCfgValCnt = 0;
            tca6424a->sendCfgFlag = 0;
        #endif

            sendCount = 0;
            SendDataBuf[sendCount++] = (uint8_t)(tca6424a->Addr << 1) | 0x00;
            SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_Config[tca6424a->ChipType];
            SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_ConfigData[tca6424a->ChipType][0];
            SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_ConfigData[tca6424a->ChipType][1];
            if (TCA6424_Command_ConfigDataLength[tca6424a->ChipType] == 3)
            {
                SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_ConfigData[tca6424a->ChipType][2];
            }

            sendLength = sendCount;
            sendCount = 0;
            SendRestart = 0;

            tca6424a->HandleState = TCA6424A_HANDLE_STATE_CHECK_BUSY;
            tca6424a->HandleStateNext = TCA6424A_HANDLE_STATE_WRITE_RUNNING;

        #if(CFG_TCA6424A_REFRESH_MODE==1)
        }
        else
        {
            tca6424a->sendCfgFlag = 1;
            tca6424a->timeCnt = 0;
            tca6424a->HandleState = TCA6424A_HANDLE_STATE_WRITE_START;
            tca6424a->HandleStateNext = TCA6424A_HANDLE_STATE_WRITE_RUNNING;
            goto TCA6242A_RESTART_QUICK;
        }
        #endif
        break;

    case TCA6424A_HANDLE_STATE_CHECK_BUSY:
        if (regBase->ICCR2_b.BBSY)
        {
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else
        {
            /* 清WAIT，ACKWP位 */
            regBase->ICMR3 &= 0xAF;

            /* 清所有的标志位 */
            regBase->ICSR2 = 0x00;

            /* 使能高低超时检测短模式，禁止输出延时 */
            regBase->ICMR2 = 0x06;

            /* 是能超时检测功能 */
            regBase->ICFER_b.TMOE = 0U;

            /* 重新配置DMA传输的字节个数，重新启动DMA传输 */
            #if (CFG_LED_IIC_USE_DMAC==1)
            bsp_led_reconfig_dma(sendLength);
            #endif

            /* 请求发送起始位 */
            regBase->ICCR2 = (uint8_t) 0x02;

            tca6424a->timeCnt = 0;

            tca6424a->HandleState = TCA6424A_HANDLE_STATE_WRITE_INIT;
        }
        break;

    case TCA6424A_HANDLE_STATE_WRITE_INIT:

        #if(CFG_LED_IIC_USE_DMAC==0)
        tca6424a->timeCnt ++;

        if ( (regBase->ICSR2 & 0x84) == 0x84)
        {
            /* 起始位已经发送，并且发送缓存处于空状态 */
            tca6424a->timeCnt = 0;
        }

        if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }

        if (tca6424a->timeCnt >= 5)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }

        if ( (tca6424a->timeCnt == 0) && (tca6424a->HandleState != TCA6424A_HANDLE_I2C_ERR) )
        {
            if (sendCount < sendLength)
            {
                regBase->ICDRT = SendDataBuf[sendCount++];
            }
            else if ( (regBase->ICSR2 & 0x44) == 0x44 )
            {
                /* 发送完成, 发送停止位 */
                if (SendRestart)
                {
                    /* 读取参数，不需要发送停止位 */

                    /* 请求发送起始位 */
                    regBase->ICCR2 = (uint8_t) 0x04;

                    SendRestart = 0;
                    tca6424a->HandleState = tca6424a->HandleStateNext;
                }
                else
                {
                    regBase->ICSR2_b.STOP = 0;
                    regBase->ICCR2_b.SP = 1;

                    tca6424a->HandleState = TCA6424A_HANDLE_STATE_WRITE_START;
                }

                /* 能进行到这里，表明没有从机有响应，将从机地址初始化/查找标志置位，表明当前已经正确获取从机芯片类型/地址 */
                if (tca6424a->bGetLedType == 0)
                {
                    tca6424a->bGetLedType = 1;
                }
            }
        }
        #else
        tca6424a->timeCnt ++;

        if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if (tca6424a->timeCnt >= 5)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if ( ( (regBase->ICSR2 & 0x44) == 0x44 )  && bsp_led_get_dma_status() )
        {
            /* 发送完成, 发送停止位 */
            if (SendRestart)
            {
                /* 读取参数，不需要发送停止位 */

                /* 请求发送起始位 */
                regBase->ICCR2 = (uint8_t) 0x04;

                SendRestart = 0;
                tca6424a->HandleState = tca6424a->HandleStateNext;
            }
            else
            {
                regBase->ICSR2_b.STOP = 0;
                regBase->ICCR2_b.SP = 1;

                tca6424a->HandleState = TCA6424A_HANDLE_STATE_WRITE_START;
            }

            /* 能进行到这里，表明没有从机有响应，将从机地址初始化/查找标志置位，表明当前已经正确获取从机芯片类型/地址 */
            if (tca6424a->bGetLedType == 0)
            {
                tca6424a->bGetLedType = 1;
            }
        }
        #endif
        break;

    case TCA6424A_HANDLE_STATE_WRITE_START:

        tca6424a->timeCnt ++;

        if ( (regBase->ICSR2_b.STOP == 1) || (tca6424a->sendCfgFlag == 1))
        {
            /* 是能超时检测功能 */
            regBase->ICFER_b.TMOE = 0U;

            switch (tca6424a->HandleStateNext)
            {
                /* 启动发送输出 - 发送设备地址，命令，LED显示字符 */
            case TCA6424A_HANDLE_STATE_WRITE_RUNNING:
                sendCount = 0;
                SendDataBuf[sendCount++] = (uint8_t)(tca6424a->Addr << 1) | 0x00;
                SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_Output[tca6424a->ChipType];

                tca6424a->BitSequenceCnt++;
                if (tca6424a->BitSequenceCnt >= 5)
                {
                    tca6424a->BitSequenceCnt = 0;
                }

                if (tca6424a->ChipType != CHIP_TYPE_PCA9535)
                {
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                    SendDataBuf[sendCount++] = (uint8_t)led_buffer[tca6424a->BitSequenceCnt];                     // 段码选择
                    SendDataBuf[sendCount++] = (uint8_t)Segment[tca6424a->ChipType][tca6424a->BitSequenceCnt];    // 位选择
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                }
                else
                {
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                    SendDataBuf[sendCount++] = (uint8_t)0xFF;
                    SendDataBuf[sendCount++] = (uint8_t)led_buffer[tca6424a->BitSequenceCnt];                     // 段码选择
                    SendDataBuf[sendCount++] = (uint8_t)Segment[tca6424a->ChipType][tca6424a->BitSequenceCnt];    // 位选择
                }

                sendLength = sendCount;
                sendCount = 0;
                SendRestart = 0;

                tca6424a->HandleState = TCA6424A_HANDLE_STATE_CHECK_BUSY;
                tca6424a->HandleStateNext = TCA6424A_HANDLE_STATE_READ_INIT;
                goto TCA6242A_RESTART_QUICK;
                break;

                /* 启动读取按键 - 发送设备地址，命令 */
            case TCA6424A_HANDLE_STATE_READ_INIT:

                #if(CFG_TCA6424A_REFRESH_MODE==1)
                tca6424a->readKeyValCnt ++;
                if (tca6424a->readKeyValCnt >= CFG_TCA6424A_READ_INPUT_INTERVAL)
                {
                    tca6424a->readKeyValCnt = 0;
                #endif
                    sendCount = 0;
                    SendDataBuf[sendCount++] = (uint8_t)(tca6424a->Addr << 1) | 0x00;
                    SendDataBuf[sendCount++] = (uint8_t)TCA6424_Command_Input[tca6424a->ChipType];
                    sendLength = sendCount;
                    sendCount = 0;
                    SendRestart = 1;
                    tca6424a->HandleState = TCA6424A_HANDLE_STATE_CHECK_BUSY;
                    tca6424a->HandleStateNext = TCA6424A_HANDLE_STATE_READ_START;
                    goto TCA6242A_RESTART_QUICK;

                #if(CFG_TCA6424A_REFRESH_MODE==1)
                }
                else
                {
                    tca6424a->HandleState = TCA6424A_HANDLE_STATE_INIT;
                }
                #endif
                break;

            default:
                tca6424a->HandleState = tca6424a->HandleStateNext;
                break;
            }
        }
        else if (tca6424a->timeCnt >= 5)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        break;

    case TCA6424A_HANDLE_STATE_WRITE_RUNNING:
    case TCA6424A_HANDLE_STATE_READ_INIT:
        tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        break;

        /* 等待读取按键的重复起始位被正确发送 */
    case TCA6424A_HANDLE_STATE_READ_START:

        tca6424a->timeCnt ++;

        if (tca6424a->timeCnt >= 5)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if ( (regBase->ICCR2 & 0x04) == 0)
        {
            /* 在没有任何错误的情况下，如果RS标志被清零，表示起始位被正确发送 */
            regBase->ICDRT = (uint8_t)(tca6424a->Addr << 1) | 0x01;

            /* 固定为3字节，如果修改，后续程序需要修改 */
            sendCount = 0;
            sendLength = 3;
            SendRestart = 0;
            tca6424a->timeCnt = 0;

            tca6424a->HandleState = TCA6424A_HANDLE_STATE_READ_RUINING;
        }
        break;

        /* 等待从机返回按键状态 */
    case TCA6424A_HANDLE_STATE_READ_RUINING:
        tca6424a->timeCnt ++;

        if (tca6424a->timeCnt > 10)
        {
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if (regBase->ICSR2 & 0x0B)
        {
            /* 超时，仲裁丢失，停止位接收 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        else if (regBase->ICSR2 & 0x10)
        {
            /* 无应答接收错误 */
            regBase->ICSR2_b.STOP = 0;
            regBase->ICCR2_b.SP = 1;
            regBase->ICMR3_b.WAIT = 0;
            (void) regBase->ICDRR;
            tca6424a->timeCnt = 0;
            tca6424a->HandleState = TCA6424A_HANDLE_STATE_READ_WAIT_FINISH;
        }
        else if (SendRestart == 0)
        {
            /* 先启动传输，固定认为是读取3个字节，如果不为3个字节，就需要修改程序 */
            tca6424a->timeCnt = 0;

            (void) regBase->ICDRR;

            SendRestart = 1;
        }
        else if (regBase->ICSR2 & 0x20)
        {
            regBase->ICMR3_b.ACKWP = 1; /* Write enable ACKBT */
            regBase->ICMR3_b.ACKBT = 1;

            /* 只有一个字节数据，再次进来肯定得到了正确的数据了 */
            if ( ((sendCount + 2) == sendLength) )
            {
                SendDataBuf[sendCount++] = regBase->ICDRR;

                regBase->ICSR2_b.STOP = 0;

                regBase->ICMR3_b.WAIT = 0;

                tca6424a->timeCnt = 8;

                while (tca6424a->timeCnt)
                {
                    if (regBase->ICSR2_b.STOP == 0)
                    {
                        break;
                    }

                    tca6424a->timeCnt --;
                }

                regBase->ICCR2_b.SP = 1;

                tca6424a->timeCnt = 0;
                tca6424a->HandleState = TCA6424A_HANDLE_STATE_READ_WAIT_FINISH;
            }

            SendDataBuf[sendCount++] = regBase->ICDRR;
        }
        break;

        /* 等待发送停止位完成 */
    case TCA6424A_HANDLE_STATE_READ_WAIT_FINISH:

        tca6424a->timeCnt ++;

        if (regBase->ICSR2_b.STOP == 1)
        {
            tca6424a->timeCnt = 0;

            /* 清WAIT，ACKWP位 */
            regBase->ICMR3 &= 0xAF;

            regBase->ICSR2 = 0x00;

            regBase->ICMR3 &= 0xEF;

            /* 是能超时检测功能 */
            regBase->ICFER_b.TMOE = 0U;

            if (sendCount != sendLength)
            {
                tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
            }
            else
            {
                tca6424a->key_val = SendDataBuf[TCA6424_Input_Position[tca6424a->ChipType]];

                tca6424a->timeCnt = 0;
                tca6424a->HandleState = TCA6424A_HANDLE_STATE_FINISH_CHECK_EEPROM;
            }
        }
        else if (tca6424a->timeCnt >= 5)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        }
        break;

    case TCA6424A_HANDLE_STATE_FINISH_CHECK_EEPROM:
        if (tca6424a->EepromControlFlag != 1)
        {
            tca6424a->timeCnt = 0;

            if (tca6424a->bGetLedType != 0)
            {
                /* 按键面板从机地址已经取得，直接正常操作 */
                tca6424a->HandleState = TCA6424A_HANDLE_STATE_INIT;

                goto TCA6242A_RESTART_QUICK;
            }
            else
            {
                /* 按键面板从机地址未正确获取，这里需要对从机地址进行测试，以获取当前安装的LED面板型号/地址 */
                tca6424a->HandleState = TCA6424A_HANDLE_STATE_TEST_ADDR_INIT;
            }
        }
        break;

        /* IIC出现故障后，不知从机处于何种模式下，因此这里发送10个bit的停止位，用来对从机状态机进行复位 */
    case TCA6424A_HANDLE_I2C_ERR:
        /* ICCR1默认值(I2C引脚处于非激活状态) */
        regBase->ICCR1 = (uint8_t) 0x1FU;
        /* 复位I2C模块 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);
        /* I2C处于内部复位，引脚处于激活状态 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);

        tca6424a->timeCnt = 0;
        break;

    case TCA6424A_HANDLE_I2C_ERR_START:
        tca6424a->timeCnt ++;
        if (tca6424a->timeCnt >= 20)
        {
            tca6424a->timeCnt = 0;

            sendCount = 0;

            if ((regBase->ICCR1 & 0x01) == 0)
            {
                tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR_LOW;
            }
            else
            {
                tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR_FINISH;
            }
        }
        break;

    case TCA6424A_HANDLE_I2C_ERR_LOW:

        tca6424a->timeCnt ++;

        if (tca6424a->timeCnt == 1)
        {
            regBase->ICCR1 = 0x84;
        }
        else if (tca6424a->timeCnt >= 50)
        {
            tca6424a->timeCnt = 0;

            tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR_HIGH;
        }
        break;

    case TCA6424A_HANDLE_I2C_ERR_HIGH:

        tca6424a->timeCnt ++;

        if (tca6424a->timeCnt == 0)
        {
            regBase->ICCR1 = 0x8C;
        }
        else if (tca6424a->timeCnt >= 50)
        {
            tca6424a->timeCnt = 0;

            sendCount ++;
            if (sendCount >= 10)
            {
                sendCount = 0;

                tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR_FINISH;
            }
            else
            {
                tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR_LOW;
            }
        }
        break;

    case TCA6424A_HANDLE_I2C_ERR_FINISH:
        /* ICCR1默认值(I2C引脚处于非激活状态) */
        regBase->ICCR1 = (uint8_t) 0x1FU;
        /* 复位I2C模块 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);
        /* I2C处于内部复位，引脚处于激活状态 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);
        /* I2C复位释放 */
        regBase->ICCR1 = (uint8_t) (0x80 | 0x1F);

        tca6424a->HandleState = TCA6424A_HANDLE_STATE_FINISH_CHECK_EEPROM;

        break;

    default:
        tca6424a->HandleState = TCA6424A_HANDLE_I2C_ERR;
        break;
    }
}

