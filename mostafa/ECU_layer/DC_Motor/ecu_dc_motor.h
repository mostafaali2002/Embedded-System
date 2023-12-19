/* 
 * File:   ecu_dc_motor.h
 * Author: user
 *
 * Created on August 27, 2023, 5:08 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/* Section : Includes*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/
#define MOTOR_ON_STATUS 0x01
#define MOTOR_OFF_STATUS 0x00
/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef struct{
    uint8 motor_pin : 3 ;
    uint8 motor_port :4 ;
    uint8 motor_status : 1 ;
}motor_pin_t;

typedef struct{
    motor_pin_t dc_motor[2];
}motor_t;
/* Section : Function Declaration*/
Std_ReturnType dc_motor_intialize(const motor_t *motor);
Std_ReturnType dc_motor_turn_right(const motor_t *motor);
Std_ReturnType dc_motor_turn_left(const motor_t *motor);
Std_ReturnType dc_motor_stop(const motor_t *motor);
#endif	/* ECU_DC_MOTOR_H */

