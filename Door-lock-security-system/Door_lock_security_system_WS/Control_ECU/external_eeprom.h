/******************************************************************************
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for EEPROM functions
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

#define EEPROM_ADDRESS 0b10100000
#define ERROR 0
#define SUCCESS 1

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);
void EEPROM_writeLong(uint32 data, uint16 address);
void EEPROM_readLong(uint16 address,uint32 *data);

#endif /* EEPROM_H_ */
