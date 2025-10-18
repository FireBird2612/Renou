#include "stm32_clock.h"
#include "stm32f4_gpio.h"

void gpio_init(uint32_t GPIOxPort) {
  if (!GPIOxPort) {
    return;
  }

  /* set the clock for the particular gpio instance */
  RCC_GPIO_CLK_EN(GPIOxPort);
  return;
}

