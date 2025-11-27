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
  if (!uInstance) {
    return;
  }

  __uart_init(uInstance);
}

void uart_tx(uart_def *uInstance, const uint8_t *data) {
  if ((!uInstance) || (!data)) {
    return;
  }

  __uart_tx(uInstance, data);
}

void uart_deinit(uart_def *uInstance) {
  if (!uInstance) {
    return;
  }

  __uart_deinit(uInstance);
}
