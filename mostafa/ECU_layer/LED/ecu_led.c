/* 
 * File:   ecu_led.c
 * Author: user
 *
 * Created on August 15, 2023, 4:15 PM
 */

#include "ecu_led.h"

Std_ReturnType led_intialize(const led_t *led){
    Std_ReturnType ret =  E_OK ;
    if(NULL == led)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        pin_config_t config = {
          .pin = led->pin ,.port = led->port ,
          .logic = led->led_status ,
          .direction = OUTPUT_DIRECTION  
        };
        gpio_pin_intialize(&config);
    }
    return ret ;
}
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret =  E_OK ;
    if(NULL == led)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        pin_config_t config = {
          .pin = led->pin ,.port = led->port ,
          .logic = led->led_status ,
          .direction = OUTPUT_DIRECTION  
        };
        gpio_pin_write_logic(&config , GPIO_HIGH);
    }
      return ret ;
}
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret =  E_OK ;
    if(NULL == led)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        pin_config_t config = {
          .pin = led->pin ,.port = led->port ,
          .logic = led->led_status ,
          .direction = OUTPUT_DIRECTION  
        };
        gpio_pin_write_logic(&config , GPIO_LOW);
    }
      return ret ;
}
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret =  E_OK ;
    if(NULL == led)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        pin_config_t config = {
          .pin = led->pin ,.port = led->port ,
          .logic = led->led_status ,
          .direction = OUTPUT_DIRECTION  
        };
       gpio_pin_toggle_logic(&config);
    }
      return ret ;
}