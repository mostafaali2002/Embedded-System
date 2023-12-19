/* 
 * File:   mcal_interrupt_config.h
 * Author: user
 *
 * Created on September 10, 2023, 11:21 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/* Section : Macro Declaration*/
#define INTERRUPT_ENABLE     1
#define INTERRUPT_DISABLE     0
#define INTERRUPT_OCCURE      1
#define INTERRUPT_NOT_OCCURE      0
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_Disable  0
/* Section : Macro Function Declaration*/
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
#define INTERRUPT_PriorityLevelsEnable()   (RCONbits.IPEN = 1)
#define INTERRUPT_PriorityLevelsDisable()   (RCONbits.IPEN = 0)

#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH = 1)
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)

#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
#define INTERRUPT_GlobalInterruptLowDisable()   (INTCONbits.GIEL = 0)
#else

#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)

#define INTERRUPT_GlobalInterruptEnable()   (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()   (INTCONbits.GIE = 0)



#endif
/* Section : Data Type Declaration */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,
    INTERRUPT_HIGH_PRIORITY 
}interrupt_priority_cfg;

/* Section : Function Declaration*/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

