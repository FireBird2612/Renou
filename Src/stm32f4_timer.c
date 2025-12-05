
#include "stm32f4_timer.h"
#include "stm32_clock.h"
/**
    For initial testing to check wether the TIM2 is working as intended.
    PSC = 15, ARR = 0xFFFFFFFF (TIM2), System CLK = 16 MHz
*/
int timer_init_upcounter(tim_reg_def *timer_instance) {
  
  /* Enable the clock for TIMx in RCC */
  RCC_TIMX_CLK_ENABLE(timer_instance);

  SET_BITS(timer_instance->TIMx_EGR, TIMx_EGR_UG_MSK);
  timer_instance->TIMx_PSC = 15;
  timer_instance->TIMx_ARR = 0xFFFFFFFF;

  SET_BITS(timer_instance->TIMx_CR1, TIMx_CR1_CEN_MSK);
  return 1;
}

uint32_t timer_read_upcounter(tim_reg_def *timer_instance){
  return timer_instance->TIMx_CNT;
}

