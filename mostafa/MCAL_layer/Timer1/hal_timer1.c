/* 
 * File:   hal_timer1.c
 * Author: user
 *
 * Created on September 19, 2023, 6:01 PM
 */
#include "hal_timer1.h"

#if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*TM1_InterruptHandler)(void);
 #endif
uint16 timer1_preload = ZERO_INIT ;
static inline void Timer1_Mode_Select(const timer1_t *timer);

Std_ReturnType Timer1_Init(const timer1_t *timer){
     Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TIMER1_MODULE_DISABLE() ; 
        TIMER1_PRESCALER_SELECT(timer->timer1_prescaler_Value);
        Timer1_Mode_Select(timer);
        TMR1H = (timer->timer1_preload_value)>> 8 ;
        TMR1L = (uint8)(timer->timer1_preload_value);
        timer1_preload = timer->timer1_preload_value ;
#if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
         TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
       TM1_InterruptHandler = timer->TM1_InterruptHandler;
 
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable  
       INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == timer->priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 TIMER1_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == timer->priority)  
             {
                 TIMER1_LowPriorityEnable();
                 INTERRUPT_GlobalInterruptLowEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
        
#endif  
#endif 
                
         TIMER1_MODULE_ENABLE() ;     
 
        
        
    }
     return ret ;
}
Std_ReturnType Timer1_DEinit(const timer1_t *timer){
       Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        
          TIMER1_MODULE_DISABLE();
 #if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        TIMER1_InterruptDisable();
 #endif
    }
     return ret ;
}
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , uint16 value){
       Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TMR1H = (value)>> 8 ;
        TMR1L = (uint8)(value);
        
    }
     return ret ;
}
Std_ReturnType Timer1_Read_Value(const timer1_t *timer, uint16  *value){
       Std_ReturnType ret =  E_OK ;
        uint8 tmr1l = ZERO_INIT ,tmr1h = ZERO_INIT ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        tmr1l = TMR1L ;
        tmr1h = TMR1H ;
        *value = (uint16)((tmr1h << 8)+ tmr1l) ;
        
    }
     return ret ;
}
static inline void Timer1_Mode_Select(const timer1_t *timer)
{
    if(TIMER1_TIMER_MODE == timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
        
    }
    else if(TIMER1_COUNTER_MODE == timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE== timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{}
    }
    else {}
}
void TM1_ISR(void){
     TIMER1_InterruptFlagClear();
    TMR1H = (timer1_preload)>> 8 ;
    TMR1L = (uint8)(timer1_preload);
    
    if(TM1_InterruptHandler)
    {
        TM1_InterruptHandler();
    }
}