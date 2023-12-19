/* 
 * File:   ecu_chr_lcd.h
 * Author: user
 *
 * Created on September 2, 2023, 5:39 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* Section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration*/
#define LCD_CLEAR                           0x01
#define LCD_RETURN_HOME                     0x02
#define LCD_ENTRY_MODE                      0x06 
#define LCD_DISPLAY_OFF_CURSOR_OFF          0x08
#define LCD_DISPLAY_ON_CURSOR_OFF           0x0C
#define LCD_DISPLAY_ON_CURSOR_ON            0x0E
#define LCD_DISPLAY_ON_BLOCK_ON             0x0D
#define LCD_DISPLAY_ON_CURSOR_ON_BLOCK_ON   0x0F
#define LCD_DISPLAY_SHIFT_RIGHT             0x1C
#define LCD_DISPLAY_SHIFT_LEFT              0x18
#define LCD_8BIT_MODE_2_LINE                0x38
#define LCD_4BIT_MODE_2_LINE                0x28
#define LCD_DDRAM_START                     0x80
#define LCD_CGRAM_START                     0x40

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/* Section : Function Declaration*/
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , uint8 command);
Std_ReturnType lcd_4bit_send_chr_data(const chr_lcd_4bit_t *lcd ,uint8 data);
Std_ReturnType lcd_4bit_send_chr_data_pos(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd , uint8 *str,uint8 row , uint8 column);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd ,uint8 row,uint8 column,const uint8 _chr[], uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , uint8 command);
Std_ReturnType lcd_8bit_send_chr_data(const chr_lcd_8bit_t *lcd ,uint8 data);
Std_ReturnType lcd_8bit_send_chr_data_pos(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd , uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd ,uint8 row,uint8 column,const uint8 _chr[], uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value ,uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value ,uint8 *str);
#endif	/* ECU_CHR_LCD_H */

