#include "ulog.h"
#include "stm32_clock.h"
#include "stm32f4_periphs.h"
#include "stdarg.h"
#include <stdio.h>
#include "stm32f4_uart.h"
#include "string.h"
#include "stm32f4_uart.h"
#include "uart.h"

#define ULOG_MAX_MSG_LEN 256

static uart_def usart2;

void ulog_init(void) {
  /*  Initialize the ulog dependency and memory if required.  */
  /* Configure uart */
  usart2.instance = USART2; /* Select which type of uart instance you want to use   */
  usart2.uart_init.BaudRate = UBR1152; /* Configure the uart buadrate */
  usart2.uart_init.Mode = TX_ONLY;   /* Configure 1Wire UART or 2Wire UART   */
  usart2.uart_init.StopBits = STP_1; /* Specify stop bits    */
  usart2.uart_init.WordLength = WORD_LEN_8;   /* Choose wordlength    */
  usart2.gpio_port.GPIOxPortInstance = GPIOA; /* GPIO Port for USART2 */
  usart2.gpio_port.GPIOxMode = GPIO_AFM;      /* PA2 = Tx */
  usart2.gpio_port.GPIOxPinCount = 1;
  usart2.gpio_port.GPIOxPinSetBits = (1U << 2); /* Bit mask for PA2 as TX */
  usart2.gpio_port.GPIOxAF = GPIO_AF7;

  __uart_init(&usart2);
}

void ulog_log(ulog_level_t log_level, const char *fmt) {
  char buffer[ULOG_MAX_MSG_LEN] = {0};
  const char *level_str;

  /* select level string */
  switch (log_level) {
  case LOG_INFO:
    level_str = "[INFO]:";
    break;

  case LOG_WARN:
    level_str = "[WARN]:";
    break;

  case LOG_ERROR:
    level_str = "[ERROR]:";
    break;

  default:
    return;
  }

  /*  copy and concatenate  */
  int level_str_len = strlen(level_str);
  strncpy(buffer, level_str, level_str_len);

  /*  fmt length should be less than buffer size - level_str_len    */
  strcat(buffer, fmt);
  strcat(buffer, "\r\n");

  // TODO: Call the uart_tx().
  __uart_tx(&usart2, buffer);
}



