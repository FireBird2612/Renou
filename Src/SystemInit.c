#include "stm32f4_timer.h"
#include "stm32_clock.h"
#include "ulog.h"

void SystemInit(void) {
  //osc_select_hse(); For now we are using the HSI clock. 
  timer_init_upcounter(TIM2);
  ulog_init();
  ULOG_INFO("ulog initialized with USART2 instance");
}
