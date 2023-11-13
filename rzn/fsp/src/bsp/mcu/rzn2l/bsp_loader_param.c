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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if !(BSP_CFG_RAM_EXECUTION)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define BSP_LOADER_PARAM_MAX    (20)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
extern void *_loader_data_start;
extern void *_loader_text_start;
extern void *_loader_text_start;
extern void *_loader_text_end;
extern void *_loader_data_start;
extern void *_loader_data_end;
extern void *_fvector_start;
extern void *_fvector_end;
extern void *_ram_code_start;
extern void *_ram_code_end;
extern void *_text_start;
extern void *_text_end;
extern void *_data_start;
extern void *_data_end;

extern void *_mloader_text;
extern void *_mloader_data;
extern void *_mfvector;
extern void *_mramcode_text;
extern void *_mtext;
extern void *_mdata;
extern void *flash_contents_end;

/* Parameter Information for the Loader. */
BSP_DONT_REMOVE const uint32_t g_bsp_loader_param[BSP_LOADER_PARAM_MAX] BSP_PLACE_IN_SECTION(BSP_SECTION_LOADER_PARAM) =
{
//    BSP_CFG_CACHE_FLG,
//    BSP_CFG_CS0BCR_V_WRAPCFG_V,
//    BSP_CFG_CS0WCR_V_COMCFG_V,
//    BSP_CFG_DUMMY0_BMCFG_V,
//    BSP_CFG_BSC_FLG_xSPI_FLG,
//    BSP_CFG_LDR_ADDR_NML,
//    BSP_CFG_LDR_SIZE_NML,
//    BSP_CFG_DEST_ADDR_NML,
//    BSP_CFG_DNUMMY1,
//    BSP_CFG_DNUMMY2,
//    BSP_CFG_DNUMMY3_CSSCTL_V,
//    BSP_CFG_DNUMMY4_LIOCFGCS0_V,
//    BSP_CFG_DNUMMY5,
//    BSP_CFG_DNUMMY6,
//    BSP_CFG_DNUMMY7,
//    BSP_CFG_DNUMMY8,
//    BSP_CFG_DNUMMY9,
//    BSP_CFG_DNUMMY10_ACCESS_SPEED,
//    BSP_CFG_CHECK_SUM
    (uint32_t)&_mloader_text,       // 0 起始运行程序在FLASH中的起始装载地址
    (uint32_t)&_mloader_data,       // 1 起始运行程序变量数据在FLASH中的起始装载地址
    (uint32_t)&_mfvector,           // 2 中断向量在FLASH中的起始装载地址
    (uint32_t)&_mramcode_text,      // 3 ramcode代码在FLASH中起始装载地址
    (uint32_t)&_mtext,              // 4 代码在FLASH中的起始装载地址
    (uint32_t)&_mdata,              // 5 变量数据在FLASH中的起始装载地址
    (uint32_t)&flash_contents_end,  // 6 固件装载在FLASH中的末尾地址
    (uint32_t)&_loader_text_start,  // 7 起始运行程序从FLASH中搬运到RAM中的起始地址
    (uint32_t)&_loader_text_end,    // 8 起始运行程序从FLASH中搬运到RAM中的末尾地址
    (uint32_t)&_loader_data_start,  // 9 起始运行程序变量在RAM中的起始地址
    (uint32_t)&_loader_data_end,    // 10 起始运行程序变量在RAM中的末尾地址
    (uint32_t)&_fvector_start,      // 11 中断向量在RAM中的起始地址
    (uint32_t)&_fvector_end,        // 12 中断向量在RAM中的末尾地址
    (uint32_t)&_ram_code_start,     // 13 RAMCODE代码在RAM中的起始地址
    (uint32_t)&_ram_code_end,       // 14 RAMCODE代码在RAM中的末尾地址
    (uint32_t)&_text_start,         // 15 代码在RAM中的起始地址
    (uint32_t)&_text_end,           // 16 代码在RAM中的末尾地址
    (uint32_t)&_data_start,         // 17 数据在RAM中的起始地址
    (uint32_t)&_data_end,           // 18 数据在RAM中的末尾地址
    0x00000000UL                    // 19 存放最后的校验和
};

#endif
