/*
 * bsp_eeprom.h
 *
 *  Created on: Oct 25, 2023
 *      Author: xgj12
 */

#ifndef BSP_EEPROM_H_
#define BSP_EEPROM_H_




extern void bsp_eeprom_init(void);
extern uint8_t I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t * pData, uint16_t Size, uint32_t Timeout);
extern uint8_t I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t * pData, uint16_t Size, uint32_t Timeout);


#endif /* BSP_EEPROM_H_ */
