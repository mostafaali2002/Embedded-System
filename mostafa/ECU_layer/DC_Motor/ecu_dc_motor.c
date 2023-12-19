/* 
 * File:   ecu_dc_motor.h
 * Author: user
 *
 * Created on August 27, 2023, 5:08 PM
 */
#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_intialize(const motor_t *motor){
     Std_ReturnType ret = E_OK ;
    if(NULL == motor)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        pin_config_t config_1 = {
          .pin = motor->dc_motor[0].motor_pin,
          .port = motor->dc_motor[0].motor_port,
          .logic = motor->dc_motor[0].motor_status,
          .direction =OUTPUT_DIRECTION ,
      
        };
        pin_config_t config_2 = {
          .pin = motor->dc_motor[1].motor_pin,
          .port = motor->dc_motor[1].motor_port,
          .logic = motor->dc_motor[1].motor_status,
          .direction =OUTPUT_DIRECTION 
         };
        gpio_pin_intialize(&config_1);
        gpio_pin_intialize(&config_2);
        
    }
     return ret ; 
}
Std_ReturnType dc_motor_turn_right(const motor_t *motor){
    Std_ReturnType ret = E_OK ;
     if(NULL == motor)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
         pin_config_t config_1 = {
          .pin = motor->dc_motor[0].motor_pin,
          .port = motor->dc_motor[0].motor_port,
          .logic = motor->dc_motor[0].motor_status,
          .direction =OUTPUT_DIRECTION ,
           
        };
         pin_config_t config_2 = {
          .pin = motor->dc_motor[1].motor_pin,
          .port = motor->dc_motor[1].motor_port,
          .logic = motor->dc_motor[1].motor_status,
          .direction =OUTPUT_DIRECTION 
         };
         gpio_pin_write_logic(&config_1 , GPIO_HIGH);
         gpio_pin_write_logic(&config_2 , GPIO_LOW);
     }
     
     return ret ;
}
Std_ReturnType dc_motor_turn_left(const motor_t *motor){
    Std_ReturnType ret = E_OK ;
     if(NULL == motor)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
           pin_config_t config_1 = {
          .pin = motor->dc_motor[0].motor_pin,
          .port = motor->dc_motor[0].motor_port,
          .logic = motor->dc_motor[0].motor_status,
          .direction =OUTPUT_DIRECTION ,
           
        };
         pin_config_t config_2 = {
          .pin = motor->dc_motor[1].motor_pin,
          .port = motor->dc_motor[1].motor_port,
          .logic = motor->dc_motor[1].motor_status,
          .direction =OUTPUT_DIRECTION 
         };
         gpio_pin_write_logic(&config_1 , GPIO_LOW);
         gpio_pin_write_logic(&config_2 , GPIO_HIGH);
     }
     
     
     return ret ;
}
Std_ReturnType dc_motor_stop(const motor_t *motor){
    Std_ReturnType ret = E_OK ;
     if(NULL == motor)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
           pin_config_t config_1 = {
          .pin = motor->dc_motor[0].motor_pin,
          .port = motor->dc_motor[0].motor_port,
          .logic = motor->dc_motor[0].motor_status,
          .direction =OUTPUT_DIRECTION ,
           
        };
         pin_config_t config_2 = {
          .pin = motor->dc_motor[1].motor_pin,
          .port = motor->dc_motor[1].motor_port,
          .logic = motor->dc_motor[1].motor_status,
          .direction =OUTPUT_DIRECTION 
         };
         gpio_pin_write_logic(&config_1 , GPIO_LOW);
         gpio_pin_write_logic(&config_2 , GPIO_LOW);
     
     }
     return ret ;
}
