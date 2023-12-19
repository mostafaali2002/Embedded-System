/* 
 * File:   hal_timer0.c
 * Author: user
 *
 * Created on September 18, 2023, 5:41 PM
 */
#include "hal_timer0.h"

static inline void Timer0_Prescaler_Config(const timer0_t *timer);
static inline void Timer0_Mode_Select(const timer0_t *timer);
static inline void Timer0_Register_Size(const timer0_t *timer);
void TM0_ISR(void);

#if  TIMER0_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*TM0_InterruptHandler)(void);
 #endif
uint16 timer0_preload = ZERO_INIT ;

Std_ReturnType Timer0_Init(const timer0_t *timer){
    Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler_Config(timer);
        Timer0_Mode_Select(timer);
        Timer0_Register_Size(timer);
        TMR0H = (timer->timer0_preload_value)>> 8 ;
        TMR0L = (uint8)(timer->timer0_preload_value);
        timer0_preload = timer->timer0_preload_value ;
 #if  TIMER0_INTERRUPT_FEATURE_ENABLE == FeatureEnable
         
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
       TM0_InterruptHandler = timer->TM0_InterruptHandler;
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
       INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == timer->priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 TIMER0_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == timer->priority)  
             {
                 TIMER0_LowPriorityEnable();
                 INTERRUPT_GlobalInterruptLowEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
#endif
               
  #endif
        TIMER0_MODULE_ENABLE();
        
    }
    return ret ;
}
Std_ReturnType Timer0_DEinit(const timer0_t *timer){
     Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        
        TIMER0_MODULE_DISABLE();
 #if  TIMER0_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        TIMER0_InterruptDisable();
 #endif
      
    }
    return ret ;
}
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , uint16 value){
     Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          TMR0H = (value)>> 8 ;
        TMR0L = (uint8)(value);
    }
    return ret ;
}
Std_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16  *value){
     Std_ReturnType ret =  E_OK ;
     uint8 tmr0l = ZERO_INIT ,tmr0h = ZERO_INIT ;
    if((NULL == timer)||(NULL == value))
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        tmr0l = TMR0L ;
        tmr0h = TMR0H ;
        *value = (uint16)((tmr0h << 8)+ tmr0l) ;
        
    }
    return ret ;
}

void TM0_ISR(void){
     TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload)>> 8 ;
    TMR0L = (uint8)(timer0_preload);
    
    if(TM0_InterruptHandler)
    {
        TM0_InterruptHandler();
    }
}

static inline void Timer0_Prescaler_Config(const timer0_t *timer)
{
    if(TIMER0_PRESCALER_ENABLE_CFG == timer->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS =timer->prescaler_Value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == timer->prescaler_enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else {}
}

static inline void Timer0_Mode_Select(const timer0_t *timer)
{
    if(TIMER0_TIMER_MODE == timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
        
    }
    else if(TIMER0_COUNTER_MODE == timer->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_RASING_EDGE_ENABLE_CFG == timer->timer0_counter_edge)
        {
            TIMER0_RASING_EDGE_ENABLE();
        }
        else  if(TIMER0_FALLING_EDGE_ENABLE_CFG == timer->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{}
    }
    else {}
}

static inline void Timer0_Register_Size(const timer0_t *timer)
{
    if(TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_ENABLE();
        
    }
    else if(TIMER0_16BIT_REGISTER_MODE == timer->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_ENABLE();
    }
    else {}
}