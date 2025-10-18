#ifndef __STM32F4_GPIO_H__
#define __STM32F4_GPIO_H__

#include "stm32f4_periphs.h"
#include <stdint.h>

/*  Register address
    NOTE TO SELF: May be change the naming convention. Ex GPIOA -> GPIOA_REG
*/
#define GPIOA ((gpio_reg_def *)GPIOA_BASE)
#define GPIOB ((gpio_reg_def *)GPIOB_BASE)
#define GPIOC ((gpio_reg_def *)GPIOC_BASE)
#define GPIOD ((gpio_reg_def *)GPIOD_BASE)
#define GPIOE ((gpio_reg_def *)GPIOE_BASE)
#define GPIOF ((gpio_reg_def *)GPIOF_BASE)
#define GPIOG ((gpio_reg_def *)GPIOG_BASE)
#define GPIOH ((gpio_reg_def *)GPIOH_BASE)

/*  Helper defines */
#define GPIOA_PORT GPIOA_BASE
#define GPIOB_PORT GPIOB_BASE
#define GPIOC_PORT GPIOC_BASE
#define GPIOD_PORT GPIOD_BASE
#define GPIOE_PORT GPIOD_BASE
#define GPIOF_PORT GPIOF_BASE
#define GPIOG_PORT GPIOG_BASE
#define GPIOH_PORT GPIOH_BASE

/* GPIO Pins in a portX */
#define GPIO_PIN_0 (0U)
#define GPIO_PIN_1 (1U)
#define GPIO_PIN_2 (2U)
#define GPIO_PIN_3 (3U)
#define GPIO_PIN_4 (4U)
#define GPIO_PIN_5 (5U)
#define GPIO_PIN_6 (6U)
#define GPIO_PIN_7 (7U)
#define GPIO_PIN_8 (8U)
#define GPIO_PIN_9 (9U)
#define GPIO_PIN_10 (10U)
#define GPIO_PIN_11 (11U)
#define GPIO_PIN_12 (12U)
#define GPIO_PIN_13 (13U)
#define GPIO_PIN_14 (14U)
#define GPIO_PIN_15 (15U)

/* GPIO modes */
#define GPIO_INPUT (0U)
#define GPIO_OUTPUT (1U)
#define GPIO_AFM (2U)
#define GPIO_ANALOG (3U)

/* GPIO AF Pins */
#define GPIO_AF0 (0U)
#define GPIO_AF1 (1U)
#define GPIO_AF2 (2U)
#define GPIO_AF3 (3U)
#define GPIO_AF4 (4U)
#define GPIO_AF5 (5U)
#define GPIO_AF6 (6U)
#define GPIO_AF7 (7U)
#define GPIO_AF8 (8U)
#define GPIO_AF9 (9U)
#define GPIO_AF10 (10U)
#define GPIO_AF11 (11U)
#define GPIO_AF12 (12U)
#define GPIO_AF13 (13U)
#define GPIO_AF14 (14U)
#define GPIO_AF15 (15U)

#define GPIO_SPI_4W_PC (4U)
#define GPIO_SPI_3W_PC (3U)
#define GPIO_I2C_PC (2U)
#define UART_2W_PC (2U)
#define UART_1W_PC (1U)

/* Set GPIO Mode */
#define GPIO_MODE_SET(portX, gpioPinX, gpioModeX)                              \
  do {                                                                         \
    CLEAR_BITS((portX), ((3U) << (gpioPinX * 2)));                             \
    SET_BITS((portX), ((gpioModeX) << (gpioPinX * 2)));                         \
  } while (0U)

/* Set GPIO pin alternate function */
#define GPIO_AF_SET(portX, gpioPinX, afMode)                                   \
  do {                                                                         \
    uint8_t temp_bit_pos;                                                      \
    if (gpioPinX <= 7) {                                                       \
      temp_bit_pos = gpioPinX * 4;                                             \
      CLEAR_BITS((portX->GPIOx_AFRL), ((0xF) << temp_bit_pos));                \
      SET_BITS((portX->GPIOx_AFRL), (afMode << temp_bit_pos));                 \
    } else {                                                                   \
      temp_bit_pos = (gpioPinX * 4) - 32;                                      \
      CLEAR_BITS((portX->GPIOx_AFRH), ((0xF) << temp_bit_pos));                \
      SET_BITS((portX->GPIOx_AFRH), (afMode << temp_bit_pos));                 \
    }                                                                          \
  } while (0U)

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
} gpio_reg_def;

/**
    \brief GPIO Pin Configuration params
*/
typedef struct {
  gpio_reg_def *GPIOxPortInstance;
  uint16_t GPIOxMode;
  uint16_t GPIOxPinCount;
  uint16_t GPIOxPinSetBits;
  uint16_t GPIOxPinSpeed;
  uint16_t GPIOxPushPull;
  uint16_t GPIOxAF;
} gpio_pin_config_def;

/**
    @brief  This will initialze the GPIOx Port by enabling the clock
    @param  gpio_reg_def *GPIOxPort
    @return void
*/
void gpio_init(uint32_t GPIOxPort);

/**
    @brief  set the mode for the given pin
    @param  gpio_reg_def *GPIOxPortInstance Such as pointer to GPIOx addresses GPIOA, GPIOB, etc... 
    @return error status
*/
//int gpio_set_params(gpio_pin_config_def GPIOxPin);

#endif
