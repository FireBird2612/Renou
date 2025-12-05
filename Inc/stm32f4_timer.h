#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f4_periphs.h"

/**
    \brief Define TIM2 Instance macro
*/
#define TIM2 ((tim_reg_def *)TIM2_BASE)

/**
    \brief TIMxCR1 Control Register-1 bit definitions
*/
#define TIMx_CR1_CEN_POS (0U)
#define TIMx_CR1_CEN_MSK ((1U) << (TIMx_CR1_CEN_POS))

/**
    \brief TIMxEGR Event Generation register bit definition
*/
#define TIMx_EGR_UG_POS (0U)
#define TIMx_EGR_UG_MSK ((1U) << (TIMx_EGR_UG_POS))

/**
    \brief Describes TIMx Registers
*/
typedef struct {
  volatile uint32_t TIMx_CR1;
  volatile uint32_t TIMx_CR2;
  volatile uint32_t TIMx_SMCR;
  volatile uint32_t TIMx_DIER;
  volatile uint32_t TIMx_SR;
  volatile uint32_t TIMx_EGR;
  volatile uint32_t TIMx_CCMR1;
  volatile uint32_t TIMx_CCMR2;
  volatile uint32_t TIMx_CCER;
  volatile uint32_t TIMx_CNT;
  volatile uint32_t TIMx_PSC;
  volatile uint32_t TIMx_ARR;
  volatile uint32_t reserved0;
  volatile uint32_t TIMx_CCR1;
  volatile uint32_t TIMx_CCR2;
  volatile uint32_t TIMx_CCR3;
  volatile uint32_t TIMx_CCR4;
  volatile uint32_t reserved1;
  volatile uint32_t TIMx_DCR;
  volatile uint32_t TIMx_DMAR;
  volatile uint32_t TIM2_OR;
  volatile uint32_t TIM5_OR;
} tim_reg_def;

/**
    \brief Initialize the timer in upcounter mode with following configuration,
    - Auto-reload register is not buffered.
    - Set the UG bit in EGR
    - Populate PSC depending on the passed parameter.
    - Populate ARR depending on the passed parameter.
*/
int timer_init_upcounter(tim_reg_def *timer_instance);

/**
    \brief Read the value of timer counter register when upcounting.
    \return timer counter register
*/
uint32_t timer_read_upcounter(tim_reg_def *timer_instance);

#endif
