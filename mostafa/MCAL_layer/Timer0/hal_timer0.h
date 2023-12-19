/* 
 * File:   hal_timer0.h
 * Author: user
 *
 * Created on September 18, 2023, 5:41 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/
#define TIMER0_PRESCALER_ENABLE_CFG     1
#define TIMER0_PRESCALER_DISABLE_CFG    0

#define TIMER0_RASING_EDGE_ENABLE_CFG     1
#define TIMER0_FALLING_EDGE_ENABLE_CFG    0

#define TIMER0_TIMER_MODE    1
#define TIMER0_COUNTER_MODE    0

#define TIMER0_8BIT_REGISTER_MODE    1
#define TIMER0_16BIT_REGISTER_MODE     0
/* Section : Macro Function Declaration*/
#define TIMER0_PRESCALER_ENABLE()       (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()       (T0CONbits.PSA = 1)

#define TIMER0_RASING_EDGE_ENABLE()       (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()       (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()       (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()       (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_ENABLE()       (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_ENABLE()       (T0CONbits.T0CS = 0)

#define TIMER0_MODULE_ENABLE()       (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()       (T0CONbits.TMR0ON = 0)
/* Section : Data Type Declaration */
typedef enum{
    TIMER_PRESCALER_DIV_BY_2 =0 ,
    TIMER_PRESCALER_DIV_BY_4    ,
    TIMER_PRESCALER_DIV_BY_8    , 
    TIMER_PRESCALER_DIV_BY_16   ,
    TIMER_PRESCALER_DIV_BY_32   ,
    TIMER_PRESCALER_DIV_BY_64   ,
    TIMER_PRESCALER_DIV_BY_128  ,
    TIMER_PRESCALER_DIV_BY_256        
    
}timer0_prescaler_select_t;

typedef struct {
#if  TIMER0_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*TM0_InterruptHandler)(void);
     interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_Value ;
    uint8 prescaler_enable : 1 ;
    uint16 timer0_preload_value ;
    uint8 timer0_counter_edge : 1 ;
    uint8 timer0_mode : 1 ;
    uint8 timer0_register_size : 1 ;
    uint8 timer0_reserved : 4 ;
    
}timer0_t;

/* Section : Function Declaration*/
Std_ReturnType Timer0_Init(const timer0_t *timer);
Std_ReturnType Timer0_DEinit(const timer0_t *timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , uint16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16  *value);


#endif	/* HAL_TIMER0_H */

