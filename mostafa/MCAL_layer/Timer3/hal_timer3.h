/* 
 * File:   hal_timer3.h
 * Author: user
 *
 * Created on September 20, 2023, 5:26 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* -----Section : Macro Declaration-----*/

#define TIMER3_TIMER_MODE    0
#define TIMER3_COUNTER_MODE    1

#define TIMER3_ASYNC_COUNTER_MODE    1
#define TIMER3_SYNC_COUNTER_MODE    0

#define  TIMER3_PRESCALER_DIV_BY_1    0
#define  TIMER3_PRESCALER_DIV_BY_2    1
#define  TIMER3_PRESCALER_DIV_BY_4    2
#define  TIMER3_PRESCALER_DIV_BY_8    3

#define  TIMER3_RW_REG_8BITS_MODE     0
#define  TIMER3_RW_REG_16BITS_MODE    1

#define  TIMER1_CAPTURE_COMPARE_CCP_MODULES   0
#define  TIMER1_CAPTURE_COMPARE_CCP1_MODULES  1
#define  TIMER3_CAPTURE_COMPARE_CCP2_MODULES  1
#define  TIMER3_CAPTURE_COMPARE_CCP_MODULES   2
/* Section : Macro Function Declaration*/
#define TIMER3_MODULE_ENABLE()       (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()       (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()       (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()       (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 0)


#define TIMER3_PRESCALER_SELECT(_PRESCALER_)    (T3CONbits.T3CKPS = _PRESCALER_)



#define TIMER3_RW_REG_8BITS_ENABLE()        (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BITS_ENABLE()       (T3CONbits.RD16 = 1)
/* Section : Data Type Declaration */
typedef struct {
#if  TIMER3_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*TM3_InterruptHandler)(void);
     interrupt_priority_cfg priority;
#endif
      uint16 timer3_preload_value ;
     uint8 timer3_prescaler_Value :2;
     uint8 timer3_mode : 1 ;
     uint8 timer3_counter_mode : 1 ;
    uint8 timer3_reg_rw_mode : 1 ;
    
}timer3_t;

/* Section : Function Declaration*/
Std_ReturnType Timer3_Init(const timer3_t *timer);
Std_ReturnType Timer3_DEinit(const timer3_t *timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *timer, uint16  *value);


#endif	/* HAL_TIMER3_H */

