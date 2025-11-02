#include "stdio.h"
#include "stdint.h"

/* Hardware specific includes */
#include "stm32_clock.h"
#include "stm32f4_gpio.h"
#include "stm32f4_uart.h"
#include <stdint.h>

/* Generic layer */
#include "uart.h"


void uart_init(uart_def *uInstance) {
  /* Check for passed parameters, could be made more robust */
  if (!uInstance) {
    uInstance->uart_state = UART_STATE_ERROR;
    return;
  }
  /* Why do we need buffer checking at initialization?
  if (uInstance->uRxBuffer == NULL && uInstance->uTxBuffer == NULL) {
    uInstance->uart_state = UART_STATE_ERROR;
    return;
  }
  */

  /*  Set the GPIO Functionality here */
  if (uInstance->instance == USART2) {
    /* Enable Clock for GPIOA Port    */
    gpio_init((uint32_t)(uInstance->gpio_port.GPIOxPortInstance));

    /* Enable USART2 Clock as well  */
    RCC_UARTX_CLK_EN(uInstance->instance);

    /* From the GPIOxPinSetBits member extract the gpio pin number which ranges
    from 0 to 15. The application is required to set the bit for the GPIO Pin
    which need to be configured.
    Ex: GPIO Pin PA2 = TX and PA3 = RX
    | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    | 0  | 0  | 0  | 0  | 0  | 0  | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 |
    */
    uint8_t bit_pos, set_bits_found = 0;
    /* Extract the pin number from the GPIOxPinSetBits */
    for (bit_pos = 0; bit_pos < 16; bit_pos++) {
      if ((uInstance->gpio_port.GPIOxPinSetBits >> bit_pos) & 1) {
        set_bits_found++;
        /* pass the bit position as gpio number */
        GPIO_MODE_SET(uInstance->gpio_port.GPIOxPortInstance->GPIOx_MODER,
                      bit_pos, uInstance->gpio_port.GPIOxMode);
        GPIO_AF_SET(uInstance->gpio_port.GPIOxPortInstance, bit_pos, uInstance->gpio_port.GPIOxAF);
      }
      if (set_bits_found == uInstance->gpio_port.GPIOxPinCount) {
        break;
      }
    }
  }

  /* Enable UART, OVER8=0, 8 Data bit, */
  uint32_t make_mask = 0;

  /* set wordlength */
  if (uInstance->uart_init.WordLength == WORD_LEN_9) {
    make_mask |= WORD_LEN_9;
  }
 
  uInstance->instance->USART_CR1 |= make_mask;

  /* check for stop bits */
  make_mask = 0;
  if (uInstance->uart_init.StopBits == STP_05) {
    make_mask |= STP_05;
  } else if (uInstance->uart_init.StopBits == STP_2) {
    make_mask |= STP_2;
  } else if (uInstance->uart_init.StopBits == STP_15) {
    make_mask |= STP_15;
  }

  if (make_mask) {
    uInstance->instance->USART_CR2 |= make_mask;
  }

  /* Baudrate calculation */
  float fclk = 16000000.0, udiv;
  uint32_t mantissa;
  uint64_t frac;
  uint16_t BRR;

  if (((uInstance->instance->USART_CR1 >> OVER8_BIT_POS) & 1) == 0) {
    // Oversampling by 16, default
    udiv = (float)(fclk / (16 * uInstance->uart_init.BaudRate));
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

void uart_tx(uart_def *uInstance, int8_t *data) {
  /* Enable uart  */
  uInstance->instance->USART_CR1 |= (UE_BIT_MSK);

  uInstance->uart_state = UART_STATE_BUSY_TX;

  // clear stale transmission complete flag before new TX
  uInstance->instance->USART_SR &= ~TC_BIT_MSK;

  while (*data) {
    while (!((uInstance->instance->USART_SR >> TXE_BIT_POS) & 1)); /*  Keep polling for until Transmit Data Register becomes 1 */
    uInstance->instance->USART_DR = *data++;
  }

  while (!((uInstance->instance->USART_SR >> 6) & 1)); /*  When TC = 1, End of transmission */
  uInstance->instance->USART_SR &= ~(TC_BIT_MSK);

  uInstance->uart_state = UART_STATE_READY;

  /* Disable uart after current transmission  */
  uInstance->instance->USART_CR1 &= ~(UE_BIT_MSK);
}

void uart_deinit(uart_def *uInstance) {
  /*   disable the uart pin outs for tx/rx  */
  if ((uInstance->uart_state != UART_STATE_BUSY_TX) &&
      (uInstance->uart_state != UART_STATE_BUSY_TX_RX) &&
      (uInstance->uart_state != UART_STATE_BUSY_RX)) {

    if (uInstance->uart_init.Mode == TX_RX) {
      // Enable Transmit as well as Receive
      uInstance->instance->USART_CR1 &= ~(RE_BIT_MSK | TE_BIT_MSK);
    } else if (uInstance->uart_init.Mode == TX_ONLY) {
      // Enable Transmit
      uInstance->instance->USART_CR1 &= ~TE_BIT_MSK;
    } else if (uInstance->uart_init.Mode == RX_ONLY) {
      // Enable Receive
      uInstance->instance->USART_CR1 &= ~RE_BIT_MSK;
    } else {
      // Error; need some mechanism for error handling.
      uInstance->uart_state = UART_STATE_ERROR;
      return;
    }
  }

  // disable the clock
  RCC_UARTX_CLK_DISABLE(uInstance->instance);
}
