#include "uart.h"
#include "stdio.h"
#include "stm32f4_uart.h"
#include <stdint.h>


void uart_init(uart_def *uInstance) {
  if (!uInstance) {
    uInstance->uart_state = UART_STATE_ERROR;
    return;
  }
  if (uInstance->uRxBuffer == NULL && uInstance->uTxBuffer == NULL) {
    uInstance->uart_state = UART_STATE_ERROR;
    return;
  }
  
  /*  Set the GPIO Functionality here */

  /* Enable UART, OVER8=0, 8 Data bit, */
  uInstance->instance->USART_CR1 |=  UE_BIT_MSK;

  float fclk = 16000000.0, udiv;
  uint32_t mantissa;
  uint64_t frac;
  uint16_t BRR;

  if (((uInstance->instance->USART_CR1 >> OVER8_BIT_POS) & 1) == 0) {
    // Oversampling by 16, default
    udiv = (float)(fclk / 16 * uInstance->uart_init.BaudRate);
    mantissa = (uint32_t)udiv;
    frac = (uint64_t)((udiv - mantissa) * 16);
    BRR = ((mantissa & 0xFFF) << 4) | (frac & 0xF);
  } else {
    // Oversampling by 8, when OVER8_BIT is set as 1
    udiv = (float)(fclk / 8 * uInstance->uart_init.BaudRate);
    mantissa = (uint32_t)udiv;
    frac = (uint64_t)((udiv - mantissa) * 8);
    BRR = ((mantissa & 0xFFF) << 4) | (frac & 0x7);
  }

  /* Set the calculated baudrate */
  uInstance->instance->USART_BRR = BRR;

  if (uInstance->uart_init.Mode == TX_RX) {
    // Enable Transmit as well as Receive
    uInstance->instance->USART_CR1 |= (RE_BIT_MSK | TE_BIT_MSK);
  } else if (uInstance->uart_init.Mode == TX_ONLY) {
    // Enable Transmit
    uInstance->instance->USART_CR1 |= TE_BIT_MSK;
  } else if(uInstance->uart_init.Mode == RX_ONLY){
    // Enable Receive
    uInstance->instance->USART_CR1 |= RE_BIT_MSK;
  } else {
    // Error; need some mechanism for error handling.
    uInstance->uart_state = UART_STATE_ERROR;
    return;
  }

  uInstance->uart_state = UART_STATE_READY;

  return;
}
