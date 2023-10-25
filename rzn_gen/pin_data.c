/* generated pin source file - do not edit */
#include "bsp_api.h"
#include "r_ioport_api.h"
#include "r_ioport.h"

extern const ioport_extend_cfg_t g_ioport_cfg_extend;

const ioport_pin_cfg_t g_bsp_pin_cfg_data[] =
        {
        { .pin = BSP_IO_PORT_00_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P000_PFC_04_DE2) },
          { .pin = BSP_IO_PORT_00_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P001_PFC_05_RXD2_SCL2_MISO2) },
          { .pin = BSP_IO_PORT_00_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P002_PFC_04_TXD2_SDA2_MOSI2) },
          { .pin = BSP_IO_PORT_00_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_00_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P004_PFC_06_MCLK0) },
          { .pin = BSP_IO_PORT_00_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P005_PFC_06_MDAT0) },
          { .pin = BSP_IO_PORT_00_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P006_PFC_02_MTIOC3B) },
          { .pin = BSP_IO_PORT_00_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P007_PFC_02_MTIOC4A) },
          { .pin = BSP_IO_PORT_01_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P010_PFC_04_MTIOC4C) },
          { .pin = BSP_IO_PORT_01_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P011_PFC_04_MTIOC3D) },
          { .pin = BSP_IO_PORT_01_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P012_PFC_03_MTIOC4B) },
          { .pin = BSP_IO_PORT_01_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P013_PFC_02_MTIOC4D) },
          { .pin = BSP_IO_PORT_01_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P014_PFC_03_POE0) },
          { .pin = BSP_IO_PORT_01_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_01_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_01_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_02_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_02_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P021_PFC_03_ESC_SYNC0) },
          { .pin = BSP_IO_PORT_02_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P022_PFC_08_CANTX0) },
          { .pin = BSP_IO_PORT_02_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_02_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P024_PFC_00_TDO) },
          { .pin = BSP_IO_PORT_02_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P025_PFC_01_TDI) },
          { .pin = BSP_IO_PORT_02_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P026_PFC_00_TMS_SWDIO) },
          { .pin = BSP_IO_PORT_02_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P027_PFC_00_TCK_SWCLK) },
          { .pin = BSP_IO_PORT_03_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_03_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_03_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_03_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_04_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P040_PFC_04_RXD3_SCL3_MISO3) },
          { .pin = BSP_IO_PORT_04_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P041_PFC_03_IIC_SDA2) },
          { .pin = BSP_IO_PORT_04_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P044_PFC_06_SPI_RSPCK1) },
          { .pin = BSP_IO_PORT_04_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P045_PFC_01_DE3) },
          { .pin = BSP_IO_PORT_05_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_05_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_05_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_05_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P053_PFC_09_IIC_SDA1) },
          { .pin = BSP_IO_PORT_05_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P054_PFC_04_RXD4_SCL4_MISO4) },
          { .pin = BSP_IO_PORT_05_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P055_PFC_02_ESC_PHYLINK1) },
          { .pin = BSP_IO_PORT_05_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P056_PFC_01_ETH1_RXER) },
          { .pin = BSP_IO_PORT_05_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P057_PFC_00_ETH1_TXD2) },
          { .pin = BSP_IO_PORT_06_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P060_PFC_00_ETH1_TXD3) },
          { .pin = BSP_IO_PORT_06_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P061_PFC_00_ETH1_REFCLK) },
          { .pin = BSP_IO_PORT_06_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P062_PFC_00_ETH1_TXD1) },
          { .pin = BSP_IO_PORT_06_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P063_PFC_00_ETH1_TXD0) },
          { .pin = BSP_IO_PORT_06_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P064_PFC_00_ETH1_TXCLK) },
          { .pin = BSP_IO_PORT_06_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P065_PFC_00_ETH1_TXEN) },
          { .pin = BSP_IO_PORT_06_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P066_PFC_00_ETH1_RXD0) },
          { .pin = BSP_IO_PORT_06_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P067_PFC_00_ETH1_RXD1) },
          { .pin = BSP_IO_PORT_07_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P070_PFC_00_ETH1_RXD2) },
          { .pin = BSP_IO_PORT_07_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P071_PFC_00_ETH1_RXD3) },
          { .pin = BSP_IO_PORT_07_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P072_PFC_00_ETH1_RXDV) },
          { .pin = BSP_IO_PORT_07_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P073_PFC_00_ETH1_RXCLK) },
          { .pin = BSP_IO_PORT_07_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P074_PFC_02_USB_VBUSIN) },
          { .pin = BSP_IO_PORT_08_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P084_PFC_00_ETH0_RXD3) },
          { .pin = BSP_IO_PORT_08_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P085_PFC_00_ETH0_RXDV) },
          { .pin = BSP_IO_PORT_08_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P086_PFC_00_ETH0_RXCLK) },
          { .pin = BSP_IO_PORT_08_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P087_PFC_00_GMAC_MDC) },
          { .pin = BSP_IO_PORT_09_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P090_PFC_00_GMAC_MDIO) },
          { .pin = BSP_IO_PORT_09_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P091_PFC_00_ETH0_REFCLK) },
          { .pin = BSP_IO_PORT_09_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P092_PFC_01_ETH0_RXER) },
          { .pin = BSP_IO_PORT_09_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P093_PFC_00_ETH0_TXD3) },
          { .pin = BSP_IO_PORT_09_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P094_PFC_00_ETH0_TXD2) },
          { .pin = BSP_IO_PORT_09_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P095_PFC_00_ETH0_TXD1) },
          { .pin = BSP_IO_PORT_09_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P096_PFC_00_ETH0_TXD0) },
          { .pin = BSP_IO_PORT_09_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P097_PFC_00_ETH0_TXCLK) },
          { .pin = BSP_IO_PORT_10_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P100_PFC_00_ETH0_TXEN) },
          { .pin = BSP_IO_PORT_10_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P101_PFC_00_ETH0_RXD0) },
          { .pin = BSP_IO_PORT_10_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P102_PFC_00_ETH0_RXD1) },
          { .pin = BSP_IO_PORT_10_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P103_PFC_00_ETH0_RXD2) },
          { .pin = BSP_IO_PORT_10_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P104_PFC_03_ESC_PHYLINK0) },
          { .pin = BSP_IO_PORT_12_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_13_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P132_PFC_05_ESC_I2CCLK) },
          { .pin = BSP_IO_PORT_13_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P133_PFC_04_ESC_I2CDATA) },
          { .pin = BSP_IO_PORT_13_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_13_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P135_PFC_04_MTCLKA) },
          { .pin = BSP_IO_PORT_13_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P136_PFC_04_MTCLKB) },
          { .pin = BSP_IO_PORT_13_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P137_PFC_04_MTCLKC) },
          { .pin = BSP_IO_PORT_14_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P140_PFC_04_MTCLKD) },
          { .pin = BSP_IO_PORT_14_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P141_PFC_03_MTIOC8A) },
          { .pin = BSP_IO_PORT_14_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_14_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_14_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P144_PFC_02_ESC_IRQ) },
          { .pin = BSP_IO_PORT_14_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P145_PFC_02_POE8) },
          { .pin = BSP_IO_PORT_14_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_14_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P147_PFC_03_SPI_MISO1) },
          { .pin = BSP_IO_PORT_15_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P150_PFC_03_SPI_MOSI1) },
          { .pin = BSP_IO_PORT_15_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_15_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_15_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P153_PFC_02_MCLK1) },
          { .pin = BSP_IO_PORT_15_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P154_PFC_02_MDAT1) },
          { .pin = BSP_IO_PORT_15_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_15_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW) },
          { .pin = BSP_IO_PORT_15_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW) },
          { .pin = BSP_IO_PORT_16_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P160_PFC_03_SPI_MOSI3) },
          { .pin = BSP_IO_PORT_16_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P161_PFC_04_SPI_MISO3) },
          { .pin = BSP_IO_PORT_16_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P162_PFC_03_SPI_RSPCK3) },
          { .pin = BSP_IO_PORT_16_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P163_PFC_05_SPI_SSL30) },
          { .pin = BSP_IO_PORT_16_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P165_PFC_01_TXD0_SDA0_MOSI0) },
          { .pin = BSP_IO_PORT_16_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_PULLUP_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P166_PFC_02_RXD0_SCL0_MISO0) },
          { .pin = BSP_IO_PORT_16_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P167_PFC_02_XSPI1_IO0) },
          { .pin = BSP_IO_PORT_17_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P170_PFC_02_XSPI1_IO1) },
          { .pin = BSP_IO_PORT_17_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P173_PFC_07_XSPI1_IO2) },
          { .pin = BSP_IO_PORT_17_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P174_PFC_07_XSPI1_IO3) },
          { .pin = BSP_IO_PORT_17_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_17_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_17_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P177_PFC_07_XSPI1_CKP) },
          { .pin = BSP_IO_PORT_18_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P180_PFC_04_TXD3_SDA3_MOSI3) },
          { .pin = BSP_IO_PORT_18_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_18_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P182_PFC_05_XSPI1_CS0) },
          { .pin = BSP_IO_PORT_18_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_18_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P184_PFC_02_TXD4_SDA4_MOSI4) },
          { .pin = BSP_IO_PORT_18_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P185_PFC_08_CANRX0) },
          { .pin = BSP_IO_PORT_18_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P186_PFC_06_IIC_SCL2) },
          { .pin = BSP_IO_PORT_19_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_20_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P201_PFC_01_ESC_LINKACT0) },
          { .pin = BSP_IO_PORT_20_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P202_PFC_01_ESC_LEDRUN) },
          { .pin = BSP_IO_PORT_20_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P203_PFC_01_ESC_LEDERR) },
          { .pin = BSP_IO_PORT_20_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P204_PFC_01_ESC_LINKACT1) },
          { .pin = BSP_IO_PORT_21_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P211_PFC_07_IIC_SCL1) },
          { .pin = BSP_IO_PORT_21_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P212_PFC_02_MTIOC6B) },
          { .pin = BSP_IO_PORT_21_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_21_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P214_PFC_02_MTIOC6D) },
          { .pin = BSP_IO_PORT_21_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P215_PFC_03_MTIOC7A) },
          { .pin = BSP_IO_PORT_21_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P216_PFC_03_MTIOC7B) },
          { .pin = BSP_IO_PORT_21_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P217_PFC_03_MTIOC7C) },
          { .pin = BSP_IO_PORT_22_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P220_PFC_03_MTIOC7D) },
          { .pin = BSP_IO_PORT_22_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P221_PFC_03_POE4) },
          { .pin = BSP_IO_PORT_22_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_22_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_23_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P237_PFC_07_MCLK4) },
          { .pin = BSP_IO_PORT_24_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P240_PFC_08_MDAT4) },
          { .pin = BSP_IO_PORT_24_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P241_PFC_07_MCLK5) },
          { .pin = BSP_IO_PORT_24_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P242_PFC_07_MDAT5) }, };

const ioport_cfg_t g_bsp_pin_cfg =
{ .number_of_pins = sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t),
  .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
  .p_extend = &g_ioport_cfg_extend, };
