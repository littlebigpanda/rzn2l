/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"
#define DE2 (IOPORT_PORT_00_PIN_0) /* 2轴编码器DE信号 */
#define RX2 (IOPORT_PORT_00_PIN_1) /* 2轴编码器RX信号 */
#define TX2 (IOPORT_PORT_00_PIN_2) /* 2轴编码器TX信号 */
#define Z1 (IOPORT_PORT_00_PIN_3) /* 1轴增量式编码器Z信号 */
#define CLK1_U (IOPORT_PORT_00_PIN_4) /* 1轴U相电流采样时钟信号 */
#define DATA1_U (IOPORT_PORT_00_PIN_5) /* 1轴U相电流采样数据信号 */
#define PWM1_UP (IOPORT_PORT_00_PIN_6) /* 1轴PWM信号UP */
#define PWM1_VP (IOPORT_PORT_00_PIN_7) /* 1轴PWM信号VP */
#define PWM1_VN (IOPORT_PORT_01_PIN_0) /* 1轴PWM信号VN */
#define PWM1_UN (IOPORT_PORT_01_PIN_1) /* 1轴PWM信号UN */
#define PWM1_WP (IOPORT_PORT_01_PIN_2) /* 1轴PWM信号WP */
#define PWM1_WN (IOPORT_PORT_01_PIN_3) /* 1轴PWM信号WN */
#define IPM_OC1 (IOPORT_PORT_01_PIN_4) /* 1轴IPM过流信号 */
#define DO1 (IOPORT_PORT_01_PIN_5) /* 通用DO1 */
#define ECAT_ACT0 (IOPORT_PORT_01_PIN_6) /* ECAT数据指示0(from PHY) */
#define ECAT1_ACT1 (IOPORT_PORT_01_PIN_7) /* ECAT数据指示1(from PHY) */
#define ISO5 (IOPORT_PORT_02_PIN_0) /* 芯片间通讯信号5 */
#define SYNC0 (IOPORT_PORT_02_PIN_1) /* EtherCAT同步信号 */
#define CAN_TX (IOPORT_PORT_02_PIN_2) /* CAN通讯发送信号 */
#define FAN (IOPORT_PORT_02_PIN_3) /* 风扇控制信号 */
#define TDO (IOPORT_PORT_02_PIN_4) /* JTAG调试口TDO */
#define TDI (IOPORT_PORT_02_PIN_5) /* JTAG调试口TDI */
#define TMS (IOPORT_PORT_02_PIN_6) /* JTAG调试口TMS */
#define TCK (IOPORT_PORT_02_PIN_7) /* JTAG调试口TCK */
#define PIN_DI1 (IOPORT_PORT_03_PIN_0) /* 通用DI1 */
#define PIN_STO2 (IOPORT_PORT_03_PIN_5) /* STO2输入信号 */
#define PIN_DI2 (IOPORT_PORT_03_PIN_6) /* 通用DI2 */
#define PIN_DI3 (IOPORT_PORT_03_PIN_7) /* 通用DI3 */
#define RX1 (IOPORT_PORT_04_PIN_0) /* 1轴编码器RX信号 */
#define KB_SDA (IOPORT_PORT_04_PIN_1) /* 键盘显示数据信号 */
#define SPI_CLK2 (IOPORT_PORT_04_PIN_4) /* 2轴Biss_C(SPI)时钟信号 */
#define MD0_DE1 (IOPORT_PORT_04_PIN_5) /* BOOT模式选择与1轴编码器DE信号 */
#define MD1 (IOPORT_PORT_04_PIN_6) /* BOOT模式选择1 */
#define MD2 (IOPORT_PORT_04_PIN_7) /* BOOT模式选择2 */
#define AC_Loss (IOPORT_PORT_05_PIN_0) /* 交流输入缺相检测 */
#define DO2 (IOPORT_PORT_05_PIN_1) /* 通用DO2 */
#define PWM_OE1 (IOPORT_PORT_05_PIN_2) /* 1轴PWM使能信号 */
#define SDA (IOPORT_PORT_05_PIN_3) /* MCU_EEPROM数据信号 */
#define ZX_485_RX (IOPORT_PORT_05_PIN_4) /* RS485总线RX信号 */
#define ECAT1_LINK (IOPORT_PORT_05_PIN_5) /* ETherCAT端口1连接信号 */
#define ECAT1_RXER (IOPORT_PORT_05_PIN_6) /* ETherCAT端口1接收错误信号 */
#define ECAT1_TXD2 (IOPORT_PORT_05_PIN_7) /* ETherCAT端口1发送数据信号2 */
#define ECAT1_TXD3 (IOPORT_PORT_06_PIN_0) /* ETherCAT端口1发送数据信号3 */
#define ECAT1_REFCLK (IOPORT_PORT_06_PIN_1) /* ETherCAT端口1时钟信号(To PHY) */
#define ECAT1_TXD1 (IOPORT_PORT_06_PIN_2) /* ETherCAT端口1发送数据信号1 */
#define ECAT1_TXD0 (IOPORT_PORT_06_PIN_3) /* ETherCAT端口1发送数据信号0 */
#define ECAT1_TXC (IOPORT_PORT_06_PIN_4) /* ETherCAT端口1发送完成信号 */
#define ECAT1_TXEN (IOPORT_PORT_06_PIN_5) /* ETherCAT端口1发送使能信号 */
#define ECAT1_RXD0 (IOPORT_PORT_06_PIN_6) /* ETherCAT端口1接收数据信号0 */
#define ECAT1_RXD1 (IOPORT_PORT_06_PIN_7) /* ETherCAT端口1接收数据信号1 */
#define ECAT1_RXD2 (IOPORT_PORT_07_PIN_0) /* ETherCAT端口1接收数据信号2 */
#define ECAT1_RXD3 (IOPORT_PORT_07_PIN_1) /* ETherCAT端口1接收数据信号3 */
#define ECAT1_RXDV (IOPORT_PORT_07_PIN_2) /* ETherCAT端口1接收数据有效信号 */
#define ECAT1_RXC (IOPORT_PORT_07_PIN_3) /* ETherCAT端口1接收数据完成 */
#define USB_Vbus_IN (IOPORT_PORT_07_PIN_4) /* USB电源输入检测 */
#define ECAT0_RXD3 (IOPORT_PORT_08_PIN_4) /* ETherCAT端口0接收数据信号3 */
#define ECAT0_RXDV (IOPORT_PORT_08_PIN_5) /* ETherCAT端口0接收数据有效信号 */
#define ECAT0_RXC (IOPORT_PORT_08_PIN_6) /* ETherCAT端口0接收数据完成 */
#define ECAT0_MDC (IOPORT_PORT_08_PIN_7) /* ETherCAT PHY管理时钟 */
#define ECAT0_MDIO (IOPORT_PORT_09_PIN_0) /* ETherCAT PHY芯片管理数据 */
#define ECAT0_REFCLK (IOPORT_PORT_09_PIN_1) /* ETherCAT端口0时钟信号(To PHY) */
#define ECAT0_RXER (IOPORT_PORT_09_PIN_2) /* ETherCAT端口0接收错误 */
#define ECAT0_TXD3 (IOPORT_PORT_09_PIN_3) /* ETherCAT端口0发送数据信号3 */
#define ECAT0_TXD2 (IOPORT_PORT_09_PIN_4) /* ETherCAT端口0发送数据信号2 */
#define ECAT0_TXD1 (IOPORT_PORT_09_PIN_5) /* ETherCAT端口0发送数据信号1 */
#define ECAT0_TXD0 (IOPORT_PORT_09_PIN_6) /* ETherCAT端口0发送数据信号0 */
#define ECAT0_TXC (IOPORT_PORT_09_PIN_7) /* ETherCAT端口0发送完成信号 */
#define ECAT0_TXEN (IOPORT_PORT_10_PIN_0) /* ETherCAT端口0发送使能信号 */
#define ECAT0_RXD0 (IOPORT_PORT_10_PIN_1) /* ETherCAT端口0接收数据信号0 */
#define ECAT0_RXD1 (IOPORT_PORT_10_PIN_2) /* ETherCAT端口0接收数据信号1 */
#define ECAT0_RXD2 (IOPORT_PORT_10_PIN_3) /* ETherCAT端口0接收数据信号2 */
#define ECAT0_LINK (IOPORT_PORT_10_PIN_4) /* ETherCAT端口0连接信号 */
#define DB1 (IOPORT_PORT_12_PIN_4) /* 1轴动态制动信号 */
#define ECAT_EEPROM_CLK (IOPORT_PORT_13_PIN_2) /* ETherCAT_EEPROM 时钟信号 */
#define ECAT_EEPROM_DATA (IOPORT_PORT_13_PIN_3) /* ETherCAT_EEPROM数据信号 */
#define ECAT_RESETOUT (IOPORT_PORT_13_PIN_4) /* ETherCAT复位信号 */
#define PUL1_A2 (IOPORT_PORT_13_PIN_5) /* 1轴脉冲信号(2轴增量式编码器A信号) */
#define DIR1_B2 (IOPORT_PORT_13_PIN_6) /* 1轴方向信号(2轴增量式编码器B信号) */
#define PUL2_A1 (IOPORT_PORT_13_PIN_7) /* 1轴增量式编码器A信号 */
#define DIR2_B1 (IOPORT_PORT_14_PIN_0) /* 1轴增量式编码器B信号 */
#define SYNC0_DC (IOPORT_PORT_14_PIN_1) /* ETherCAT SYNC0检测(引出测试点) */
#define BK_FB (IOPORT_PORT_14_PIN_2) /* 制动反馈信号 */
#define BK_CTRL (IOPORT_PORT_14_PIN_3) /* 制动控制信号 */
#define ECAT_IRQ (IOPORT_PORT_14_PIN_4) /* EtherCAT中断信号 */
#define OC_Vbus (IOPORT_PORT_14_PIN_5) /* 母线过流 */
#define IOS1 (IOPORT_PORT_14_PIN_6) /* 芯片间通讯信号1 */
#define SPI_MISO2 (IOPORT_PORT_14_PIN_7) /* 2轴Biss_C(SPI)数据输入信号 */
#define SPI_MOSI2 (IOPORT_PORT_15_PIN_0) /* 2轴Biss_C(SPI)数据输出信号 */
#define IOS2 (IOPORT_PORT_15_PIN_1) /* 芯片间通讯信号2 */
#define DB2 (IOPORT_PORT_15_PIN_2) /* 2轴动态制动信号 */
#define CLK2_U (IOPORT_PORT_15_PIN_3) /* 2轴U相电流采样时钟信号 */
#define DATA2_U (IOPORT_PORT_15_PIN_4) /* 2轴U相电流采样数据信号 */
#define Relay_CTRL (IOPORT_PORT_15_PIN_5) /* 软启动 */
#define ZX_485_DE (IOPORT_PORT_15_PIN_6) /* RS485总线控制信号DE */
#define TS_485_DE (IOPORT_PORT_15_PIN_7) /* 调试485控制信号 */
#define SPI_MOSI1 (IOPORT_PORT_16_PIN_0) /* 1轴Biss-C(SPI)数据输出信号 */
#define SPI_MISO1 (IOPORT_PORT_16_PIN_1) /* 1轴Biss-C(SPI)数据输入信号 */
#define SPI_CLK1 (IOPORT_PORT_16_PIN_2) /* 1轴Biss-C(SPI)时钟信号 */
#define SPI_CS1 (IOPORT_PORT_16_PIN_3) /* 1轴Biss-C(SPI)片选信号 */
#define TS_485_TX (IOPORT_PORT_16_PIN_5) /* 调试485发送信号 */
#define TS_485_RX (IOPORT_PORT_16_PIN_6) /* 调试485接收信号 */
#define XSPI1_IO0 (IOPORT_PORT_16_PIN_7) /* MCU外部flash数据信号0 */
#define XSPI1_IO1 (IOPORT_PORT_17_PIN_0) /* MCU外部flash数据信号1 */
#define XSPI1_IO2 (IOPORT_PORT_17_PIN_3) /* MCU外部flash数据信号2 */
#define XSPI1_IO3 (IOPORT_PORT_17_PIN_4) /* MCU外部flash数据信号3 */
#define IOS3 (IOPORT_PORT_17_PIN_5) /* 芯片间通讯信号3 */
#define IOS4 (IOPORT_PORT_17_PIN_6) /* 芯片间通讯信号4 */
#define XSPI1_CKP (IOPORT_PORT_17_PIN_7) /* MCU外部flash时钟信号 */
#define TX1 (IOPORT_PORT_18_PIN_0) /* 1轴编码器TX信号 */
#define PIN_DI4 (IOPORT_PORT_18_PIN_1) /* 通用DI4 */
#define XSPI1_CS (IOPORT_PORT_18_PIN_2) /* MCU外部flash片选信号 */
#define Z2 (IOPORT_PORT_18_PIN_3) /* 2轴增量编码器Z信号 */
#define ZX_485_TX (IOPORT_PORT_18_PIN_4) /* RS485总线TX信号 */
#define CAN_RX (IOPORT_PORT_18_PIN_5) /* CAN通讯接收信号 */
#define KB_SCL (IOPORT_PORT_18_PIN_6) /* 键盘显示时钟信号 */
#define MDV4_ISO6 (IOPORT_PORT_19_PIN_0) /* QSPI1外设电源选择与芯片间通讯信号6 */
#define ECAT_LINK0 (IOPORT_PORT_20_PIN_1) /* ETherCAT连接指示0 */
#define ECAT_RUN (IOPORT_PORT_20_PIN_2) /* ETherCAT运行指示 */
#define ECAT_ERR (IOPORT_PORT_20_PIN_3) /* ETherCAT故障指示 */
#define ECAT_LINK1 (IOPORT_PORT_20_PIN_4) /* ETherCAT连接指示1 */
#define SCL (IOPORT_PORT_21_PIN_1) /* MCU_EEPROM时钟信号 */
#define PWM2_UP (IOPORT_PORT_21_PIN_2) /* 2轴PWM信号UP */
#define DO4 (IOPORT_PORT_21_PIN_3) /* 通用DO4 */
#define PWM2_UN (IOPORT_PORT_21_PIN_4) /* 2轴PWM信号UN */
#define PWM2_VP (IOPORT_PORT_21_PIN_5) /* 2轴PWM信号VP */
#define PWM2_WP (IOPORT_PORT_21_PIN_6) /* 2轴PWM信号WP */
#define PWM2_VN (IOPORT_PORT_21_PIN_7) /* 2轴PWM信号VN */
#define PWM2_WN (IOPORT_PORT_22_PIN_0) /* 2轴PWM信号WN */
#define IPM_OC2 (IOPORT_PORT_22_PIN_1) /* 2轴IPM过流信号 */
#define PIN_STO1 (IOPORT_PORT_22_PIN_2) /* STO1输入信号 */
#define DO3 (IOPORT_PORT_22_PIN_3) /* 通用DO3 */
#define CLK1_V (IOPORT_PORT_23_PIN_7) /* 1轴V相电流采样时钟信号 */
#define DATA1_V (IOPORT_PORT_24_PIN_0) /* 1轴V相电流采样数据信号 */
#define CLK2_V (IOPORT_PORT_24_PIN_1) /* 2轴V相电流采样时钟信号 */
#define DATA2_V (IOPORT_PORT_24_PIN_2) /* 2轴V相电流采样数据信号 */
extern const ioport_cfg_t g_bsp_pin_cfg; /* servov5_rzn2l.pincfg */
#endif /* BSP_PIN_CFG_H_ */
