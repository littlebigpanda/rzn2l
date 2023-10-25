/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#include "bsp_api.h"
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (12)
#endif
/* ISR prototypes */
void dmac_int_isr(void);
void null(void);
void dsmif_cdrui_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_DMAC0_INT0 ((IRQn_Type) 21) /* DMAC0_INT0 (DMAC0 transfer completion 0) */
#define VECTOR_NUMBER_DMAC0_INT1 ((IRQn_Type) 22) /* DMAC0_INT1 (DMAC0 transfer completion 1) */
#define VECTOR_NUMBER_TGIC0 ((IRQn_Type) 71) /* TGIC0 (MTU0.TGRC input capture/compare match) */
#define VECTOR_NUMBER_IIC1_EEI ((IRQn_Type) 312) /* IIC1_EEI (IIC1 Transfer error or event generation) */
#define VECTOR_NUMBER_IIC1_RXI ((IRQn_Type) 313) /* IIC1_RXI (IIC1 Receive data full) */
#define VECTOR_NUMBER_IIC1_TXI ((IRQn_Type) 314) /* IIC1_TXI (IIC1 Transmit data empty) */
#define VECTOR_NUMBER_IIC1_TEI ((IRQn_Type) 315) /* IIC1_TEI (IIC1 Transmit end) */
#define VECTOR_NUMBER_DSMIF0_CDRUI ((IRQn_Type) 343) /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
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
    TGIC0_IRQn = 71, /* TGIC0 (MTU0.TGRC input capture/compare match) */
    IIC1_EEI_IRQn = 312, /* IIC1_EEI (IIC1 Transfer error or event generation) */
    IIC1_RXI_IRQn = 313, /* IIC1_RXI (IIC1 Receive data full) */
    IIC1_TXI_IRQn = 314, /* IIC1_TXI (IIC1 Transmit data empty) */
    IIC1_TEI_IRQn = 315, /* IIC1_TEI (IIC1 Transmit end) */
    DSMIF0_CDRUI_IRQn = 343, /* DSMIF0_CDRUI (DSMIF0 current data register update (ORed ch0 to ch2)) */
    IIC2_EEI_IRQn = 439, /* IIC2_EEI (IIC2 Transfer error or event generation) */
    IIC2_RXI_IRQn = 440, /* IIC2_RXI (IIC2 Receive data full) */
    IIC2_TXI_IRQn = 441, /* IIC2_TXI (IIC2 Transmit data empty) */
    IIC2_TEI_IRQn = 442, /* IIC2_TEI (IIC2 Transmit end) */
    SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
} IRQn_Type;
#endif /* VECTOR_DATA_H */
