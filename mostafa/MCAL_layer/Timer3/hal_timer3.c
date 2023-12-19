/* 
 * File:   hal_timer3.h
 * Author: user
 *
 * Created on September 20, 2023, 5:26 PM
 */

#include "hal_timer3.h"

#if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*TM3_InterruptHandler)(void);
 #endif
static inline void Timer3_Mode_Select(const timer3_t *timer);
uint16 timer3_preload = ZERO_INIT ;
void TM3_ISR(void){
    
    
    if(TM3_InterruptHandler)
    {
        TM3_InterruptHandler();
    }
}
Std_ReturnType Timer3_Init(const timer3_t *timer){
     Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TIMER3_MODULE_DISABLE() ; 
        TIMER3_PRESCALER_SELECT(timer->timer3_prescaler_Value);
        Timer3_Mode_Select(timer);
        TMR3H = (timer->timer3_preload_value)>> 8 ;
        TMR3L = (uint8)(timer->timer3_preload_value);
        timer3_preload = timer->timer3_preload_value ;
#if  TIMER3_INTERRUPT_FEATURE_ENABLE == FeatureEnable
         TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
       TM3_InterruptHandler = timer->TM3_InterruptHandler;
 
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable  
       INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == timer->priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 TIMER3_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == timer->priority)  
             {
                 TIMER3_LowPriorityEnable();
                 INTERRUPT_GlobalInterruptLowEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
        
#endif  
#endif 
                
         TIMER3_MODULE_ENABLE() ;     
 
        
        
    }
     return ret ;
}
Std_ReturnType Timer3_DEinit(const timer3_t *timer){
       Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        
          TIMER3_MODULE_DISABLE();
 #if  TIMER3_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        TIMER3_InterruptDisable();
 #endif
    }
     return ret ;
}
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , uint16 value){
       Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TMR3H = (value)>> 8 ;
        TMR3L = (uint8)(value);
        
    }
     return ret ;
}
Std_ReturnType Timer3_Read_Value(const timer3_t *timer, uint16  *value){
      Std_ReturnType ret =  E_OK ;
        uint8 tmr3l = ZERO_INIT ,tmr3h = ZERO_INIT ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        tmr3l = TMR3L ;
        tmr3h = TMR3H ;
        *value = (uint16)((tmr3h << 8)+ tmr3l) ;
        
    }
     return ret ;
}
static inline void Timer3_Mode_Select(const timer3_t *timer)
{
    if(TIMER3_TIMER_MODE == timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
        
    }
    else if(TIMER3_COUNTER_MODE == timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE== timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{}
    }
    else {}
}