/* 
 * File:   mcal_interrupt_manager.h
 * Author: user
 *
 * Created on September 10, 2023, 11:18 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes */
#include "mcal_interrupt_config.h"
/* Section : Macro Declaration*/

/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */

/* Section : Function Declaration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB_Source);
void RB5_ISR(uint8 RB_Source);
void RB6_ISR(uint8 RB_Source);
void RB7_ISR(uint8 RB_Source);
void ADC_ISR(void);
void TM0_ISR(void);
void TM1_ISR(void);
void TM2_ISR(void);
void TM3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void USART_RX_ISR(void);
void USART_TX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BUSC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

