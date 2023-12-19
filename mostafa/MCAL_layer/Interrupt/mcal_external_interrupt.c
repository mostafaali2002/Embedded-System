/* 
 * File:   mcal_external_interrupt.c
 * Author: user
 *
 * Created on September 10, 2023, 11:19 AM
 */

#include "mcal_external_interrupt.h"
static void(*INT0_InterruptHandler)(void) = NULL ;
static void(*INT1_InterruptHandler)(void) = NULL ;
static void(*INT2_InterruptHandler)(void) = NULL ;

static void(*RB4_InterruptHandler_High)(void) = NULL ;
static void(*RB4_InterruptHandler_Low)(void) = NULL ;
static void(*RB5_InterruptHandler_High)(void) = NULL ;
static void(*RB5_InterruptHandler_Low)(void) = NULL ;
static void(*RB6_InterruptHandler_High)(void) = NULL ;
static void(*RB6_InterruptHandler_Low)(void) = NULL ;
static void(*RB7_InterruptHandler_High)(void) = NULL ;
static void(*RB7_InterruptHandler_Low)(void) = NULL ;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *obj);


Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        /* disable external interrupt*/
        ret = Interrupt_INTx_Disable(obj);
        /* Clear flag */
        ret |= Interrupt_INTx_ClearFlag(obj);
        /* configure interrupt  priority*/
        
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
        ret = Interrupt_INTx_Priority_Init(obj);
#endif
        /* configure interrupt edge*/
        ret |= Interrupt_INTx_Edge_Init(obj);
        /* configure interrupt  I/O pin */
        ret |= Interrupt_INTx_Pin_Init(obj);
        /* configure default interrupt callback*/
        ret |= Interrupt_INTx_SetInterruptHandler(obj);
        /* enable external interrupt*/
        ret |= Interrupt_INTx_Enable(obj);
        
          
    }
      return ret ;
}
void INT0_ISR(void)
{
    EXT_INT0_InterruptFlagClear();
    
    
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}
void INT2_ISR(void)
{
    EXT_INT2_InterruptFlagClear();
    
    
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}
void INT1_ISR(void)

{
    EXT_INT1_InterruptFlagClear();
   if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
    
    
}
void RB4_ISR(uint8 RB_Source){
     EXT_RBx_InterruptFlagClear();
    
    
       if(1 == RB_Source)
    {
        if(RB4_InterruptHandler_High)
        {
        RB4_InterruptHandler_High();
        }
    }
    else if (0 == RB_Source)
    {
        if(RB4_InterruptHandler_Low)
        {
        RB4_InterruptHandler_Low();
        }
    }
    else{
        
    }
}
void RB5_ISR(uint8 RB_Source){
     EXT_RBx_InterruptFlagClear();
    
    
       if(1 == RB_Source)
    {
        if(RB5_InterruptHandler_High)
        {
        RB5_InterruptHandler_High();
        }
    }
    else if (0 == RB_Source)
    {
        if(RB5_InterruptHandler_Low)
        {
        RB5_InterruptHandler_Low();
        }
    }
    else{
        
    }
}
void RB6_ISR(uint8 RB_Source){
     EXT_RBx_InterruptFlagClear();
    
    
       if(1 == RB_Source)
    {
        if(RB6_InterruptHandler_High)
        {
        RB6_InterruptHandler_High();
        }
    }
    else if (0 == RB_Source)
    {
        if(RB6_InterruptHandler_Low)
        {
        RB6_InterruptHandler_Low();
        }
    }
    else{
        
    }
}
void RB7_ISR(uint8 RB_Source){
     EXT_RBx_InterruptFlagClear();
    
    
       if(1 == RB_Source)
    {
        if(RB7_InterruptHandler_High)
        {
        RB7_InterruptHandler_High();
        }
    }
    else if (0 == RB_Source)
    {
        if(RB7_InterruptHandler_Low)
        {
        RB7_InterruptHandler_Low();
        }
    }
    else{
        
    }
}
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t *obj)
{
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        ret = Interrupt_INTx_Disable(obj);
          
    }
      return ret ;
    
}
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    } else {
        /* disable external interrupt*/
        EXT_RBx_InterruptDisable();
        /* clear flag*/
        EXT_RBx_InterruptFlagClear();

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == obj->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_High_Priority();
        } else if (INTERRUPT_LOW_PRIORITY == obj->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_Low_Priority();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif 
        ret = gpio_pin_direction_intialize(&(obj->mcu_pin));
        switch (obj->mcu_pin.pin) {
            case PIN4:
                RB4_InterruptHandler_High = obj->Ext_Interrupt_High;
                RB4_InterruptHandler_Low = obj->Ext_Interrupt_Low;
                break;
            case PIN5:
                RB5_InterruptHandler_High = obj->Ext_Interrupt_High;
                RB5_InterruptHandler_Low = obj->Ext_Interrupt_Low;
                break;
            case PIN6:
                RB6_InterruptHandler_High = obj->Ext_Interrupt_High;
                RB6_InterruptHandler_Low = obj->Ext_Interrupt_Low;
                break;
            case PIN7:
                RB7_InterruptHandler_High = obj->Ext_Interrupt_High;
                RB7_InterruptHandler_Low = obj->Ext_Interrupt_Low;
                break;
            default:
                ret = E_NOT_OK;
        }


        EXT_RBx_InterruptEnable();

    }
      return ret ;
}
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
      
    }
      return ret ;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        switch(obj->source)
        {
            case INTERRUPT_External_INTx0 : 
 #if INTERRUPT_Priority_Levels_Enable == FeatureEnable

              INTERRUPT_GlobalInterruptHighEnable() ;

              
  #else
                 INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
 #endif               
               
               EXT_INT0_InterruptEnable();
                break ;
            case INTERRUPT_External_INTx1 : 
  #if INTERRUPT_Priority_Levels_Enable == FeatureEnable
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == obj->priority){
                   INTERRUPT_GlobalInterruptHighEnable() ;
                }
                else if(INTERRUPT_LOW_PRIORITY ==obj->priority){
                   INTERRUPT_GlobalInterruptLowEnable() ;
                }
                else{/*Nothing*/}
  #else
                 INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
 #endif 
                EXT_INT1_InterruptEnable();
                break ;
            case INTERRUPT_External_INTx2 : 
  #if INTERRUPT_Priority_Levels_Enable == FeatureEnable
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == obj->priority){
                   INTERRUPT_GlobalInterruptHighEnable() ;
                }
                else if(INTERRUPT_LOW_PRIORITY ==obj->priority){
                   INTERRUPT_GlobalInterruptLowEnable() ;
                }
                else{/*Nothing*/}
  #else
                 INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
 #endif 
                EXT_INT2_InterruptEnable();
                break ;
            default :
                ret = E_NOT_OK;
        }
          
    }
      return ret ;
}
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          switch(obj->source)
        {
            case INTERRUPT_External_INTx0 : 
               EXT_INT0_InterruptDisable();
                break ;
            case INTERRUPT_External_INTx1 : 
                EXT_INT1_InterruptDisable();
                break ;
            case INTERRUPT_External_INTx2 : 
                EXT_INT2_InterruptDisable();
                break ;
            default :
                ret = E_NOT_OK;
        }
    }
      return ret ;
}
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        switch(obj->source)
        {
            
            case INTERRUPT_External_INTx1 : 
                if(INTERRUPT_HIGH_PRIORITY == obj->priority){
                    EXT_INT1_HighPriorityEnable();
                }
                else if(INTERRUPT_LOW_PRIORITY ==obj->priority){
                    EXT_INT1_LowPriorityDisable();
                }
                else{/*Nothing*/}
                
                break ;
            case INTERRUPT_External_INTx2 : 
                if(INTERRUPT_HIGH_PRIORITY == obj->priority){
                    EXT_INT2_HighPriorityEnable();
                }
                else if(INTERRUPT_LOW_PRIORITY ==obj->priority){
                    EXT_INT2_LowPriorityDisable();
                }
                else{/*Nothing*/}
                break ;
            default :
                ret = E_NOT_OK;
        }
          
    }
      return ret ;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         switch(obj->source)
        {
             case INTERRUPT_External_INTx0 : 
                if(INTERRUPT_RASING_EDGE == obj->edge){
                    EXT_INT0_RisingEdge();
                }
                else if(INTERRUPT_FALLING_EDGE == obj->edge){
                    EXT_INT0_FallingEdge();
                }
                else{/*Nothing*/}
            
            case INTERRUPT_External_INTx1 : 
                if(INTERRUPT_RASING_EDGE == obj->edge){
                    EXT_INT1_RisingEdge();
                }
                else if(INTERRUPT_FALLING_EDGE == obj->edge){
                    EXT_INT1_FallingEdge();
                }
                else{/*Nothing*/}
                
                break ;
            case INTERRUPT_External_INTx2 : 
                if(INTERRUPT_RASING_EDGE == obj->edge){
                    EXT_INT2_RisingEdge();
                }
                else if(INTERRUPT_FALLING_EDGE == obj->edge){
                    EXT_INT2_FallingEdge();
                }
                else{/*Nothing*/}
                break ;
            default :
                ret = E_NOT_OK;
        }
          
    }
      return ret ;
}
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        ret =  gpio_pin_direction_intialize(&(obj->mcu_pin));
    }
      return ret ;
}
static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *obj){
      Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
      switch(obj->source)
        {
             case INTERRUPT_External_INTx0 : 
                 EXT_INT0_InterruptFlagClear();
                 break;
            case INTERRUPT_External_INTx1 : 
               EXT_INT1_InterruptFlagClear();
                break ;
            case INTERRUPT_External_INTx2 :          
                EXT_INT2_InterruptFlagClear();
                break ;
            default :
                ret = E_NOT_OK;
        }
    }
      return ret ;
}
static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
     Std_ReturnType ret =  E_OK ;
    if(NULL == InterruptHandler)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
    }
     return ret ;
}
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void))
{
     Std_ReturnType ret =  E_OK ;
    if(NULL == InterruptHandler)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
    }
     return ret ;
}
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
     Std_ReturnType ret =  E_OK ;
    if(NULL == InterruptHandler)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
    }
     return ret ;
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *obj){
       Std_ReturnType ret =  E_OK ;
    if(NULL == obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
      switch(obj->source)
        {
             case INTERRUPT_External_INTx0 : 
                 INT0_SetInterruptHandler(obj->Ext_InterruptHandler);
                 break;
            case INTERRUPT_External_INTx1 : 
              INT1_SetInterruptHandler(obj->Ext_InterruptHandler);
                break ;
            case INTERRUPT_External_INTx2 :          
               INT2_SetInterruptHandler(obj->Ext_InterruptHandler);
                break ;
            default :
                ret = E_NOT_OK;
        }
    }
      return ret ;
}
