/* 
 * File:   Embe_Initialization.h
 * Author: user
 *
 * Created on September 23, 2023, 5:10 PM
 */

#ifndef EMBE_INITIALIZATION_H
#define	EMBE_INITIALIZATION_H

#include "ECU_layer/LED/ecu_led.h"
#include "ECU_layer/Button/ecu_button.h"
#include "ECU_layer/Relay/ecu_relay.h"
#include "ECU_layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_layer/7_segment/ecu_seven_segment.h"
#include "ECU_layer/Keypad/ecu_keypad.h"
#include "ECU_layer/chr_LCD/ecu_chr_lcd.h"
#include "MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_layer/Timer0/hal_timer0.h"
#include "MCAL_layer/Timer1/hal_timer1.h"
#include "MCAL_layer/Timer2/hal_timer2.h"
#include "MCAL_layer/Timer3/hal_timer3.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "MCAL_layer/CCP1/hal_ccp1.h"
#include "MCAL_layer/GPIO/hal_gpio.h"
#include "MCAL_layer/USART/hal_usart.h"
#include "MCAL_layer/I2C/hal_i2c.h"

void APP_ISR(void);
void APP_RB4_High(void);
void APP_RB4_Low(void);
void timer1_Counter_Init(void);
void timer1_Init(void);
void Timer1_Default(void);
void timer_ISR(void);
void timer2_ISR(void);
void Timer3_Interrupt_capture(void);
 void CCP_Interrupt_Capture(void);
 void Timer3_Interrupt_compare (void);

#endif	/* EMBE_INITIALIZATION_H */

