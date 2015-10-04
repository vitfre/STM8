#include "stm8s.h"
#include "stm8s_gpio.h"

static void delay(uint32_t t)
{
  while(t--);
}

int main( void )
{
  GPIOC->DDR |= GPIO_PIN_3 | GPIO_PIN_4;
  GPIOC->CR1 |= GPIO_PIN_3 | GPIO_PIN_4;
  GPIOC->ODR |= GPIO_PIN_3;
  
  while(1)            
  {
    delay(20000);
    GPIOC->ODR ^= GPIO_PIN_3 | GPIO_PIN_4;
  }
}
