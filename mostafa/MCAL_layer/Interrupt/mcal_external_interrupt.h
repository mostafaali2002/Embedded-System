/* 
 * File:   mcal_external_interrupt.h
 * Author: user
 *
 * Created on September 10, 2023, 11:19 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declaration*/
#if  EXTERNAL_INTERRUPT_INTx_Feature_Enable == FeatureEnable

#define EXT_INT0_InterruptEnable()          (INTCONbits.INT0IE = 1)
#define EXT_INT0_InterruptDisable()         (INTCONbits.INT0IE = 0)
#define EXT_INT0_InterruptFlagClear()       (INTCONbits.INT0IF = 0)
#define EXT_INT0_RisingEdge()               (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdge()              (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1IE = 1)
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1IE = 0)
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1IF = 0)
#define EXT_INT1_RisingEdge()               (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdge()              (INTCON2bits.INTEDG1 = 0)

#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2IE = 1)
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2IE = 0)
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2IF = 0)
#define EXT_INT2_RisingEdge()               (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdge()              (INTCON2bits.INTEDG2 = 0)

  #if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define EXT_INT1_HighPriorityEnable()          (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPriorityDisable()          (INTCON3bits.INT1IP = 0)

#define EXT_INT2_HighPriorityEnable()          (INTCON3bits.INT2IP = 1)
#define EXT_INT2_LowPriorityDisable()          (INTCON3bits.INT2IP = 0)
#endif
#endif

#if  EXTERNAL_INTERRUPT_OnChange_Feature_Enable == FeatureEnable
#define EXT_RBx_InterruptEnable()          (INTCONbits.RBIE = 1)
#define EXT_RBx_InterruptDisable()          (INTCONbits.RBIE = 0)
#define EXT_RBx_InterruptFlagClear()          (INTCONbits.RBIF = 0)

  #if INTERRUPT_Priority_Levels_Enable == FeatureEnable
#define EXT_RBx_High_Priority()             (INTCON2bits.RBIP = 1)
#define EXT_RBx_Low_Priority()             (INTCON2bits.RBIP = 0)
#endif
#endif


/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef enum {
    
    INTERRUPT_FALLING_EDGE = 0 ,
    INTERRUPT_RASING_EDGE 
}interrupt_INTx_edge;

typedef enum {
    INTERRUPT_External_INTx0 = 0 ,
    INTERRUPT_External_INTx1, 
    INTERRUPT_External_INTx2
}interrupt_INTx_src;

typedef struct {
    void (* Ext_InterruptHandler)(void);
    interrupt_INTx_edge edge;
    interrupt_INTx_src source ;
    interrupt_priority_cfg priority;
    pin_config_t mcu_pin;
}interrupt_INTx_t;

typedef struct {
        void (* Ext_Interrupt_High)(void);
        void (* Ext_Interrupt_Low) (void);
          pin_config_t mcu_pin;
          interrupt_priority_cfg priority;

    
}interrupt_RBx_t;

/* Section : Function Declaration*/
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *obj);
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t *obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *obj);
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

