/* 
 * File:   ecu_keypad.h
 * Author: user
 *
 * Created on August 30, 2023, 10:03 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/* Section : Macro Declaration*/
#define KEYPAD_ROW  4
#define KEYPAD_COLUMN 4
/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef struct {
    pin_config_t keypad_row_pin[KEYPAD_ROW];
    pin_config_t keypad_column_pin[KEYPAD_COLUMN];
}keypad_t;
/* Section : Function Declaration*/
Std_ReturnType keypad_initialize(const keypad_t *key);
Std_ReturnType keypad_get_value(const keypad_t *key,uint8 *value);
#endif	/* ECU_KEYPAD_H */

