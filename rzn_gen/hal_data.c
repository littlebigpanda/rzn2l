/* generated HAL source file - do not edit */
#include "hal_data.h"

cmt_instance_ctrl_t g_timer_free_run_ctrl;
const timer_cfg_t g_timer_free_run_cfg =
{ .mode = TIMER_MODE_PERIODIC,
  /* Actual period: 0.01048576 seconds. */.period_counts = (uint32_t) 0x10000,
  .source_div = (timer_source_div_t) 3,
  .channel = 2,
  .p_callback = NULL,
  .p_context = NULL,
  .p_extend = NULL,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_CMT2_CMI)
    .cycle_end_irq       = VECTOR_NUMBER_CMT2_CMI,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer_free_run =
{ .p_ctrl = &g_timer_free_run_ctrl, .p_cfg = &g_timer_free_run_cfg, .p_api = &g_timer_on_cmt };
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

  .activation_source = ELC_EVENT_SCI4_TXI,

  .ack_mode = DMAC_ACK_MODE_LEVEL_MODE,
  .detection_mode = (dmac_detection_t) ((0) << 2 | (1) << 1 | (0) << 0), .activation_request_source_select =
          DMAC_REQUEST_DIRECTION_DESTINATION_MODULE,

  .next_register_operation = DMAC_REGISTER_SELECT_REVERSE_DISABLE,

  .transfer_interval = 0,
  .channel_scheduling = DMAC_CHANNEL_SCHEDULING_FIXED,

  .p_callback = sci_zx_tx_dma_transfer_end_isr,
  .p_context = (void*) &g_sci_zx_tx_dma,

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
  .p_context = (void*) &g_sci_debug_tx_dma,

  .p_peripheral_module_handler = NULL, };
const transfer_cfg_t g_sci_debug_tx_dma_cfg =
{ .p_info = &g_sci_debug_tx_dma_info, .p_extend = &g_sci_debug_tx_dma_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_sci_debug_tx_dma =
{ .p_ctrl = &g_sci_debug_tx_dma_ctrl, .p_cfg = &g_sci_debug_tx_dma_cfg, .p_api = &g_transfer_on_dmac };
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
xspi_qspi_instance_ctrl_t g_qspi_flash_ctrl;

static const spi_flash_erase_command_t g_qspi_flash_erase_command_list[] =
{
#if 4096 > 0
  { .command = 0x20, .size = 4096 },
#endif
#if 32768 > 0
  { .command = 0x52, .size = 32768 },
#endif
#if 65536 > 0
  { .command = 0xD8, .size = 65536 },
#endif
#if 0xC7 > 0
  { .command = 0xC7, .size = SPI_FLASH_ERASE_SIZE_CHIP_ERASE },
#endif
        };

static xspi_qspi_timing_setting_t g_qspi_flash_timing_settings =
{ .command_to_command_interval = XSPI_QSPI_COMMAND_INTERVAL_CLOCKS_7, .cs_pullup_lag =
          XSPI_QSPI_CS_PULLUP_CLOCKS_NO_EXTENSION,
  .cs_pulldown_lead = XSPI_QSPI_CS_PULLDOWN_CLOCKS_NO_EXTENSION };

static const xspi_qspi_extended_cfg_t g_qspi_flash_extended_cfg =
{ .unit = 1, .chip_select = XSPI_QSPI_CHIP_SELECT_0, .memory_size = XSPI_QSPI_MEMORY_SIZE_16MB, .p_timing_settings =
          &g_qspi_flash_timing_settings,
  .prefetch_en = XSPI_QSPI_PREFETCH_FUNCTION_ENABLE, };
const spi_flash_cfg_t g_qspi_flash_cfg =
{ .spi_protocol = SPI_FLASH_PROTOCOL_1S_1S_1S,
  .address_bytes = SPI_FLASH_ADDRESS_BYTES_3,
  .dummy_clocks = SPI_FLASH_DUMMY_CLOCKS_0,
  .read_command = 0x03,
  .page_program_command = 0x02,
  .write_enable_command = 0x06,
  .status_command = 0x05,
  .write_status_bit = 0,
  .xip_enter_command = 0x20,
  .xip_exit_command = 0xFF,
  .p_erase_command_list = &g_qspi_flash_erase_command_list[0],
  .erase_command_list_length = sizeof(g_qspi_flash_erase_command_list) / sizeof(g_qspi_flash_erase_command_list[0]),
  .p_extend = &g_qspi_flash_extended_cfg, };
/** This structure encompasses everything that is needed to use an instance of this interface. */
const spi_flash_instance_t g_qspi_flash =
{ .p_ctrl = &g_qspi_flash_ctrl, .p_cfg = &g_qspi_flash_cfg, .p_api = &g_spi_flash_on_xspi_qspi, };
usb_instance_ctrl_t g_basic0_ctrl;

#if !defined(g_usb_descriptor)
extern usb_descriptor_t g_usb_descriptor;
#endif
#define FSP_NOT_DEFINED (1)
const usb_cfg_t g_basic0_cfg =
{ .usb_mode = USB_MODE_PERI, .usb_speed = USB_SPEED_HS, .module_number = 0, .type = USB_CLASS_PCDC,
#if defined(g_usb_descriptor)
                .p_usb_reg = g_usb_descriptor,
#else
  .p_usb_reg = &g_usb_descriptor,
#endif
  .usb_complience_cb = NULL,
#if defined(VECTOR_NUMBER_USB_FI)
                .irq       = VECTOR_NUMBER_USB_FI,
#elif defined(VECTOR_NUMBER_USB_HI)
                .irq       = VECTOR_NUMBER_USB_HI,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_RESUME)
                .irq_r     = VECTOR_NUMBER_USBFS_RESUME,
#else
  .irq_r = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USB_FDMA0)
                .irq_d0    = VECTOR_NUMBER_USB_FDMA0,
#else
  .irq_d0 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USB_FDMA1)
                .irq_d1    = VECTOR_NUMBER_USB_FDMA1,
#else
  .irq_d1 = FSP_INVALID_VECTOR,
#endif
  .hsirq = FSP_INVALID_VECTOR,
  .hsirq_d0 = FSP_INVALID_VECTOR, .hsirq_d1 = FSP_INVALID_VECTOR, .ipl = (30), .ipl_r = (30), .ipl_d0 = (30), .ipl_d1 =
          (30),
  .hsipl = (12), .hsipl_d0 = (12), .hsipl_d1 = (12),
#if (BSP_CFG_RTOS == 2)
                .p_usb_apl_callback = NULL,
#else
  .p_usb_apl_callback = NULL,
#endif
#if defined(NULL)
                .p_context = NULL,
#else
  .p_context = &NULL,
#endif
  .p_transfer_tx = NULL,
  .p_transfer_rx = NULL, };
#undef FSP_NOT_DEFINED

/* Instance structure to use this module. */
const usb_instance_t g_basic0 =
{ .p_ctrl = &g_basic0_ctrl, .p_cfg = &g_basic0_cfg, .p_api = &g_usb_on_usb, };

void g_hal_init(void)
{
    g_common_init ();
}
