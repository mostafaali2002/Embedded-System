/* 
 * File:   hal_adc.h
 * Author: user
 *
 * Created on September 16, 2023, 6:04 PM
 */

#include "hal_adc.h"
#if  ADC_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        static void (* ADC_InterruptHandler)(void);
#endif 


static inline void adc_input_channel_port_config(adc_channel_select_t channel);
static inline void adc_select_format (const adc_conf_t *adc);
static inline void adc_voltage_reference (const adc_conf_t *adc);
void ADC_ISR(void);

Std_ReturnType ADC_Init(const adc_conf_t *adc){
      Std_ReturnType ret = E_OK ;
    if((NULL == adc))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
       /*Disable Conversion*/
        ADC_CONVERTER_DISABLE();
       /*configure acquisition  time*/  
        ADCON2bits.ACQT = adc->aquisition_time;
        /*configure the conversion clock*/
        ADCON2bits.ADCS =adc->conversion_clock ;
        /*configure the default channel*/
        ADCON0bits.CHS = adc->channel_select ;
        adc_input_channel_port_config(adc->channel_select);
        /*configure interrupt */
#if  ADC_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable        
        if(INTERRUPT_HIGH_PRIORITY == adc->priority){ADC_HighPriorityEnable() ;}
        else if(INTERRUPT_LOW_PRIORITY == adc->priority){ADC_LowPriorityDisable() ;} 
        else {}
#else
      INTERRUPT_PeripheralInterruptEnable() ;
       INTERRUPT_GlobalInterruptEnable() ;  
#endif        
        
        ADC_InterruptHandler = adc->ADC_InterruptHandler ;
#endif 
        
        /* configure the result format*/
        adc_select_format(adc);
        /* configure voltage*/
        adc_voltage_reference(adc);
        
       /*Enable Conversion*/
        ADC_CONVERTER_ENABLE();
    }
       return ret ;
}
Std_ReturnType ADC_DeInit(const adc_conf_t *adc){
       Std_ReturnType ret = E_OK ;
    if((NULL == adc))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        /*Disable Conversion*/
        ADC_CONVERTER_DISABLE();
        /*disable interrupt */
#if  ADC_INTERRUPT_FEATURE_ENABLE == FeatureEnable
        ADC_InterruptDisable();
#endif       
    }
       return ret ;

}
Std_ReturnType ADC_SelectChannal(const adc_conf_t *adc,adc_channel_select_t channel){
       Std_ReturnType ret = E_OK ;
    if((NULL == adc))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
         ADCON0bits.CHS = channel ;
        adc_input_channel_port_config(channel);
       
    }
       return ret ;

}
Std_ReturnType ADC_StartConversion(const adc_conf_t *adc){
       Std_ReturnType ret = E_OK ;
    if((NULL == adc))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        ADC_START_CONVERSION();
    }
       return ret ;

}
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *adc , uint8 *conversion_state){
       Std_ReturnType ret = E_OK ;
    if((NULL == adc)||(NULL==conversion_state))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *conversion_state = (uint8)(!(ADCON0bits.GO_DONE));/* If conversion complete status = 1 */
       
    }
       return ret ;

}
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *adc , uint16 *conversion_result){
     Std_ReturnType ret = E_OK ;
    if((NULL == adc)||(NULL==conversion_result))
    {
        ret = E_NOT_OK ; 
    } else {
        if (ADC_RESULT_RIGH == adc->result_format) {
            *conversion_result = (uint16)((ADRESH <<8) + ADRESL) ;
        } else if (ADC_RESULT_LEFT == adc->result_format) {
            *conversion_result = (uint16)(((ADRESH <<8) + ADRESL)>>6) ;
        } else {
            *conversion_result = (uint16)((ADRESH <<8) + ADRESL) ;
        }
    }
       return ret ;
}
Std_ReturnType ADC_GetConversion_Bloking(const adc_conf_t *adc , adc_channel_select_t channel,uint16 *conversion_result)
{
     Std_ReturnType ret = E_OK ;
     uint8 l_conversion_status = ZERO_INIT ;
    if((NULL == adc)||(NULL==conversion_result))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        /*configure the default channel*/
        ret = ADC_SelectChannal(adc,channel);
        /* Start Conversion*/
        ret = ADC_StartConversion(adc);
        /* check if conversion complete*/
        while (ADCON0bits.GO_DONE) ;
         ret = ADC_GetConversionResult(adc,conversion_result);

   
    }
       return ret ;
    
}
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc , adc_channel_select_t channel){
     Std_ReturnType ret = E_OK ;
    
    if((NULL == adc))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        /*configure the default channel*/
        ret = ADC_SelectChannal(adc,channel);
        /* Start Conversion*/
        ret = ADC_StartConversion(adc);
       
       

   
    }
       return ret ;
}

static inline void adc_input_channel_port_config(adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA , _TRISA_RA0_POSN); break ;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA , _TRISA_RA1_POSN); break ;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA , _TRISA_RA2_POSN); break ;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA , _TRISA_RA3_POSN); break ;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA , _TRISA_RA5_POSN); break ;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE , _TRISE_RE0_POSN); break ;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE , _TRISE_RE1_POSN); break ;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE , _TRISE_RE2_POSN); break ;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB , _TRISB_RB2_POSN); break ;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB , _TRISB_RB3_POSN); break ;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB , _TRISB_RB1_POSN); break ;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB , _TRISB_RB4_POSN); break ;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB , _TRISB_RB0_POSN); break ;
        default : /*Nothing */ ;
            
    }
}
static inline void adc_select_format (const adc_conf_t *adc)
{
    if(ADC_RESULT_RIGH == adc->result_format)
    {
        ADC_RESULT_RIGH_FORMAT();
    }
    else if (ADC_RESULT_LEFT == adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGH_FORMAT();
    }
}
static inline void adc_voltage_reference (const adc_conf_t *adc)
{
    if(ADC_ENABLE_VOLTAGE_REFERENCE_ENABLE == adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if (ADC_ENABLE_VOLTAGE_REFERENCE_DISABLE == adc->voltage_reference)
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

void ADC_ISR(void){
     ADC_InterruptFlagClear();
    
    
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}