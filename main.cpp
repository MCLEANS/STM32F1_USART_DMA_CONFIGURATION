#include "stm32f10x.h"

int main(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH |= GPIO_CRH_MODE13;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
  
  while(1){
      for(int i = 0; i<1000000; i++){}
      GPIOC->ODR ^= GPIO_ODR_ODR13;

  }
}
