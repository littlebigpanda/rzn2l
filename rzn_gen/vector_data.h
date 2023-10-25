/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#include "bsp_api.h"
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (50)
#endif
/* ISR prototypes */
void dmac_int_isr(void);
void null(void);

/* Vector table allocations */
#define VECTOR_NUMBER_DMAC0_INT0 ((IRQn_Type) 21) /* DMAC0_INT0 (DMAC0 transfer completion 0) */
#define VECTOR_NUMBER_DMAC0_INT1 ((IRQn_Type) 22) /* DMAC0_INT1 (DMAC0 transfer completion 1) */
#define VECTOR_NUMBER_CMT0_CMI ((IRQn_Type) 53) /* CMT0_CMI (CMT0 Compare match) */
#define VECTOR_NUMBER_CMT1_CMI ((IRQn_Type) 54) /* CMT1_CMI (CMT1 Compare match) */
#define VECTOR_NUMBER_TGIA0 ((IRQn_Type) 69) /* TGIA0 (MTU0.TGRA input capture/compare match) */
#define VECTOR_NUMBER_TGIB0 ((IRQn_Type) 70) /* TGIB0 (MTU0.TGRB input capture/compare match) */
#define VECTOR_NUMBER_TGIC0 ((IRQn_Type) 71) /* TGIC0 (MTU0.TGRC input capture/compare match) */
#define VECTOR_NUMBER_TGID0 ((IRQn_Type) 72) /* TGID0 (MTU0.TGRD input capture/compare match) */
#define VECTOR_NUMBER_TCIV0 ((IRQn_Type) 73) /* TCIV0 (MTU0.TCNT overflow) */
#define VECTOR_NUMBER_TGIE0 ((IRQn_Type) 74) /* TGIE0 (MTU0.TGRE compare match) */
#define VECTOR_NUMBER_TGIF0 ((IRQn_Type) 75) /* TGIF0 (MTU0.TGRF compare match) */
#define VECTOR_NUMBER_TGIA3 ((IRQn_Type) 84) /* TGIA3 (MTU3.TGRA input capture/compare match) */
#define VECTOR_NUMBER_TCIV4 ((IRQn_Type) 93) /* TCIV4 (MTU4.TCNT overflow/underflow) */
#define VECTOR_NUMBER_GPT13_OVF ((IRQn_Type) 239) /* GPT13_OVF (GPT13 GTCNT overflow (GTPR compare match)) */
#define VECTOR_NUMBER_ESC_SYNC0 ((IRQn_Type) 277) /* ESC_SYNC0 (EtherCAT Sync0 interrupt) */
#define VECTOR_NUMBER_ESC_SYNC1 ((IRQn_Type) 278) /* ESC_SYNC1 (EtherCAT Sync1 interrupt) */
#define VECTOR_NUMBER_ESC_CAT ((IRQn_Type) 279) /* ESC_CAT (EtherCAT interrupt) */
#define VECTOR_NUMBER_USB_FI ((IRQn_Type) 285) /* USB_FI (USB (Function) interrupt) */
#define VECTOR_NUMBER_USB_FDMA0 ((IRQn_Type) 286) /* USB_FDMA0 (USB (Function) DMA 0 transmit completion) */
#define VECTOR_NUMBER_USB_FDMA1 ((IRQn_Type) 287) /* USB_FDMA1 (USB (Function) DMA 1 transmit completion) */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 288) /* SCI0_ERI (SCI0 Receive error) */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 289) /* SCI0_RXI (SCI0 Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 290) /* SCI0_TXI (SCI0 Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 291) /* SCI0_TEI (SCI0 Transmit end) */
#define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type) 292) /* SCI1_ERI (SCI1 Receive error) */
#define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type) 293) /* SCI1_RXI (SCI1 Receive data full) */
#define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type) 294) /* SCI1_TXI (SCI1 Transmit data empty) */
#define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type) 295) /* SCI1_TEI (SCI1 Transmit end) */
#define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type) 296) /* SCI2_ERI (SCI2 Receive error) */
#define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type) 297) /* SCI2_RXI (SCI2 Receive data full) */
#define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type) 298) /* SCI2_TXI (SCI2 Transmit data empty) */
#define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type) 299) /* SCI2_TEI (SCI2 Transmit end) */
#define VECTOR_NUMBER_SCI3_ERI ((IRQn_Type) 300) /* SCI3_ERI (SCI3 Receive error) */
#define VECTOR_NUMBER_SCI3_RXI ((IRQn_Type) 301) /* SCI3_RXI (SCI3 Receive data full) */
#define VECTOR_NUMBER_SCI3_TXI ((IRQn_Type) 302) /* SCI3_TXI (SCI3 Transmit data empty) */
#define VECTOR_NUMBER_SCI3_TEI ((IRQn_Type) 303) /* SCI3_TEI (SCI3 Transmit end) */
#define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 304) /* SCI4_ERI (SCI4 Receive error) */
#define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 305) /* SCI4_RXI (SCI4 Receive data full) */
#define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 306) /* SCI4_TXI (SCI4 Transmit data empty) */
#define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 307) /* SCI4_TEI (SCI4 Transmit end) */
#define VECTOR_NUMBER_IIC1_EEI ((IRQn_Type) 312) /* IIC1_EEI (IIC1 Transfer error or event generation) */
#define VECTOR_NUMBER_IIC1_RXI ((IRQn_Type) 313) /* IIC1_RXI (IIC1 Receive data full) */
#define VECTOR_NUMBER_IIC1_TXI ((IRQn_Type) 314) /* IIC1_TXI (IIC1 Transmit data empty) */
#define VECTOR_NUMBER_IIC1_TEI ((IRQn_Type) 315) /* IIC1_TEI (IIC1 Transmit end) */
#define VECTOR_NUMBER_DSMIF0_CDRUI ((IRQn_Type) 343) /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
#define VECTOR_NUMBER_DSMIF1_CDRUI ((IRQn_Type) 344) /* DSMIF1_CDRUI (DSMIF1 current data register update (ORed ch3 to ch5)) */
#define VECTOR_NUMBER_IIC2_EEI ((IRQn_Type) 439) /* IIC2_EEI (IIC2 Transfer error or event generation) */
#define VECTOR_NUMBER_IIC2_RXI ((IRQn_Type) 440) /* IIC2_RXI (IIC2 Receive data full) */
#define VECTOR_NUMBER_IIC2_TXI ((IRQn_Type) 441) /* IIC2_TXI (IIC2 Transmit data empty) */
#define VECTOR_NUMBER_IIC2_TEI ((IRQn_Type) 442) /* IIC2_TEI (IIC2 Transmit end) */
typedef enum IRQn
{
    SoftwareGeneratedInt0 = -32,
    SoftwareGeneratedInt1 = -31,
    SoftwareGeneratedInt2 = -30,
    SoftwareGeneratedInt3 = -29,
    SoftwareGeneratedInt4 = -28,
    SoftwareGeneratedInt5 = -27,
    SoftwareGeneratedInt6 = -26,
    SoftwareGeneratedInt7 = -25,
    SoftwareGeneratedInt8 = -24,
    SoftwareGeneratedInt9 = -23,
    SoftwareGeneratedInt10 = -22,
    SoftwareGeneratedInt11 = -21,
    SoftwareGeneratedInt12 = -20,
    SoftwareGeneratedInt13 = -19,
    SoftwareGeneratedInt14 = -18,
    SoftwareGeneratedInt15 = -17,
    DebugCommunicationsChannelInt = -10,
    PerformanceMonitorCounterOverflowInt = -9,
    CrossTriggerInterfaceInt = -8,
    VritualCPUInterfaceMaintenanceInt = -7,
    HypervisorTimerInt = -6,
    VirtualTimerInt = -5,
    NonSecurePhysicalTimerInt = -2,
    DMAC0_INT0_IRQn = 21, /* DMAC0_INT0 (DMAC0 transfer completion 0) */
    DMAC0_INT1_IRQn = 22, /* DMAC0_INT1 (DMAC0 transfer completion 1) */
    CMT0_CMI_IRQn = 53, /* CMT0_CMI (CMT0 Compare match) */
    CMT1_CMI_IRQn = 54, /* CMT1_CMI (CMT1 Compare match) */
    TGIA0_IRQn = 69, /* TGIA0 (MTU0.TGRA input capture/compare match) */
    TGIB0_IRQn = 70, /* TGIB0 (MTU0.TGRB input capture/compare match) */
    TGIC0_IRQn = 71, /* TGIC0 (MTU0.TGRC input capture/compare match) */
    TGID0_IRQn = 72, /* TGID0 (MTU0.TGRD input capture/compare match) */
    TCIV0_IRQn = 73, /* TCIV0 (MTU0.TCNT overflow) */
    TGIE0_IRQn = 74, /* TGIE0 (MTU0.TGRE compare match) */
    TGIF0_IRQn = 75, /* TGIF0 (MTU0.TGRF compare match) */
    TGIA3_IRQn = 84, /* TGIA3 (MTU3.TGRA input capture/compare match) */
    TCIV4_IRQn = 93, /* TCIV4 (MTU4.TCNT overflow/underflow) */
    GPT13_OVF_IRQn = 239, /* GPT13_OVF (GPT13 GTCNT overflow (GTPR compare match)) */
    ESC_SYNC0_IRQn = 277, /* ESC_SYNC0 (EtherCAT Sync0 interrupt) */
    ESC_SYNC1_IRQn = 278, /* ESC_SYNC1 (EtherCAT Sync1 interrupt) */
    ESC_CAT_IRQn = 279, /* ESC_CAT (EtherCAT interrupt) */
    USB_FI_IRQn = 285, /* USB_FI (USB (Function) interrupt) */
    USB_FDMA0_IRQn = 286, /* USB_FDMA0 (USB (Function) DMA 0 transmit completion) */
    USB_FDMA1_IRQn = 287, /* USB_FDMA1 (USB (Function) DMA 1 transmit completion) */
    SCI0_ERI_IRQn = 288, /* SCI0_ERI (SCI0 Receive error) */
    SCI0_RXI_IRQn = 289, /* SCI0_RXI (SCI0 Receive data full) */
    SCI0_TXI_IRQn = 290, /* SCI0_TXI (SCI0 Transmit data empty) */
    SCI0_TEI_IRQn = 291, /* SCI0_TEI (SCI0 Transmit end) */
    SCI1_ERI_IRQn = 292, /* SCI1_ERI (SCI1 Receive error) */
    SCI1_RXI_IRQn = 293, /* SCI1_RXI (SCI1 Receive data full) */
    SCI1_TXI_IRQn = 294, /* SCI1_TXI (SCI1 Transmit data empty) */
    SCI1_TEI_IRQn = 295, /* SCI1_TEI (SCI1 Transmit end) */
    SCI2_ERI_IRQn = 296, /* SCI2_ERI (SCI2 Receive error) */
    SCI2_RXI_IRQn = 297, /* SCI2_RXI (SCI2 Receive data full) */
    SCI2_TXI_IRQn = 298, /* SCI2_TXI (SCI2 Transmit data empty) */
    SCI2_TEI_IRQn = 299, /* SCI2_TEI (SCI2 Transmit end) */
    SCI3_ERI_IRQn = 300, /* SCI3_ERI (SCI3 Receive error) */
    SCI3_RXI_IRQn = 301, /* SCI3_RXI (SCI3 Receive data full) */
    SCI3_TXI_IRQn = 302, /* SCI3_TXI (SCI3 Transmit data empty) */
    SCI3_TEI_IRQn = 303, /* SCI3_TEI (SCI3 Transmit end) */
    SCI4_ERI_IRQn = 304, /* SCI4_ERI (SCI4 Receive error) */
    SCI4_RXI_IRQn = 305, /* SCI4_RXI (SCI4 Receive data full) */
    SCI4_TXI_IRQn = 306, /* SCI4_TXI (SCI4 Transmit data empty) */
    SCI4_TEI_IRQn = 307, /* SCI4_TEI (SCI4 Transmit end) */
    IIC1_EEI_IRQn = 312, /* IIC1_EEI (IIC1 Transfer error or event generation) */
    IIC1_RXI_IRQn = 313, /* IIC1_RXI (IIC1 Receive data full) */
    IIC1_TXI_IRQn = 314, /* IIC1_TXI (IIC1 Transmit data empty) */
    IIC1_TEI_IRQn = 315, /* IIC1_TEI (IIC1 Transmit end) */
    DSMIF0_CDRUI_IRQn = 343, /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
    DSMIF1_CDRUI_IRQn = 344, /* DSMIF1_CDRUI (DSMIF1 current data register update (ORed ch3 to ch5)) */
    IIC2_EEI_IRQn = 439, /* IIC2_EEI (IIC2 Transfer error or event generation) */
    IIC2_RXI_IRQn = 440, /* IIC2_RXI (IIC2 Receive data full) */
    IIC2_TXI_IRQn = 441, /* IIC2_TXI (IIC2 Transmit data empty) */
    IIC2_TEI_IRQn = 442, /* IIC2_TEI (IIC2 Transmit end) */
    SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
} IRQn_Type;
#endif /* VECTOR_DATA_H */
