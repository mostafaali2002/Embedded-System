/* 
 * File:   ecu_led.h
 * Author: user
 *
 * Created on August 15, 2023, 4:26 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/

/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef enum{
    LED_OFF ,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port : 4 ;
    uint8 pin :3 ;
    uint8 led_status : 1 ;
}led_t ;

/* Section : Function Declaration*/
Std_ReturnType led_intialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

