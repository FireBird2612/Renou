#include <stm32f4_periphs.h>
#include <stm32_clock.h>

/**
    @brief  Select HSE as system clock source
    @param  None
    @return None
*/
int osc_select_hse(void) {
  /*  Set the HSEBYP bit to set the HSE as bypass external clock  */
  SET_BITS(RCC->RCC_CR, RCC_CR_HSEBYP_MSK);

  /* Enable the HSE by setting the HSEON bit in RCC_CR register */
  SET_BITS(RCC->RCC_CR, RCC_CR_HSEON_MSK);

  /*  Wait until the HSERDY flag is set
      TODO: Define a timeout mechanism later
  */
  if (!(RCC->RCC_CR & RCC_CR_HSERDY_MSK)) {
    return 0;
  }

  return 1;
}
