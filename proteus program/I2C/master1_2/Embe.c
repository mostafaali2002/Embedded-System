/* 
 * File:   Embe.c
 * Author: user
 *
 * Created on August 15, 2023, 4:15 PM
 */

#include "Embe.h"

 Std_ReturnType ret = E_NOT_OK ;
#define Slave_1 0x60
#define Slave_2 0x62
mssp_i2c_t i2c_obj ;
  uint8 slave2_ack ;
 static volatile uint8 slave_rec_data ;


void MSSP_I2C_SEND_BYTE(uint8 slave_add , uint8 data)
{
    ret = mssp_i2c_Master_send_start(&i2c_obj);
    ret = mssp_i2c_Write(&i2c_obj ,slave_add ,&slave2_ack );
    ret = mssp_i2c_Write(&i2c_obj ,data ,&slave2_ack );
    ret = mssp_i2c_Master_send_stop(&i2c_obj);
}
 
int main() {
    

//  i2c_obj.I2C_Report_Write_Collision= NULL ;
//  i2c_obj.I2C_Report_Recive_OverFlow = NULL;
//  i2c_obj.I2C_DefaultInterruptHandler= NULL ;
    i2c_obj.i2c_clock = 100000 ;
  i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBUS_CONTROL_DISABLE ;
  i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE ;
  i2c_obj.i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE;
  i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_MASTER_DEFINED_CLOCK ;
  
  ret = mssp_i2c_Init(&i2c_obj);
  
      while(1)
      {  
        
           MSSP_I2C_SEND_BYTE(Slave_1 ,'a');
           __delay_ms(1000);
           MSSP_I2C_SEND_BYTE(Slave_2 ,'b');
           __delay_ms(1000);
           MSSP_I2C_SEND_BYTE(Slave_1 ,'c');
           __delay_ms(1000);
           MSSP_I2C_SEND_BYTE(Slave_2 ,'d');
           __delay_ms(1000);
         
      }  
    return (EXIT_SUCCESS);
}
void application_intialize(void){
 
}



