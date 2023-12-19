/* 
 * File:   Embe.c
 * Author: user
 *
 * Created on August 15, 2023, 4:15 PM
 */

#include "Embe.h"

 Std_ReturnType ret = E_NOT_OK ;
//#define Slave_1 0x60
//#define Slave_2 0x62
//mssp_i2c_t i2c_obj ;
// volatile uint8 slave2_ack ;
// static volatile uint8 slave_rec_data ;

// led_t led_1={
//  .pin = PIN1,
//  .port =PORTD_INDEX,
//  .led_status =GPIO_LOW 
//          
//};
segment_t seg_1 ={
    .segment_pins[0].port = PORTD_INDEX,
    .segment_pins[0].pin =PIN0,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = OUTPUT_DIRECTION,
    .segment_pins[1].port = PORTD_INDEX,
    .segment_pins[1].pin =PIN1,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = OUTPUT_DIRECTION,
    .segment_pins[2].port = PORTD_INDEX,
    .segment_pins[2].pin =PIN2,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = OUTPUT_DIRECTION,
    .segment_pins[3].port = PORTD_INDEX,
    .segment_pins[3].pin =PIN3,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = OUTPUT_DIRECTION,
    .segment_type = SEVEN_COMMON_ANODE
};

//void MSSP_I2C_DefaultInterruptHandler(void)
//{
//   I2C_CLOCK_STRETCH_ENABLE();
//   if(SSPSTATbits.R_nW ==0  && SSPSTATbits.D_nA == 0)
//   {
//       uint8 buffer = SSPBUF ;
//       while(!SSPSTATbits.BF);
//       slave_rec_data = SSPBUF ;
//   }
//   else if(SSPSTATbits.R_nW ==1 )
//   {
//       
//   }
//   I2C_CLOCK_STRETCH_DISABLE();
//}
 
int main() {
    

//  i2c_obj.I2C_Report_Write_Collision= NULL ;
//  i2c_obj.I2C_Report_Recive_OverFlow = NULL;
//  i2c_obj.I2C_DefaultInterruptHandler= MSSP_I2C_DefaultInterruptHandler ;
//  i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBUS_CONTROL_DISABLE ;
//  i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
//   i2c_obj.i2c_cfg.i2c_slave_addres = Slave_1;
//  i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE ;
//  i2c_obj.i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE ;
//  i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SALVE_MODE_7BIT_ADDRESS ;
//  
//  ret = mssp_i2c_Init(&i2c_obj);
//  ret = led_intialize(&led_1);
  ret = seven_segment_intialize(&seg_1);
      while(1)
      {  
        
//          if('a'==slave_rec_data)
//          {
//              ret = led_turn_on(&led_1);
//          }
//          else if('c'==slave_rec_data)
//          {
//              ret = led_turn_off(&led_1);
//          }
          
//         ret = led_turn_on(&led_1);
         ret = seven_segment_write_number(&seg_1,7);
         
      }  
    return (EXIT_SUCCESS);
}
void application_intialize(void){
 
}



