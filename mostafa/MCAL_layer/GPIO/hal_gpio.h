/* 
 * File:   hal_gpio.h
 * Author: user
 *
 * Created on August 15, 2023, 4:27 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

#include "pic18f4620.h"
#include "../device_config.h"
#include "../mcal_std_types.h"

/* Section : Macro Declaration*/
#define BIT_MASK    (uint8)   1
#define PORT_PIN_MAX_NUMBER   8
#define PORT_MAX_NUMBER       5

/* Section : Macro Function Declaration*/
#define HWREG8(_x)        ((*(volatile uint8 *)(_x)))

#define  SET_BIT(REG,BIT_POS)        (REG |= (BIT_MASK << BIT_POS))
#define  CLEAR_BIT(REG,BIT_POS)      (REG &= ~(BIT_MASK << BIT_POS))
#define  TOGGLE_BIT(REG,BIT_POS)     (REG ^= (BIT_MASK << BIT_POS))
#define  READ_BIT(REG,BIT_POS)       ((REG >> BIT_POS)& BIT_MASK)

#define CONFIG_ENABLE        0x01
#define CONFIG_DISENABLE        0x00
#define GPIO_PORT_CONFIGRATION  CONFIG_ENABLE 

#define _XTAL_FREQ  8000000UL 

/* Section : Data Type Declaration */
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t ;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t ;

typedef enum{
    PIN0= 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t ;


typedef enum{
    OUTPUT_DIRECTION = 0,
    INPUT_DIRECTION
}direction_t ;

typedef struct{
    uint8 port       :3  ; 
    uint8 pin        :3 ;
    uint8 direction  :1  ;
    uint8 logic      :1  ;
}pin_config_t ;


/* Section : Function Declaration*/
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port , uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

