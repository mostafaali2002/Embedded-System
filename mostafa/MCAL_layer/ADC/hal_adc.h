/* 
 * File:   hal_adc.h
 * Author: user
 *
 * Created on September 16, 2023, 6:04 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* Section : Macro Declaration*/
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAl_FUNCTIONALITY   0x0F

#define ADC_RESULT_RIGH     0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_ENABLE_VOLTAGE_REFERENCE_ENABLE  0x01U
#define ADC_ENABLE_VOLTAGE_REFERENCE_DISABLE  0x00U



#define ADC_CONVERSION_COMPLETED  1

#define ADC_CONVERSION_NOT_COMPLETED  0



/* Section : Macro Function Declaration*/
#define ADC_CONVERSION_STATUS()      (ADCON0bits.GO_nDONE)

#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)

#define ADC_CONVERTER_ENABLE()        (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()        (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VOLTAGE_REFERENCE()    do{ ADCON1bits.VCFG0 = 1 ;\
                                              ADCON1bits.VCFG1 = 1 ;\
                                            }while(0) 

#define ADC_DISABLE_VOLTAGE_REFERENCE()    do{ ADCON1bits.VCFG0 = 0 ;\
                                              ADCON1bits.VCFG1 = 0 ;\
                                            }while(0) 

#define ADC_ANALOG_DIGITAL_CONFIG(_CONFIG)   (ADCON1bits.PCFG =_CONFIG)

#define ADC_RESULT_RIGH_FORMAT()            (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()            (ADCON2bits.ADFM = 0)
                                              
/* Section : Data Type Declaration */
typedef enum{
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1  ,
    ADC_CHANNEL_AN2  ,
    ADC_CHANNEL_AN3  ,
    ADC_CHANNEL_AN4  ,
    ADC_CHANNEL_AN5  ,
    ADC_CHANNEL_AN6  ,
    ADC_CHANNEL_AN7  ,
    ADC_CHANNEL_AN8  ,
    ADC_CHANNEL_AN9  ,
    ADC_CHANNEL_AN10 ,
    ADC_CHANNEL_AN11 ,
    ADC_CHANNEL_AN12 
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD =0 ,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD ,       
    ADC_12_TAD ,
    ADC_16_TAD,
    ADC_20_TAD        
         
}adc_aquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 =0 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4 ,       
    ADC_CONVERSION_CLOCK_FOSC_DIV_16 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
          
         
}adc_conversion_clock_t ;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*ADC_InterruptHandler)(void);
     interrupt_priority_cfg priority;
#endif    
    adc_conversion_clock_t conversion_clock ;
    adc_aquisition_time_t  aquisition_time;
    adc_channel_select_t   channel_select;
    uint8 voltage_reference : 1 ;
    uint8 result_format : 1 ;
    uint8 ADC_Reserved : 6 ;
}adc_conf_t;
/* Section : Function Declaration*/
Std_ReturnType ADC_Init(const adc_conf_t *adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *adc);
Std_ReturnType ADC_SelectChannal(const adc_conf_t *adc,adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *adc);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *adc , uint8 *conversion_state);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *adc , uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Bloking(const adc_conf_t *adc , adc_channel_select_t channel,uint16 *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc , adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

