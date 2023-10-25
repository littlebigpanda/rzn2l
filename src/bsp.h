/*
 * bsp.h
 *
 *  Created on: Oct 24, 2023
 *      Author: xgj12
 */

#ifndef BSP_H_
#define BSP_H_


/* SCI相关 */

/* 这些由FSP中的中断配置生成，这里仅仅是为了编译通过 */

/* SCI0 - 调试用SCI端口 */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 288) /* SCI0_ERI (SCI0 Receive error) */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 289) /* SCI0_RXI (SCI0 Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 290) /* SCI0_TXI (SCI0 Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 291) /* SCI0_TEI (SCI0 Transmit end) */

/* SCI2 - 2轴编码器用SCI端口*/
#define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type) 296) /* SCI3_ERI (SCI3 Receive error) */
#define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type) 297) /* SCI3_RXI (SCI3 Receive data full) */
#define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type) 298) /* SCI3_TXI (SCI3 Transmit data empty) */
#define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type) 299) /* SCI3_TEI (SCI3 Transmit end) */

/* SCI3 - 1轴编码器用SCI端口*/
#define VECTOR_NUMBER_SCI3_ERI ((IRQn_Type) 300) /* SCI3_ERI (SCI3 Receive error) */
#define VECTOR_NUMBER_SCI3_RXI ((IRQn_Type) 301) /* SCI3_RXI (SCI3 Receive data full) */
#define VECTOR_NUMBER_SCI3_TXI ((IRQn_Type) 302) /* SCI3_TXI (SCI3 Transmit data empty) */
#define VECTOR_NUMBER_SCI3_TEI ((IRQn_Type) 303) /* SCI3_TEI (SCI3 Transmit end) */

/* SCI4 - RS485总线用SCI端口*/
#define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 304) /* SCI3_ERI (SCI3 Receive error) */
#define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 305) /* SCI3_RXI (SCI3 Receive data full) */
#define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 306) /* SCI3_TXI (SCI3 Transmit data empty) */
#define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 307) /* SCI3_TEI (SCI3 Transmit end) */


void bsp_sci_init_debug(uint32_t buadrate, uint8_t format);
void bsp_sci_init_zx(uint32_t buadrate, uint8_t format);
void bsp_sci_init_encoder(uint8_t axis_num);







/* PWM相关 */

/* 这些由FSP中的中断配置生成，这里仅仅是为了编译通过 */
#define VECTOR_NUMBER_TGIE0 ((IRQn_Type) 74) /* TGIE0 (MTU0.TGRE compare match) */
#define VECTOR_NUMBER_TGIA3 ((IRQn_Type) 84) /* TGIA3 (MTU3.TGRA input capture/compare match) */
#define VECTOR_NUMBER_TCIV4 ((IRQn_Type) 93) /* TCIV4 (MTU4.TCNT overflow/underflow) */



void bsp_pwm_init(uint32_t mtu0_prd, uint32_t mtu0_cmp_init, uint32_t mtu0_cmp_cap, uint32_t mtu3_prd, uint32_t dead);






void bsp_i2c_init(uint32_t base);



#endif /* BSP_H_ */
