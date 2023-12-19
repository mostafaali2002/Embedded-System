/* 
 * File:   ecu_button.c
 * Author: user
 *
 * Created on August 22, 2023, 8:52 PM
 */

#include "ecu_button.h"

Std_ReturnType button_intialize(const button_t *btn){
    Std_ReturnType ret =  E_OK ;
    if(NULL == btn)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
      return ret ;
}
Std_ReturnType button_read_state(const button_t *btn ,button_state_t *btn_state){
    Std_ReturnType ret =  E_OK ;
    logic_t pin_logic = GPIO_LOW;
    
    if(NULL == btn || NULL == btn_state)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
     gpio_pin_read_logic(&(btn->button_pin),&pin_logic);
     if(BUTTON_ACTIVE_HIGH == btn->button_active)
     {
         if(GPIO_HIGH == pin_logic){
             *btn_state = BUTTON_PRESSED ;
         }
         else
         {
                *btn_state = BUTTON_RELASED ;
         }
             
     }
     else if(BUTTON_ACTIVE_LOW == btn->button_active)
     {
         if(GPIO_HIGH == pin_logic){
             *btn_state = BUTTON_RELASED ;
         }
         else
         {
                *btn_state = BUTTON_PRESSED ;
         }
     }
     else{/* nothing*/}
    }
      return ret ;
}