/* 
 * File:   ecu_chr_lcd.c
 * Author: user
 *
 * Created on September 2, 2023, 5:39 PM
 */

#include "ecu_chr_lcd.h"
static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd ,uint8 data_command);
static Std_ReturnType lcd_send_4bit_enable_signal(const chr_lcd_4bit_t *lcd );
static Std_ReturnType lcd_send_8bit_enable_signal(const chr_lcd_8bit_t *lcd );
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column);

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
        Std_ReturnType ret = E_OK;
        uint8 counter_pin = ZERO_INIT ;
        if (NULL == lcd) {
            ret = E_NOT_OK;
        } 
        else {
            ret = gpio_pin_intialize(&(lcd->lcd_rs));
            ret = gpio_pin_intialize(&(lcd->lcd_en));
            for(counter_pin = ZERO_INIT ; counter_pin < 4 ; counter_pin++){
                 ret = gpio_pin_intialize(&(lcd->lcd_data[counter_pin]));
            }
               __delay_ms(20);
            ret = lcd_4bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            __delay_ms(5);
            ret = lcd_4bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            __delay_us(150);
            ret = lcd_4bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            ret = lcd_4bit_send_command(lcd ,LCD_CLEAR);
            ret = lcd_4bit_send_command(lcd ,LCD_RETURN_HOME);
            ret = lcd_4bit_send_command(lcd ,LCD_ENTRY_MODE);
            ret = lcd_4bit_send_command(lcd ,LCD_DISPLAY_ON_CURSOR_OFF);
             ret = lcd_4bit_send_command(lcd ,LCD_4BIT_MODE_2_LINE);
        }
    return ret;
}
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , uint8 command){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
         ret = lcd_send_4bit(lcd , command >> 4);
         ret = lcd_send_4bit_enable_signal(lcd);
          ret = lcd_send_4bit(lcd , command);
          ret = lcd_send_4bit_enable_signal(lcd);
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_chr_data(const chr_lcd_4bit_t *lcd ,uint8 data){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
         ret = lcd_send_4bit(lcd , data >> 4);
         ret = lcd_send_4bit_enable_signal(lcd);
          ret = lcd_send_4bit(lcd , data);
          ret = lcd_send_4bit_enable_signal(lcd);
     
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_chr_data_pos(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column,uint8 data){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = lcd_4bit_set_cursor(lcd , row , column );
         ret = lcd_4bit_send_chr_data(lcd ,data );
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column, uint8 *str){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          while(*str)
         {
             ret = lcd_4bit_send_chr_data(lcd , *str++);
         }
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd , uint8 *str,uint8 row , uint8 column){
     Std_ReturnType ret = E_OK ;
     
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = lcd_4bit_set_cursor(lcd , row , column );
      while(*str)
         {
             ret = lcd_4bit_send_chr_data(lcd , *str++);
         }
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column,const uint8 _chr[], uint8 mem_pos){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
     
    }
    return ret ;
}

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
      Std_ReturnType ret = E_OK;
        uint8 counter_pin = ZERO_INIT ;
        if (NULL == lcd) {
            ret = E_NOT_OK;
        } 
        else {
            ret = gpio_pin_intialize(&(lcd->lcd_rs));
            ret = gpio_pin_intialize(&(lcd->lcd_en));
            for(counter_pin = ZERO_INIT ; counter_pin < 8 ; counter_pin++){
                 ret = gpio_pin_intialize(&(lcd->lcd_data[counter_pin]));
            }
            __delay_ms(20);
            ret = lcd_8bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            __delay_ms(5);
            ret = lcd_8bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            __delay_us(150);
            ret = lcd_8bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
            ret = lcd_8bit_send_command(lcd ,LCD_CLEAR);
            ret = lcd_8bit_send_command(lcd ,LCD_RETURN_HOME);
            ret = lcd_8bit_send_command(lcd ,LCD_ENTRY_MODE);
            ret = lcd_8bit_send_command(lcd ,LCD_DISPLAY_ON_CURSOR_OFF);
             ret = lcd_8bit_send_command(lcd ,LCD_8BIT_MODE_2_LINE);
           
        
        }
    return ret;
}
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_OK ;
    uint8 pin_counter = ZERO_INIT ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW); 
         for(pin_counter =ZERO_INIT ; pin_counter < 8;pin_counter++ )
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),(command >> pin_counter)& (uint8)0x01);
         }
             ret = lcd_send_8bit_enable_signal(lcd);
         
     
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_chr_data(const chr_lcd_8bit_t *lcd ,uint8 data){
     Std_ReturnType ret = E_OK ;
      uint8 pin_counter = ZERO_INIT ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
          ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
          for(pin_counter =ZERO_INIT ; pin_counter < 8;pin_counter++ )
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),(data >> pin_counter)& (uint8)0x01);
         }
             ret = lcd_send_8bit_enable_signal(lcd);
         
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_chr_data_pos(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column,uint8 data){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = lcd_8bit_set_cursor(lcd , row , column);
         ret = lcd_8bit_send_chr_data(lcd , data);
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd ,uint8 *str){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         while(*str)
         {
             ret = lcd_8bit_send_chr_data(lcd , *str++);
         }
         
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column,  uint8 *str){
     Std_ReturnType ret = E_OK ;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = lcd_8bit_set_cursor(lcd , row , column);
         while(*str)
         {
             ret = lcd_8bit_send_chr_data(lcd , *str++);
         }
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column,const uint8 _chr[], uint8 mem_pos){
     Std_ReturnType ret = E_OK ;
     uint8 lcd_count = ZERO_INIT;
     if(NULL == lcd)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         ret = lcd_8bit_send_command(lcd , (LCD_CGRAM_START + (mem_pos * 8)));
         for(lcd_count = 0 ; lcd_count <=7 ;lcd_count++)
         {
             ret = lcd_8bit_send_chr_data(lcd ,_chr[lcd_count]);
         }
         ret = lcd_8bit_send_chr_data_pos(lcd , row,column , mem_pos);
    }
    return ret ;
}

Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *str){
    Std_ReturnType ret = E_OK ;
     if(NULL == str)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         memset(*str , '\0',4);
         sprintf(*str,"%i",value);
    }
    return ret ;
}
Std_ReturnType convert_short_to_string(uint16 value ,uint8 *str){
    Std_ReturnType ret = E_OK ;
    uint8 Temp_String[6]= {0};
    uint8 CoutData = 0 ;
     if(NULL == str)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         memset(str ,' ',5);
         str[5]='\0';
         sprintf((char *)Temp_String,"%i",value);
         while(Temp_String[CoutData] != '\0')
         {
             str[CoutData] = Temp_String[CoutData];
             CoutData ++ ;
         }
    }
    return ret ;
}
Std_ReturnType convert_int_to_string(uint32 value ,uint8 *str){
     Std_ReturnType ret = E_OK ;
     if(NULL == str)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
         memset(*str , '\0',11);
         sprintf(*str,"%i",value);
    }
    return ret ;
}
static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd ,uint8 data_command)
{
    Std_ReturnType ret = E_OK ;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]),(data_command >> 0)& (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]),(data_command >> 1)& (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]),(data_command >> 2)& (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]),(data_command >> 3)& (uint8)0x01);
    
     return ret ;
}
static Std_ReturnType lcd_send_4bit_enable_signal(const chr_lcd_4bit_t *lcd )
{
    Std_ReturnType ret = E_OK ;
    ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_us(5);
      ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    
     return ret ;
}
static Std_ReturnType lcd_send_8bit_enable_signal(const chr_lcd_8bit_t *lcd )
{
    Std_ReturnType ret = E_OK ;
    ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_us(5);
      ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    
     return ret ;
}

static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK ;
    column--;
    switch(row)
    {
        case ROW1 : ret = lcd_8bit_send_command (lcd ,(0x80 + column));break ;
         case ROW2 : ret = lcd_8bit_send_command (lcd ,(0xc0 + column));break ;
          case ROW3 : ret = lcd_8bit_send_command (lcd ,(0x94 + column));break ;
           case ROW4 : ret = lcd_8bit_send_command (lcd ,(0xd4 + column));break ;
        default : ;
    }
    
    
     return ret ;
}
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK ;
    column--;
    switch(row)
    {
        case ROW1 : ret = lcd_4bit_send_command (lcd ,(0x80 + column));break ;
         case ROW2 : ret = lcd_4bit_send_command (lcd ,(0xc0 + column));break ;
          case ROW3 : ret = lcd_4bit_send_command (lcd ,(0x94 + column));break ;
           case ROW4 : ret = lcd_4bit_send_command (lcd ,(0xd4 + column));break ;
        default : ;
    }
    
    
     return ret ;
}