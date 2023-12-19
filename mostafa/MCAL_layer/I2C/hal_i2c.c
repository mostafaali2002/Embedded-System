/* 
 * File:   hal_i2c.c
 * Author: user
 *
 * Created on October 2, 2023, 5:19 PM
 */

#include "hal_i2c.h"

#if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
static void (*I2C_Report_Write_Collision_InterruptHandler)(void);
static void (*I2C_DefaultInterruptHandler)(void);
static void (*I2C_Report_Recive_OverFlow_InterruptHandler)(void);
 #endif
static inline void  MSSP_Interrupt_config(const mssp_i2c_t *i2c_obj);

Std_ReturnType mssp_i2c_Init(const mssp_i2c_t *i2c_obj){
     Std_ReturnType ret =  E_OK ;
    if(NULL == i2c_obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          I2C_MODULE_DISABLE();
        if(I2C_MSSP_MASTER_MODE==i2c_obj->i2c_cfg.i2c_mode )
        {
            SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg ;
            SSPADD = ((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock )-1 ;
        }
        else if(I2C_MSSP_SLAVE_MODE==i2c_obj->i2c_cfg.i2c_mode )
        {
            if(I2C_GENERAL_CALL_ENABLE ==i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE ==i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            SSPCON1bits.WCOL = 0 ; /*clear the write collision*/
            SSPCON1bits.SSPOV = 0 ; /*No overflow*/
             SSPCON1bits.CKP = 1 ; /*release the clock*/
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_addres ;
            SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg ;
            
            
            
        }
        else{/*NOTHING*/}
        TRISCbits.TRISC3 = 1 ;         /*clock line*/
        TRISCbits.TRISC4 = 1 ;      /*data line*/
        
         if(I2C_SLEW_RATE_ENABLE ==i2c_obj->i2c_cfg.i2c_slew_rate)
            {
                I2C_SLEW_RATE_ENABLE_CFG();
            }
            else if(I2C_SLEW_RATE_DISABLE ==i2c_obj->i2c_cfg.i2c_slew_rate)
            {
                I2C_SLEW_RATE_DISABLE_CFG();
            }
            else{}
        if(I2C_SMBUS_CONTROL_ENABLE ==i2c_obj->i2c_cfg.i2c_slew_rate)
            {
                I2C_SLEW_RATE_ENABLE_CFG();
            }
            else if(I2C_SMBUS_CONTROL_DISABLE ==i2c_obj->i2c_cfg.i2c_slew_rate)
            {
                I2C_SLEW_RATE_DISABLE_CFG();
            }
            else{}
  #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
      MSSP_Interrupt_config(i2c_obj);
  #endif
        
         I2C_MODULE_ENABLE();
        
    }
    return ret ;
}
Std_ReturnType mssp_i2c_DeInit(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret =  E_OK ;
    if(NULL == i2c_obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         I2C_MODULE_DISABLE();
      #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
               MSSP_I2C_InterruptDisable();         
               MSSP_I2C_BUS_COL_InterruptDisable();
      #endif
        
    }
    return ret ;
}
Std_ReturnType mssp_i2c_Master_send_start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret =  E_OK ;
    if(NULL == i2c_obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        SSPCON2bits.SEN = 1; /*send start*/
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0 ; /*clear flag*/
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret =  E_OK ;
        }
        else if(I2C_START_BIT_NOT_DETECTED == SSPSTATbits.S)
        {
            ret =  E_NOT_OK ;
        }
        else{}
    }
    return ret ;
}
Std_ReturnType mssp_i2c_Master_send_stop(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret =  E_OK ;
    if(NULL == i2c_obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         SSPCON2bits.PEN = 1; /*send Stop*/
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0 ; /*clear flag*/
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            ret =  E_OK ;
        }
        else if(I2C_STOP_BIT_NOT_DETECTED == SSPSTATbits.P)
        {
            ret =  E_NOT_OK ;
        }
        else{}
    }
    return ret ;
}
Std_ReturnType mssp_i2c_Master_send_repeated_start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret =  E_OK ;
    if(NULL == i2c_obj)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        SSPCON2bits.RSEN = 1; /*send start*/
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0 ; /*clear flag*/
        
    }
    return ret ;
}
Std_ReturnType mssp_i2c_Write(const mssp_i2c_t *i2c_obj , uint8 data , uint8 *ack){
    Std_ReturnType ret =  E_OK ;
    if((NULL == i2c_obj) || (NULL ==ack))
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        SSPBUF = data ;
        while(!PIR1bits.SSPIF);
        
        PIR1bits.SSPIF = 0 ;
        if(I2C_ACK_RECEIVED_FROM_SLAVE ==SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE ;
            
        }
        else
        {
             *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE ;
        }
    }
    return ret ;
}
Std_ReturnType mssp_i2c_Read(const mssp_i2c_t *i2c_obj ,uint8 *data,uint8 ack){
    Std_ReturnType ret =  E_OK ;
    if((NULL == i2c_obj) || (NULL == data))
    {
        ret =  E_NOT_OK ;
    }
    else
    {
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);
        *data = SSPBUF ;
        if(I2C_MASTER_SEND_ACK == ack)
        {
            SSPCON2bits.ACKDT = 0 ;
            SSPCON2bits.ACKEN = 1;
        }
        else if(I2C_MASTER_SEND_NOT_ACK == ack)
        {
             SSPCON2bits.ACKDT = 1 ;
            SSPCON2bits.ACKEN = 1;
        }
    }
    return ret ;
}

static inline void MSSP_Interrupt_config(const mssp_i2c_t *i2c_obj){
 #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
     MSSP_I2C_BUS_COL_InterruptEnable();    
        MSSP_I2C_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        MSSP_I2C_BUS_COL_InterruptFlagClear();
      I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
      I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler ;
      I2C_Report_Recive_OverFlow_InterruptHandler =i2c_obj->I2C_Report_Recive_OverFlow ;
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
       INTERRUPT_PriorityLevelsEnable();
             if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 MSSP_I2C_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_priority)  
             {
                 TIMER0_LowPriorityEnable();
                 MSSP_I2C_LowPriorityEnable();
             }  
             else{}
        if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_busc_priority)  
             {
                 INTERRUPT_GlobalInterruptHighEnable();
                 MSSP_I2C_BUS_COL_HighPriorityEnable();
             }
             else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_busc_priority)  
             {
                 TIMER0_LowPriorityEnable();
                 MSSP_I2C_BUS_COL_LowPriorityEnable();
             }  
             else{}
#else
INTERRUPT_PeripheralInterruptEnable() ;
INTERRUPT_GlobalInterruptEnable() ;
#endif
#endif
               
}

void MSSP_I2C_ISR(void){
    #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    MSSP_I2C_InterruptFlagClear();
    if(I2C_DefaultInterruptHandler)
    {
        I2C_DefaultInterruptHandler();
    }
#endif
}

void MSSP_I2C_BUSC_ISR(void){
     #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(I2C_Report_Write_Collision_InterruptHandler)
    {
        I2C_Report_Write_Collision_InterruptHandler();
    }
#endif
}