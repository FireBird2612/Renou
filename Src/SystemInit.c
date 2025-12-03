#include <stm32_clock.h>
#include "ulog.h"

void SystemInit(void) {
  osc_select_hse();
  ulog_init();
  ULOG_INFO("ulog initialized with USART2 instance");
}
