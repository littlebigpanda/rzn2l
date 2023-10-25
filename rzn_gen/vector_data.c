/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
                        [21] = dmac_int_isr, /* DMAC0_INT0 (DMAC0 transfer completion 0) */
            [22] = dmac_int_isr, /* DMAC0_INT1 (DMAC0 transfer completion 1) */
            [71] = null, /* TGIC0 (MTU0.TGRC input capture/compare match) */
            [312] = null, /* IIC1_EEI (IIC1 Transfer error or event generation) */
            [313] = null, /* IIC1_RXI (IIC1 Receive data full) */
            [314] = null, /* IIC1_TXI (IIC1 Transmit data empty) */
            [315] = null, /* IIC1_TEI (IIC1 Transmit end) */
            [343] = dsmif_cdrui_isr, /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
            [439] = null, /* IIC2_EEI (IIC2 Transfer error or event generation) */
            [440] = null, /* IIC2_RXI (IIC2 Receive data full) */
            [441] = null, /* IIC2_TXI (IIC2 Transmit data empty) */
            [442] = null, /* IIC2_TEI (IIC2 Transmit end) */
        };
        #endif
