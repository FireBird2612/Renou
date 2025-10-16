#ifndef __UART_H__
#define __UART_H__

#include "stm32f4_uart.h"

/**
    @brief  This will initialze the uart instance by doing following procedures
            1. Enable the clock for USART instance and GPIO
            2. Configure the GPIO for alternate function
            3. Configure the UART for Tx/Rx/TxRx
    @param
    @return
*/
void uart_init(void);

#endif
