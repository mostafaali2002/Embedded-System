/* 
 * File:   mcal_interrupt_manager.c
 * Author: user
 *
 * Created on September 10, 2023, 11:18 AM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1 , RB5_Flag = 1 , RB6_Flag = 1,RB7_Flag = 1;

#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
void __interrupt() interruptMangerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCURE == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCURE == INTCONbits.INT0IF))
    {
        INT2_ISR();
    }
    else {/*Nothing */}
}
void __interrupt(low_priority) interruptMangerLow(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCURE == INTCONbits.INT0IF))
    {
        INT1_ISR();
    }
    else {/*Nothing */}
}

#else
void __interrupt() interruptManger(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCURE == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else {/*Nothing */}
      if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCURE == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else {/*Nothing */}
     if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCURE == INTCON3bits.INT2IF))
    {
        INT1_ISR();
    }
    else {/*Nothing */}
     if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCURE == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB4 == GPIO_HIGH)
            &&(RB4_Flag ==1))
    {
        RB4_Flag = 0 ;
        RB4_ISR(1);
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB4 == GPIO_LOW) 
            &&(RB4_Flag ==0))
    {
        RB4_Flag = 1 ;
        RB4_ISR(0);
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB5 == GPIO_HIGH)
             &&(RB5_Flag ==1))
    {
        RB5_Flag =0 ;
        RB5_ISR(1);
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB5 == GPIO_LOW)
            &&(RB5_Flag ==0))
    {
        RB5_Flag = 1 ;
        RB5_ISR(0);
    }
    else {/*Nothing */}
    
      if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB6 == GPIO_HIGH)
             &&(RB6_Flag ==1))
    {
        RB6_Flag =0 ;
        RB6_ISR(1);
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB6 == GPIO_LOW)
            &&(RB6_Flag ==0))
    {
        RB6_Flag = 1 ;
        RB6_ISR(0);
    }
    else {/*Nothing */}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB7 == GPIO_HIGH)
             &&(RB7_Flag ==1))
    {
        RB7_Flag =0 ;
        RB7_ISR(1);
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCURE == INTCONbits.RBIF)&&(PORTBbits.RB7 == GPIO_LOW)
            &&(RB7_Flag ==0))
    {
        RB7_Flag = 1 ;
        RB7_ISR(0);
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE )&&(INTERRUPT_OCCURE == INTCONbits.TMR0IF ))
    {
        TM0_ISR();
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE  )&&(INTERRUPT_OCCURE == PIR1bits.TMR1IF ))
    {
        TM1_ISR();
    }
    else {/*Nothing */}
      if((INTERRUPT_ENABLE == PIE1bits.TMR2IE  )&&(INTERRUPT_OCCURE == PIR1bits.TMR2IF ))
    {
        TM2_ISR();
    }
    else {/*Nothing */}
       if((INTERRUPT_ENABLE == PIE2bits.TMR3IE  )&&(INTERRUPT_OCCURE == PIR2bits.TMR3IF ))
    {
        TM3_ISR();
    }
    else {/*Nothing */}
        if((INTERRUPT_ENABLE == PIE1bits.CCP1IE  )&&(INTERRUPT_OCCURE == PIR1bits.CCP1IF ))
    {
        CCP1_ISR();
    }
    else {/*Nothing */}
        if((INTERRUPT_ENABLE == PIE2bits.CCP2IE  )&&(INTERRUPT_OCCURE == PIR2bits.CCP2IF ))
    {
        CCP2_ISR();
    }
    else {/*Nothing */}
        if((INTERRUPT_ENABLE == PIE1bits.RCIE  )&&(INTERRUPT_OCCURE == PIR1bits.RCIF ))
    {
        USART_RX_ISR();
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.TXIE )&&(INTERRUPT_OCCURE == PIR1bits.TXIF))
    {
        USART_TX_ISR();
    }
    else {/*Nothing */}
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE )&&(INTERRUPT_OCCURE == PIR1bits.SSPIF))
    {
        MSSP_I2C_ISR();
    }
    else {/*Nothing */}
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE )&&(INTERRUPT_OCCURE == PIR2bits.BCLIF))
    {
        MSSP_I2C_BUSC_ISR();
    }
    else {/*Nothing */}
}


#endif