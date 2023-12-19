/* 
 * File:   hal_ccp1.c
 * Author: user
 *
 * Created on September 23, 2023, 12:37 PM
 */
#include "hal_ccp1.h" 
#if  CCP1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*CCP1_InterruptHandler)(void);
 #endif
#if  CCP2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*CCP2_InterruptHandler)(void);
 #endif

static void CCP_Interrupt_Config(const ccp_t *ccp);
static void CCP_Timer_Selected(const ccp_t *ccp);
uint16 ccp1_preload = ZERO_INIT ;

Std_ReturnType ccp_Init(const ccp_t *ccp) {
    Std_ReturnType ret = E_OK;
    if (NULL == ccp) {
        ret = E_NOT_OK;
    } 
    else {
          if(CCP1_INST == ccp->ccp_inst)
          {
                
          CCP1_MODE_SELECTED(CCP_MODULE_DISABLE);
              
              
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
             CCP2_MODE_SELECTED(CCP_MODULE_DISABLE);
          }       
          else {/*nothing*/}
     
        if (CAPTURE_MODE == ccp->ccp_mode) {
            if(CCP1_INST == ccp->ccp_inst)
          {
               switch (ccp->ccp_mode_varient) {
                case CCP_CAPTURE_MODE_EVERY_FAILLING_EDGE:
                    CCP1_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_FAILLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_RAISING_EDGE:
                    CCP1_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_RAISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_4th_RAISING_EDGE:
                    CCP1_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_4th_RAISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_16th_RAISING_EDGE:
                    CCP1_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_16th_RAISING_EDGE);
                    break;
                default:
                    ret = E_NOT_OK;
            }
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
              switch (ccp->ccp_mode_varient) {
                case CCP_CAPTURE_MODE_EVERY_FAILLING_EDGE:
                    CCP2_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_FAILLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_RAISING_EDGE:
                    CCP2_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_RAISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_4th_RAISING_EDGE:
                    CCP2_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_4th_RAISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_EVERY_16th_RAISING_EDGE:
                    CCP2_MODE_SELECTED(CCP_CAPTURE_MODE_EVERY_16th_RAISING_EDGE);
                    break;
                default:
                    ret = E_NOT_OK;
            }
               
          }    
           else {/*nothing*/}
            CCP_Timer_Selected(ccp);

        }
        else if (COMPARE_MODE == ccp->ccp_mode) {
           if(CCP1_INST == ccp->ccp_inst)
          {
                 switch (ccp->ccp_mode_varient) {
                case CCP_COMPARE_MODE_INITIAL_PIN_LOW:
                    CCP1_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_INITIAL_PIN_HIGH:
                    CCP1_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                    CCP1_MODE_SELECTED(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_TRIGGER_SEPECIAL_EVENT:
                    CCP1_MODE_SELECTED(CCP_COMPARE_MODE_TRIGGER_SEPECIAL_EVENT);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                    CCP1_MODE_SELECTED(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                    break;
                default:
                    ret = E_NOT_OK;
            }
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
               switch (ccp->ccp_mode_varient) {
                case CCP_COMPARE_MODE_INITIAL_PIN_LOW:
                    CCP2_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_INITIAL_PIN_HIGH:
                    CCP2_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                    CCP2_MODE_SELECTED(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_TRIGGER_SEPECIAL_EVENT:
                    CCP2_MODE_SELECTED(CCP_COMPARE_MODE_TRIGGER_SEPECIAL_EVENT);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                    CCP2_MODE_SELECTED(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                    break;
                default:
                    ret = E_NOT_OK;
            }
               
          }    
           else {/*nothing*/}
              CCP_Timer_Selected(ccp);
        }
#if(CCP1_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED) ||(CCP2_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED)       
        else if (PWM_MODE == ccp->ccp_mode) {
            
            if(CCP1_INST == ccp->ccp_inst)
          {
                 if (CCP_PWM_MODE == ccp->ccp_mode_varient) {
              CCP1_MODE_SELECTED(CCP_PWM_MODE);
            } 
            else {/*nothing*/}  
              
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
                 if (CCP_PWM_MODE == ccp->ccp_mode_varient) {
                CCP2_MODE_SELECTED(CCP_PWM_MODE);
                 } 
            else {/*nothing*/}
          }
          else {/*nothing*/}  
           
                
            
            PR2 = (uint8) ((_XTAL_FREQ / (ccp->PWM_frequence * 4.0 * ccp->timer2_postcaler_Value * ccp->timer2_prescaler_Value)) - 1);

        }
#endif       
        else {
            /*nothing*/
        }

        ret = gpio_pin_intialize(&(ccp->pin));
           CCP_Interrupt_Config(ccp);

    }
    return ret;
}
Std_ReturnType ccp_DEInit(const ccp_t *ccp){
         Std_ReturnType ret =  E_OK ;
    if(NULL == ccp)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          if(CCP1_INST == ccp->ccp_inst)
          {
               CCP1_MODE_SELECTED(CCP_MODULE_DISABLE);
        #if CCP1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
             CCP1_InterruptDisable();
        #endif
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
               CCP2_MODE_SELECTED(CCP_MODULE_DISABLE);
        #if CCP2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
             CCP2_InterruptDisable();
        #endif
          }    
           else {/*nothing*/}
        
         
    }
     return ret ;
}

#if(CCP1_CFG_SELECTED_MODE ==CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType ccp1_capture_IS_Ready( uint8 *capture_status  ){
         Std_ReturnType ret =  E_OK ;
         
    if(NULL == capture_status)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF)
        {
            *capture_status = CCP1_CAPTURE_READY ;
        }
        else{
            *capture_status =CCP1_CAPTURE_NOT_READY ;
        }
    }
     return ret ;
}

Std_ReturnType ccp1_capture_mode_Read_value( uint16 *capture_value){
         Std_ReturnType ret =  E_OK ;
         ccp_reg_t capture_temp_value = {.ccp_low = 0 , .ccp_high = 0};
    if(NULL == capture_value)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        capture_temp_value.ccp_low = CCPR1L ;
        capture_temp_value.ccp_high = CCPR1H;
        *capture_value = capture_temp_value.ccp_16Bit ;
    }
     return ret ;
}

#endif 

#if(CCP1_CFG_SELECTED_MODE ==CCP1_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType ccp1_compare_IS_Completed( uint8 *compare_status  ){
         Std_ReturnType ret =  E_OK ;
    if(NULL == compare_status)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        if(CCP1_COMPARE_READY == PIR1bits.CCP1IF)
        {
            *compare_status = CCP1_COMPARE_READY ;
        }
        else{
            *compare_status =CCP1_COMPARE_NOT_READY;
        }
        
    }
     return ret ;
}

Std_ReturnType ccp_compare_mode_write_value( const ccp_t *ccp,uint16 compare_value){
      Std_ReturnType ret =  E_OK ;
      ccp_reg_t capture_temp_value = {.ccp_low = 0 , .ccp_high = 0};
         if(NULL == ccp)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
           if(CCP1_INST == ccp->ccp_inst)
          {
             CCPR1L = capture_temp_value.ccp_low ;
             CCPR1H = capture_temp_value.ccp_high ;
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
              CCPR2L = capture_temp_value.ccp_low ;
             CCPR2H = capture_temp_value.ccp_high ;
          }
           capture_temp_value.ccp_16Bit =compare_value;
    }
       
       
       
     return ret ;
}
#endif 

#if(CCP1_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType ccp_PWM_set_duty( const ccp_t *ccp,const uint8 duty ){
      Std_ReturnType ret =  E_OK ;
      uint16 duty_temp = 0 ;
       if(NULL == ccp)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
            duty_temp =  (uint16)(4*(PR2+1)*(duty / 100.0));
            if(CCP1_INST == ccp->ccp_inst)
          {
             CCP1CONbits.DC1B = (uint8)(duty_temp & 0x0003);
             CCPR1L =(uint8)(duty_temp  >> 2);
      
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
               CCP2CONbits.DC2B = (uint8)(duty_temp & 0x0003);
             CCPR2L =(uint8)(duty_temp  >> 2);
      
          }
           
    }
     
      
      
     return ret ;
}
Std_ReturnType cccp_PWM_start(const ccp_t *ccp){
      Std_ReturnType ret =  E_OK ;
      if(NULL == ccp)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          if(CCP1_INST == ccp->ccp_inst)
          {
              CCP1CONbits.CCP1M = CCP_PWM_MODE ;
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
              CCP2CONbits.CCP2M = CCP_PWM_MODE ;
          }
    }
      
     return ret ;
}
Std_ReturnType cccp_PWM_stop(const ccp_t *ccp){
    Std_ReturnType ret =  E_OK ;
     if(NULL == ccp)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          if(CCP1_INST == ccp->ccp_inst)
          {
               CCP1CONbits.CCP1M = CCP_MODULE_DISABLE  ;
          }
          else if(CCP2_INST == ccp->ccp_inst)
          {
              CCP2CONbits.CCP2M = CCP_MODULE_DISABLE  ;
          }
    }
   
     return ret ;
}
#endif 
void CCP1_ISR(void){
     CCP1_InterruptFlagClear();

    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
}
void CCP2_ISR(void){
     CCP2_InterruptFlagClear();

    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
}

static void CCP_Interrupt_Config(const ccp_t *ccp)
{
    #if  CCP1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        CCP1_InterruptHandler = ccp->CCP1_InterruptHandler;

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable  
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == ccp->ccp1_priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPriorityEnable();
        } else if (INTERRUPT_LOW_PRIORITY == ccp->ccp1_priority) {
            CCP1_LowPriorityEnable();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else {
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();

#endif  
#endif 
#if  CCP2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        CCP2_InterruptHandler = ccp->CCP2_InterruptHandler;

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable  
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == ccp->ccp2_priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_HighPriorityEnable();
        } else if (INTERRUPT_LOW_PRIORITY == ccp->ccp2_priority) {
            CCP2_LowPriorityEnable();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else {
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();

#endif  
#endif 

}
static void CCP_Timer_Selected(const ccp_t *ccp)
{
    if(CCP1_CCP2_TIMER3 == ccp->ccp_capture_timer)
    {
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 1 ;
    }
    else if(CCP1_CCP2_TIMER1 == ccp->ccp_capture_timer)
    {
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp->ccp_capture_timer)
    {
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 0;
    }
    else {}
}