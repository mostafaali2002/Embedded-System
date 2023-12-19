/* 
 * File:   ecu_seven_segment.h
 * Author: user
 *
 * Created on August 29, 2023, 5:25 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/

/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef enum{
    SEVEN_COMMON_ANODE,
    SEVEN_COMMON_CATHODE
          
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type ;
}segment_t;
/* Section : Function Declaration*/
Std_ReturnType seven_segment_intialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg , uint8 number);
#endif	/* ECU_SEVEN_SEGMENT_H */

