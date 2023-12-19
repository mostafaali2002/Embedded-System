/* 
 * File:   Embe_Initialization.c
 * Author: user
 *
 * Created on September 23, 2023, 5:10 PM
 */
#include "Embe_Initialization.h"
   uint8 m = 23 , x;
   uint8 minutes = 59 , hour = 23 , second = 55 , count= 0 ,value_column=0;
   uint16 Reslt_1 ,Reslt_2 ;
   uint8 Convert_1[6] ,Convert_2[6] ;
   uint8 LM35_celisis_1, LM35_celisis_2;
  volatile uint16 timer0_value = ZERO_INIT;
   volatile uint32 timer1_on ;
   volatile uint16 timer2_on ;
    volatile uint16 timer1_counter ;
     timer1_t counter_obj ;
   timer2_t timer2;
   Std_ReturnType ret = E_NOT_OK ;
/*****************ccp*****************/
    volatile uint8 CCP_Second_capture_flag = 0 ;
 uint16 second_capture = 0;
 volatile uint32 timer3_overflow = 0 ;
  uint32 freq_capture= 0;
 uint32 total_period_Micro_capture = 0 ;
   

void timer1_Init(void)
{
    timer1_t timer_obj ;
    timer_obj.TM1_InterruptHandler = Timer1_Default;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer_obj.timer1_prescaler_Value = TIMER1_PRESCALER_DIV_BY_4;
    timer_obj.timer1_preload_value = 15536;
    timer_obj.timer1_reg_rw_mode = TIMER1_RW_REG_16BITS_MODE ;       
    Timer1_Init(&timer_obj);

}
void timer1_Counter_Init(void)
{
   
  
        
   timer2.TM2_InterruptHandler = timer2_ISR  ;
   timer2.priority = INTERRUPT_LOW_PRIORITY ;
   timer2.timer2_postcaler_Value = TIMER2_POSTCALER_DIV_BY_1;
   timer2.timer2_prescaler_Value = TIMER2_PRESCALER_DIV_BY_16;
   timer2.timer2_preload_value = 249 ;
   ret = Timer2_Init(&timer2);

}

led_t led_2={
  .pin = PIN1,
  .port =PORTC_INDEX,
  .led_status =LED_OFF
};
led_t led_1={
  .pin = PIN0,
  .port =PORTC_INDEX,
  .led_status =LED_OFF
  
          
};

button_t btn_high ={
    .button_pin.pin = PIN2 ,
    .button_pin.port =PORTC_INDEX ,
    .button_pin.direction = INPUT_DIRECTION ,
    .button_pin.logic = GPIO_LOW ,
    .button_state = BUTTON_RELASED ,
    .button_active = BUTTON_ACTIVE_HIGH
};

button_t btn_low = {
    .button_pin.pin = PIN0,
    .button_pin.port =PORTD_INDEX ,
    .button_pin.direction = INPUT_DIRECTION ,
    .button_pin.logic = GPIO_HIGH ,
    .button_state = BUTTON_RELASED ,
    .button_active = BUTTON_ACTIVE_LOW
};
relay_t relay_1 = {
  .relay_pin = PIN0,
  .relay_port = PORTC_INDEX,
  .relay_status =RELAY_OFF_STATUS
          
};


motor_t dc_motor_1 = {
    .dc_motor[0].motor_pin = PIN0 ,
    .dc_motor[0].motor_port=PORTD_INDEX,
    .dc_motor[0].motor_status = MOTOR_OFF_STATUS,
    .dc_motor[1].motor_pin = PIN1 ,
    .dc_motor[1].motor_port=PORTD_INDEX,
    .dc_motor[1].motor_status = MOTOR_OFF_STATUS
    
};
motor_t dc_motor_2 = {
    .dc_motor[0].motor_pin = PIN2,
    .dc_motor[0].motor_port=PORTD_INDEX,
    .dc_motor[0].motor_status = MOTOR_OFF_STATUS,
    .dc_motor[1].motor_pin = PIN3 ,
    .dc_motor[1].motor_port=PORTD_INDEX,
    .dc_motor[1].motor_status = MOTOR_OFF_STATUS
    
};

segment_t seg_1 ={
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin =PIN0,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = OUTPUT_DIRECTION,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin =PIN1,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = OUTPUT_DIRECTION,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin =PIN2,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = OUTPUT_DIRECTION,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin =PIN3,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = OUTPUT_DIRECTION,
    .segment_type = SEVEN_COMMON_ANODE
};
keypad_t keypad1 ={
  .keypad_row_pin[0].port= PORTC_INDEX ,
  .keypad_row_pin[0].pin = PIN0,
   .keypad_row_pin[0].direction = OUTPUT_DIRECTION,
  .keypad_row_pin[0].logic = GPIO_LOW ,
  .keypad_row_pin[1].port= PORTC_INDEX ,
  .keypad_row_pin[1].pin = PIN1,
  .keypad_row_pin[1].direction = OUTPUT_DIRECTION,
  .keypad_row_pin[1].logic = GPIO_LOW ,
  .keypad_row_pin[2].port= PORTC_INDEX ,
  .keypad_row_pin[2].pin = PIN2,
  .keypad_row_pin[2].direction = OUTPUT_DIRECTION,
  .keypad_row_pin[2].logic = GPIO_LOW ,
  .keypad_row_pin[3].port= PORTC_INDEX ,
  .keypad_row_pin[3].pin = PIN3,
  .keypad_row_pin[3].direction = OUTPUT_DIRECTION,
  .keypad_row_pin[3].logic = GPIO_LOW ,
  .keypad_column_pin[0].port= PORTC_INDEX ,
  .keypad_column_pin[0].pin = PIN4,
  .keypad_column_pin[0].direction = INPUT_DIRECTION,
  .keypad_column_pin[0].logic = GPIO_LOW ,
  .keypad_column_pin[1].port= PORTC_INDEX ,
  .keypad_column_pin[1].pin = PIN5,
  .keypad_column_pin[1].direction = INPUT_DIRECTION,
  .keypad_column_pin[1].logic = GPIO_LOW ,
  .keypad_column_pin[2].port= PORTC_INDEX ,
  .keypad_column_pin[2].pin = PIN6,
  .keypad_column_pin[2].direction = INPUT_DIRECTION,
  .keypad_column_pin[2].logic = GPIO_LOW ,
  .keypad_column_pin[3].port= PORTC_INDEX ,
  .keypad_column_pin[3].pin = PIN7,
  .keypad_column_pin[3].direction = INPUT_DIRECTION,
  .keypad_column_pin[3].logic = GPIO_LOW ,
};
chr_lcd_8bit_t lcd1 = {
  .lcd_rs.port = PORTC_INDEX ,
  .lcd_rs.pin = PIN6,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = OUTPUT_DIRECTION ,
  .lcd_en.port = PORTC_INDEX ,
  .lcd_en.pin = PIN7,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = OUTPUT_DIRECTION ,
  .lcd_data[0].port = PORTD_INDEX,
  .lcd_data[0].pin = PIN0,
  .lcd_data[0].direction = OUTPUT_DIRECTION,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTD_INDEX,
  .lcd_data[1].pin = PIN1,
  .lcd_data[1].direction = OUTPUT_DIRECTION,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTD_INDEX,
  .lcd_data[2].pin = PIN2,
  .lcd_data[2].direction = OUTPUT_DIRECTION,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTD_INDEX,
  .lcd_data[3].pin = PIN3,
  .lcd_data[3].direction = OUTPUT_DIRECTION,
  .lcd_data[3].logic = GPIO_LOW,
  .lcd_data[4].port = PORTD_INDEX,
  .lcd_data[4].pin = PIN4,
  .lcd_data[4].direction = OUTPUT_DIRECTION,
  .lcd_data[4].logic = GPIO_LOW,
  .lcd_data[5].port = PORTD_INDEX,
  .lcd_data[5].pin = PIN5,
  .lcd_data[5].direction = OUTPUT_DIRECTION,
  .lcd_data[5].logic = GPIO_LOW,
  .lcd_data[6].port = PORTD_INDEX,
  .lcd_data[6].pin = PIN6,
  .lcd_data[6].direction = OUTPUT_DIRECTION,
  .lcd_data[6].logic = GPIO_LOW,
  .lcd_data[7].port = PORTD_INDEX,
  .lcd_data[7].pin = PIN7,
  .lcd_data[7].direction = OUTPUT_DIRECTION,
  .lcd_data[7].logic = GPIO_LOW
  
  
};
interrupt_INTx_t intx_0 ={
 .Ext_InterruptHandler = APP_ISR,
 .edge = INTERRUPT_RASING_EDGE,
 .priority = INTERRUPT_HIGH_PRIORITY,
 .source = INTERRUPT_External_INTx0,
 .mcu_pin.port= PORTB_INDEX,
 .mcu_pin.pin = PIN0,
 .mcu_pin.direction = INPUT_DIRECTION
 
};
interrupt_RBx_t intRB_0 = {
   .Ext_Interrupt_High = APP_RB4_High,
   .Ext_Interrupt_Low = APP_RB4_Low,
   .priority  = INTERRUPT_HIGH_PRIORITY ,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.pin = PIN6,
   .mcu_pin.direction = INPUT_DIRECTION
};
adc_conf_t ADC_1 ={
  .channel_select =  ADC_CHANNEL_AN0 ,
  .aquisition_time = ADC_12_TAD ,
  .conversion_clock =ADC_CONVERSION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGH ,
  .voltage_reference =ADC_ENABLE_VOLTAGE_REFERENCE_DISABLE ,
  .ADC_InterruptHandler = NULL
};
chr_lcd_4bit_t CHR_4_LCD = {
  .lcd_rs.port = PORTC_INDEX ,
  .lcd_rs.pin = PIN0 ,
  .lcd_rs.direction = OUTPUT_DIRECTION ,
   .lcd_rs.logic = GPIO_LOW,
   .lcd_en.port= PORTC_INDEX ,
  .lcd_en.pin = PIN1 ,
  .lcd_en.direction = OUTPUT_DIRECTION ,
   .lcd_en.logic = GPIO_LOW   ,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin  =PIN2 ,
  .lcd_data[0].direction =OUTPUT_DIRECTION,
  .lcd_data[0].logic = GPIO_LOW ,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin  =PIN3 ,
  .lcd_data[1].direction =OUTPUT_DIRECTION,
  .lcd_data[1].logic = GPIO_LOW ,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin  =PIN4 ,
  .lcd_data[2].direction =OUTPUT_DIRECTION,
  .lcd_data[2].logic = GPIO_LOW ,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin  =PIN5 ,
  .lcd_data[3].direction =OUTPUT_DIRECTION,
  .lcd_data[3].logic = GPIO_LOW 
};

timer0_t timer0 = {
  .TM0_InterruptHandler = timer_ISR,
  .prescaler_Value = TIMER_PRESCALER_DIV_BY_8,
  .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
  .timer0_mode = TIMER0_TIMER_MODE ,
  .timer0_register_size =TIMER0_16BIT_REGISTER_MODE ,
  .timer0_preload_value = 3036 

};
 timer0_t timer0_counter = {
  .TM0_InterruptHandler = timer_ISR,
  .prescaler_enable =  TIMER0_PRESCALER_DISABLE_CFG ,
  .timer0_counter_edge =TIMER0_RASING_EDGE_ENABLE_CFG,
  .timer0_mode = TIMER0_COUNTER_MODE ,
  .timer0_register_size =TIMER0_16BIT_REGISTER_MODE ,
  .timer0_preload_value = 0
 
};
  usart_t usart_obj_1 ={
   .baudrate = 9600 ,
   .baudrate_gen =BAUDRATE_ASYNC_8BIT_LOW_SPEED,
   .usart_rx.usart_rx_9bit_enable = USART_ASYNCHRONOUS_RX_9BIT_DISENABLE,
   .usart_rx.usart_rx_enable = USART_ASYNCHRONOUS_RX_ENABLE,
   .usart_rx.usart_rx_interrupt_enable = USART_ASYNCHRONOUS_INTERRUPT_RX_DISENABL,
   .usart_tx.usart_tx_9bit_enable = USART_ASYNCHRONOUS_TX_9BIT_DISENABLE,
   .usart_tx.usart_tx_enable = USART_ASYNCHRONOUS_TX_ENABLE,
   .usart_tx.usart_tx_interrupt_enable = USART_ASYNCHRONOUS_INTERRUPT_TX_DISENABL,
   .USART_FRAMING_InterruptHandler = NULL,
   .USART_RX_InterruptHandler = NULL ,
   .USART_TX_InterruptHandler=NULL,
   .USART_OVERRUN_InterruptHandler= NULL
 };
 /*
   ccp_t ccp1_obj ={
  .CCP1_InterruptHandler = NULL ,
  .ccp_inst = CCP1_INST ,
  .ccp_mode =PWM_MODE ,
  .PWM_frequence = 20000 ,
  .pin.port = PORTC_INDEX ,
  .pin.pin = PIN2 ,
  .pin.direction = OUTPUT_DIRECTION ,
  .timer2_postcaler_Value = CCP_POSTCALER_DIV_BY_1 ,
  .timer2_prescaler_Value = CCP_PRESCALER_DIV_BY_1 ,
  .ccp_mode_varient = CCP_PWM_MODE 
   };
  ccp_t ccp2_obj ={
  .CCP1_InterruptHandler = NULL ,
  .ccp_inst = CCP2_INST ,
  .ccp_mode =PWM_MODE ,
  .PWM_frequence = 20000 ,
  .pin.port = PORTC_INDEX ,
 .pin.pin = PIN1 ,
  .pin.direction = OUTPUT_DIRECTION ,
  .timer2_postcaler_Value =CCP_POSTCALER_DIV_BY_1 ,
  .timer2_prescaler_Value =CCP_PRESCALER_DIV_BY_1 ,
  .ccp_mode_varient = CCP_PWM_MODE 
  };
  */
 timer2_t timer2_obj ={
       .TM2_InterruptHandler= NULL ,
  .timer2_postcaler_Value = TIMER2_POSTCALER_DIV_BY_1,
  .timer2_prescaler_Value = TIMER2_PRESCALER_DIV_BY_1 ,
  .timer2_preload_value = 0 

 };

 
 ccp_t ccp_obj_capture ={
      .CCP1_InterruptHandler = Timer3_Interrupt_capture ,
    .ccp_mode = CAPTURE_MODE ,
     .ccp_capture_timer = CCP1_CCP2_TIMER3 ,
     .ccp_mode_varient = CCP_CAPTURE_MODE_EVERY_RAISING_EDGE,
     .pin.port= PORTC_INDEX ,
     .pin.pin =PIN2,
     .pin.direction = INPUT_DIRECTION ,
     .ccp_inst = CCP1_INST
     
 };
 timer3_t timer_obj_capture ={
     .TM3_InterruptHandler = Timer3_Interrupt_capture ,
     .priority = INTERRUPT_LOW_PRIORITY ,
     .timer3_mode = TIMER3_TIMER_MODE,
     .timer3_prescaler_Value = TIMER3_PRESCALER_DIV_BY_1,
     .timer3_preload_value = 0 ,
     .timer3_reg_rw_mode = TIMER3_RW_REG_8BITS_MODE
 };
  ccp_t ccp_compare = {
      .CCP1_InterruptHandler = Timer3_Interrupt_compare ,
    .ccp_mode = COMPARE_MODE ,
     .ccp_capture_timer = CCP1_CCP2_TIMER3 ,
     .ccp_mode_varient = CCP_COMPARE_MODE_INITIAL_PIN_LOW,
     .pin.port= PORTC_INDEX ,
     .pin.pin =PIN2,
     .pin.direction = OUTPUT_DIRECTION ,
     .ccp_inst = CCP1_INST
 
 };
 timer3_t timer3_compare ={
     .TM3_InterruptHandler = NULL ,
     .priority = INTERRUPT_LOW_PRIORITY ,
     .timer3_mode = TIMER3_TIMER_MODE,
     .timer3_prescaler_Value = TIMER3_PRESCALER_DIV_BY_1,
     .timer3_preload_value = 0 ,
     .timer3_reg_rw_mode = TIMER3_RW_REG_16BITS_MODE
 };
 volatile uint8 ccp_callback =0;
 
 
 void Timer3_Interrupt_compare (void)
 {
     ccp_callback ++ ;
     ret = Timer3_Write_Value(&timer3_compare , 0);
     if(ccp_callback==1)
     {
           ret = ccp_compare_mode_write_value(&ccp_compare ,12500); 
           CCP1_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_HIGH);
           
     }
     else if(ccp_callback==2)
     {
           ret = ccp_compare_mode_write_value(&ccp_compare ,37500);
           CCP1_MODE_SELECTED(CCP_COMPARE_MODE_INITIAL_PIN_LOW);
           ccp_callback = 0; 
     }
 }
 
 
 
  void CCP_Interrupt_Capture(void)
 {
     static uint8 CCP_interrupt_flag = 0;
     CCP_interrupt_flag++ ;
     CCP_Second_capture_flag++ ;
     if(CCP_interrupt_flag == 1)
     {
         ret = Timer3_Write_Value(&timer_obj_capture , 0);
     }
     else if (CCP_interrupt_flag == 2)
     {
         timer3_overflow = 0;
         CCP_interrupt_flag = 0 ;
      //  ret= ccp1_capture_mode_Read_value(&second_capture);
     }
     
 }
 void Timer3_Interrupt_capture(void)
 {
     timer3_overflow++ ;
 }
 void calculate_frequnce_capture(void){
  if(CCP_Second_capture_flag == 2){
              total_period_Micro_capture = (timer3_overflow * 65536) + second_capture ;
              freq_capture = (1 / total_period_Micro_capture / 1000000); 
              CCP_Second_capture_flag = 0;
          }
}

 
 

 
    void APP_ISR(void)
{
   ret = led_toggle(&led_1);

}
  void APP_RB4_High(void)
{
   ret = led_turn_on(&led_1);

}
    void APP_RB4_Low(void)
{
   ret = led_turn_off(&led_1);

}
 
    void timer_ISR(void){
        
    }
    
    void timer2_ISR(void){
        timer2_on ++;
    }
    void Timer1_Default(void)
{
    timer1_on ++ ;
}
    
/*  
 
 
 for(count = 0 ; count < 50 ; count++)
          {
              ret = gpio_port_write_logic(PORTD_INDEX , 0x3E);      //0011 1110
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(hour / 10))) ;
              __delay_us(3333);
              ret = gpio_port_write_logic(PORTD_INDEX , 0x3D);      //0011 1101
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(hour % 10)));
              __delay_us(3333);
              ret = gpio_port_write_logic(PORTD_INDEX , 0x3B);     //0011 1011
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(minutes / 10)));
              __delay_us(3333);
              ret = gpio_port_write_logic(PORTD_INDEX , 0x37);
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(minutes % 10)));
              __delay_us(3333);
              
              ret = gpio_port_write_logic(PORTD_INDEX , 0x2F);
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(second / 10)));
              __delay_us(3333);
               ret = gpio_port_write_logic(PORTD_INDEX , 0x1F);
              ret = gpio_port_write_logic(PORTC_INDEX ,((uint8)(second % 10)));
              __delay_us(3333);
          }
          second ++ ; 
          if(second == 60)
          {
              minutes ++ ;
              second = 0 ;
          }
          if(minutes == 60)
          {
              hour ++ ;
              minutes = 0 ;
          }
           if(hour == 24)
          {
              hour ++ ;
              hour = 0 ;
          }
 
 // x =  ((uint8)m %10) | ((uint8)m /10 << 4) ;
 * 
 * ----------------------------ADC with LM35-------------------------------
 * ret= ADC_GetConversion_Bloking(&ADC_1 ,ADC_CHANNEL_AN0 ,&Reslt_1);
           ret= ADC_GetConversion_Bloking(&ADC_1 ,ADC_CHANNEL_AN1 ,&Reslt_2);
           
           LM35_celisis_1 = Reslt_1 *4.88f ;
           LM35_celisis_2 = Reslt_2 *4.88f ;
           LM35_celisis_1 /=10;
            LM35_celisis_2 /=10;
        
           ret =convert_short_to_string(LM35_celisis_1 ,Convert_1);
           ret =convert_short_to_string(LM35_celisis_2 ,Convert_2);
           
           ret =lcd_4bit_send_string_pos(&CHR_4_LCD ,Convert_1, 1 ,8);
           ret =lcd_4bit_send_string_pos(&CHR_4_LCD ,Convert_2, 2 ,8);
           
           if(LM35_celisis_2 > 20)
           {
             ret =  dc_motor_turn_left(&dc_motor_2);
           }
           else if (LM35_celisis_1 > 24)
           {
              ret = dc_motor_turn_right(&dc_motor_1);
           }
           else{
             ret =  dc_motor_stop(&dc_motor_2);
              ret =  dc_motor_stop(&dc_motor_1);
           }
 */
