/* 
 * File:   hal_timer2.c
 * Author: user
 *
 * Created on September 20, 2023, 5:24 PM
 */
#include "hal_timer2.h"

#if  TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*TM2_InterruptHandler)(void);
 #endif
uint16 timer2_preload = ZERO_INIT ;

Std_ReturnType Timer2_Init(const timer2_t *timer){
     Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
         TIMER2_PRESCALER_SELECT(timer->timer2_prescaler_Value);
          TIMER2_POSTCALER_SELECT(timer->timer2_postcaler_Value);
         TMR2 =(timer->timer2_preload_value);
         timer2_preload = timer->timer2_preload_value ;
        #if  TIMER2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
         TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
       TM2_InterruptHandler = timer->TM2_InterruptHandler;
 
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
                    TIMER2_MODULE_ENABLE();
    }
     return ret ;
}
Std_ReturnType Timer2_DEinit(const timer2_t *timer){
      Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
                TIMER2_MODULE_DISABLE();
 #if  TIMER2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        TIMER2_InterruptDisable();
 #endif
    }
     return ret ;
}
Std_ReturnType Timer2_Write_Value(const timer2_t *timer , uint16 value){
      Std_ReturnType ret =  E_OK ;
    if(NULL == timer)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        TMR2 = value ;
    }
     return ret ;
}
Std_ReturnType Timer2_Read_Value(const timer2_t *timer, uint16  *value){
      Std_ReturnType ret =  E_OK ;
    if((NULL == timer)||(NULL == value))
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        *value = TMR2;
    }
     return ret ;
}

void TM2_ISR(void){
     TIMER2_InterruptFlagClear();
     TMR2 = timer2_preload ;
    
    if(TM2_InterruptHandler)
    {
        TM2_InterruptHandler();
    }
}