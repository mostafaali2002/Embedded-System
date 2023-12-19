/* 
 * File:   hal_usart.c
 * Author: user
 *
 * Created on September 26, 2023, 1:43 PM
 */

#include "hal_usart.h"

#if USART_TX_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*USART_TX_InterruptHandler)(void);
 #endif
#if USART_RX_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*USART_RX_InterruptHandler)(void);
static void (*USART_FRAMING_ERROR_InterruptHandler)(void);
static void (*USART_OVERRUN_ERROR_InterruptHandler)(void);
 #endif

static void USART_BaudRate_Calculation(const usart_t *usart);
static void USART_ASYNC_TX_Init(const usart_t *usart);
static void USART_ASYNC_RX_Init(const usart_t *usart);

Std_ReturnType USART_ASYNC_Init(const usart_t *usart){
     Std_ReturnType ret =  E_OK ;
    if(NULL == usart)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        RCSTAbits.SPEN = USART_MODULE_DISABLE ;
        USART_BaudRate_Calculation(usart);
        USART_ASYNC_TX_Init(usart);
         USART_ASYNC_RX_Init(usart);
        RCSTAbits.SPEN = USART_MODULE_ENABLE ;
    }
     return ret;
}
Std_ReturnType USART_ASYNC_DEinit(const usart_t *usart){
        Std_ReturnType ret =  E_OK ;
    if(NULL == usart)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        RCSTAbits.SPEN = USART_MODULE_DISABLE ;
    }
     return ret;
}
Std_ReturnType USART_ASYNC_ReadByteBloking( uint8 *data){
        Std_ReturnType ret =  E_OK ;
    if((NULL == data))
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        while(!PIR1bits.RCIF)
        *data = RCREG ;
    }
     return ret;
}
Std_ReturnType USART_ASYNC_ReadByteNoBloking( uint8 *data){
     Std_ReturnType ret =  E_OK ;
     if(1 == PIR1bits.RCIF){
          *data = RCREG ;
          
     }
     else{
         ret =  E_NOT_OK; 
     }
             
     
    return ret ;
}
Std_ReturnType USART_ASYNC_WriteByteBloking( uint8 data){
        Std_ReturnType ret =  E_OK ;
    
        while(!TXSTAbits.TRMT);
#if USART_TX_INTERRUPT_FEATURE_ENABLE == FeatureEnable        
        USART_TX_InterruptEnable();
#endif        
         TXREG= data ;
    
     return ret;
}
Std_ReturnType USART_ASYNC_WriteStringBloking( uint8 *data,uint16 str_len){
    Std_ReturnType ret =  E_OK ;
    uint16 count = ZERO_INIT ;
    for(count = ZERO_INIT ; count < str_len ;count++)
    {
       ret = USART_ASYNC_WriteByteBloking(data[count]);
    }
    return ret;
}
static void USART_BaudRate_Calculation(const usart_t *usart){
    float USART_BaudRate = 0 ;
    switch(usart->baudrate_gen)
    {
       case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
           TXSTAbits.SYNC = USART_ASYNCHRONOUS_ENABLE ;
           TXSTAbits.BRGH =USART_ASYNCHRONOUS_LOW_SPEED;
           BAUDCONbits.BRG16 =USART_8BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/64)-1;
         break ;
       case BAUDRATE_ASYNC_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_ENABLE ;
           TXSTAbits.BRGH =USART_ASYNCHRONOUS_HIGH_SPEED;
           BAUDCONbits.BRG16 =USART_8BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/16)-1;
         break ;
       case BAUDRATE_ASYNC_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_ENABLE ;
           TXSTAbits.BRGH =USART_ASYNCHRONOUS_LOW_SPEED;
           BAUDCONbits.BRG16 =USART_16BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/16)-1;
         break ;
       case BAUDRATE_ASYNC_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_ENABLE ;
           TXSTAbits.BRGH =USART_ASYNCHRONOUS_HIGH_SPEED;
           BAUDCONbits.BRG16 =USART_16BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/4)-1;
         break ;
       case BAUDRATE_SYNC_8BIT :
           TXSTAbits.SYNC = USART_ASYNCHRONOUS_ENABLE ;
           BAUDCONbits.BRG16 =USART_8BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/4)-1;
         break ;
       case BAUDRATE_SYNC_16BIT :
           TXSTAbits.SYNC = USART_SYNCHRONOUS_ENABLE ;
           BAUDCONbits.BRG16 =USART_16BIT_BAUDRATE ;
           USART_BaudRate = ((_XTAL_FREQ /(float)usart->baudrate)/4)-1;
         break ;
    }
    SPBRG = (uint8)((uint32)USART_BaudRate);
    SPBRGH = (uint8)(((uint32)USART_BaudRate)>> 8);
}

static void USART_ASYNC_TX_Init(const usart_t *usart){
    if(USART_ASYNCHRONOUS_TX_ENABLE == usart->usart_tx.usart_tx_enable){
        TXSTAbits.TXEN = USART_ASYNCHRONOUS_TX_ENABLE ;
        USART_TX_InterruptHandler = usart->USART_TX_InterruptHandler;
        if(USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == usart->usart_tx.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ;
 #if  USART_TX_INTERRUPT_FEATURE_ENABLE == FeatureEnable
            USART_TX_InterruptEnable();
 #if INTERRUPT_Priority_Levels_Enable == FeatureEnable
                 INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == usart->usart_tx.usart_tx_int_priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 USART_TX_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == usart->usart_tx.usart_tx_int_priority)  
             {
                 USART_TX_LowPriorityEnable();
                 INTERRUPT_GlobalInterruptLowEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
#endif
#endif            
        }
        
        else if(USART_ASYNCHRONOUS_INTERRUPT_TX_DISENABL == usart->usart_tx.usart_tx_interrupt_enable){
            PIE1bits.TXIE = USART_ASYNCHRONOUS_INTERRUPT_TX_DISENABL ;
        }
         else{/*Nothing*/}
        if(USART_ASYNCHRONOUS_TX_9BIT_ENABLE == usart->usart_tx.usart_tx_9bit_enable)
        {
            TXSTAbits.TX9 =USART_ASYNCHRONOUS_TX_9BIT_ENABLE ;
        }
        
        else if(USART_ASYNCHRONOUS_TX_9BIT_DISENABLE == usart->usart_tx.usart_tx_9bit_enable){
            TXSTAbits.TX9 =USART_ASYNCHRONOUS_TX_9BIT_DISENABLE ;
        }
         else{/*Nothing*/}
        
    }
    else{/*Nothing*/}
}
static void USART_ASYNC_RX_Init(const usart_t *usart){
     if(USART_ASYNCHRONOUS_RX_ENABLE == usart->usart_rx.usart_rx_enable){
         RCSTAbits.CREN = USART_ASYNCHRONOUS_RX_ENABLE ;
         
        if(USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == usart->usart_rx.usart_rx_interrupt_enable)
        {
            PIE1bits.RCIE = USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ;
 #if  USART_RX_INTERRUPT_FEATURE_ENABLE == FeatureEnable
            USART_RX_InterruptEnable();
         USART_RX_InterruptHandler =usart->USART_RX_InterruptHandler;
         USART_FRAMING_ERROR_InterruptHandler = usart->USART_FRAMING_InterruptHandler;
         USART_OVERRUN_ERROR_InterruptHandler= usart->USART_OVERRUN_InterruptHandler;
            
 #if INTERRUPT_Priority_Levels_Enable == FeatureEnable
                 INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == usart->usart_rx.usart_rx_int_priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 USART_RX_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == usart->usart_rx.usart_rx_int_priority)  
             {
                 USART_RX_LowPriorityEnable();
                 INTERRUPT_GlobalInterruptLowEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
#endif
#endif     
        }
        
        else if(USART_ASYNCHRONOUS_INTERRUPT_RX_DISENABL == usart->usart_rx.usart_rx_interrupt_enable){
            PIE1bits.RCIE = USART_ASYNCHRONOUS_INTERRUPT_RX_DISENABL ;
        }
         else{/*Nothing*/}
        if(USART_ASYNCHRONOUS_RX_9BIT_ENABLE == usart->usart_rx.usart_rx_9bit_enable)
        {
            RCSTAbits.RX9 =USART_ASYNCHRONOUS_RX_9BIT_ENABLE ;
        }
        
        else if(USART_ASYNCHRONOUS_RX_9BIT_DISENABLE == usart->usart_rx.usart_rx_9bit_enable){
            RCSTAbits.RX9 =USART_ASYNCHRONOUS_RX_9BIT_DISENABLE ;
        }
         else{/*Nothing*/}
        
    }
    else{/*Nothing*/}
}

void USART_RX_ISR(void){
    PIR1bits.RCIF = 1 ;
    if(USART_RX_InterruptHandler)
    {
        USART_RX_InterruptHandler();
    }
    else{/*Nothing*/}
    PIR1bits.RCIF = 0;
    if(USART_FRAMING_ERROR_InterruptHandler)
    {
        USART_FRAMING_ERROR_InterruptHandler();
    }
    else{/*Nothing*/}
    if(USART_OVERRUN_ERROR_InterruptHandler)
    {
        USART_OVERRUN_ERROR_InterruptHandler();
    }
    else{/*Nothing*/}
}

void USART_TX_ISR(void){
    USART_TX_InterruptDisable();
    if(USART_TX_InterruptHandler)
    {
        USART_TX_InterruptHandler();
    }
    
}