/* 
 * File:   ecu_button.h
 * Author: user
 *
 * Created on August 22, 2023, 8:52 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/

/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef enum{
    BUTTON_RELASED,
    BUTTON_PRESSED
}button_state_t;

typedef enum{
    
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH        
}button_active_t;

typedef struct{
    pin_config_t button_pin ;
    button_state_t button_state ;
    button_active_t button_active ;
    
}button_t;
/* Section : Function Declaration*/
Std_ReturnType button_intialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn ,button_state_t *btn_state);
#endif	/* ECU_BUTTON_H */

