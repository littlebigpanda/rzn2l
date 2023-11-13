/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
                        [21] = dmac_int_isr, /* DMAC0_INT0 (DMAC0 transfer completion 0) */
            [22] = dmac_int_isr, /* DMAC0_INT1 (DMAC0 transfer completion 1) */
            [53] = null, /* CMT0_CMI (CMT0 Compare match) */
            [54] = null, /* CMT1_CMI (CMT1 Compare match) */
            [69] = null, /* TGIA0 (MTU0.TGRA input capture/compare match) */
            [70] = null, /* TGIB0 (MTU0.TGRB input capture/compare match) */
            [71] = null, /* TGIC0 (MTU0.TGRC input capture/compare match) */
            [72] = null, /* TGID0 (MTU0.TGRD input capture/compare match) */
            [73] = null, /* TCIV0 (MTU0.TCNT overflow) */
            [74] = null, /* TGIE0 (MTU0.TGRE compare match) */
            [75] = null, /* TGIF0 (MTU0.TGRF compare match) */
            [84] = null, /* TGIA3 (MTU3.TGRA input capture/compare match) */
            [93] = null, /* TCIV4 (MTU4.TCNT overflow/underflow) */
            [112] = null, /* OEI1 (Output enable interrupt 1) */
            [113] = null, /* OEI2 (Output enable interrupt 2) */
            [114] = null, /* OEI3 (Output enable interrupt 3) */
            [239] = null, /* GPT13_OVF (GPT13 GTCNT overflow (GTPR compare match)) */
            [277] = null, /* ESC_SYNC0 (EtherCAT Sync0 interrupt) */
            [278] = null, /* ESC_SYNC1 (EtherCAT Sync1 interrupt) */
            [279] = null, /* ESC_CAT (EtherCAT interrupt) */
            [285] = usbfs_interrupt_handler, /* USB_FI (USB (Function) interrupt) */
            [286] = r_usb_dmaca_intDMAC0I_isr, /* USB_FDMA0 (USB (Function) DMA 0 transmit completion) */
            [287] = r_usb_dmaca_intDMAC1I_isr, /* USB_FDMA1 (USB (Function) DMA 1 transmit completion) */
            [288] = null, /* SCI0_ERI (SCI0 Receive error) */
            [289] = null, /* SCI0_RXI (SCI0 Receive data full) */
            [290] = null, /* SCI0_TXI (SCI0 Transmit data empty) */
            [291] = null, /* SCI0_TEI (SCI0 Transmit end) */
            [292] = null, /* SCI1_ERI (SCI1 Receive error) */
            [293] = null, /* SCI1_RXI (SCI1 Receive data full) */
            [294] = null, /* SCI1_TXI (SCI1 Transmit data empty) */
            [295] = null, /* SCI1_TEI (SCI1 Transmit end) */
            [296] = null, /* SCI2_ERI (SCI2 Receive error) */
            [297] = null, /* SCI2_RXI (SCI2 Receive data full) */
            [298] = null, /* SCI2_TXI (SCI2 Transmit data empty) */
            [299] = null, /* SCI2_TEI (SCI2 Transmit end) */
            [300] = null, /* SCI3_ERI (SCI3 Receive error) */
            [301] = null, /* SCI3_RXI (SCI3 Receive data full) */
            [302] = null, /* SCI3_TXI (SCI3 Transmit data empty) */
            [303] = null, /* SCI3_TEI (SCI3 Transmit end) */
            [304] = null, /* SCI4_ERI (SCI4 Receive error) */
            [305] = null, /* SCI4_RXI (SCI4 Receive data full) */
            [306] = null, /* SCI4_TXI (SCI4 Transmit data empty) */
            [307] = null, /* SCI4_TEI (SCI4 Transmit end) */
            [312] = null, /* IIC1_EEI (IIC1 Transfer error or event generation) */
            [313] = null, /* IIC1_RXI (IIC1 Receive data full) */
            [314] = null, /* IIC1_TXI (IIC1 Transmit data empty) */
            [315] = null, /* IIC1_TEI (IIC1 Transmit end) */
            [343] = null, /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
            [344] = null, /* DSMIF1_CDRUI (DSMIF1 current data register update (ORed ch3 to ch5)) */
            [439] = null, /* IIC2_EEI (IIC2 Transfer error or event generation) */
            [440] = null, /* IIC2_RXI (IIC2 Receive data full) */
            [441] = null, /* IIC2_TXI (IIC2 Transmit data empty) */
            [442] = null, /* IIC2_TEI (IIC2 Transmit end) */
        };
        #endif
