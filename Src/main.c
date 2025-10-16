#include <stdint.h>
#include "stm32f4_uart.h"
#include "uart.h"

/*  global variables    */
uart_def usart2;

int main(void) {

  usart2.instance = USART2;
  usart2.uart_init.BaudRate = UBR1152;
  usart2.uart_init.Mode = TX_RX;
  usart2.uart_init.StopBits = STP_1;
  usart2.uart_init.WordLength = WORD_LEN_8;

  uart_init(&usart2);

  return 0;

}
