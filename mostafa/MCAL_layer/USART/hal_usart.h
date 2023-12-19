/* 
 * File:   hal_usart.h
 * Author: user
 *
 * Created on September 26, 2023, 1:43 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration*/
#define USART_MODULE_ENABLE     1
#define USART_MODULE_DISABLE     0

#define USART_SYNCHRONOUS_ENABLE        1
#define USART_ASYNCHRONOUS_ENABLE       0

#define USART_ASYNCHRONOUS_HIGH_SPEED       1
#define USART_ASYNCHRONOUS_LOW_SPEED        0

#define USART_16BIT_BAUDRATE     1
#define USART_8BIT_BAUDRATE      0

#define USART_ASYNCHRONOUS_TX_ENABLE          1
#define USART_ASYNCHRONOUS_TX_DISENABLE       0
#define USART_ASYNCHRONOUS_TX_9BIT_ENABLE          1
#define USART_ASYNCHRONOUS_TX_9BIT_DISENABLE       0
#define USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define USART_ASYNCHRONOUS_INTERRUPT_TX_DISENABL   0

#define USART_ASYNCHRONOUS_RX_ENABLE          1
#define USART_ASYNCHRONOUS_RX_DISENABLE       0
#define USART_ASYNCHRONOUS_RX_9BIT_ENABLE          1
#define USART_ASYNCHRONOUS_RX_9BIT_DISENABLE       0
#define USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define USART_ASYNCHRONOUS_INTERRUPT_RX_DISENABL   0

#define USART_ASYNCHRONOUS_FREMING_ERROR_DETECT      1
#define USART_ASYNCHRONOUS_FREMING_ERROR_CLEAR       0
#define USART_ASYNCHRONOUS_OVERRUN_ERROR_DETECT      1
#define USART_ASYNCHRONOUS_OVERRUN_ERROR_CLEAR       0


/* Section : Macro Function Declaration*/

/* Section : Data Type Declaration */
typedef enum {
    BAUDRATE_ASYNC_8BIT_LOW_SPEED = 0,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,  
    BAUDRATE_SYNC_8BIT  ,  
    BAUDRATE_SYNC_16BIT          
}baudrate_gen_t;

typedef struct{
    uint8 usart_tx_enable :1 ;
    uint8 usart_tx_interrupt_enable :1 ;
    uint8 usart_tx_9bit_enable :1 ;
     interrupt_priority_cfg usart_tx_int_priority;
}usart_tx_confg_t;

typedef struct{
    uint8 usart_rx_enable :1 ;
    uint8 usart_rx_interrupt_enable :1 ;
    uint8 usart_rx_9bit_enable :1 ;
     interrupt_priority_cfg usart_rx_int_priority;
}usart_rx_confg_t;

typedef union {
    struct {
        uint8 usart_ferr_error : 1 ;
        uint8 usart_oerr_error : 1 ;
    };
    uint8 status_error ;
}usart_error_status_t;

typedef struct {  
    uint32 baudrate ;
    baudrate_gen_t  baudrate_gen;
    usart_rx_confg_t  usart_rx ;
    usart_tx_confg_t  usart_tx ;
    usart_error_status_t error_status ;
    void(*USART_TX_InterruptHandler)(void);
    void(*USART_RX_InterruptHandler)(void);
    void(*USART_FRAMING_InterruptHandler)(void);
    void(*USART_OVERRUN_InterruptHandler)(void);
}usart_t;
/* Section : Function Declaration*/
Std_ReturnType USART_ASYNC_Init(const usart_t *usart);
Std_ReturnType USART_ASYNC_DEinit(const usart_t *usart);
Std_ReturnType USART_ASYNC_ReadByteBloking( uint8 *data);
Std_ReturnType USART_ASYNC_ReadByteNoBloking( uint8 *data);
Std_ReturnType USART_ASYNC_WriteByteBloking( uint8 data);
Std_ReturnType USART_ASYNC_WriteStringBloking( uint8 *data,uint16 str_len);
#endif	/* HAL_USART_H */

