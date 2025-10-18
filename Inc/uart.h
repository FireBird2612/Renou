#ifndef __UART_H__
#define __UART_H__

#include "stm32f4_uart.h"

/*  UART BAUDRATES  */
#define UBR12 1200U
#define UBR24 2400U
#define UBR96 9600U
#define UBR192 19200U
#define UBR384 38400U
#define UBR576 57600U
#define UBR1152 115200U

/*  UART oprating modes */
#define RX_ONLY 0U
#define TX_ONLY 1U
#define TX_RX 2U

/*  UART configurable stop bits    */
#define STP_1 0U
#define STP_05 (1U << STOP_BIT_POS)
#define STP_2 (2U << STOP_BIT_POS)
#define STP_15 (3U << STOP_BIT_POS)

/*  UART configurable word length   */
#define WORD_LEN_8 0U
#define WORD_LEN_9 M_BIT_MSK

/**
    @brief  This will initialze the uart instance by doing following procedures
            1. Enable the clock for USART instance and GPIO
            2. Configure the GPIO for alternate function
            3. Configure the UART for Tx/Rx/TxRx
    @param
    @return
*/
void uart_init(uart_def *uInstance);

/**
    @brief  
    @param
    @return
*/
void uart_tx(uart_def *uInstance, uint8_t *data);

#endif
