/* 
 * File:   hal_i2c.h
 * Author: user
 *
 * Created on October 2, 2023, 5:19 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/
#define I2C_SLEW_RATE_ENABLE              1
#define I2C_SLEW_RATE_DISABLE             0

#define I2C_MSSP_MASTER_MODE              1
#define I2C_MSSP_SLAVE_MODE               0

#define I2C_SMBUS_CONTROL_ENABLE          1
#define I2C_SMBUS_CONTROL_DISABLE         0

#define I2C_STOP_BIT_DETECTED             1
#define I2C_STOP_BIT_NOT_DETECTED         0

#define I2C_START_BIT_DETECTED            1
#define I2C_START_BIT_NOT_DETECTED        0

#define I2C_LAST_BYTE_DATA            1
#define I2C_LAST_BYTE_ADDRESS        0

#define I2C_SALVE_MODE_7BIT_ADDRESS  0x06
#define I2C_SALVE_MODE_10BIT_ADDRESS  0x07
#define I2C_SALVE_MODE_7BIT_ADDRESS_INTERRUPT_ENABLE  0x0E
#define I2C_SALVE_MODE_10BIT_ADDRESS_INTERRUPT_ENABLE  0x0F
#define I2C_MASTER_FIRMWARE_CONTROLLED                 0x0B
#define I2C_MASTER_DEFINED_CLOCK                       0x08

#define I2C_GENERAL_CALL_ENABLE   1
#define I2C_GENERAL_CALL_DISABLE   0

#define I2C_MASTER_RECEIVE_ENABLE   1
#define I2C_MASTER_RECEIVE_DISABLE   0

#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE  1
#define I2C_ACK_RECEIVED_FROM_SLAVE   0

#define I2C_MASTER_SEND_ACK           0
#define I2C_MASTER_SEND_NOT_ACK            1



/* Section : Macro Function Declaration*/
#define I2C_SLEW_RATE_ENABLE_CFG()           (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_DISABLE_CFG()          (SSPSTATbits.SMP = 0)

#define I2C_SMBUS_CONTROL_ENABLE_CFG()           (SSPSTATbits.CKE = 1)
#define I2C_SMBUS_CONTROL_DISABLE_CFG()          (SSPSTATbits.CKE = 0)

#define I2C_GENERAL_CALL_ENABLE_CFG()           (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG()          (SSPCON2bits.GCEN = 0)

#define I2C_MASTER_RECEIVE_ENABLE_CFG()           (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECEIVE_DISABLE_CFG()          (SSPCON2bits.RCEN = 0)

#define  I2C_MODULE_ENABLE()          (SSPCON1bits.SSPEN = 1)
#define  I2C_MODULE_DISABLE()          (SSPCON1bits.SSPEN = 1)

#define I2C_CLOCK_STRETCH_ENABLE()              (SSPCON1bits.CKP = 0) 
#define I2C_CLOCK_STRETCH_DISABLE()           (SSPCON1bits.CKP = 1)    


/* Section : Data Type Declaration */
typedef struct {
    uint8 i2c_mode_cfg ;      /* master synchronous mode */
    uint8 i2c_slave_addres ; 
    uint8 i2c_mode :1;         /* master or slave */
    uint8 i2c_slew_rate :1;
    uint8 i2c_SMBus_control :1; /* enable \ disable */
    uint8 i2c_general_call :1;
    uint8 i2c_master_rec_mode :1;/* master receive enable \ disable */
 #if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
  interrupt_priority_cfg mssp_priority;
  interrupt_priority_cfg mssp_busc_priority;
#endif 
}i2c_config_t;
typedef struct {
    uint32 i2c_clock ;
#if  MSSP_I2C_INTERRUPT_FEATURE_ENABLE == FeatureEnable
    void(*I2C_Report_Write_Collision)(void);
     void(*I2C_DefaultInterruptHandler)(void);
     void(*I2C_Report_Recive_OverFlow)(void);
#endif    
    
   
    i2c_config_t i2c_cfg ;
}mssp_i2c_t;

/* Section : Function Declaration*/
Std_ReturnType mssp_i2c_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType mssp_i2c_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType mssp_i2c_Master_send_start(const mssp_i2c_t *i2c_obj);
Std_ReturnType mssp_i2c_Master_send_stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType mssp_i2c_Master_send_repeated_start(const mssp_i2c_t *i2c_obj);
Std_ReturnType mssp_i2c_Write(const mssp_i2c_t *i2c_obj , uint8 data, uint8 *ack);
Std_ReturnType mssp_i2c_Read(const mssp_i2c_t *i2c_obj ,uint8 *data,uint8 ack);



#endif	/* HAL_I2C_H */

