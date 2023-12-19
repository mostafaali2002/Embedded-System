/* 
 * File:   hal_timer2.h
 * Author: user
 *
 * Created on September 20, 2023, 5:24 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/

/*------------POSTCALER--------*/
#define  TIMER2_POSTCALER_DIV_BY_1    0
#define  TIMER2_POSTCALER_DIV_BY_2    1
#define  TIMER2_POSTCALER_DIV_BY_3    2
#define  TIMER2_POSTCALER_DIV_BY_4    3
#define  TIMER2_POSTCALER_DIV_BY_5    4
#define  TIMER2_POSTCALER_DIV_BY_6    5
#define  TIMER2_POSTCALER_DIV_BY_7    6
#define  TIMER2_POSTCALER_DIV_BY_8    7
#define  TIMER2_POSTCALER_DIV_BY_9    8
#define  TIMER2_POSTCALER_DIV_BY_10    9
#define  TIMER2_POSTCALER_DIV_BY_11    10
#define  TIMER2_POSTCALER_DIV_BY_12    11
#define  TIMER2_POSTCALER_DIV_BY_13    12
#define  TIMER2_POSTCALER_DIV_BY_14    13
#define  TIMER2_POSTCALER_DIV_BY_15    14
#define  TIMER2_POSTCALER_DIV_BY_16    15

/*------------PRESCALER--------*/
#define  TIMER2_PRESCALER_DIV_BY_1     0
#define  TIMER2_PRESCALER_DIV_BY_4     1
#define  TIMER2_PRESCALER_DIV_BY_16    2



/* Section : Macro Function Declaration*/
#define TIMER2_MODULE_ENABLE()       (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()       (T2CONbits.TMR2ON = 0)
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)
#define TIMER2_POSTCALER_SELECT(_PRESCALER_)    (T2CONbits.TOUTPS = _PRESCALER_)

/* Section : Data Type Declaration */
typedef struct {
#if  TIMER2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*TM2_InterruptHandler)(void);
     interrupt_priority_cfg priority;
#endif
     uint16 timer2_preload_value ;
     uint8 timer2_prescaler_Value :2;
     uint8 timer2_postcaler_Value :4;
  
}timer2_t;
/* Section : Function Declaration*/
Std_ReturnType Timer2_Init(const timer2_t *timer);
Std_ReturnType Timer2_DEinit(const timer2_t *timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *timer , uint16 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *timer, uint16  *value);


#endif	/* HAL_TIMER2_H */

