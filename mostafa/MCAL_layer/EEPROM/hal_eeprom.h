/* 
 * File:   hal_eeprom.h
 * Author: user
 *
 * Created on September 12, 2023, 8:44 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/* section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/
#define ACCESS_FLASH_PROGRAM_MEMORY   1
#define ACCESS_EEPROM_PROGRAM_MEMORY  0
#define ACCESS_CONFIG_REGISTER        1
#define ACCESS_FLASH_EEPROM_MEMORY    0

#define ALLOW_WRITE_CYCLE             1
#define INHIBITS_WRITE_CYCLE          0

#define INIATE_DATA_EEPROM_WRITE      1
#define DATA_EEPROM_WRITE             0

#define INIATE_DATA_EEPROM_Read       1
/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */

/* Section : Function Declaration*/
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData);

#endif	/* HAL_EEPROM_H */

