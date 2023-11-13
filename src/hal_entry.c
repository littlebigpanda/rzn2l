/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#include "hal_data.h"
#include "bsp_eeprom.h"
#include "bsp_led.h"

void R_BSP_WarmStart(bsp_warm_start_event_t event) BSP_PLACE_IN_SECTION(".warm_start");

//extern bsp_leds_t g_bsp_leds;

uint8_t returnVal = 0;
uint16_t DevAddress = 0x50;
uint16_t MemAddress = 32;
uint16_t MemAddSize = 2;
uint8_t pData[32];
uint16_t Size = 32;
uint32_t Timeout = 50;
uint8_t pDataR[32];

const uint8_t ledDispChar[] =
{
 0xC0,  0xF9,   0xA4,   0xB0,   0x99,   0x92,   0x82,   0xF8,   0x80,   0x90,
// 0,   1,      2,      3,      4,      5,      6,      7,      8,      9,
 0x88,  0x83,   0xC6,   0xA1,   0x86, 0x8E};
// A,   B,      C,      D,      E,    F


/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the software delay function provided by the BSP.
 *
 **********************************************************************************************************************/
void hal_entry (void)
{
    /* Define the units to be used with the software delay function */
    const bsp_delay_units_t bsp_delay_units = BSP_DELAY_UNITS_MILLISECONDS;

    /* Set the blink frequency (must be <= bsp_delay_units */
    const uint32_t freq_in_hz = 2;

    /* Calculate the delay in terms of bsp_delay_units */
    const uint32_t delay = bsp_delay_units / freq_in_hz;

    /* LED type structure */
//    bsp_leds_t leds = g_bsp_leds;
//
//    /* If this board has no LEDs then trap here */
//    if (0 == leds.led_count)
//    {
//        while (1)
//        {
//            ;                          // There are no LEDs on this board
//        }
//    }
//
//    /* This code uses BSP IO functions to show how it is used.*/
//    /* Turn off LEDs */
//    for (uint32_t i = 0; i < leds.led_count; i++)
//    {
//        R_BSP_PinClear(BSP_IO_REGION_SAFE, (bsp_io_port_pin_t) leds.p_leds[i]);
//    }

    __disable_irq();

    uint32_t u32temp1 = 0;
    uint32_t u32temp2 = 0;

    #if 0

    /* Eeprom读写测试 */
    bsp_eeprom_init();

    while (1)
    {
        for (u32temp1 = 0; u32temp1 < sizeof(pData); u32temp1++)
        {
            pData[u32temp1] = (uint8_t)u32temp1;
        }

        memset(&pDataR[0], 0x00, sizeof(pDataR));

        returnVal = I2C_Mem_Write(DevAddress, MemAddress, MemAddSize, &pData[0], Size, Timeout);

        if (returnVal != 0)
        {
            __NOP();
            break;
        }

        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);

        returnVal = I2C_Mem_Read(DevAddress, MemAddress, MemAddSize, &pDataR[0], Size, Timeout);

        if (returnVal != 0)
        {
            __NOP();
            break;
        }

        MemAddress = (uint16_t)((MemAddress + Size));

        if (memcmp(&pData[0], &pDataR[0], Size) != 0)
        {
            __NOP();
            break;
        }
        else if (MemAddress >= 4096)
        {
            __NOP();
            break;
        }

        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    }

    #endif


    #if 1
    /* LED显示及按键功能测试 */
    /* 注意确认修改LED使用的IIC外设通道宏定义 */
    bsp_led_init();

    led_buffer[0] = 0xC0;
    led_buffer[1] = 0xC0;
    led_buffer[2] = 0xC0;
    led_buffer[3] = 0xC0;
    led_buffer[4] = 0xC0;

    while (1)
    {
        if (u32temp2 ++ > 500)
        {
//            u32temp2 = 0;
//            u32temp1 = (u32temp1 + 1) % 0xFFFFF;
//            led_buffer[0] = ledDispChar[(uint8_t)((u32temp1 >> 16) & 0xF)];
//            led_buffer[1] = ledDispChar[(uint8_t)((u32temp1 >> 12) & 0xF)];
//            led_buffer[2] = ledDispChar[(uint8_t)((u32temp1 >> 8) & 0xF)];
//            led_buffer[3] = ledDispChar[(uint8_t)((u32temp1 >> 4) & 0xF)];
//            led_buffer[4] = ledDispChar[(uint8_t)((u32temp1 >> 0) & 0xF)];

            u32temp1 = (u32temp1 + 1) % 99999;
            u32temp2 = u32temp1;
            led_buffer[4] = ledDispChar[(uint8_t)((u32temp2 % 10) & 0xF)];
            u32temp2 = u32temp2 / 10;
            led_buffer[3] = ledDispChar[(uint8_t)((u32temp2 % 10) & 0xF)];
            u32temp2 = u32temp2 / 10;
            led_buffer[2] = ledDispChar[(uint8_t)((u32temp2 % 10) & 0xF)];
            u32temp2 = u32temp2 / 10;
            led_buffer[1] = ledDispChar[(uint8_t)((u32temp2 % 10) & 0xF)];
            u32temp2 = u32temp2 / 10;
            led_buffer[0] = ledDispChar[(uint8_t)((u32temp2 % 10) & 0xF)];
            u32temp2 = u32temp2 / 10;

            u32temp2 = 0;
        }

        bsp_led_handle();

        R_BSP_SoftwareDelay(125, BSP_DELAY_UNITS_MICROSECONDS);
    }
    #endif












    while (1)
    {
        /* Toggle board LEDs */
//        for (uint32_t i = 0; i < leds.led_count; i++)
//        {
//            R_BSP_PinToggle(BSP_IO_REGION_SAFE, (bsp_io_port_pin_t) leds.p_leds[i]);
//        }



        /* Delay */
        R_BSP_SoftwareDelay(delay, bsp_delay_units);
    }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
        /* Pre clock initialization */
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}
