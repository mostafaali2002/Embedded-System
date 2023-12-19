/* 
 * File:   ecu_keypad.c
 * Author: user
 *
 * Created on August 30, 2023, 10:03 PM
 */

#include "ecu_keypad.h"

 const uint8 btn_value[KEYPAD_ROW][KEYPAD_COLUMN] = {
                                                        {'7','8','9','/'},
                                                         {'4','5','6','*'},
                                                         {'1','2','3','-'},
                                                         {'#','0','=','+'}
                                                    };

Std_ReturnType keypad_initialize(const keypad_t *key){
       Std_ReturnType ret = E_OK ;
       uint8 row = ZERO_INIT , column = ZERO_INIT ;
    if((NULL == key))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        for(row = ZERO_INIT ; row <KEYPAD_ROW ; row++ )
        {
            ret=gpio_pin_intialize(&(key->keypad_row_pin[row]));
        }
        for(column = ZERO_INIT ; column <KEYPAD_COLUMN ; column++ )
        {
            ret= gpio_pin_direction_intialize(&(key->keypad_column_pin[column]));
        }
      
      
       
    }
       return ret ;
}
Std_ReturnType keypad_get_value(const keypad_t *key,uint8 *value){
       Std_ReturnType ret = E_OK ;
        uint8 row = ZERO_INIT , column = ZERO_INIT ,l_counter = ZERO_INIT , column_logic = ZERO_INIT;
    if((key == NULL) || (value == NULL))
    {
        ret = E_NOT_OK ; 
    }
    else
{
        for (row = ZERO_INIT; row < KEYPAD_ROW; row++) {
            for (column = ZERO_INIT; column < KEYPAD_COLUMN; column++) {
                ret = gpio_pin_write_logic(&(key->keypad_row_pin[column]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(key->keypad_row_pin[row]), GPIO_HIGH);

            for (l_counter = ZERO_INIT; l_counter < KEYPAD_COLUMN; l_counter++) {
                ret = gpio_pin_read_logic(&(key->keypad_column_pin[l_counter]), &column_logic);
                if (GPIO_HIGH == column_logic) {
                    *value = btn_value[row][l_counter];
                }
            }
        }
        
    }
       return ret ;
}