/* 
 * File:   hal_ccp1.h
 * Author: user
 *
 * Created on September 23, 2023, 12:37 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes */
#include "hal_ccp1_cfg.h"
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/

#define CCP_COMPARE_MODE_TOGGLE_OUTPUT            (uint8) 0x02
#define CCP_CAPTURE_MODE_EVERY_FAILLING_EDGE       (uint8)0x04
#define CCP_CAPTURE_MODE_EVERY_RAISING_EDGE        (uint8)0x05
#define CCP_CAPTURE_MODE_EVERY_4th_RAISING_EDGE    (uint8)0x06
#define CCP_CAPTURE_MODE_EVERY_16th_RAISING_EDGE   (uint8)0x07
#define CCP_COMPARE_MODE_INITIAL_PIN_LOW          (uint8) 0x08
#define CCP_COMPARE_MODE_INITIAL_PIN_HIGH          (uint8)0x09
#define CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT     (uint8)0x0A
#define CCP_COMPARE_MODE_TRIGGER_SEPECIAL_EVENT    (uint8)0x0B 
#define CCP_MODULE_DISABLE                         (uint8)0x00
#define CCP_RESERVED                               (uint8)0x01 
#define CCP_PWM_MODE                               (uint8)0x0C

/*------------------------------------------*/
#define CCP1_CAPTURE_READY               0x01
#define CCP1_CAPTURE_NOT_READY           0x00

#define CCP1_COMPARE_READY               0x01
#define CCP1_COMPARE_NOT_READY           0x00

/*------------POSTCALER--------*/
#define  CCP_POSTCALER_DIV_BY_1    1
#define  CCP_POSTCALER_DIV_BY_2    2
#define  CCP_POSTCALER_DIV_BY_3    3
#define  CCP_POSTCALER_DIV_BY_4    4
#define  CCP_POSTCALER_DIV_BY_5    5
#define  CCP_POSTCALER_DIV_BY_6    6
#define  CCP_POSTCALER_DIV_BY_7    7
#define  CCP_POSTCALER_DIV_BY_8    8
#define  CCP_POSTCALER_DIV_BY_9    9
#define  CCP_POSTCALER_DIV_BY_10    10
#define  CCP_POSTCALER_DIV_BY_11    11
#define  CCP_POSTCALER_DIV_BY_12    12
#define  CCP_POSTCALER_DIV_BY_13    13
#define  CCP_POSTCALER_DIV_BY_14    14
#define  CCP_POSTCALER_DIV_BY_15    15
#define  CCP_POSTCALER_DIV_BY_16    16

/*------------PRESCALER--------*/
#define  CCP_PRESCALER_DIV_BY_1     1
#define  CCP_PRESCALER_DIV_BY_4     2
#define  CCP_PRESCALER_DIV_BY_16    3

/* Section : Macro Function Declaration*/
#define CCP1_MODE_SELECTED(_set_)            (CCP1CONbits.CCP1M=_set_)
#define CCP2_MODE_SELECTED(_set_)            (CCP2CONbits.CCP2M=_set_)
/* Section : Data Type Declaration */
typedef union {
    struct{
        uint8 ccp_low ;
         uint8 ccp_high ;
    };
    struct{
        uint16 ccp_16Bit ;
    };
}ccp_reg_t;

typedef enum {
    CAPTURE_MODE = 0 ,
    COMPARE_MODE,
    PWM_MODE        
}ccp1_mode;

typedef enum {
    CCP1_INST = 0 ,
    CCP2_INST,
         
}ccp_inst_t;

typedef enum {
    CCP1_CCP2_TIMER3 = 0 ,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1        
         
}ccp_capture_timer_t;

typedef struct {
    ccp1_mode ccp_mode ;
    uint8 ccp_mode_varient ; 
    pin_config_t pin ;
    ccp_inst_t ccp_inst ;
    ccp_capture_timer_t ccp_capture_timer ;
 #if  CCP1_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*CCP1_InterruptHandler)(void);
     interrupt_priority_cfg ccp1_priority;
#endif
#if  CCP2_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*CCP2_InterruptHandler)(void);
     interrupt_priority_cfg ccp2_priority;
#endif
#if(CCP1_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED) ||(CCP2_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED)
  uint32 PWM_frequence ;
  uint8 timer2_prescaler_Value :2;
  uint8 timer2_postcaler_Value :4;
#endif 
}ccp_t;
/* Section : Function Declaration*/
Std_ReturnType ccp_Init(const ccp_t *ccp);
Std_ReturnType ccp_DEInit(const ccp_t *ccp);
#if(CCP1_CFG_SELECTED_MODE ==CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType ccp1_capture_IS_Ready( uint8 *capture_status  );
Std_ReturnType ccp1_capture_mode_Read_value( uint16 *capture_value);
#endif 

#if(CCP1_CFG_SELECTED_MODE ==CCP1_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType ccp1_compare_IS_Completed( uint8 *compare_status  );
Std_ReturnType ccp_compare_mode_write_value( const ccp_t *ccp,uint16 compare_value);
#endif 

#if(CCP1_CFG_SELECTED_MODE ==CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType ccp_PWM_set_duty( const ccp_t *ccp , const uint8 duty );
Std_ReturnType cccp_PWM_start(const ccp_t *ccp);
Std_ReturnType cccp_PWM_stop(const ccp_t *ccp);
#endif 
#endif	/* HAL_CCP1_H */

