#ifndef __STM32F4_PERIPH_H__
#define __STM32F4_PERIPH_H__

#include <stdint.h>

#define STM32F4X

/* Peripherals Base Address */
#define GPIOA_BASE  0x40020000U
#define USART2_BASE 0x40004400U

/**
    \brief Describes the GPIO registers
*/
typedef struct {
  volatile uint32_t GPIOx_MODER;   /*  port mode regsiter register */
  volatile uint32_t GPIOx_OTYPER;  /*  port output type register   */
  volatile uint32_t GPIOx_OSPEEDR; /*  port output speed register  */
  volatile uint32_t GPIOx_PUPDR;   /*  port pull-up/pull-down register */
  volatile uint32_t GPIOx_IDR;     /*  port input data register    */
  volatile uint32_t GPIOx_ODR;     /*  port output data register   */
  volatile uint32_t GPIOx_BSRR;    /*  port bit set/reset register */
  volatile uint32_t GPIOx_LCKR;    /*  port configuration lock register    */
  volatile uint32_t GPIOx_AFRL; /*  port alternate function low register    */
  volatile uint32_t GPIOx_AFRH; /*  port alternate function high register   */
} gpio_def;

#define GPIOA ((gpio_def *)GPIOA_BASE)


#endif
