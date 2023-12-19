/* 
 * File:   ecu_relay.h
 * Author: user
 *
 * Created on August 25, 2023, 12:58 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/
#define RELAY_ON_STATUS 0x01
#define RELAY_OFF_STATUS 0x00
/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef struct{
    uint8 relay_pin : 3 ;
    uint8 relay_port :4 ;
    uint8 relay_status : 1 ;
}relay_t;
/* Section : Function Declaration*/
Std_ReturnType relay_intialize (const relay_t *relay);
Std_ReturnType relay_turn_on (const relay_t *relay);
Std_ReturnType relay_turn_off (const relay_t *relay);

#endif	/* ECU_RELAY_H */

