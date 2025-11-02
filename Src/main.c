#include <stdint.h>
#include <string.h>
#include "stdlib.h"
#include "stdio.h"
#include "stm32f4_gpio.h"
#include "stm32f4_periphs.h"
#include "stm32f4_uart.h"
#include "uart.h"

/*  global variables    */
uart_def usart2;

int main(void) {

  usart2.instance = USART2;                     /* Select which type of uart instance you want to use   */
  usart2.uart_init.BaudRate = UBR1152;          /* Configure the uart buadrate */
  usart2.uart_init.Mode = TX_ONLY;              /* Configure 1Wire UART or 2Wire UART   */
  usart2.uart_init.StopBits = STP_1;            /* Specify stop bits    */
  usart2.uart_init.WordLength = WORD_LEN_8;     /* Choose wordlength    */
  usart2.gpio_port.GPIOxPortInstance = GPIOA;   /* GPIO Port for USART2 */
  usart2.gpio_port.GPIOxMode = GPIO_AFM;        /* PA2 = Tx */
  usart2.gpio_port.GPIOxPinCount = 1;
  usart2.gpio_port.GPIOxPinSetBits = (1U << 2); /* Bit mask for PA2 as TX */
  usart2.gpio_port.GPIOxAF = GPIO_AF7;

  uart_init(&usart2);

  int8_t tx_buffer[30] = "Hello World\n";
  uart_tx(&usart2, tx_buffer);

  int length = strlen((const char *)tx_buffer);
  snprintf((char *)tx_buffer, sizeof(tx_buffer), "Length = %d\n", length);
  uart_tx(&usart2, tx_buffer);

  uart_deinit(&usart2);

  for (;;)
    ;
  
  return 0;

}
