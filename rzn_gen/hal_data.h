/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_dsmif.h"
#include "r_adc_api.h"
FSP_HEADER
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_iic_led_tx_dma;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_iic_led_tx_dma_ctrl;
extern const transfer_cfg_t g_iic_led_tx_dma_cfg;

#ifndef NULL
void NULL(dmac_callback_args_t *p_args);
#endif

#ifndef NULL
extern void NULL(IRQn_Type irq);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_sci_zx_tx_dma;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_sci_zx_tx_dma_ctrl;
extern const transfer_cfg_t g_sci_zx_tx_dma_cfg;

#ifndef sci_zx_tx_dma_transfer_end_isr
void sci_zx_tx_dma_transfer_end_isr(dmac_callback_args_t *p_args);
#endif

#ifndef NULL
extern void NULL(IRQn_Type irq);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_sci_debug_tx_dma;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_sci_debug_tx_dma_ctrl;
extern const transfer_cfg_t g_sci_debug_tx_dma_cfg;

#ifndef sci_debug_tx_dma_transfer_end_isr
void sci_debug_tx_dma_transfer_end_isr(dmac_callback_args_t *p_args);
#endif

#ifndef NULL
extern void NULL(IRQn_Type irq);
#endif
/** ADC on DSMIF Instance. */
extern const adc_instance_t g_dsmif1;
extern dsmif_instance_ctrl_t g_dsmif1_ctrl;
extern const adc_cfg_t g_dsmif1_cfg;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
/** ADC on DSMIF Instance. */
extern const adc_instance_t g_dsmif0;
extern dsmif_instance_ctrl_t g_dsmif0_ctrl;
extern const adc_cfg_t g_dsmif0_cfg;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
