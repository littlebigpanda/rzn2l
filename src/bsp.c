/*
 * bsp.c
 *
 *  Created on: Oct 24, 2023
 *      Author: xgj12
 */
#include "hal_data.h"
#include "bsp.h"



static void bsp_sci_buadtrate(R_SCI0_Type * regBase, uint32_t buadrate)
{
    /* 复位默认值 */
    regBase->CCR2 = 0xFF00FF04;

    /* 位速率调制功能/波特率小数分频功能使能，1-使能 */
    regBase->CCR2_b.BRME = 1;
    /* 0-禁止外部时钟 */
    regBase->CCR2_b.ABCSE = 0;

    /* 波特率寄存器设置, 输入时钟为96MHz
     * PCLKSCIx = 96MHz
     * BBR = ( (PCLKSCIx * 10000000) / (64 * 2^(2*n-1) * B) ) - 1
     * BBR  : 寄存器设定值
     * B    : 波特率值
     * n    : 时钟源分频设定值
     * 计算公式基于一个bit采样时钟16个，单速率模式下
     */
    switch (buadrate)
    {
    case 4800UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 0;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 64;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 2;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 213;
        break;

    case 9600UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 0;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 0;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 176;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 145;
        break;

    case 19200UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 0;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 176;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 145;
        break;

    case 38400UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 1;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 176;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 145;
        break;

    case 57600UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 0;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 58;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 145;
        break;

    case 2500000UL:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 1;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 2;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 160;
        break;

    case 115200UL:
    default:
        /* 波特率生成双速率模式使能，1-使能 */
        regBase->CCR2_b.BGDM = 1;
        /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
        regBase->CCR2_b.ABCS = 1;
        /* 波特率计数器 */
        regBase->CCR2_b.BRR = 58;
        /* 输入时钟源分频选择，0-部分品，1-4分频，2-16分频，3-64分频 */
        regBase->CCR2_b.CKS = 0;
        /* 调制占空比设置 */
        regBase->CCR2_b.MDDR = 145;
        break;
    }
}

static void bsp_sci_format(R_SCI0_Type * regBase, uint8_t format)
{
    switch (format)
    {
    case 1:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 0;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 0;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 1;
        break;
    case 2:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 1;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 0;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 0;
        break;
    case 3:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 1;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 0;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 1;
        break;
    case 4:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 1;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 1;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 0;
        break;
    case 5:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 1;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 1;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 1;
        break;
    case 0:
    default:
        /* 奇偶校验使能，1-使能*/
        regBase->CCR1_b.PE = 0;
        /* 0-偶校验(enen)，1-奇校验(odd) */
        regBase->CCR1_b.PM = 0;
        /* 0-1位停止位，1-2位停止位 */
        regBase->CCR3_b.STP = 0;
        break;
    }
}

/**
 * 调试用SCI0初始化，程序开启了GIC级的TEI，TXI中断(外设级需要再发送数据的时候开启), 开启了RXI中断(GIC级中断被禁止，触发DMA传输时需要外设中断标志)
 * @param buadrate  - 波特率，目前支持(4800/9600/19200/38400/57600/115200/2500000)
 * @param format    - 数据格式，0-8N1,1-8N2，2-8E1，3-8E2，4-8O1,5-8O2
 */
void bsp_sci_init_debug(uint32_t buadrate, uint8_t format)
{
    /* SCIx外设基地址 */
    R_SCI0_Type * regBase = ((R_SCI0_Type *) R_SCI0_BASE);

    /* SCIx通道 */
    uint32_t channel = 0UL;

    /* Cancel SCI0 module stop state */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCI, channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* 禁止GIC级中断 */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI0_ERI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI0_RXI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI0_TXI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI0_TEI);

    /* Clear transmit/receive enable bits */
    regBase->CCR0_b.TE = 0U;
    regBase->CCR0_b.RE = 0U;

    /* Reset transmit/receive FIFO data register operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* Read and clear status flags */
    regBase->CFCLR = 0UL;
    regBase->FFCLR = 0UL;

    /* Set transmission/reception format */

    regBase->CCR1 = 0x00000000;
    /* TXD引脚在TE为0时的电平，0-低电平，1-高电平(CCR1.bit12是取反意思) */
    regBase->CCR1_b.SPB2DT = 1;
    /* TXD引脚在TE为0时的输出是否受SPB2DT控制，1-使能控制 */
    regBase->CCR1_b.SPB2IO = 1;
    /* TXD输出引脚电平取反 */
    regBase->CCR1_b.TINV = 0;
    /* RXD输入引脚电平取反 */
    regBase->CCR1_b.RINV = 0;
    /* RXD输入数字滤波时钟选择 */
    regBase->CCR1_b.NFCS = 0;
    /* RXD输入数字滤波使能，1-使能 */
    regBase->CCR1_b.NFEN = 0;

    /* 波特率配置 */
    bsp_sci_buadtrate(regBase, buadrate);

    /* 复位默认值 */
    regBase->CCR3 = 0x00001203;
    /* 字符长度，0/1-9bit，2-8bit，3-7bit */
    regBase->CCR3_b.CHR = 2;
    /* 0-MSB先发送，1-LSB先发送 */
    regBase->CCR3_b.LSBF = 1;
    /* 1-接收/发送数据反相使能 */
    regBase->CCR3_b.SINV = 0;
    /* 0-低电平作为起始位检测，1-下降沿作为起始位检测 */
    regBase->CCR3_b.RXDESEL = 1;
    /* 0-串口通讯模式 */
    regBase->CCR3_b.MOD = 0;
    /* 1-FIFO功能使能 */
    regBase->CCR3_b.FM = 1;
    /* 1-RS485控制引脚驱动使能 */
    regBase->CCR3_b.DEN = 0;

    /* 数据格式配置 */
    bsp_sci_format(regBase, format);

    /* 复位默认值 */
    regBase->CCR4 = 0x00000000;

    /* Wait for at least 1-bit interval */
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

    /* Set FIFO trigger conditions */

    /* FIFO控制寄存器复位默认值 */
    regBase->FCR = 0x00000000;
    /* FIFO发送缓存触发中断设定值(使用DMA进行接收时，需要设置为0) */
    regBase->FCR_b.TTRG = 0;
    /* FIFO接收缓存触发中断设定值(使用DMA进行接收时，需要设置为0) */
    regBase->FCR_b.RTRG = 8;

    /* Disable transmit/receive FIFO data register reset operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* 配置SCI中断优先级 */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI0_ERI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI0_RXI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI0_TXI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI0_TEI, 12, NULL);

    /* 使能GIC级中断 */
    //R_BSP_IrqEnable(VECTOR_NUMBER_SCI0_ERI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI0_RXI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI0_TXI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI0_TEI);

    /* 外设级中断使能：(只有使能了外设级别的接收中断才可以触发DMA进行数据传输) */
    regBase->CCR0_b.RIE = 1U;    /* 接收中断 */
    //regBase->CCR0_b.TIE = 1U;    /* 发送空中断 */
    //regBase->CCR0_b.TEIE = 1U;    /* 发送结束中断 */

    /* 使能接收及使能发送  */
    regBase->CCR0_b.TE = 1U;
    regBase->CCR0_b.RE = 1U;
    while(1U != regBase->CCR0_b.TE)
    {
        ;
    }
}


/**
 * 总线用SCI4初始化，程序开启了GIC级的TEI，TXI中断(外设级需要再发送数据的时候开启), 开启了RXI中断(GIC级中断被禁止，触发DMA传输时需要外设中断标志),
 * 使能
 * @param buadrate  - 波特率，目前支持(4800/9600/19200/38400/57600/115200/2500000)
 * @param format    - 数据格式，0-8N1,1-8N2，2-8E1，3-8E2，4-8O1,5-8O2
 */
void bsp_sci_init_zx(uint32_t buadrate, uint8_t format)
{
    /* SCIx外设基地址 */
    R_SCI0_Type * regBase = ((R_SCI0_Type *) R_SCI4_BASE);

    /* SCIx通道 */
    uint32_t channel = 4UL;

    /* Cancel SCI0 module stop state */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCI, channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* 禁止GIC级中断 */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI4_ERI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI4_RXI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI4_TXI);
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI4_TEI);

    /* Clear transmit/receive enable bits */
    regBase->CCR0_b.TE = 0U;
    regBase->CCR0_b.RE = 0U;

    /* Reset transmit/receive FIFO data register operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* Read and clear status flags */
    regBase->CFCLR = 0UL;
    regBase->FFCLR = 0UL;

    /* Set transmission/reception format */

    regBase->CCR1 = 0x00000000;
    /* TXD引脚在TE为0时的电平，0-低电平，1-高电平(CCR1.bit12是取反意思) */
    regBase->CCR1_b.SPB2DT = 1;
    /* TXD引脚在TE为0时的输出是否受SPB2DT控制，1-使能控制 */
    regBase->CCR1_b.SPB2IO = 1;
    /* TXD输出引脚电平取反 */
    regBase->CCR1_b.TINV = 0;
    /* RXD输入引脚电平取反 */
    regBase->CCR1_b.RINV = 0;
    /* RXD输入数字滤波时钟选择 */
    regBase->CCR1_b.NFCS = 0;
    /* RXD输入数字滤波使能，1-使能 */
    regBase->CCR1_b.NFEN = 0;

    /* 波特率配置 */
    bsp_sci_buadtrate(regBase, buadrate);

    /* 复位默认值 */
    regBase->CCR3 = 0x00001203;
    /* 字符长度，0/1-9bit，2-8bit，3-7bit */
    regBase->CCR3_b.CHR = 2;
    /* 0-MSB先发送，1-LSB先发送 */
    regBase->CCR3_b.LSBF = 1;
    /* 1-接收/发送数据反相使能 */
    regBase->CCR3_b.SINV = 0;
    /* 0-低电平作为起始位检测，1-下降沿作为起始位检测 */
    regBase->CCR3_b.RXDESEL = 1;
    /* 0-串口通讯模式 */
    regBase->CCR3_b.MOD = 0;
    /* 1-FIFO功能使能 */
    regBase->CCR3_b.FM = 1;
    /* 1-RS485控制引脚驱动使能 */
    regBase->CCR3_b.DEN = 0;

    /* 数据格式配置 */
    bsp_sci_format(regBase, format);

    /* 复位默认值 */
    regBase->CCR4 = 0x00000000;

    /* Wait for at least 1-bit interval */
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

    /* Set FIFO trigger conditions */

    /* FIFO控制寄存器复位默认值 */
    regBase->FCR = 0x00000000;
    /* FIFO发送缓存触发中断设定值(使用DMA进行接收时，需要设置为0) */
    regBase->FCR_b.TTRG = 0;
    /* FIFO接收缓存触发中断设定值(使用DMA进行接收时，需要设置为0) */
    regBase->FCR_b.RTRG = 8;

    /* Disable transmit/receive FIFO data register reset operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* 配置SCI中断优先级 */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI4_ERI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI4_RXI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI4_TXI, 12, NULL);
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI4_TEI, 12, NULL);

    /* 使能GIC级中断 */
    //R_BSP_IrqEnable(VECTOR_NUMBER_SCI4_ERI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI4_RXI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI4_TXI);
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI4_TEI);

    /* 外设级中断使能：(只有使能了外设级别的接收中断才可以触发DMA进行数据传输) */
    regBase->CCR0_b.RIE = 1U;    /* 接收中断 */
    //regBase->CCR0_b.TIE = 1U;    /* 发送空中断 */
    //regBase->CCR0_b.TEIE = 1U;    /* 发送结束中断 */

    /* 使能接收及使能发送  */
    regBase->CCR0_b.TE = 1U;
    regBase->CCR0_b.RE = 1U;
    while(1U != regBase->CCR0_b.TE)
    {
        ;
    }
}

/**
 * 配置编码器用SCI3(编码器轴1)和SCI2(编码器轴2)
 * 1. 2.5M波特率，8数据位+无校验+1停止位，开启FIFO，无任何中断使能
 * 2. 启用了硬件DE功能
 *
 * @param channel - 编码器轴号， 1-1号编码器轴外设(SCI3)，2-2号编码器轴外设(SCI2)
 */
void bsp_sci_init_encoder(uint8_t axis_num)
{
    /* SCIx外设基地址 */
    R_SCI0_Type * regBase = ((R_SCI0_Type *) ( (axis_num == 1) ? R_SCI3_BASE : R_SCI2_BASE ) );

    /* SCIx通道 */
    uint32_t channel = (axis_num == 1) ? 3UL : 2UL;

    /* Cancel SCI0 module stop state */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCI, channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* 禁止中断 */
    R_BSP_IrqDisable( ((channel == 3) ? VECTOR_NUMBER_SCI3_ERI : VECTOR_NUMBER_SCI2_ERI) );
    R_BSP_IrqDisable( ((channel == 3) ? VECTOR_NUMBER_SCI3_RXI : VECTOR_NUMBER_SCI2_RXI) );
    R_BSP_IrqDisable( ((channel == 3) ? VECTOR_NUMBER_SCI3_TXI : VECTOR_NUMBER_SCI2_TXI) );
    R_BSP_IrqDisable( ((channel == 3) ? VECTOR_NUMBER_SCI3_TEI : VECTOR_NUMBER_SCI2_TEI) );

    /* Clear transmit/receive enable bits */
    regBase->CCR0_b.TE = 0U;
    regBase->CCR0_b.RE = 0U;

    /* CCR0默认值 */
    regBase->CCR0 = 0x00000000U;

    /* Reset transmit/receive FIFO data register operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* Read and clear status flags */
    regBase->CFCLR = 0UL;
    regBase->FFCLR = 0UL;

    /* Set transmission/reception format */

    regBase->CCR1 = 0x00000000;
    /* TXD引脚在TE为0时的电平，0-低电平，1-高电平(CCR1.bit12是取反意思) */
    regBase->CCR1_b.SPB2DT = 1;
    /* TXD引脚在TE为0时的输出是否受SPB2DT控制，1-使能控制 */
    regBase->CCR1_b.SPB2IO = 1;
    /* TXD输出引脚电平取反 */
    regBase->CCR1_b.TINV = 0;
    /* RXD输入引脚电平取反 */
    regBase->CCR1_b.RINV = 0;
    /* RXD输入数字滤波时钟选择 */
    regBase->CCR1_b.NFCS = 0;
    /* RXD输入数字滤波使能，1-使能 */
    regBase->CCR1_b.NFEN = 0;

    /* 复位默认值 */
    regBase->CCR2 = 0xFF00FF04;

    /* 位速率调制功能/波特率小数分频功能使能，1-使能 */
    regBase->CCR2_b.BRME = 1;
    /* 0-禁止外部时钟 */
    regBase->CCR2_b.ABCSE = 0;
    /* 波特率寄存器设置, 输入时钟为96MHz
     * PCLKSCIx = 96MHz
     * BBR = ( (PCLKSCIx * 10000000) / (64 * 2^(2*n-1) * B) ) - 1
     * BBR  : 寄存器设定值
     * B    : 波特率值
     * n    : 时钟源分频设定值
     * 计算公式基于一个bit采样时钟16个，单速率模式下
     */
    /* 波特率生成双速率模式使能，1-使能 */
    regBase->CCR2_b.BGDM = 1;
    /* 0-16个时钟发送一个bit，1-8个时钟发送一个bit */
    regBase->CCR2_b.ABCS = 1;
    /* 波特率计数器 */
    regBase->CCR2_b.BRR = 2;
    /* 输入时钟源分频选择，0-不分频，1-4分频，2-16分频，3-64分频 */
    regBase->CCR2_b.CKS = 0;
    /* 调制占空比设置 */
    regBase->CCR2_b.MDDR = 160;

    /* 复位默认值 */
    regBase->CCR3 = 0x00001203;
    /* 字符长度，0/1-9bit，2-8bit，3-7bit */
    regBase->CCR3_b.CHR = 2;
    /* 0-MSB先发送，1-LSB先发送 */
    regBase->CCR3_b.LSBF = 1;
    /* 1-接收/发送数据反相使能 */
    regBase->CCR3_b.SINV = 0;
    /* 0-低电平作为起始位检测，1-下降沿作为起始位检测 */
    regBase->CCR3_b.RXDESEL = 1;
    /* 0-串口通讯模式 */
    regBase->CCR3_b.MOD = 0;
    /* 1-FIFO功能使能 */
    regBase->CCR3_b.FM = 1;


    /* 1-RS485控制引脚驱动使能 */

    /* 测试发现起始位延时设定值和手册描述不符 */
    /* 停止位延时和手册一致，在目前的波特率设定下，1-50ns，5-250ns延迟，每个bit需要8个时钟周期，每个时钟周期是50ns的，延迟时间按照50ns为单位 */
    /* 起始位设定测试 1-1940ns，2-之后的数值也是按照50ns单位计算，但是会有很大的抖动，测试设定值2时，最短的延迟是100ns，最长延迟有450ns
     * 测试设定值3时，最短的延迟是150ns，最长延迟有500ns */
    regBase->DCR_b.DEPOL = 0;   // 极性选择 0-发送数据时低电平
    regBase->DCR_b.DEAST = 2;   // DE输出有效到数据起始位之间的延迟时间
    regBase->DCR_b.DENGT = 6;   // 数据停止位到DE无效之间的延迟时间
    regBase->CCR3_b.DEN = 1;    // DE端口控制功能使能

    /* 奇偶校验使能，1-使能*/
    regBase->CCR1_b.PE = 0;
    /* 0-偶校验(enen)，1-奇校验(odd) */
    regBase->CCR1_b.PM = 0;
    /* 0-1位停止位，1-2位停止位 */
    regBase->CCR3_b.STP = 0;

    /* 复位默认值 */
    regBase->CCR4 = 0x00000000;

    /* Wait for at least 1-bit interval */
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

    /* Set FIFO trigger conditions */

    /* FIFO控制寄存器复位默认值 */
    regBase->FCR = 0x00000000;
    /* FIFO发送缓存触发中断设定值 */
    regBase->FCR_b.TTRG = 0;
    /* FIFO接收缓存触发中断设定值 */
    regBase->FCR_b.RTRG = 0;

    /* Disable transmit/receive FIFO data register reset operation */
    regBase->FCR_b.TFRST = 1U;
    regBase->FCR_b.RFRST = 1U;

    /* 清除标志位 */
    regBase->CFCLR = 0xBD070010;
    regBase->FFCLR = 0x00000001;

    /* 清除挂起中断 */
    R_BSP_IrqClearPending( ((channel == 3) ? VECTOR_NUMBER_SCI3_ERI : VECTOR_NUMBER_SCI2_ERI) );
    R_BSP_IrqClearPending( ((channel == 3) ? VECTOR_NUMBER_SCI3_RXI : VECTOR_NUMBER_SCI2_RXI) );
    R_BSP_IrqClearPending( ((channel == 3) ? VECTOR_NUMBER_SCI3_TXI : VECTOR_NUMBER_SCI2_TXI) );
    R_BSP_IrqClearPending( ((channel == 3) ? VECTOR_NUMBER_SCI3_TEI : VECTOR_NUMBER_SCI2_TEI) );

    /* 仅配置中断优先级 */
    R_BSP_IrqCfg( ((channel == 3) ? VECTOR_NUMBER_SCI3_ERI : VECTOR_NUMBER_SCI2_ERI), 12UL, (NULL) );
    R_BSP_IrqCfg( ((channel == 3) ? VECTOR_NUMBER_SCI3_RXI : VECTOR_NUMBER_SCI2_RXI), 12UL, (NULL) );
    R_BSP_IrqCfg( ((channel == 3) ? VECTOR_NUMBER_SCI3_TXI : VECTOR_NUMBER_SCI2_TXI), 12UL, (NULL) );
    R_BSP_IrqCfg( ((channel == 3) ? VECTOR_NUMBER_SCI3_TEI : VECTOR_NUMBER_SCI2_TEI), 12UL, (NULL) );

    /* 使能GIC级中断 */
//    R_BSP_IrqEnable( ((channel == 3) ? VECTOR_NUMBER_SCI3_ERI : VECTOR_NUMBER_SCI2_ERI) );
//    R_BSP_IrqEnable( ((channel == 3) ? VECTOR_NUMBER_SCI3_RXI : VECTOR_NUMBER_SCI2_RXI) );
//    R_BSP_IrqEnable( ((channel == 3) ? VECTOR_NUMBER_SCI3_TXI : VECTOR_NUMBER_SCI2_TXI) );
//    R_BSP_IrqEnable( ((channel == 3) ? VECTOR_NUMBER_SCI3_TEI : VECTOR_NUMBER_SCI2_TEI) );

    /* 使能外设级中断 */
//    regBase->CCR0_b.RIE = 1U;    /* 接收中断 */
//    regBase->CCR0_b.TIE = 1U;    /* 发送空中断 */
//    regBase->CCR0_b.TEIE = 1U;   /* 发送结束中断 */

    /* 使能接收及使能发送 */
    regBase->CCR0_b.TE = 1U;
    regBase->CCR0_b.RE = 1U;
    while(1U != regBase->CCR0_b.TE)
    {
        ;
    }

}



static void bsp_pwm_mtu34_init(uint32_t period, uint32_t dead)
{
    /* MTU3定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零禁止 */
    R_MTU3->TCR = 0x00;
    R_MTU3->TCR2 = 0x00;

    /* MTU4定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零禁止 */
    R_MTU4->TCR = 0x00;
    R_MTU4->TCR2 = 0x00;

    /* 死区最小设定值是1，即使不使用死区功能 */
    if (dead < 1)
    {
        dead = 1;
    }

    /* MTU3定时器计数器起始值必须设置为死区时间设定值，如果禁用死区，其值应为1, MTU4一定要清零 */
    R_MTU3->TCNT = dead;
    R_MTU4->TCNT = 0x0000;

    /* 定时器MTU3、MTU4同步设置/清零功能禁用 */
    R_MTU->TSYRA &= 0xC0;

    /* 定时器通用寄存器(用于设定通道比较值) */
    R_MTU3->TGRB = (uint16_t)((period >> 1) + dead / 2);    /* U-phase output compare register */
    R_MTU3->TGRD = (uint16_t)((period >> 1) + dead / 2);    /* U-phase output buffer register */
    R_MTU4->TGRA = (uint16_t)((period >> 1) + dead / 2);    /* V-phase output compare register */
    R_MTU4->TGRC = (uint16_t)((period >> 1) + dead / 2);    /* V-phase output buffer register */
    R_MTU4->TGRB = (uint16_t)((period >> 1) + dead / 2);    /* W-phase output compare register */
    R_MTU4->TGRD = (uint16_t)((period >> 1) + dead / 2);    /* W-phase output buffer register */

    /* TDDRA死区时间设定寄存器，MTU3/MTU4使用 */
    R_MTU->TDDRA = dead;

    /* TCDRA是MTU4定时器周期设定值 */
    R_MTU->TCDRA = period;
    /* TCBRA是MTU4定时器周期设定值TCDRA缓存 */
    R_MTU->TCBRA = period;

    /* MTU3定时器周期值，一定是周期设定值+死区时间(死区禁用时为1) */
    R_MTU3->TGRA = (uint16_t)(period + dead);
    /* TGRC是TGRA的缓存寄存器 */
    R_MTU3->TGRC = (uint16_t)(period + dead);

    /* 设置PWM信号输出的电平逻辑 */

    /* MTU3/MTU4 */

    /* TOCL是写使能，0-写访问使能 */
    R_MTU->TOCR1A_b.TOCL = 0;
    /* PWM同步输出禁止 0-禁止 */
    R_MTU->TOCR1A_b.PSYE = 0;
    /* 选择TOCR1作为TOC的控制 */
    R_MTU->TOCR1A_b.TOCS = 0;
    /* 在互补输出模式及同步复位模式有效 */
    /* 输给IPM模块的隔离光耦是，高电平输入时，输出的是低电平；低电平输入时，输出的事高电平 */
    /* 正极，上升计数比较匹配输出低电平，下降比较匹配输出高电平 */
    /* 负极，上升计数比较匹配输出高电平，下降比较匹配输出低电平 */
    R_MTU->TOCR1A_b.OLSP = 0;   /* Initial output:H, Active level:L */
    R_MTU->TOCR1A_b.OLSN = 0;   /* Initial output:H, Active level:L */

    /* 0x0E: 在计数0时进行映射传输 0x0D: 在周期值时进行映射传输 0x0F: 在周期和0时都进行映射传输*/
    R_MTU3->TMDR1_b.MD = 0x0F;
    /* TGRC和TGRA同时使用，TGRC作为TGRA的映射寄存器 1-使能映射 */
    R_MTU3->TMDR1_b.BFA = 1;
    /* TGRD和TGRB同时使用，TGRD作为TGRB的映射寄存器 1-使能映射 */
    R_MTU3->TMDR1_b.BFB = 1;

    /* 双缓冲模式禁止 */
    R_MTU->TMDR2A_b.DRS = 0x00;

    /* MTU4计数器下溢时触发ADC转换请求，还有一个计数器和TGA比较匹配可以触发ADC转换 */
    R_MTU4->TIER_b.TTGE2 = 1;
    R_MTU7->TIER_b.TTGE2 = 1;

    /* 在MTU3-CH3计数值和TGA(周期值)匹配时产生中断 */
    R_MTU3->TIER_b.TGIEA = 1;
    /* 在MTU4下溢时产生中断 */
    R_MTU4->TIER_b.TCIEV = 1;


    /* GIC级中断配置 - MTU0产生中断 */

    /* MTU3周期中断(PWM波峰比较中断) */
    R_BSP_IrqDisable(VECTOR_NUMBER_TGIA3);
    R_BSP_IrqCfg(VECTOR_NUMBER_TGIA3, 5UL, (NULL));
    //R_BSP_IrqEnable(VECTOR_NUMBER_TGIA3);

    /* MTU4下溢中断(PWM波谷中断) */
    R_BSP_IrqDisable(VECTOR_NUMBER_TCIV4);
    R_BSP_IrqCfg(VECTOR_NUMBER_TCIV4, 5UL, (NULL));
    //R_BSP_IrqEnable(VECTOR_NUMBER_TCIV4);
}

static void bsp_pwm_mtu67_init(uint32_t period, uint32_t dead)
{
    /* MTU6定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零禁止 */
    R_MTU6->TCR = 0x00;
    R_MTU6->TCR2 = 0x00;

    /* MTU7定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零禁止 */
    R_MTU7->TCR = 0x00;
    R_MTU7->TCR2 = 0x00;

    /* 死区最小设定值是1，即使不使用死区功能 */
    if (dead < 1)
    {
        dead = 1;
    }

    /* MTU3定时器计数器起始值必须设置为死区时间设定值，如果禁用死区，其值应为1, MTU4一定要清零 */
    R_MTU6->TCNT = dead;
    R_MTU7->TCNT = 0x0000;

    /* 定时器MTU6、MTU7同步设置/清零功能禁用 */
    R_MTU->TSYRB &= 0xC0;

    /* 定时器通用寄存器(用于设定通道比较值) */
    R_MTU6->TGRB = (uint16_t)((period >> 1) + dead / 2);    /* U-phase output compare register */
    R_MTU6->TGRD = (uint16_t)((period >> 1) + dead / 2);    /* U-phase output buffer register */
    R_MTU7->TGRA = (uint16_t)((period >> 1) + dead / 2);    /* V-phase output compare register */
    R_MTU7->TGRC = (uint16_t)((period >> 1) + dead / 2);    /* V-phase output buffer register */
    R_MTU7->TGRB = (uint16_t)((period >> 1) + dead / 2);    /* W-phase output compare register */
    R_MTU7->TGRD = (uint16_t)((period >> 1) + dead / 2);    /* W-phase output buffer register */

    /* TDDRA死区时间设定寄存器，MTU6/MTU7使用 */
    R_MTU->TDDRB = dead;

    /* TCDRA是MTU7定时器周期设定值 */
    R_MTU->TCDRB = period;
    /* TCBRA是MTU7定时器周期设定值TCDRA缓存 */
    R_MTU->TCBRB = period;

    /* MTU6定时器周期值，一定是周期设定值+死区时间(死区禁用时为1) */
    R_MTU6->TGRA = (uint16_t)(period + dead);
    /* TGRC是TGRA的缓存寄存器 */
    R_MTU6->TGRC = (uint16_t)(period + dead);


    /* 设置PWM信号输出的电平逻辑 */

    /* TOCL是写使能，0-写访问使能 */
    R_MTU->TOCR1B_b.TOCL = 0;
    /* PWM同步输出禁止 0-禁止 */
    R_MTU->TOCR1B_b.PSYE = 0;
    /* 选择TOCR1作为TOC的控制 */
    R_MTU->TOCR1B_b.TOCS = 0;
    /* 在互补输出模式及同步复位模式有效 */
    /* 输给IPM模块的隔离光耦是，高电平输入时，输出的是低电平；低电平输入时，输出的事高电平 */
    /* 正极，上升计数比较匹配输出低电平，下降比较匹配输出高电平 */
    /* 负极，上升计数比较匹配输出高电平，下降比较匹配输出低电平 */
    R_MTU->TOCR1B_b.OLSP = 0;   /* Initial output:H, Active level:L */
    R_MTU->TOCR1B_b.OLSN = 0;   /* Initial output:H, Active level:L */


    /* 0x0E: 在计数0时进行映射传输 0x0D: 在周期值时进行映射传输 0x0F: 在周期和0时都进行映射传输*/
    R_MTU6->TMDR1_b.MD = 0x0F;
    /* TGRC和TGRA同时使用，TGRC作为TGRA的映射寄存器 1-使能映射 */
    R_MTU6->TMDR1_b.BFA = 1;
    /* TGRD和TGRB同时使用，TGRD作为TGRB的映射寄存器 1-使能映射 */
    R_MTU6->TMDR1_b.BFB = 1;

    /* 双缓冲模式禁止 */
    R_MTU->TMDR2B_b.DRS = 0x00;

    /* MTU4计数器下溢时触发ADC转换请求，还有一个计数器和TGA比较匹配可以触发ADC转换 */
    R_MTU7->TIER_b.TTGE2 = 1;

    /* 在MTU3-CH3计数值和TGA(周期值)匹配时产生中断 */
    R_MTU6->TIER_b.TGIEA = 1;
    /* 在MTU4下溢时产生中断 */
    R_MTU7->TIER_b.TCIEV = 1;
}

static void bsp_pwm_mtu0_init(uint32_t mtu0_prd, uint32_t mtu0_cmp_init, uint32_t mtu0_cmp_cap)
{
    /*
     * TGRE的值为周期值、计数清零源
     * TGRF作为TGRE的缓存值，在周期比较时进行映射传输
     *
     * TRGA作为触发delta-sigma采样计数器清零
     *
     * TGRC作为触发delta-sigma采样结果捕获
     *
     * TGRB和TGRD暂时保留
     *
     */

    /* 停止定时器MTU0 */
    R_MTU->TSTRA_b.CST0 = 0;

    /* MTU0定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零在TGRB比较匹配时 */
    R_MTU0->TCR_b.TPSC = 0x00;
    R_MTU0->TCR_b.CKEG = 0x00;
    R_MTU0->TCR_b.CCLR = 0x05;
    R_MTU0->TCR2 = 0x00;

    /* 缓存传输模式：0-在比较匹配时进行映射传输; 1-在TCN被清零时进行映射传输(在互补输出时不生效) */
    R_MTU0->TBTM_b.TTSA = 0x00;
    R_MTU0->TBTM_b.TTSB = 0x00;
    R_MTU0->TBTM_b.TTSE = 0x00;

    /* 定时器计数器设置为0 */
    R_MTU0->TCNT = 0x0000;

    /* 定时器通用寄存器(用于设定通道比较值) */

    /* 周期设定值 */
    R_MTU0->TGRE = (uint16_t)(mtu0_prd - 1);
    R_MTU0->TGRF = (uint16_t)(mtu0_prd - 1);

    /* 触发对delta-sigma采样计数器进行清零 */
    R_MTU0->TGRA = (uint16_t)(mtu0_cmp_init);

    /* 触发对delta-sigma采样结果值进行捕获，同时产生中断 */
    R_MTU0->TGRC = (uint16_t)(mtu0_cmp_cap);

    /* 0x02: PWM模式1 */
    R_MTU0->TMDR1_b.MD = 0x2;
    /* TGRC和TGRA同时使用，TGRC作为TGRA的映射寄存器 1-使能映射， 0-禁止映射模式 */
    R_MTU0->TMDR1_b.BFA = 0;
    /* TGRD和TGRB同时使用，TGRD作为TGRB的映射寄存器 1-使能映射， 0-禁止映射模式 */
    R_MTU0->TMDR1_b.BFB = 0;
    /* TGRE和TGRF同时使用，TGRD作为TGRB的映射寄存器 1-使能映射， 0-禁止映射模式 */
    R_MTU0->TMDR1_b.BFE = 1;

    /* 计数值和TGB匹配时产生中断 */
    R_MTU0->TIER_b.TGIEB = 1;
}

static void bsp_pwm_mtu8_init(void)
{
    /* 停止定时器MTU8 */
    R_MTU->TSTRA_b.CST8 = 0;

    /* MTU0定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零被禁止 */
    R_MTU8->TCR_b.TPSC = 0x00;
    R_MTU8->TCR_b.CKEG = 0x00;
    R_MTU8->TCR_b.CCLR = 0x00;
    R_MTU8->TCR2 = 0x00;

    /* 定时器计数器设置为0 */
    R_MTU8->TCNT = 0x0000;

    /* 0x00: 自由运行模式(Normal mode) */
    R_MTU8->TMDR1_b.MD = 0x0;
    /* TGRC和TGRA同时使用，TGRC作为TGRA的映射寄存器 1-使能映射， 0-禁止映射模式 */
    R_MTU8->TMDR1_b.BFA = 0;
    /* TGRD和TGRB同时使用，TGRD作为TGRB的映射寄存器 1-使能映射， 0-禁止映射模式 */
    R_MTU8->TMDR1_b.BFB = 0;

    /* 配置引脚捕获引脚功能 0-禁止输出/捕获功能，8-上升沿捕获，9-下降沿捕获，10-上升/下降沿均捕获 */
    R_MTU8->TIORH_b.IOA = 8;
    R_MTU8->TIORH_b.IOB = 0;

    /* 启动定时器MTU8 */
    R_MTU->TSTRA_b.CST8 = 1;
}
/**
 *
 * @param mode      - 计数模式 0-正交计数，1-脉冲+方向(上升沿)，2-脉冲+方向(下降沿)，3-双脉冲(上升沿计数)，4-双脉冲(下降沿计数)
 * @param period    - 计数的最大值
 */
static void pwm_mtu1_init(uint8_t mode, uint32_t period)
{

    /* 停止定时器MTU0 */
    R_MTU->TSTRA_b.CST1 = 0;

    /* MTU0定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零在TGRA比较匹配时 */
    R_MTU1->TCR_b.TPSC = 0x00;      /* 计数模式时，设定值无效 */
    R_MTU1->TCR_b.CKEG = 0x00;      /* 计数模式时，设定值无效 */
    R_MTU1->TCR_b.CCLR = 0x01;      /* 0-禁止清零， 1-TGRA比较清零，2-TRGB比较清零 */
    R_MTU1->TCR2 = 0x00;

    /* 定时器计数器设置为0 */
    R_MTU1->TCNT = 0x0000;

    /* 定时器通用寄存器(用于设定通道比较值) */

    /* 周期设定值 */
    R_MTU1->TGRA = (uint16_t)(period - 1);

    /* MTU1/MTU2级联功能禁止 */
    R_MTU1->TMDR3_b.LWA = 0;
    /* MTU2使用MTCLKC和MTCLKD两个引脚作为计数引脚 */
    R_MTU1->TMDR3_b.PHCKSEL = 1;

    /* 计数模式设置 */

    if (mode == 0)
    {
        /* 脉冲+方向(上升沿)：计数模式2 */
        R_MTU1->TMDR1_b.MD = 0x5;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU1->TCR2_b.PCB = 1;
    }
    else if (mode == 0)
    {
        /* 脉冲+方向(下降沿)：计数模式2 */
        R_MTU1->TMDR1_b.MD = 0x5;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU1->TCR2_b.PCB = 0;
    }
    else if (mode == 0)
    {
        /* 双脉冲(上升沿计数)：计数模式3 */
        R_MTU1->TMDR1_b.MD = 0x6;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU1->TCR2_b.PCB = 1;
    }
    else if (mode == 0)
    {
        /* 双脉冲(下降沿计数)：计数模式3 */
        R_MTU1->TMDR1_b.MD = 0x6;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU1->TCR2_b.PCB = 0;
    }
    else
    {
        /* 正交计数模式：计数模式1 */
        R_MTU1->TMDR1_b.MD = 0x4;
    }

    /* 启动计数器 */
    R_MTU->TSTRA_b.CST1 = 1;
}


/**
 *
 * @param mode      - 计数模式 0-正交计数，1-脉冲+方向(上升沿)，2-脉冲+方向(下降沿)，3-双脉冲(上升沿计数)，4-双脉冲(下降沿计数)
 * @param period    - 计数的最大值
 */
static void pwm_mtu2_init(uint8_t mode, uint32_t period)
{

    /* 停止定时器MTU0 */
    R_MTU->TSTRA_b.CST2 = 0;

    /* MTU0定时器计数时钟为 PCLKH/1, 计数边沿为时钟的上升沿, 定时器计数器TCNT清零在TGRA比较匹配时 */
    R_MTU2->TCR_b.TPSC = 0x00;      /* 计数模式时，设定值无效 */
    R_MTU2->TCR_b.CKEG = 0x00;      /* 计数模式时，设定值无效 */
    R_MTU2->TCR_b.CCLR = 0x01;      /* 0-禁止清零， 1-TGRA比较清零，2-TRGB比较清零 */
    R_MTU2->TCR2 = 0x00;

    /* 定时器计数器设置为0 */
    R_MTU2->TCNT = 0x0000;

    /* 定时器通用寄存器(用于设定通道比较值) */

    /* 周期设定值 */
    R_MTU2->TGRA = (uint16_t)(period - 1);

    /* MTU1/MTU2级联功能禁止 */
    R_MTU1->TMDR3_b.LWA = 0;
    /* MTU2使用MTCLKC和MTCLKD两个引脚作为计数引脚 */
    R_MTU1->TMDR3_b.PHCKSEL = 1;

    /* 计数模式设置 */

    if (mode == 0)
    {
        /* 脉冲+方向(上升沿)：计数模式2 */
        R_MTU2->TMDR1_b.MD = 0x5;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU2->TCR2_b.PCB = 1;
    }
    else if (mode == 0)
    {
        /* 脉冲+方向(下降沿)：计数模式2 */
        R_MTU2->TMDR1_b.MD = 0x5;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU2->TCR2_b.PCB = 0;
    }
    else if (mode == 0)
    {
        /* 双脉冲(上升沿计数)：计数模式3 */
        R_MTU2->TMDR1_b.MD = 0x6;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU2->TCR2_b.PCB = 1;
    }
    else if (mode == 0)
    {
        /* 双脉冲(下降沿计数)：计数模式3 */
        R_MTU2->TMDR1_b.MD = 0x6;
        /* 计数模式2下，0-下降沿计数，1-上升沿计数，2/3-上升及下降沿均计数 */
        R_MTU2->TCR2_b.PCB = 0;
    }
    else
    {
        /* 正交计数模式：计数模式1 */
        R_MTU2->TMDR1_b.MD = 0x4;
    }

    /* 启动计数器 */
    R_MTU->TSTRA_b.CST2 = 1;
}


static void bsp_poe_init(void)
{
    /* POE有些寄存器只能写入一次，再次写入必须复位 */
    R_POE3_Type POE3;

    /* 1轴IPM过流输入引脚是P01_4, 对应的POE功能引脚是POE0# */
    /* 2轴IPM过流输入引脚是P22_1, 对应的POE功能引脚是POE4# */
    /* 母线过流输入引脚是P14_5, 对应的POE功能引脚是POE8# */

    /* 1轴伺服PWM引脚
     * PWMU+ - P00_6
     * PWMU- - P01_1
     * PWMV+ - P00_7
     * PWMV- - P01_0
     * PWMW+ - P01_2
     * PWMW- - P01_3
     */

    /* 选择需要将哪些引脚设置为高阻态 */
    POE3.M3SELR = R_POE3->M3SELR;
    /* 0-P17_6 / 1-P00_6 / 2-P03_6 */
    POE3.M3SELR_b.M3BSEL = 0x01;
    /* 0-P18_1 / 1-P01_1 / 2-P04_0 */
    POE3.M3SELR_b.M3DSEL = 0x01;
    R_POE3->M3SELR = POE3.M3SELR;

    POE3.M4SELR1 = R_POE3->M4SELR1;
    /* 0-P17_7 / 1-P00_7 / 2-P05_0 / P18_0 */
    POE3.M4SELR1_b.M4ASEL = 0x01;
    /* 0-P18_0 / 1-P01_0 / 2-P05_2 / P17_7 */
    POE3.M4SELR1_b.M4CSEL = 0x01;
    R_POE3->M4SELR1 = POE3.M4SELR1;

    POE3.M4SELR2 = R_POE3->M4SELR2;
    /* 0-P18_2 / 1-P01_2 / 2-P05_1 / P18_3 */
    POE3.M4SELR2_b.M4BSEL = 0x01;
    /* 0-P18_3 / 1-P01_3 / 2-P05_3 / P18_2 */
    POE3.M4SELR2_b.M4DSEL = 0x01;
    R_POE3->M4SELR2 = POE3.M4SELR2;

    /* 2轴伺服PWM引脚
     * PWMU+ - P21_2
     * PWMU- - P21_4
     * PWMV+ - P21_5
     * PWMV- - P21_7
     * PWMW+ - P21_6
     * PWMW- - P22_0
     */

    /* 选择需要将哪些引脚设置为高阻态 */
    POE3.M6SELR = R_POE3->M6SELR;
    /* 1-P21_2 / 2-P08_5 / 其他-禁止 */
    POE3.M6SELR_b.M6BSEL = 0x01;
    /* 1-P21_4 / 2-P08_7 / 其他-禁止 */
    POE3.M6SELR_b.M6DSEL = 0x01;
    R_POE3->M6SELR = POE3.M6SELR;

    POE3.M7SELR1 = R_POE3->M7SELR1;
    /* 1-P21_5 / 2-P09_0 / 其他-禁止 */
    POE3.M7SELR1_b.M7ASEL = 0x01;
    /* 1-P21_7 / 2-P09_2 / 其他-禁止 */
    POE3.M7SELR1_b.M7CSEL = 0x01;
    R_POE3->M7SELR1 = POE3.M7SELR1;

    POE3.M7SELR2 = R_POE3->M7SELR2;
    /* 1-P21_6 / 2-P09_1 / 其他-禁止 */
    POE3.M7SELR2_b.M7BSEL = 0x01;
    /* 1-P22_0 / 2-P09_3 / 其他-禁止 */
    POE3.M7SELR2_b.M7DSEL = 0x01;
    R_POE3->M7SELR2 = POE3.M7SELR2;

    /* 高阻态输出使能，只有这个使能了，才能够根据条件输出高阻态，这是必须条件 */
    POE3.POECR2 = R_POE3->POECR2;
    POE3.POECR2_b.MTU4BDZE = 1;
    POE3.POECR2_b.MTU4ACZE = 1;
    POE3.POECR2_b.MTU3BDZE = 1;
    POE3.POECR2_b.MTU7BDZE = 1;
    POE3.POECR2_b.MTU7ACZE = 1;
    POE3.POECR2_b.MTU6BDZE = 1;
    R_POE3->POECR2 = POE3.POECR2;

    /* 添加POE8#标志到MTU3/MTU4输出高阻态控制条件 */
    /* 添加POE8#标志到MTU6/MTU7输出高阻态控制条件 */
    POE3.POECR4 = R_POE3->POECR4;
    POE3.POECR4_b.IC3ADDMT34ZE = 1;
    POE3.POECR4_b.IC3ADDMT67ZE = 1;
    R_POE3->POECR4 = POE3.POECR4;

    /* 配置POE1模式 */
    POE3.ICSR1 = R_POE3->ICSR1;
    /* 0-下降沿检测， 1-16次采样在PCLKH/8时钟，2-16次采样在PCLKH/16时钟， 3-16次采样在PCLKH/128时钟*/
    POE3.ICSR1_b.POE0M = 1;
    /* 1-使能中断产生 */
    POE3.ICSR1_b.PIE1 = 1;
    R_POE3->ICSR1 = POE3.ICSR1;

    /* 配置POE4模式 */
    POE3.ICSR2 = R_POE3->ICSR2;
    /* 0-下降沿检测， 1-16次采样在PCLKH/8时钟，2-16次采样在PCLKH/16时钟， 3-16次采样在PCLKH/128时钟*/
    POE3.ICSR2_b.POE4M = 1;
    /* 1-使能中断产生 */
    POE3.ICSR2_b.PIE2 = 1;
    R_POE3->ICSR2 = POE3.ICSR2;

    /* 配置POE8模式 */
    POE3.ICSR3 = R_POE3->ICSR3;
    /* 0-下降沿检测， 1-16次采样在PCLKH/8时钟，2-16次采样在PCLKH/16时钟， 3-16次采样在PCLKH/128时钟*/
    POE3.ICSR3_b.POE8M = 1;
    /* 1-使能中断产生 */
    POE3.ICSR3_b.PIE3 = 1;
    R_POE3->ICSR3 = POE3.ICSR3;

    /* 配置MTU3/MTU4 PWM输出短路高阻态检测/使能 */

    /* 配置PWM输出引脚短路功能使能/中断产生 */
    POE3.OCSR1 = R_POE3->OCSR1;
    /* 1-使能输出短路时中断产生 */
    POE3.OCSR1_b.OIE1 = 0;
    /* 1-使能输出短路时控制高阻态功能 */
    POE3.OCSR1_b.OCE1 = 0;
    R_POE3->OCSR1 = POE3.OCSR1;


    /* 配置MTU6/MTU7 PWM输出短路高阻态检测/使能 */

    /* 配置PWM输出引脚短路功能使能/中断产生 */
    POE3.OCSR2 = R_POE3->OCSR2;
    /* 1-使能输出短路时中断产生 */
    POE3.OCSR2_b.OIE2 = 0;
    /* 1-使能输出短路时控制高阻态功能 */
    POE3.OCSR2_b.OCE2 = 0;
    R_POE3->OCSR2 = POE3.OCSR2;

    /* 配置PWM输出引脚短路检测电平 */
    POE3.ALR1 = R_POE3->ALR1;
    /* 0-PWM有效电平是低电平， 1-PWM有效电平是高电平 */
    POE3.ALR1_b.OLSG0A = 1;     // MTIOC3B
    POE3.ALR1_b.OLSG0B = 1;     // MTIOC3D
    POE3.ALR1_b.OLSG1A = 1;     // MTIOC4A
    POE3.ALR1_b.OLSG1B = 1;     // MTIOC4C
    POE3.ALR1_b.OLSG2A = 1;     // MTIOC4B
    POE3.ALR1_b.OLSG2B = 1;     // MTIOC4D
    /* 1-使能上述有效电平设置值， 0-禁止上述有效电平设置值(禁止后由MTU.MOCR1A或者MTU.MOCR1B中的有效电平设定) */
    POE3.ALR1_b.OLSEN = 0;
    R_POE3->ALR1 = POE3.ALR1;
}

void bsp_dsmif_init(void)
{
    g_dsmif0.p_api->open(g_dsmif0.p_ctrl, g_dsmif0.p_cfg);
    g_dsmif1.p_api->open(g_dsmif1.p_ctrl, g_dsmif1.p_cfg);

    g_dsmif0.p_api->scanStart(g_dsmif0.p_ctrl);
    g_dsmif1.p_api->scanStart(g_dsmif1.p_ctrl);
}

/**
 * PWM初始化
 * @param mtu0_prd  - mtu0周期值(周期时的计数个数，增计数模式，程序内部自动对该值进行了减1处理)
 * @param mtu0_cmp_init - mtu0的TGRA寄存器设定值，即用来触发delta-sigma采样计数器清零
 * @param mtu0_cmp_cap - mtu0的TGRC寄存器设定值，即用来触发delt-sigma采样结果捕获
 * @param mtu3_prd  - mtu3/mtu6周期值(波峰时的计数个数)
 * @param dead      - 死区设定值(计数个数)
 */
void bsp_pwm_init(uint32_t mtu0_prd, uint32_t mtu0_cmp_init, uint32_t mtu0_cmp_cap, uint32_t mtu3_prd, uint32_t dead)
{
    volatile unsigned long dummy;

    /* Cancel MTU stop state in LPC */
    dummy = 1u;
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_MTU3, dummy);
    dummy = BSP_MSTP_REG_FSP_IP_MTU3(dummy);
    /* Dummy-read for the module-stop state(2) */
    dummy = R_MTU5->TSTR;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    for (dummy = 0; dummy < 5; dummy++)
    {
        __asm volatile ("nop");
    }

    /* TRWERA_b控制MTU3/MTU4定时器相关受写保护功能保护的寄存器 */
    R_MTU->TRWERA_b.RWE = 1U;
    /* TRWERB_b控制MTU6/MTU7定时器相关受写保护功能保护的寄存器 */
    R_MTU->TRWERB_b.RWE = 1U;

    /* 停止MTU通道 */
    R_MTU->TSTRA = 0x00;
    R_MTU5->TSTR = 0x00;
    R_MTU->TSTRB = 0x00;

    /* 1轴PWM输出初始化 */
    bsp_pwm_mtu34_init(mtu3_prd, dead);

    /* 2轴PWM输出初始化 */
    bsp_pwm_mtu67_init(mtu3_prd, dead);

    /* MTU0初始化 */
    bsp_pwm_mtu0_init(mtu0_prd, mtu0_cmp_init, mtu0_cmp_cap);

    /* MTU8捕获用 */
    bsp_pwm_mtu8_init();

    /* MTU1用于脉冲计数 */
    pwm_mtu1_init(1, 0xFFFF);

    /* MTU2用于脉冲计数 */
    pwm_mtu2_init(0, 10000UL);

    /* POE初始化 */
    bsp_poe_init();

    /* Delta-Sigma采样初始化 */
    bsp_dsmif_init();

    /* 配置事件连接器用于同步触发电流采样 */
    R_ELC->ELC_SSEL_b[7].ELC_SEL0 = ELC_EVENT_TGIA0;    /* ADC1 A */
    R_ELC->ELC_SSEL_b[7].ELC_SEL2 = ELC_EVENT_TGIC0;    /* DSMIF0 CAP_TRG0(结果值捕获事件) */
    R_ELC->ELC_SSEL_b[9].ELC_SEL2 = ELC_EVENT_TGIA0;    /* DSMIF0 CDCNT_INT_TRG0(计数值清零事件) */
    R_ELC->ELC_SSEL_b[10].ELC_SEL2 = ELC_EVENT_TGIC0;   /* DSMIF1 CAP_TRG0(结果值捕获事件) */
    R_ELC->ELC_SSEL_b[12].ELC_SEL2 = ELC_EVENT_TGIA0;   /* DSMIF1 CDCNT_INT_TRG0(计数值清零事件) */

    /* GIC级中断配置 - MTU0产生中断(目前禁止了MTU3/MTU4中断生成) */

    /* MTU3周期中断(PWM波峰比较中断) */
    R_BSP_IrqDisable(VECTOR_NUMBER_TGIA3);
    R_BSP_IrqCfg(VECTOR_NUMBER_TGIA3, 5UL, (NULL));
    //R_BSP_IrqEnable(VECTOR_NUMBER_TGIA3);

    /* MTU4下溢中断(PWM波谷中断) */
    R_BSP_IrqDisable(VECTOR_NUMBER_TCIV4);
    R_BSP_IrqCfg(VECTOR_NUMBER_TCIV4, 5UL, (NULL));
    //R_BSP_IrqEnable(VECTOR_NUMBER_TCIV4);

    /* MTU0.TGRC产生中断 */
    R_BSP_IrqDisable(VECTOR_NUMBER_TGIC0);
    R_BSP_IrqCfg(VECTOR_NUMBER_TGIC0, 5UL, (NULL));
    R_BSP_IrqEnable(VECTOR_NUMBER_TGIC0);
}

void bsp_pwm_output_enable(void)
{
    /* MTU3/MTU4: PWM端口输出使能 */
    R_MTU->TOERA = 0xFF;

    /* MTU6/MTU7: PWM端口输出使能 */
    R_MTU->TOERB = 0xFF;
}

void bsp_pwm_output_disable(void)
{
    /* MTU3/MTU4: PWM端口输出禁止(PWM引脚设置为无效-具体引脚电平由其他寄存器设置) */
    R_MTU->TOERA = 0xC0;

    /* MTU6/MTU7: PWM端口输出禁止(PWM引脚设置为无效-具体引脚电平由其他寄存器设置) */
    R_MTU->TOERB = 0xC0;
}

void bsp_pwm_start(void)
{
    /* 同步启动MTU3/MTU4/MTU6/MTU7/MTU0定时器 */
    R_MTU->TCSYSTR |= 0x9B;
}

void bsp_pwm_stop(void)
{
    bsp_pwm_output_disable();

    R_MTU->TSTRA_b.CST0 = 0u;
    R_MTU->TSTRA_b.CST3 = 0u;
    R_MTU->TSTRA_b.CST4 = 0u;
    R_MTU->TSTRB_b.CST6 = 0u;
    R_MTU->TSTRB_b.CST7 = 0u;

    /* MTU3/MTU4/MTU6/MTU7在停止后自动设置了TCNT数值 */

    /* MTU0需要清零，防止再次启动时出现不同步 */
    R_MTU0->TCNT = 0x0000;
}



void sci_debug_dma_init(void)
{
    g_sci_debug_tx_dma.p_api->open(g_sci_debug_tx_dma.p_ctrl, g_sci_debug_tx_dma.p_cfg);
}

void sci_debug_tx(void)
{
    static uint8_t txBuf[2];
    static uint8_t length = 2;

    /* 目的地址： SCI串口的发送寄存器 */
    g_sci_debug_tx_dma.p_cfg->p_info->p_dest = (void *)(&R_SCI0->TDR);

    /* 源地址： 数据寄存器(由于需要手动发送一个字节启动DMA传输，因此源起始地址需要注意) */
    g_sci_debug_tx_dma.p_cfg->p_info->p_src = (void *)(&txBuf[1]);

    /* 发送数据字节长度(DMA传输的字节长度是总字节长度减1，第1个字节靠手动发送) */
    g_sci_debug_tx_dma.p_cfg->p_info->length = (length - 1);

    /* 重新配置后*/
    g_sci_debug_tx_dma.p_api->reconfigure(g_sci_debug_tx_dma.p_ctrl, g_sci_debug_tx_dma.p_cfg->p_info);

    /* 发送一个字节用来启动DMA传输(DMA请求为边沿有效) */
    R_SCI0->TDR_b.TDAT = txBuf[0];
}




/* 中断函数 */



/* 仅仅用于fsp生成中断宏定义 */
void null(void)
{

}


void sci_debug_tx_dma_transfer_end_isr(dmac_callback_args_t *p_args)
{
    /* 使能SCI串口的TEI中断 */
    R_SCI0->CCR0_b.TEIE = 1U;    /* 发送结束中断 */

    /* 在之后的TEI中断中，切换RS485芯片的控制引脚 */
}



