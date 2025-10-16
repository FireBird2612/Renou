#ifndef __STM32F4_UART_H__
#define __STM32F4_UART_H__

#include "stm32f4_periphs.h"

/**
    \brief Describes the USART registers.
*/
typedef struct {
  volatile uint32_t USART_SR;  /*  status register  */
  volatile uint32_t USART_DR;  /*  data register   */
  volatile uint32_t USART_BRR; /*  baud rate register  */
  volatile uint32_t USART_CR1; /*  control register 1 to 3 */
  volatile uint32_t USART_CR2;
  volatile uint32_t USART_CR3;
  volatile uint32_t USART_GTPR; /*  guard time and prescaler register   */
} uart_reg_def;

#define USART2 ((uart_reg_def *)USART2_BASE)

/**
    \brief Configuration parameters required for uart initialization
*/
typedef struct {
  uint32_t BaudRate;
  uint32_t WordLength;
  uint32_t StopBits;
  uint32_t Mode;
} uart_init_def;

/**
    \brief uart state of operation
*/
typedef enum {
  UART_STATE_RESET = 0,
  UART_STATE_READY,
  UART_STATE_BUSY_TX,
  UART_STATE_BUSY_RX,
  UART_STATE_BUSY_TX_RX,
  UART_STATE_ERROR
} uart_states_def;

/**
    \brief uart global handle structure
*/
typedef struct {
  uart_reg_def *instance;
  uart_init_def uart_init;
  uint8_t *uTxBuffer;
  uint32_t TxSize;
  uint8_t *uRxBuffer;
  uint32_t RxSize;
  uart_states_def uart_state;
}uart_def;

/*  USART Data Register bits */
#define PE_BIT_POS (0U)                             /*  Parity bit error    */
#define PE_BIT_MSK (1U << PE_BIT_POS)
#define FE_BIT_POS (1U)                             /*  Framing bit error   */
#define FE_BIT_MSK (1U << FE_BIT_POS)
#define NF_BIT_POS (2U)                             /*  Noise Detected flag bit */
#define NF_BIT_MSK (1U << NF_BIT_POS)
#define ORE_BIT_POS (3U)                            /*  Overrun error bit   */
#define ORE_BIT_MSK (1U << ORE_BIT_POS)
#define IDLE_BIT_POS (4U)                           /*  IDLE line detected  */
#define IDLE_BIT_MSK (1U << IDLE_BIT_POS)
#define RXNE_BIT_POS (5U)                           /*  Read Data register not empty    */
#define RXNE_BIT_MSK (1U << RXNE_BIT_POS)
#define TC_BIT_POS (6U)                             /*  Transmission Complete   */
#define TC_BIT_MSK (1U << TC_BIT_POS)
#define TXE_BIT_POS (7U)                            /*  Transmit data register empty    */
#define TXE_BIT_MSK (1U << TXE_BIT_POS)
#define LBD_BIT_POS (8U)                            /*  LIN break detection flag    */
#define LBD_BIT_MSK (1U << LBD_BIT_POS)
#define CTS_BIT_POS (9U)                            /*  CTS flag    */
#define CTS_BIT_MSK (1U << CTS_BIT_MSK)

/*  USART Control Register 1 */
#define OVER8_BIT_POS (15U)
#define UE_BIT_POS (13U)
#define UE_BIT_MSK (1U << UE_BIT_POS)
#define M_BIT_POS (12U)
#define M_BIT_MSK (1U << M_BIT_POS)
#define TE_BIT_POS (3U)
#define TE_BIT_MSK (1U << TE_BIT_POS)
#define RE_BIT_POS (2U)
#define RE_BIT_MSK (1U << RE_BIT_POS)

#endif
