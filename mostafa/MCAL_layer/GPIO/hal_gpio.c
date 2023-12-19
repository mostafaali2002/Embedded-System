/* 
 * File:   hal_gpio.c
 * Author: user
 *
 * Created on August 15, 2023, 4:15 PM
 */
#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA , &TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_register[] = {&LATA , &LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_register[] = {&PORTA , &PORTB,&PORTC,&PORTD,&PORTE};

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        switch (pin_config->direction) {
            case OUTPUT_DIRECTION:
                CLEAR_BIT(*tris_register[pin_config->port], pin_config->pin);
                break;
            case INPUT_DIRECTION:
                SET_BIT(*tris_register[pin_config->port], pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
     return ret ;
}
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config,direction_t *direction_status){
     Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER - 1 || NULL == direction_status)
    {
        ret = E_NOT_OK ; 
    }
    else{
      *direction_status =  READ_BIT(*tris_register[pin_config->port], pin_config->pin);
    }
     return ret ;
}
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic){
       Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        switch (logic) {
            case GPIO_LOW:
                CLEAR_BIT(*lat_register[pin_config->port], pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_register[pin_config->port], pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
     return ret ;
}
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config){
      Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || (pin_config->pin) > PORT_PIN_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK ; 
    }
    else{
      ret =  gpio_pin_direction_intialize(pin_config);
      ret =  gpio_pin_write_logic(pin_config ,pin_config->logic);
    }
      return ret ;
}


Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config,logic_t *logic){
     Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER - 1 || NULL == logic)
    {
        ret = E_NOT_OK ; 
    }
    else{
      *logic =  READ_BIT(*port_register[pin_config->port], pin_config->pin);
    }
     return ret ;
}

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK ; 
    }
     else
    {
        TOGGLE_BIT(*lat_register[pin_config->port], pin_config->pin);
     }
    return ret ;
}
#endif
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port , uint8 direction){
     Std_ReturnType ret = E_OK ;
    if(port == PORT_MAX_NUMBER -1 )
    {
        ret = E_NOT_OK ; 
    }
    else{
         *tris_register[port] = direction;
    }
     return ret ;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status){
       Std_ReturnType ret = E_OK ;
    if(port == PORT_MAX_NUMBER -1 && NULL == direction_status)
    {
        ret = E_NOT_OK ; 
    }
    else{
           *direction_status = *tris_register[port];
       }
       return ret ;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic){
       Std_ReturnType ret = E_OK ;
    if(port == PORT_MAX_NUMBER -1 )
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *lat_register[port] = logic ;
    }
        return ret ;
}
#endif
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic){
       Std_ReturnType ret = E_OK ;
    if((port == PORT_MAX_NUMBER -1) && NULL == logic)
    {
        ret = E_NOT_OK ; 
    }
    else{
        *logic = *lat_register[port] ;
    }
       return ret ;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
       Std_ReturnType ret = E_OK ;
    if(port == PORT_MAX_NUMBER -1)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *lat_register[port] ^= 0XFF;
    }
       return ret ;
}
#endif