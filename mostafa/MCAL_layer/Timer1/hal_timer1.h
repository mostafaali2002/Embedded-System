/* 
 * File:   hal_timer1.h
 * Author: user
 *
 * Created on September 19, 2023, 6:01 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* -----Section : Macro Declaration-----*/

#define TIMER1_TIMER_MODE    0
#define TIMER1_COUNTER_MODE    1

#define TIMER1_ASYNC_COUNTER_MODE    1
#define TIMER1_SYNC_COUNTER_MODE    0

#define TIMER1_OSCAILLATOR_ENABLE   1
#define TIMER1_OSCAILLATOR_DISABLE    0

#define  TIMER1_PRESCALER_DIV_BY_1    0
#define  TIMER1_PRESCALER_DIV_BY_2    1
#define  TIMER1_PRESCALER_DIV_BY_4    2
#define  TIMER1_PRESCALER_DIV_BY_8    3

#define  TIMER1_RW_REG_8BITS_MODE     0
#define  TIMER1_RW_REG_16BITS_MODE    1
/* Section : Macro Function Declaration*/
#define TIMER1_MODULE_ENABLE()       (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()       (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()       (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()       (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 0)

#define TIMER1_OSCAILLATOR_HW_ENABLE()       (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCAILLATOR_HW_DISABLE()       (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T1CONbits.T1CKPS = _PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()               (T1CONbits.T1RUN)

#define TIMER1RW_REG_8BITS_ENABLE()        (T1CONbits.RD16 = 0)
#define TIMER1RW_REG_16BITS_ENABLE()       (T1CONbits.RD16 = 1)
/* Section : Data Type Declaration */
typedef struct {
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*TM1_InterruptHandler)(void);
     interrupt_priority_cfg priority;
#endif
      uint16 timer1_preload_value ;
     uint8 timer1_prescaler_Value :2;
     uint8 timer1_mode : 1 ;
     uint8 timer1_counter_mode : 1 ;
     uint8 timer1_osc_cfg : 1 ;
    uint8 timer1_reg_rw_mode : 1 ;
    
}timer1_t;

/* Section : Function Declaration*/
Std_ReturnType Timer1_Init(const timer1_t *timer);
Std_ReturnType Timer1_DEinit(const timer1_t *timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *timer, uint16  *value);

#endif	/* HAL_TIMER1_H */

