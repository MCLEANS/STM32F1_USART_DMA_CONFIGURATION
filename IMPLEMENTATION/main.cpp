#include "stm32f10x.h"
#include "USART.h"
#include <string.h>

#define RX_PIN 11
#define TX_PIN 10
#define BAUDRATE 9600

custom_libraries::USART GSM(USART3,GPIOB,custom_libraries::_DMA1,DMA1_Channel3,RX_PIN,TX_PIN,BAUDRATE);

bool ok_received = false;
char reply[] = "\r\nOK";

int main(void) {

  GSM.initialize();
  GSM.println("ATE0");//USED TO AVOID MESSAGE ECHOING
  for(volatile int i = 0; i < 1000000; i++){}
  GSM.flush_buffer();
  GSM.println("AT");
  
  for(volatile int i = 0; i < 1000000; i++){}

  if(strncmp(GSM.receive_buffer,reply,(sizeof(reply)/sizeof(char))-1) == 0){
    ok_received = true;
  }

  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  GPIOC->CRH |= GPIO_CRH_MODE13;
  GPIOC->CRH &= ~GPIO_CRH_CNF13;
    
  while(1){
    if(ok_received){
      for(volatile int i = 0; i<9000000; i++){}
      GPIOC->ODR ^= GPIO_ODR_ODR13;
    }

    else{
      for(volatile int i = 0; i<1000000; i++){}
      GPIOC->ODR ^= GPIO_ODR_ODR13;
    }
      

  }
}
