#ifndef __STM32_RCC_H__
#define __STM32_RCC_H__

#include "stm32f4_periphs.h"
#include "stm32f4_gpio.h"

/*  RCC_AHB1ENR register bits    */
#define RCC_GPIOA_EN_POS (0U)
#define RCC_GPIOA_EN_MSK ((1U) << (RCC_GPIOA_EN_POS))
#define RCC_GPIOB_EN_POS (1U)
#define RCC_GPIOB_EN_MSK ((1U) << (RCC_GPIOB_EN_POS))
#define RCC_GPIOC_EN_POS (2U)
#define RCC_GPIOC_EN_MSK ((1U) << (RCC_GPIOC_EN_POS))
#define RCC_GPIOD_EN_POS (3U)
#define RCC_GPIOD_EN_MSK ((1U) << (RCC_GPIOD_EN_POS))
#define RCC_GPIOE_EN_POS (4U)
#define RCC_GPIOE_EN_MSK ((1U) << (RCC_GPIOE_EN_POS))
#define RCC_GPIOF_EN_POS (5U)
#define RCC_GPIOF_EN_MSK ((1U) << (RCC_GPIOF_EN_POS))
#define RCC_GPIOG_EN_POS (6U)
#define RCC_GPIOG_EN_MSK ((1U) << (RCC_GPIOG_EN_POS))
#define RCC_GPIOH_EN_POS (7U)
#define RCC_GPIOH_EN_MSK ((1U) << (RCC_GPIOH_EN_POS))

/*  RCC_APB1ENR register bits   */
#define RCC_USART2_EN_POS (17U)
#define RCC_USART2_EN_MSK ((1U) << (RCC_USART2_EN_POS))

/*  RCC register instance macro */
#define RCC ((rcc_reg_def *)RCC_BASE)

/*  Enable GPIOx clock
    NOTE to self: May as well convert this macro to inline function
*/
#define RCC_GPIO_CLK_EN(GPIOx)                                                 \
  do {                                                                         \
    if ((GPIOx) == GPIOA_BASE)                                                 \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOA_EN_MSK);                            \
    else if ((GPIOx) == GPIOB_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOB_EN_MSK);                            \
    else if ((GPIOx) == GPIOC_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOC_EN_MSK);                            \
    else if ((GPIOx) == GPIOD_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOD_EN_MSK);                            \
    else if ((GPIOx) == GPIOE_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOE_EN_MSK);                            \
    else if ((GPIOx) == GPIOF_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOF_EN_MSK);                            \
    else if ((GPIOx) == GPIOG_BASE)                                            \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOG_EN_MSK);                            \
    else                                                                       \
      SET_BITS(RCC->RCC_AHB1ENR, RCC_GPIOH_EN_MSK);                            \
  } while (0U)

/*  Enable UARTx Clock
    NOTE TO SELF: Complete as required...
*/
#define RCC_UARTX_CLK_EN(UARTx)                             \
do {                                                        \
  if (UARTx == USART2)                                      \
    SET_BITS(RCC->RCC_APB1ENR, RCC_USART2_EN_MSK);          \
}while(0)

/**
    \brief Describes the GPIO registers
*/
typedef struct {
  volatile uint32_t RCC_CR;
  volatile uint32_t RCC_PLL_CFGR;
  volatile uint32_t RCC_CFGR;
  volatile uint32_t RCC_CIR;
  volatile uint32_t RCC_AHB1_RSTR;
  volatile uint32_t RCC_AHB2_RSTR;
  volatile uint32_t RCC_AHB3_RSTR;
  volatile uint32_t reserved_reg0;
  volatile uint32_t RCC_APB1_RSTR;
  volatile uint32_t RCC_APB2_RSTR;
  volatile uint32_t reserved_reg1[2];
  volatile uint32_t RCC_AHB1ENR;
  volatile uint32_t RCC_AHB2ENR;
  volatile uint32_t RCC_AHB3ENR;
  volatile uint32_t reserved_reg3;
  volatile uint32_t RCC_APB1ENR;
  volatile uint32_t RCC_APB2ENR;
  volatile uint32_t reserved_reg4[2];
  volatile uint32_t RCC_AHB1LPENR;
  volatile uint32_t RCC_AHB2LPENR;
  volatile uint32_t RCC_AHB3LPENR;
  volatile uint32_t reserved_reg6;
  volatile uint32_t RCC_APB1LPENR;
  volatile uint32_t RCC_APB2LPENR;
  volatile uint32_t reserved_reg7[2];
  volatile uint32_t RCC_BDCR;
  volatile uint32_t RCC_CSR;
  volatile uint32_t reserved_reg9[2];
  volatile uint32_t RCC_SSCGR;
  volatile uint32_t RCC_PLLI2SCFGR;
  volatile uint32_t RCC_PLLSAICFGR;
  volatile uint32_t RCC_DCKCFGR;
  volatile uint32_t RCC_CKGATENR;
  volatile uint32_t RCC_DCKCFGR2;
} rcc_reg_def;

#endif
