/* generated HAL source file - do not edit */
#include "hal_data.h"

dmac_instance_ctrl_t g_iic_led_tx_dma_ctrl;

dmac_register_set_setting_t g_iic_led_tx_dma_next1_register_setting =
{ .p_dest = NULL, .p_src = NULL, .length = 1 };

dmac_extended_info_t g_iic_led_tx_dma_extend_info =
{ .src_size = DMAC_TRANSFER_SIZE_1_BYTE, .dest_size = DMAC_TRANSFER_SIZE_1_BYTE, .p_next1_register_setting =
          &g_iic_led_tx_dma_next1_register_setting, };

transfer_info_t g_iic_led_tx_dma_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED, .repeat_area = (transfer_repeat_area_t) 0, // Unused
  .irq = (transfer_irq_t) 0, // Unused
  .chain_mode = (transfer_chain_mode_t) 0, // Unused
  .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .size = (transfer_size_t) 0, // Unused
  .mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0, // Unused
  .length = 1,
  .p_extend = &g_iic_led_tx_dma_extend_info, };

const dmac_extended_cfg_t g_iic_led_tx_dma_extend =
{ .unit = 1, .channel = 2,
#if defined(VECTOR_NUMBER_DMAC1_INT2)
    .dmac_int_irq         = VECTOR_NUMBER_DMAC1_INT2,
#else
  .dmac_int_irq = FSP_INVALID_VECTOR,
#endif
  .dmac_int_ipl = (BSP_IRQ_DISABLED),
  .dmac_int_irq_detect_type = (0),

  .activation_source = ELC_EVENT_IIC0_TXI,

  .ack_mode = DMAC_ACK_MODE_LEVEL_MODE,
  .detection_mode = (dmac_detection_t) ((0) << 2 | (1) << 1 | (0) << 0), .activation_request_source_select =
          DMAC_REQUEST_DIRECTION_DESTINATION_MODULE,

  .next_register_operation = DMAC_REGISTER_SELECT_REVERSE_DISABLE,

  .transfer_interval = 0,
  .channel_scheduling = DMAC_CHANNEL_SCHEDULING_FIXED,

  .p_callback = NULL,
  .p_context = NULL,

  .p_peripheral_module_handler = NULL, };
const transfer_cfg_t g_iic_led_tx_dma_cfg =
{ .p_info = &g_iic_led_tx_dma_info, .p_extend = &g_iic_led_tx_dma_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_iic_led_tx_dma =
{ .p_ctrl = &g_iic_led_tx_dma_ctrl, .p_cfg = &g_iic_led_tx_dma_cfg, .p_api = &g_transfer_on_dmac };
dmac_instance_ctrl_t g_sci_zx_tx_dma_ctrl;

dmac_register_set_setting_t g_sci_zx_tx_dma_next1_register_setting =
{ .p_dest = NULL, .p_src = NULL, .length = 1 };

dmac_extended_info_t g_sci_zx_tx_dma_extend_info =
{ .src_size = DMAC_TRANSFER_SIZE_1_BYTE, .dest_size = DMAC_TRANSFER_SIZE_1_BYTE, .p_next1_register_setting =
          &g_sci_zx_tx_dma_next1_register_setting, };

transfer_info_t g_sci_zx_tx_dma_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED, .repeat_area = (transfer_repeat_area_t) 0, // Unused
  .irq = (transfer_irq_t) 0, // Unused
  .chain_mode = (transfer_chain_mode_t) 0, // Unused
  .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .size = (transfer_size_t) 0, // Unused
  .mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0, // Unused
  .length = 1,
  .p_extend = &g_sci_zx_tx_dma_extend_info, };

const dmac_extended_cfg_t g_sci_zx_tx_dma_extend =
{ .unit = 0, .channel = 1,
#if defined(VECTOR_NUMBER_DMAC0_INT1)
    .dmac_int_irq         = VECTOR_NUMBER_DMAC0_INT1,
#else
  .dmac_int_irq = FSP_INVALID_VECTOR,
#endif
  .dmac_int_ipl = (12),
  .dmac_int_irq_detect_type = (0),

  .activation_source = ELC_EVENT_SCI3_TXI,

  .ack_mode = DMAC_ACK_MODE_LEVEL_MODE,
  .detection_mode = (dmac_detection_t) ((0) << 2 | (1) << 1 | (0) << 0), .activation_request_source_select =
          DMAC_REQUEST_DIRECTION_DESTINATION_MODULE,

  .next_register_operation = DMAC_REGISTER_SELECT_REVERSE_DISABLE,

  .transfer_interval = 0,
  .channel_scheduling = DMAC_CHANNEL_SCHEDULING_FIXED,

  .p_callback = sci_zx_tx_dma_transfer_end_isr,
  .p_context = NULL,

  .p_peripheral_module_handler = NULL, };
const transfer_cfg_t g_sci_zx_tx_dma_cfg =
{ .p_info = &g_sci_zx_tx_dma_info, .p_extend = &g_sci_zx_tx_dma_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_sci_zx_tx_dma =
{ .p_ctrl = &g_sci_zx_tx_dma_ctrl, .p_cfg = &g_sci_zx_tx_dma_cfg, .p_api = &g_transfer_on_dmac };
dmac_instance_ctrl_t g_sci_debug_tx_dma_ctrl;

dmac_register_set_setting_t g_sci_debug_tx_dma_next1_register_setting =
{ .p_dest = NULL, .p_src = NULL, .length = 1 };

dmac_extended_info_t g_sci_debug_tx_dma_extend_info =
{ .src_size = DMAC_TRANSFER_SIZE_1_BYTE, .dest_size = DMAC_TRANSFER_SIZE_1_BYTE, .p_next1_register_setting =
          &g_sci_debug_tx_dma_next1_register_setting, };

transfer_info_t g_sci_debug_tx_dma_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED, .repeat_area = (transfer_repeat_area_t) 0, // Unused
  .irq = (transfer_irq_t) 0, // Unused
  .chain_mode = (transfer_chain_mode_t) 0, // Unused
  .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .size = (transfer_size_t) 0, // Unused
  .mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0, // Unused
  .length = 1,
  .p_extend = &g_sci_debug_tx_dma_extend_info, };

const dmac_extended_cfg_t g_sci_debug_tx_dma_extend =
{ .unit = 0, .channel = 0,
#if defined(VECTOR_NUMBER_DMAC0_INT0)
    .dmac_int_irq         = VECTOR_NUMBER_DMAC0_INT0,
#else
  .dmac_int_irq = FSP_INVALID_VECTOR,
#endif
  .dmac_int_ipl = (12),
  .dmac_int_irq_detect_type = (0),

  .activation_source = ELC_EVENT_SCI0_TXI,

  .ack_mode = DMAC_ACK_MODE_LEVEL_MODE,
  .detection_mode = (dmac_detection_t) ((0) << 2 | (1) << 1 | (0) << 0), .activation_request_source_select =
          DMAC_REQUEST_DIRECTION_DESTINATION_MODULE,

  .next_register_operation = DMAC_REGISTER_SELECT_REVERSE_DISABLE,

  .transfer_interval = 0,
  .channel_scheduling = DMAC_CHANNEL_SCHEDULING_FIXED,

  .p_callback = sci_debug_tx_dma_transfer_end_isr,
  .p_context = NULL,

  .p_peripheral_module_handler = NULL, };
const transfer_cfg_t g_sci_debug_tx_dma_cfg =
{ .p_info = &g_sci_debug_tx_dma_info, .p_extend = &g_sci_debug_tx_dma_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_sci_debug_tx_dma =
{ .p_ctrl = &g_sci_debug_tx_dma_ctrl, .p_cfg = &g_sci_debug_tx_dma_cfg, .p_api = &g_transfer_on_dmac };
dsmif_channel_cfg_t g_dsmif1_channel_cfg2 =
{ .ioel = 0,
  .ioeh = 0,
  .ise = 0,
  .iue = 0,
  .ckdir = DSMIF_CLOCK_CTRL_MASTER,
  .sedge = DSMIF_CLOCK_EDGE_POSITIVE,
  .ckdiv = DSMIF_MASTER_CLOCK_20MHZ_PCLKH200,
  .cmsinc = DSMIF_FILTER_ORDER_3RD,
  .cmdec = 63,
  .sde = 0,
  .ocsinc = DSMIF_FILTER_ORDER_3RD,
  .ocdec = 3,
  .ocmptbl = 0x0,
  .ocmptbh = 0x0,
  .scntl = 0x0,
  .scnth = 0x0,
  .odel = 0,
  .odeh = 0,
  .cmsh = (dsimf_data_shift_t) 6,
  .ocsh = (dsimf_data_shift_t) 18 };
#define DSMIF_CHANNEL_12
dsmif_channel_cfg_t g_dsmif1_channel_cfg1 =
{ .ioel = 0,
  .ioeh = 0,
  .ise = 0,
  .iue = 0,
  .ckdir = DSMIF_CLOCK_CTRL_MASTER,
  .sedge = DSMIF_CLOCK_EDGE_POSITIVE,
  .ckdiv = DSMIF_MASTER_CLOCK_20MHZ_PCLKH200,
  .cmsinc = DSMIF_FILTER_ORDER_3RD,
  .cmdec = 63,
  .sde = 0,
  .ocsinc = DSMIF_FILTER_ORDER_3RD,
  .ocdec = 3,
  .ocmptbl = 0x0,
  .ocmptbh = 0x0,
  .scntl = 0x0,
  .scnth = 0x0,
  .odel = 0,
  .odeh = 0,
  .cmsh = (dsimf_data_shift_t) 6,
  .ocsh = (dsimf_data_shift_t) 18 };
#define DSMIF_CHANNEL_11
dsmif_instance_ctrl_t g_dsmif1_ctrl;
#define DSMIF_MASK_UNIT_10  (DSMIF_UNIT0_MASK_10 | DSMIF_UNIT0_MASK_11 | DSMIF_UNIT0_MASK_12)
#define DSMIF_MASK_UNIT_11  (DSMIF_UNIT1_MASK_10 | DSMIF_UNIT1_MASK_11 | DSMIF_UNIT1_MASK_12)
/** DSMIF configuration extension. This extension is required and must be provided in adc_cfg_t::p_extend. */
const dsmif_extended_cfg_t g_dsmif1_cfg_extend =
{ .isel = 0, .iseh = 0, .sedm = DSMIF_SUM_ERR_DETECT_CHANNEL_0_2, .scmptbl = 2048, .scmptbh = 63487, .seel = 0, .seeh =
          0,
  .cap_trig_a = DSMIF_CAPTURE_TRIGGER_0, .cap_trig_b = DSMIF_CAPTURE_TRIGGER_NOT, .cnt_init_trig =
          DSMIF_COUNTER_INIT_TRIGGER_0,
  .edge = DSMIF_CLOCK_EDGE_POSITIVE,
#ifndef DSMIF_CHANNEL_10
#define DSMIF_UNIT0_MASK_10   (0)
#define DSMIF_UNIT1_MASK_10   (0)
  .p_channel_cfgs[0] = NULL,
#else
#define DSMIF_UNIT0_MASK_10   (DSMIF_CHANNEL_MASK_0)
#define DSMIF_UNIT1_MASK_10   (DSMIF_CHANNEL_MASK_3)
    .p_channel_cfgs[0]   = &g_dsmif1_channel_cfg0,
#endif
#ifndef DSMIF_CHANNEL_11
#define DSMIF_UNIT0_MASK_11   (0)
#define DSMIF_UNIT1_MASK_11   (0)
    .p_channel_cfgs[1]   = NULL,
#else
#define DSMIF_UNIT0_MASK_11   (DSMIF_CHANNEL_MASK_1)
#define DSMIF_UNIT1_MASK_11   (DSMIF_CHANNEL_MASK_4)
  .p_channel_cfgs[1] = &g_dsmif1_channel_cfg1,
#endif
#ifndef DSMIF_CHANNEL_12
#define DSMIF_UNIT0_MASK_12   (0)
#define DSMIF_UNIT1_MASK_12   (0)
    .p_channel_cfgs[2]   = NULL,
#else
#define DSMIF_UNIT0_MASK_12   (DSMIF_CHANNEL_MASK_2)
#define DSMIF_UNIT1_MASK_12   (DSMIF_CHANNEL_MASK_5)
  .p_channel_cfgs[2] = &g_dsmif1_channel_cfg2,
#endif
  .channel_mask = (dsmif_channel_mask_t)DSMIF_MASK_UNIT_11, };
const adc_cfg_t g_dsmif1_cfg =
{ .unit = 1, .mode = ADC_MODE_SYNCHRONIZE_SCAN,
#if defined(VECTOR_NUMBER_DSMIF1_CDRUI)
    .scan_end_irq        = VECTOR_NUMBER_DSMIF1_CDRUI,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (BSP_IRQ_DISABLED),
  .p_callback = NULL, .p_context = NULL, .p_extend = &g_dsmif1_cfg_extend, };
/* Instance structure to use this module. */
const adc_instance_t g_dsmif1 =
{ .p_ctrl = &g_dsmif1_ctrl, .p_cfg = &g_dsmif1_cfg, .p_api = &g_adc_on_dsmif };
dsmif_channel_cfg_t g_dsmif0_channel_cfg1 =
{ .ioel = 0,
  .ioeh = 0,
  .ise = 0,
  .iue = 0,
  .ckdir = DSMIF_CLOCK_CTRL_SLAVE,
  .sedge = DSMIF_CLOCK_EDGE_POSITIVE,
  .ckdiv = DSMIF_MASTER_CLOCK_20MHZ_PCLKH200,
  .cmsinc = DSMIF_FILTER_ORDER_3RD,
  .cmdec = 63,
  .sde = 0,
  .ocsinc = DSMIF_FILTER_ORDER_3RD,
  .ocdec = 3,
  .ocmptbl = 0x0,
  .ocmptbh = 0x0,
  .scntl = 0x0,
  .scnth = 0x0,
  .odel = 0,
  .odeh = 0,
  .cmsh = (dsimf_data_shift_t) 6,
  .ocsh = (dsimf_data_shift_t) 18 };
#define DSMIF_CHANNEL_01
dsmif_channel_cfg_t g_dsmif0_channel_cfg0 =
{ .ioel = 0,
  .ioeh = 0,
  .ise = 0,
  .iue = 0,
  .ckdir = DSMIF_CLOCK_CTRL_MASTER,
  .sedge = DSMIF_CLOCK_EDGE_POSITIVE,
  .ckdiv = DSMIF_MASTER_CLOCK_20MHZ_PCLKH200,
  .cmsinc = DSMIF_FILTER_ORDER_3RD,
  .cmdec = 63,
  .sde = 0,
  .ocsinc = DSMIF_FILTER_ORDER_3RD,
  .ocdec = 63,
  .ocmptbl = 2048,
  .ocmptbh = 63487,
  .scntl = 1000,
  .scnth = 1000,
  .odel = 0,
  .odeh = 0,
  .cmsh = (dsimf_data_shift_t) 6,
  .ocsh = (dsimf_data_shift_t) 6 };
#define DSMIF_CHANNEL_00
dsmif_instance_ctrl_t g_dsmif0_ctrl;
#define DSMIF_MASK_UNIT_00  (DSMIF_UNIT0_MASK_00 | DSMIF_UNIT0_MASK_01 | DSMIF_UNIT0_MASK_02)
#define DSMIF_MASK_UNIT_01  (DSMIF_UNIT1_MASK_00 | DSMIF_UNIT1_MASK_01 | DSMIF_UNIT1_MASK_02)
/** DSMIF configuration extension. This extension is required and must be provided in adc_cfg_t::p_extend. */
const dsmif_extended_cfg_t g_dsmif0_cfg_extend =
{ .isel = 0, .iseh = 0, .sedm = DSMIF_SUM_ERR_DETECT_CHANNEL_0_2, .scmptbl = 2048, .scmptbh = 63487, .seel = 0, .seeh =
          0,
  .cap_trig_a = DSMIF_CAPTURE_TRIGGER_0, .cap_trig_b = DSMIF_CAPTURE_TRIGGER_NOT, .cnt_init_trig =
          DSMIF_COUNTER_INIT_TRIGGER_0,
  .edge = DSMIF_CLOCK_EDGE_POSITIVE,
#ifndef DSMIF_CHANNEL_00
#define DSMIF_UNIT0_MASK_00   (0)
#define DSMIF_UNIT1_MASK_00   (0)
    .p_channel_cfgs[0]   = NULL,
#else
#define DSMIF_UNIT0_MASK_00   (DSMIF_CHANNEL_MASK_0)
#define DSMIF_UNIT1_MASK_00   (DSMIF_CHANNEL_MASK_3)
  .p_channel_cfgs[0] = &g_dsmif0_channel_cfg0,
#endif
#ifndef DSMIF_CHANNEL_01
#define DSMIF_UNIT0_MASK_01   (0)
#define DSMIF_UNIT1_MASK_01   (0)
    .p_channel_cfgs[1]   = NULL,
#else
#define DSMIF_UNIT0_MASK_01   (DSMIF_CHANNEL_MASK_1)
#define DSMIF_UNIT1_MASK_01   (DSMIF_CHANNEL_MASK_4)
  .p_channel_cfgs[1] = &g_dsmif0_channel_cfg1,
#endif
#ifndef DSMIF_CHANNEL_02
#define DSMIF_UNIT0_MASK_02   (0)
#define DSMIF_UNIT1_MASK_02   (0)
  .p_channel_cfgs[2] = NULL,
#else
#define DSMIF_UNIT0_MASK_02   (DSMIF_CHANNEL_MASK_2)
#define DSMIF_UNIT1_MASK_02   (DSMIF_CHANNEL_MASK_5)
    .p_channel_cfgs[2]   = &g_dsmif0_channel_cfg2,
#endif
  .channel_mask = (dsmif_channel_mask_t)DSMIF_MASK_UNIT_00, };
const adc_cfg_t g_dsmif0_cfg =
{ .unit = 0, .mode = ADC_MODE_SYNCHRONIZE_SCAN,
#if defined(VECTOR_NUMBER_DSMIF0_CDRUI)
    .scan_end_irq        = VECTOR_NUMBER_DSMIF0_CDRUI,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (3),
  .p_callback = NULL, .p_context = NULL, .p_extend = &g_dsmif0_cfg_extend, };
/* Instance structure to use this module. */
const adc_instance_t g_dsmif0 =
{ .p_ctrl = &g_dsmif0_ctrl, .p_cfg = &g_dsmif0_cfg, .p_api = &g_adc_on_dsmif };
void g_hal_init(void)
{
    g_common_init ();
}
