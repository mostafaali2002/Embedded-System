/* 
 * File:   ecu_relay.c
 * Author: user
 *
 * Created on August 25, 2023, 12:58 AM
 */

#include "ECU_layer/Relay/ecu_relay.h"

Std_ReturnType relay_intialize (const relay_t *relay)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == relay)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
          pin_config_t config = {
          .pin = relay->relay_pin ,.port = relay->relay_port ,
          .logic = relay->relay_status ,
          .direction = OUTPUT_DIRECTION  
        };
          gpio_pin_intialize(&config);
        
    }
     return ret ;
}
Std_ReturnType relay_turn_on (const relay_t *relay){
      Std_ReturnType ret = E_OK ;
    if(NULL == relay)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        pin_config_t config = {
          .pin = relay->relay_pin ,.port = relay->relay_port ,
          .logic = relay->relay_status ,
          .direction = OUTPUT_DIRECTION  
        };
        gpio_pin_write_logic(&config,GPIO_HIGH);
        
    }
     return ret ;
}
Std_ReturnType relay_turn_off (const relay_t *relay)
{
      Std_ReturnType ret = E_OK ;
    if(NULL == relay )
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        pin_config_t config = {
          .pin = relay->relay_pin ,.port = relay->relay_port ,
          .logic = relay->relay_status ,
          .direction = OUTPUT_DIRECTION  
        };
        gpio_pin_write_logic(&config,GPIO_LOW);
        
    }
     return ret ;
}