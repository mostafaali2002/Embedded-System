/* 
 * File:   mcal_internal_interrupt.h
 * Author: user
 *
 * Created on September 10, 2023, 11:20 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"
/* Section : Macro Declaration*/

/* Section : Macro Function Declaration*/
#if  ADC_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
#define ADC_InterruptDisable()         (PIE1bits.ADIE= 0)
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF= 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
#define ADC_HighPriorityEnable()          (IPR1bits.ADIP= 1)
#define ADC_LowPriorityDisable()          (IPR1bits.ADIP= 0)

#endif        
#endif 

#if  TIMER0_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE= 0)
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF= 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
#define TIMER0_HighPriorityEnable()          (INTCON2bits.TMR0IP= 1)
#define TIMER0_LowPriorityEnable()          (INTCON2bits.TMR0IP= 0)

#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 1)
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define TIMER1_HighPriorityEnable()          (IPR1bits.TMR1IP = 1)
#define TIMER1_LowPriorityEnable()          (IPR1bits.TMR1IP = 0)

#endif     
#endif 

/*-------------*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE = 1)
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE = 1)
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define TIMER2_HighPriorityEnable()          (IPR1bits.TMR2IP = 1)
#define TIMER2_LowPriorityEnable()          (IPR1bits.TMR2IP = 0)

#endif     
#endif 

/******/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE = 1)
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE = 1)
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define TIMER3_HighPriorityEnable()          (IPR2bits.TMR3IP = 1)
#define TIMER3_LowPriorityEnable()          (IPR2bits.TMR3IP = 0)

#endif     
#endif 
/*----------------------*/
#if CCP1_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define CCP1_InterruptEnable()          (PIE1bits.CCP1IE = 1)
#define CCP1_InterruptDisable()         (PIE1bits.CCP1IE  = 1)
#define CCP1_InterruptFlagClear()       (PIR1bits.CCP1IF= 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define CCP1_HighPriorityEnable()          (IPR1bits.CCP1IP = 1)
#define CCP1_LowPriorityEnable()          (IPR1bits.CCP1IP = 0)

#endif     
#endif 
/*****************************/
#if CCP2_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define CCP2_InterruptEnable()          (PIE2bits.CCP2IE = 1)
#define CCP2_InterruptDisable()         (PIE2bits.CCP2IE  = 0)
#define CCP2_InterruptFlagClear()       (PIR2bits.CCP2IF= 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define CCP2_HighPriorityEnable()          (IPR2bits.CCP2IP = 1)
#define CCP2_LowPriorityEnable()          (IPR2bits.CCP2IP = 0)

#endif     
#endif 
/*****************************/
#if USART_TX_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define USART_TX_InterruptEnable()          (PIE1bits.TXIE = 1)
#define USART_TX_InterruptDisable()         (PIE1bits.TXIE = 0)


#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define USART_TX_HighPriorityEnable()          (IPR1bits.TXIP = 1)
#define USART_TX_LowPriorityEnable()          (IPR1bits.TXIP = 0)

#endif     
#endif
/*****************************/
#if USART_RX_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define USART_RX_InterruptEnable()          (PIE1bits.RCIE = 1)
#define USART_RX_InterruptDisable()         (PIE1bits.RCIE = 0)


#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define USART_RX_HighPriorityEnable()          (IPR1bits.RCIP = 1)
#define USART_RX_LowPriorityEnable()          (IPR1bits.RCIP  = 0)

#endif     
#endif
/**********************************************/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable

#define MSSP_I2C_InterruptEnable()          (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()  (PIE2bits.BCLIE = 1)

#define MSSP_I2C_InterruptDisable()         (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable() (PIE2bits.BCLIE = 0)

#define MSSP_I2C_InterruptFlagClear()       (PIR1bits.SSPIF= 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear()    (PIR2bits.BCLIF= 0)

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable

#define MSSP_I2C_HighPriorityEnable()          (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPriorityEnable()   (IPR2bits.BCLIP = 1)
#define MSSP_I2C_LowPriorityEnable()          (IPR1bits.SSPIP  = 0)
#define MSSP_I2C_BUS_COL_LowPriorityEnable()  (IPR2bits.BCLIP  = 0)

#endif     
#endif
/* Section : Data Type Declaration */

/* Section : Function Declaration*/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

