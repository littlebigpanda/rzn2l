/*
 * bsp_eeprom.c
 *
 *  Created on: Oct 25, 2023
 *      Author: xgj12
 */

#include "hal_data.h"
#include "bsp_eeprom.h"

#define CFG_IIC_EEPROM_BASE     R_IIC1_BASE


#define AT24C04                 1
#define AT24C08                 2
#define AT24C32                 3
#define AT24C128                4

#define EEPROM_TYPE             AT24C128     //EEPROM类型

#if (EEPROM_TYPE==AT24C04)
#define SLAVE_ADDRESS           0x0050  // 从机地址器件地址AT24C04---1010(A2)(A1)(P8)(读写位有硬件模块写入,不计入)
#define I2C_PAGE_SIZE           16      // EEPROM页大小AT24C04---最大一次页写入16个字节
#define I2C_PAGE_NUMBER         32      // EEPROM页个数AT24C04---32页*16字节/页=512字节
#elif (EEPROM_TYPE==AT24C08)
#define SLAVE_ADDRESS           0x0050  // 从机地址器件地址AT24C08---1010(A2)(P9)(P8)(读写位有硬件模块写入,不计入)
#define I2C_PAGE_SIZE           16      // EEPROM页大小AT24C08---最大一次页写入16个字节
#define I2C_PAGE_NUMBER         64      // EEPROM页个数AT24C08---64页*16字节/页=1024字节
#elif (EEPROM_TYPE==AT24C32)
#define SLAVE_ADDRESS           0x0050  // 从机地址器件地址AT24C32---1010(A2)(A1)(A0)(读写位有硬件模块写入,不计入)
#define I2C_PAGE_SIZE           32      // EEPROM页大小AT24C32---最大一次页写入32个字节
#define I2C_PAGE_NUMBER         128     // EEPROM页个数AT24C08---128页*32字节/页=4096字节
#elif (EEPROM_TYPE==AT24C128)
#define SLAVE_ADDRESS           0x0050  // 从机地址器件地址AT24C32---1010(A2)(A1)(A0)(读写位有硬件模块写入,不计入)
#define I2C_PAGE_SIZE           64      // EEPROM页大小AT24C32---最大一次页写入32个字节
#define I2C_PAGE_NUMBER         256     // EEPROM页个数AT24C08---128页*32字节/页=4096字节
#endif


#define ACCESS_SUCCESS      0
#define ACCESS_ERROR        1
#define ACCESS_BUSY         2
#define ACCESS_TIMEOUT      3

#define I2C_READ_CMD        0    // I2C读命令
#define I2C_WRITE_CMD       1    // I2C写命令

#define CFG_FREE_RUN_TIMER_CHANNEL          2   // 自由运行用定时器CMT通道(注：修改时需要同步修改配置头文件中的)

typedef enum
{
    I2C_RW_OK = 0,
    I2C_RW_DELAY_BEFORE_START = 1,
    I2C_RW_BUSY_CHECK = 2,
    I2C_RW_MASTER_MODE_SELECT = 3,
    I2C_RW_MASTER_TRANSMITTER_MODE_SELECTED = 4,
    I2C_RW_MASTER_TRANSMITTED_ADDRESS_HIGH = 5,
    I2C_RW_MASTER_TRANSMITTED_ADDRESS_LOW = 6,
    I2C_WRITE_WAIT_DMA_END = 7,
    I2C_WRITE_DMA_END = 8,
    I2C_WRITE_WAIT_END = 9,
    I2C_WRITE_WAIT_END_STEP1 = 10,
    I2C_WRITE_WAIT_END_STEP2_DELAY_BEFORE = 11,
    I2C_WRITE_WAIT_END_STEP2 = 12,
    I2C_READ_MASTER_MODE_SELECT = 13,
    I2C_READ_MASTER_TRANSMITTER_MODE_SELECTED = 14,
    I2C_READ_WAIT_DMA_END = 15,
    I2C_RW_WRONG_REPEAT = 16,
    I2C_RW_MASTER_MODE_STOP = 17,
    I2C_RW_WAIT_REPEAT_START_ACK = 18,
    I2C_RW_WAIT_RECEIVE_TX = 19,
    I2C_RW_WAIT_RECEIVE_RX = 20,
    I2C_RW_WAIT_RECEIVE_FINISH = 21,
    I2C_RW_WAIT_RECEIVE_STOP = 22,
    I2C_RW_ERR_INIT_1,
    I2C_RW_ERR_INIT_2,
    I2C_RW_ERR_INIT_3,
    I2C_RW_ERR_INIT_4,
    I2C_RW_ERR_INIT_5,
    I2C_RW_ERR_INIT_6,
    I2C_RW_ERR_INIT_7,
    I2C_RW_ERR_INIT_8,
} ENU_I2C_RW_STATE;


typedef struct
{
    uint8_t *pDataBuf;
    uint16_t EepromByteAddr;
    uint16_t ByteNumber;
    uint8_t bIsRead;
    uint8_t bStart;
    uint8_t bFinish;
    uint8_t SlaveId;
    uint8_t retryCnt;
    uint8_t funcTimeoutFlag;
    uint32_t funcTimeoutSet;
    uint8_t stepTimeoutFlag;
    uint32_t stepTimeoutSet;
    uint32_t usToTimerTickQ10;
    ENU_I2C_RW_STATE I2cRwState;
    ENU_I2C_RW_STATE I2cDealState;
} STR_EEPROM;

static STR_EEPROM strEeprom;

/**********************************************************
 * 获取MCU定时器的计数值
 * @return  : 返回定时器当前的计数值
 *********************************************************/
static inline uint16_t getTimerCnt(void)
{
    return (uint16_t)(R_CMT->UNT[CFG_FREE_RUN_TIMER_CHANNEL / 2].CM[CFG_FREE_RUN_TIMER_CHANNEL % 2].CNT);
}

/**********************************************************
 * 超时时间处理
 **********************************************************/
static inline void timeoutHandle(void)
{
    static uint32_t funcTimeoutElapse = 0;
    static uint32_t funcTimeoutLatch = 0;
    static uint32_t stepTimeoutElapse = 0;
    static uint32_t stepTimeoutLatch = 0;

    uint16_t currTimeCnt;

    /* Eeprom读写函数的超时处理 */
    if (strEeprom.funcTimeoutFlag == 0)
    {
        funcTimeoutElapse = 0;
        funcTimeoutLatch = getTimerCnt();
        strEeprom.funcTimeoutFlag = 1;
    }
    else if (strEeprom.funcTimeoutFlag == 1)
    {
        currTimeCnt = getTimerCnt();
        funcTimeoutElapse += (((uint16_t)(currTimeCnt - funcTimeoutLatch)) & 0xFFFF);
        funcTimeoutLatch = currTimeCnt;

        if (funcTimeoutElapse >= strEeprom.funcTimeoutSet)
        {
            strEeprom.funcTimeoutFlag = 2;
        }
    }

    /* Eeprom读写函数内部使用的超时处理 */
    if (strEeprom.stepTimeoutFlag == 0)
    {
        stepTimeoutElapse = 0;
        stepTimeoutLatch = getTimerCnt();
        strEeprom.stepTimeoutFlag = 1;
    }
    else if (strEeprom.stepTimeoutFlag == 1)
    {
        currTimeCnt = getTimerCnt();
        stepTimeoutElapse += (((uint16_t)(currTimeCnt - stepTimeoutLatch)) & 0xFFFF);
        stepTimeoutLatch = currTimeCnt;

        if (stepTimeoutElapse >= strEeprom.stepTimeoutSet)
        {
            strEeprom.stepTimeoutFlag = 2;
        }
    }
}

/**********************************************************
 * 设定超时时间
 * @param channel       : 0-Eeprom读写函数通道, 1-Eeprom读写函数内部状态使用通道
 * @param timeout_us    : 超时时间设定值 [us]
 *********************************************************/
static void timeoutSet(uint8_t channel, uint32_t timeout_us)
{
    uint32_t tmp;

    tmp = (uint32_t)(((uint64_t)strEeprom.usToTimerTickQ10 * (uint64_t)timeout_us) >> 10);

    if (channel == 1)
    {
        strEeprom.stepTimeoutFlag = 0;
        strEeprom.stepTimeoutSet = tmp;
    }
    else
    {
        strEeprom.funcTimeoutFlag = 0;
        strEeprom.funcTimeoutSet = tmp;
    }
}

/**********************************************************
 * 获取超时状态
 * @param channel   : 0-Eeprom读写函数通道, 1-Eeprom读写函数内部状态使用通道
 * @return          : 在超时到达时返回1
 *********************************************************/
static uint8_t getTimeoutStatus(uint8_t channel)
{
    if (channel == 1)
    {
        return ( (strEeprom.stepTimeoutFlag == 2) ? 1 : 0);
    }
    else
    {
        return ( (strEeprom.funcTimeoutFlag == 2) ? 1 : 0);
    }
}

/**********************************************************
 * 禁止Eeprom写保护
 **********************************************************/
static inline void Eeprom_disableProtect(void)
{
    return;
}

/**********************************************************
 * 使能Eeprom写保护
 **********************************************************/
static inline void Eeprom_enableProtect(void)
{
    return;
}

static uint8_t I2cRwDeal(uint8_t* pDataBuf, uint16_t byteAddr, uint16_t byteNumber, uint8_t ReadWriteMode, uint16_t DevAddr)
{
    uint16_t RwSuccess = 0;

    switch (strEeprom.I2cRwState)
    {
    case I2C_RW_OK:
    case I2C_RW_DELAY_BEFORE_START:         /* 等待I2C总线释放 */

        strEeprom.SlaveId = (uint8_t)DevAddr;
        strEeprom.pDataBuf = pDataBuf;
        strEeprom.EepromByteAddr = byteAddr;
        strEeprom.ByteNumber = byteNumber;
        strEeprom.bIsRead = (ReadWriteMode == I2C_READ_CMD) ? 1 : 0;
        strEeprom.bFinish = 0;

        strEeprom.retryCnt = 0;
        strEeprom.bStart = 1;
        strEeprom.I2cRwState = I2C_RW_BUSY_CHECK;
        break;

    case I2C_RW_BUSY_CHECK:
        if (strEeprom.bFinish)
        {
            RwSuccess = strEeprom.bFinish;
        }
        break;

    default:
        strEeprom.I2cRwState = I2C_RW_OK;
        break;
    }

    return (uint8_t)RwSuccess;
}

static void Eeprom_deal(void)
{
    static uint16_t u16index = 0;
    static uint16_t rx_index = 0;
    static uint8_t tmpBuf[3] = {0,0,0};

    R_IIC0_Type * regBase = ((R_IIC0_Type *) CFG_IIC_EEPROM_BASE);

    timeoutHandle();

    switch (strEeprom.I2cDealState)
    {
    case I2C_RW_OK:         /* 等待I2C总线释放 */

        if (strEeprom.bStart)
        {
            Eeprom_disableProtect();

            /* 下一个状态的超时时间 */
            timeoutSet(1, 300UL);

            strEeprom.I2cDealState = I2C_RW_DELAY_BEFORE_START;
        }
        break;

    case I2C_RW_DELAY_BEFORE_START:     /* 等待模块空闲后启动传输 */

        /* 检查BBSY繁忙位 */
        if (regBase->ICCR2_b.BBSY)
        {
            /* 处于繁忙状态，进行等待 */
            if (getTimeoutStatus(1))
            {
                /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
                strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
            }

            break;
        }

        rx_index = 0;

        /* 发送设备地址 */
        #if (EEPROM_TYPE==AT24C04)
        u16index = ((strEeprom.EepromByteAddr & 0x1FF)>>8);
        tmpBuf[rx_index++] = (uint8_t)(((strEeprom.SlaveId | u16index) << 1) | 0x00);       /* 写 */
        tmpBuf[rx_index++] = ((strEeprom.EepromByteAddr & 0x00FF) >> 0);                    /* eeprom芯片内存地址 */
        #elif (EEPROM_TYPE==AT24C08)
        u16index = ((byte_address & 0x3FF)>>8);
        tmpBuf[rx_index++] = (uint8_t)(((strEeprom.SlaveId | u16index) << 1) | 0x00);       /* 写 */
        tmpBuf[rx_index++] = ((strEeprom.EepromByteAddr & 0x00FF) >> 0);                    /* eeprom芯片内存地址 */
        #elif ((EEPROM_TYPE==AT24C32) || (EEPROM_TYPE==AT24C128))
        tmpBuf[rx_index++] = (uint8_t)((strEeprom.SlaveId << 1) | 0x00);                    /* 写 */
        tmpBuf[rx_index++] = (uint8_t)((strEeprom.EepromByteAddr & 0xFF00) >> 8);           /* eeprom芯片内存地址 */
        tmpBuf[rx_index++] = (uint8_t)((strEeprom.EepromByteAddr & 0x00FF) >> 0);
        #endif

        /* 清WAIT，ACKWP位 */
        regBase->ICMR3 &= 0xAF;

        /* 清所有的标志位 */
        regBase->ICSR2 = 0x00;

        /* 使能高低超时检测短模式，禁止输出延时 */
        regBase->ICMR2 = 0x06;

        /* 禁能超时检测功能 */
        regBase->ICFER_b.TMOE = 0U;

        /* 配置DMA传输 */

        /* 请求发送起始位 */
        regBase->ICCR2 = (uint8_t) 0x02;

        /* 下一个状态的超时时间 */
        timeoutSet(1, 3000UL);

        u16index = 0;

        strEeprom.I2cDealState = I2C_RW_BUSY_CHECK;
        break;

    case I2C_RW_BUSY_CHECK:             /* 等待DMA将设备地址，内存地址/命令字节传输完成 */

        if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if (getTimeoutStatus(1))
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if ( ( (regBase->ICSR2 & 0x84) == 0x84 ) )
        {
            /* 等待发送寄存器空标志有效 */

            if (u16index < rx_index)
            {
                /* 还存在数据未发送，tmpBuf[]存储的是设备地址，Eeprom字节地址 */
                regBase->ICDRT = (uint8_t)(tmpBuf[u16index++]);
            }
            else
            {
                if (strEeprom.bIsRead)
                {
                    /* 请求发送起始位 */
                    regBase->ICCR2 = (uint8_t) 0x04;

                    /* 下一个状态的超时时间 */
                    timeoutSet(1, 500UL);

                    strEeprom.I2cDealState = I2C_RW_MASTER_MODE_SELECT;
                }
                else
                {
                    /* 写入数据，重新配置DMA传输 */

                    /* 先手动进行一次写入才可以启动DMA传输 */

                    /* 下一个状态的超时时间 */
                    timeoutSet(1, 50000UL);

                    strEeprom.I2cDealState = I2C_WRITE_DMA_END;
                }

                rx_index = 0;
                u16index = 0;
            }
        }
        break;

    case I2C_RW_MASTER_MODE_SELECT:     /* 等待重复起始位发送完成后，发送设备地址 */

        if (getTimeoutStatus(1))
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if ( (regBase->ICCR2 & 0x04) == 0)
        {
            /* 在没有任何错误的情况下，如果RS标志被清零，表示起始位被正确发送， tmpBuf[0]存储的是Eeprom的设备地址 */
            regBase->ICDRT = (uint8_t)(tmpBuf[0]) | 0x01;

            /* 下一个状态的超时时间 */
            timeoutSet(1, 50000UL);

            strEeprom.I2cDealState = I2C_RW_MASTER_TRANSMITTER_MODE_SELECTED;
        }
        break;

    case I2C_RW_MASTER_TRANSMITTER_MODE_SELECTED:   /* 等待模块切换为接收状态，启动首次读取 */
    case I2C_RW_MASTER_TRANSMITTED_ADDRESS_HIGH:    /* 读取的字节个数小于4或者DMA传输完成后处理 */
    case I2C_RW_MASTER_TRANSMITTED_ADDRESS_LOW:     /* DMA传输等待完成 */

        if (getTimeoutStatus(1))
        {
            /* 超时 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if (regBase->ICSR2 & 0x0B)
        {
            /* 超时，仲裁丢失，停止位接收 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if (regBase->ICSR2 & 0x10)
        {
            /* 无应答接收错误 */
            regBase->ICSR2_b.STOP = 0;
            regBase->ICCR2_b.SP = 1;
            (void) regBase->ICDRR;
            strEeprom.I2cDealState = I2C_WRITE_WAIT_DMA_END;
        }
        else if (strEeprom.I2cDealState == I2C_RW_MASTER_TRANSMITTER_MODE_SELECTED)
        {
            if (regBase->ICSR2 & 0x20)
            {
                /* 重复起始位发送完成，先虚拟读取一次 再启动DMA */

                if (strEeprom.ByteNumber > 3)
                {
                    /* 传输的字节个数大于3，使用DMA进行传输 */

                    rx_index = (uint16_t)(strEeprom.ByteNumber - 3);

                    /* 重新配置DMA传输的字节个数，重新启动DMA传输 */

                    (void) regBase->ICDRR;

                    strEeprom.I2cDealState = I2C_RW_MASTER_TRANSMITTED_ADDRESS_LOW;
                }
                else
                {
                    if (2U >= strEeprom.ByteNumber)
                    {
                        regBase->ICMR3_b.WAIT = 1;
                    }

                    if (1U == strEeprom.ByteNumber)
                    {
                        /* Writes to be done separately.
                         * See Note 1 in Section 'I2C Bus Mode Register 3 (ICMR3)' of the RZ microprocessor manual
                         */
                        regBase->ICMR3_b.ACKWP = 1; /* Write enable ACKBT */
                        regBase->ICMR3_b.ACKBT = 1;
                    }

                    rx_index = 0;

                    strEeprom.I2cDealState = I2C_RW_MASTER_TRANSMITTED_ADDRESS_HIGH;

                    (void) regBase->ICDRR;
                }

                u16index = 0;
            }
        }
        else if (strEeprom.I2cDealState == I2C_RW_MASTER_TRANSMITTED_ADDRESS_HIGH)
        {
            /* 不使用DMA进行数据传输或者DMA传输结束后剩下的字节数使用手动接收方式(为了发送NACK) */
            if (regBase->ICSR2 & 0x20)
            {
                /* 接收缓存满 */
                if ( ((rx_index + 3) == strEeprom.ByteNumber) )
                {
                    regBase->ICMR3_b.WAIT = 1;
                }
                else if ( ((rx_index + 2) == strEeprom.ByteNumber) )
                {
                    regBase->ICMR3_b.ACKWP = 1;
                    regBase->ICMR3_b.ACKBT = 1;
                }
                else if ( ((rx_index + 1) == strEeprom.ByteNumber) )
                {
                    regBase->ICSR2_b.STOP = 0;

                    u16index = 8;
                    while (u16index)
                    {
                        if (regBase->ICSR2_b.STOP == 0)
                        {
                            break;
                        }
                        u16index --;
                    }

                    regBase->ICCR2_b.SP = 1;
                }

                /* 读取正确的数据 */
                strEeprom.pDataBuf[rx_index++] = regBase->ICDRR;

                if ( rx_index == strEeprom.ByteNumber)
                {
                    regBase->ICMR3_b.WAIT = 0;

                    /* 下一个状态的超时时间 */
                    timeoutSet(1, 500UL);

                    /* 没有检测到错误，没有超时，并且DMA的EN位被清零时，表明数据接收完成 */
                    strEeprom.I2cDealState = I2C_WRITE_WAIT_DMA_END;
                }
            }
        }
        else if (regBase->ICSR2 & 0x20)
        {
            /* 接收字节大于3字节部分在这里进行接收，当前检测到接收缓存满标志 */
            strEeprom.pDataBuf[u16index++] = regBase->ICDRR;

            if (u16index >= rx_index)
            {
                u16index = 0;

                strEeprom.I2cDealState = I2C_RW_MASTER_TRANSMITTED_ADDRESS_HIGH;
            }
        }
        break;

    case I2C_WRITE_WAIT_DMA_END:                /* 数据接收完成  */

        if (regBase->ICSR2_b.STOP == 1)
        {
            regBase->ICSR2 = 0x00;

            regBase->ICMR3 &= 0xAF;

            /* 禁能超时检测功能 */
            regBase->ICFER_b.TMOE = 0U;

            /* 数据读取完成 */
            strEeprom.bStart = 0;
            strEeprom.bFinish = 1;

            strEeprom.I2cDealState = I2C_RW_OK;

            Eeprom_enableProtect();
        }
        else if (getTimeoutStatus(1))
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        break;

    case I2C_WRITE_DMA_END:                     /* 数据发送中，等待发送完成后发送停止位 */

        if (regBase->ICSR2 & 0x1B)
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if (getTimeoutStatus(1))
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        else if ( (regBase->ICSR2 & 0x84) == 0x84 )
        {
            if (u16index < strEeprom.ByteNumber)
            {
                /* 还存在数据未发送，tmpBuf[]存储的是设备地址，Eeprom字节地址 */
                regBase->ICDRT = (uint8_t)(strEeprom.pDataBuf[u16index++]);
            }
            else
            {
                /* 发送完成, 发送停止位 */
                regBase->ICSR2_b.STOP = 0;

                u16index = 8;
                while (u16index)
                {
                    if (regBase->ICSR2_b.STOP == 0)
                    {
                        break;
                    }
                    u16index --;
                }

                regBase->ICCR2_b.SP = 1;

                /* 下一个状态的超时时间 */
                timeoutSet(1, 1000UL);

                strEeprom.I2cDealState = I2C_WRITE_WAIT_END;
            }
        }
        break;

    case I2C_WRITE_WAIT_END:                    /* 等待停止位发送完成，启动新的起始位 */

        if (regBase->ICSR2_b.STOP == 1)
        {
            regBase->ICSR2 = 0x00;

            /* 禁能超时检测功能 */
            regBase->ICFER_b.TMOE = 0U;

            /* 一定次数后直接返回正确，用于Eeprom写入后的保存延时操作 */
            if (++u16index > 200)
            {
                strEeprom.bStart = 0;
                strEeprom.bFinish = 1;

                Eeprom_enableProtect();

                strEeprom.I2cDealState = I2C_RW_OK;
            }
            else
            {
                /* 下一个状态的超时时间 */
                timeoutSet(1, 300UL);

                strEeprom.I2cDealState = I2C_WRITE_WAIT_END_STEP1;
            }
        }
        else if (getTimeoutStatus(1))
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        }
        break;

        /* 发送起始位 */
    case I2C_WRITE_WAIT_END_STEP1:

        /* 检查BBSY繁忙位 */
        if (regBase->ICCR2_b.BBSY)
        {
            /* 一直处于繁忙状态，跳转到错误处理状态，重新初始化I2C总线 */
            if (getTimeoutStatus(1))
            {
                strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
            }

            break;
        }

        /* 清所有的标志位 */
        regBase->ICSR2 = 0x00;

        /* 使能高低超时检测短模式，禁止输出延时 */
        regBase->ICMR2 = 0x06;

        /* 禁能超时检测功能 */
        regBase->ICFER_b.TMOE = 0U;

        /* 请求发送起始位 */
        regBase->ICCR2 = (uint8_t) 0x02;

        /* 下一个状态的超时时间 */
        timeoutSet(1, 200UL);

        strEeprom.I2cDealState = I2C_WRITE_WAIT_END_STEP2_DELAY_BEFORE;

        break;

    case I2C_WRITE_WAIT_END_STEP2_DELAY_BEFORE:     /* 发送设备地址  */
    case I2C_WRITE_WAIT_END_STEP2:                  /* 查询是否有设备应答 */

        if ( (regBase->ICSR2 & 0x1B) || (getTimeoutStatus(1)) )
        {
            /* 超时，仲裁丢失，停止位接收，无应答接收错误 */
            regBase->ICSR2_b.STOP = 0;

            rx_index = 8;
            while (rx_index)
            {
                if (regBase->ICSR2_b.STOP == 0)
                {
                    break;
                }
                rx_index --;
            }

            regBase->ICCR2_b.SP = 1;

            strEeprom.I2cDealState = I2C_WRITE_WAIT_END;
        }
        else if ( ((regBase->ICSR2 & 0x50) == 0x40) && (strEeprom.I2cDealState == I2C_WRITE_WAIT_END_STEP2) )
        {
            /* 数据发送完成且应答接收正常 */
            strEeprom.bStart = 0;
            strEeprom.bFinish = 1;

            Eeprom_enableProtect();

            strEeprom.I2cDealState = I2C_RW_OK;
        }
        else if ( (regBase->ICSR2 & 0x84) == 0x84)
        {
            /* 发送缓存空，这时候可以将Eeprom的设备地址发出 */
            if (strEeprom.I2cDealState == I2C_WRITE_WAIT_END_STEP2_DELAY_BEFORE)
            {
                regBase->ICDRT = (uint8_t)(tmpBuf[0]);

                strEeprom.I2cDealState = I2C_WRITE_WAIT_END_STEP2;
            }
        }
        break;

    case I2C_RW_WRONG_REPEAT:           /* 模块出现故障后进入此状态，发送停止位 */

        regBase->ICSR2_b.STOP = 0;

        rx_index = 8;
        while (rx_index)
        {
            if (regBase->ICSR2_b.STOP == 0)
            {
                break;
            }
            rx_index --;
        }

        regBase->ICCR2_b.SP = 1;

        strEeprom.I2cDealState = I2C_RW_MASTER_MODE_STOP;
        break;

    case I2C_RW_MASTER_MODE_STOP:           /* 出现故障后延时重新初始化模块，重新启动读写 */

        /* ICCR1默认值(I2C引脚处于非激活状态) */
        regBase->ICCR1 = (uint8_t) 0x1FU;
        /* 复位I2C模块 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);
        /* I2C处于内部复位，引脚处于激活状态 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);

        /* 下一个状态的超时时间 */
        timeoutSet(1, 100UL);

        strEeprom.I2cDealState = I2C_RW_ERR_INIT_1;
        break;

        /* 检测IIC引脚是否正常 */
    case I2C_RW_ERR_INIT_1:
        if (getTimeoutStatus(1))
        {
            u16index = 0;
            rx_index = 0;

            if ((regBase->ICCR1 & 0x01) == 0)
            {
                /* 下一个状态的超时时间 */
                timeoutSet(1, 50UL);

                strEeprom.I2cDealState = I2C_RW_ERR_INIT_2;
            }
            else
            {
                strEeprom.I2cDealState = I2C_RW_ERR_INIT_4;
            }
        }
        break;

        /* 低电平 */
    case I2C_RW_ERR_INIT_2:
        if (rx_index == 0)
        {
            rx_index = 1;

            regBase->ICCR1 = 0x84;
        }
        else if (getTimeoutStatus(1))
        {
            /* 下一个状态的超时时间 */
            timeoutSet(1, 50UL);

            rx_index = 0;

            strEeprom.I2cDealState = I2C_RW_ERR_INIT_3;
        }
        break;

        /* 高电平 */
    case I2C_RW_ERR_INIT_3:
        if (rx_index == 0)
        {
            rx_index = 1;

            regBase->ICCR1 = 0x8C;
        }
        else if (getTimeoutStatus(1))
        {
            u16index ++;

            if (u16index >= 10)
            {
                u16index = 0;

                strEeprom.I2cDealState = I2C_RW_ERR_INIT_4;
            }
            else
            {
                strEeprom.I2cDealState = I2C_RW_ERR_INIT_2;
            }
        }
        break;

    case I2C_RW_ERR_INIT_4:
        /* ICCR1默认值(I2C引脚处于非激活状态) */
        regBase->ICCR1 = (uint8_t) 0x1FU;
        /* 复位I2C模块 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U);
        /* I2C处于内部复位，引脚处于激活状态 */
        regBase->ICCR1 = (uint8_t) (0x1FU + 0x40U + 0x80U);
        /* I2C复位释放 */
        regBase->ICCR1 = (uint8_t) (0x80 | 0x1F);

        strEeprom.I2cDealState = I2C_RW_OK;
        break;

    default:
        strEeprom.I2cDealState = I2C_RW_WRONG_REPEAT;
        break;
    }
}

static void bsp_eeprom_iic_init(void)
{
    /* 按键及数码管显示使用的是IIC1外设 */
    R_IIC0_Type * regBase = ((R_IIC0_Type *) CFG_IIC_EEPROM_BASE);
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

static void bsp_eeprom_timer_init(void)
{
    /* PCLKL时钟是50MHZ，定时器分频系数是32分频，计数1ms的定时器计数个数是1562.5 */

    uint16_t Unit = CFG_FREE_RUN_TIMER_CHANNEL / 2;
    uint16_t Channel = CFG_FREE_RUN_TIMER_CHANNEL % 2;

    /* 将定时器从低功耗模式唤醒 */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_CMT, Unit);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* UNIT0 - CH0 : 定时器计数器清零/固定增计数模式 */
    R_CMT->UNT[Unit].CM[Channel].CNT = 0x0000;
    /* UNIT0 - CH0 : 定时器周期/比较值设定(16位定时器) */
    R_CMT->UNT[Unit].CM[Channel].COR = 0xFFFF;
    /* UNIT0 - CH0 : 时钟源分频设置 0-8 1-32 2-128 3-512 */
    R_CMT->UNT[Unit].CM[Channel].CR_b.CKS = 1;
    /* 禁止产生中断 */
    R_CMT->UNT[Unit].CM[Channel].CR_b.CMIE = 0;
    /* 通道1启动 */
    R_CMT->UNT[Unit].CMSTR0 |= (uint16_t)(0x01 << Channel);

    /* us单位转换为定时器计数个数系数， 50MHz / 32 * 1024 = 1600 */
    strEeprom.usToTimerTickQ10 = 1600;
}

void bsp_eeprom_init(void)
{
    memset(&strEeprom, 0x00, sizeof(strEeprom));

    /* 初始化Eeprom所用的iic外设 */
    bsp_eeprom_iic_init();

    /* 操作Eeprom超时检测用定时器初始化 */
    bsp_eeprom_timer_init();
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
    (void) MemAddSize;

    /* 读写变量设置 */
    strEeprom.I2cRwState = I2C_RW_OK;
    strEeprom.I2cDealState = I2C_RW_OK;

    /* 函数处理超时时间设置 */
    timeoutSet(0, (Timeout * 1000UL));

    while(1)
    {
        if (I2cRwDeal(pData, MemAddress, Size, I2C_READ_CMD, DevAddress))
        {
            /* 读写成功 */
            return ACCESS_SUCCESS;
        }

        Eeprom_deal();

        if (getTimeoutStatus(0))
        {
            /* 函数处理超时 */
            return ACCESS_TIMEOUT;
        }
    }
}

uint8_t I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,
        uint8_t * pData, uint16_t Size, uint32_t Timeout)
{

    (void) MemAddSize;

    /* 读写变量设置 */
    strEeprom.I2cRwState = I2C_RW_OK;
    strEeprom.I2cDealState = I2C_RW_OK;

    /* 函数处理超时时间设置 */
    timeoutSet(0, (Timeout * 1000UL));

    while(1)
    {
        if (I2cRwDeal(pData, MemAddress, Size, I2C_WRITE_CMD, DevAddress))
        {
            /* 读写成功 */
            return ACCESS_SUCCESS;
        }

        Eeprom_deal();

        if (getTimeoutStatus(0))
        {
            /* 函数处理超时 */
            return ACCESS_TIMEOUT;
        }
    }
}















