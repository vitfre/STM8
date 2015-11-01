#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_exti.h"
#include "stm8s_itc.h"
#include "stm8s_uart1.h"
#include "stm8s_tim2.h"
#include "stm8s_flash.h"
#include "stm8s_adc1.h"
#include "delay.h"
#include "Init.h"

#define EEPROM_START    FLASH_DATA_START_PHYSICAL_ADDRESS                       //Начало EEPROM = 0x4000

unsigned char HELLO[16]={0};
unsigned char *byteNum = HELLO; // Указатель на передаваемый байт.


/* Private function prototypes -----------------------------------------------*/
void UART_send_buf(uint8_t * buf, uint8_t len);
void UART_send_str(uint8_t * str);
void send_int(uint16_t);



uint32_t FLASH_ReadWord(uint32_t Address)
{
  uint32_t data=0;
  //data=FLASH_ReadByte(Address);
  //data=FLASH_ReadByte(Address);
  //data=FLASH_ReadByte(Address);
  //data=FLASH_ReadByte(Address);
  
  *((uint8_t*)(&data)) = FLASH_ReadByte(Address);
  *((uint8_t*)(&data)+1) = FLASH_ReadByte(Address + 1);
  *((uint8_t*)(&data)+2) = FLASH_ReadByte(Address + 2);
  *((uint8_t*)(&data)+3) = FLASH_ReadByte(Address + 3);
  return data;
};

/*
//Button 1
INTERRUPT_HANDLER(EXTI0_IRQHandler, EXTI_PORT_GPIOC)
{
  GPIO_WriteLow(GPIOB, GPIO_PIN_6);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_6);
  
  GPIO_WriteLow(GPIOB, GPIO_PIN_7);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
   
  GPIO_WriteLow(GPIOB, GPIO_PIN_5);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
  //EXTI_ClearITPendingBit(EXTI_PORT_GPIOC);
}

//Button 2
INTERRUPT_HANDLER(EXTI2_IRQHandler, EXTI2_IRQn)
{
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
  delay_10us(20);
  GPIO_ResetBits(GPIOC, GPIO_Pin_7);
  n1++; 
  EXTI_ClearITPendingBit(EXTI_IT_Pin2);
}

//Button 3
INTERRUPT_HANDLER(EXTI1_IRQHandler, EXTI1_IRQn)
{
  GPIO_SetBits(GPIOE, GPIO_Pin_7);
  //delay_10us(20);
  FLASH_ProgramWord(0x1004, n1);
  GPIO_ResetBits(GPIOE, GPIO_Pin_7);
  delay_10us(20);
  GPIO_SetBits(GPIOE, GPIO_Pin_7);
  FLASH_ReadByte(0x1000);
  FLASH_ReadByte(0x1001);
  FLASH_ReadByte(0x1002);
  FLASH_ReadByte(0x1003);
  GPIO_ResetBits(GPIOE, GPIO_Pin_7);
  
  send_int(n0);
  send_int(n1);
  
  EXTI_ClearITPendingBit(EXTI_IT_Pin1);
}
*/
//
/*
INTERRUPT_HANDLER(TIM2_handler,ITC_IRQ_TIM2_OVF)
{
GPIO_WriteLow(GPIOB, GPIO_PIN_7);
  delay_ms(50);
  GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
}


INTERRUPT_HANDLER(USART_IT_TXE_handler,USART1_TX_IRQn)
{
  
}

void send_int(uint16_t data)
{
  //---------------------------------------------------------------------------------------
  uint8_t dat[5]={0};
  for (uint8_t i=0;i<5;i++)
  {
    //---------------------------------------------------------------------------------------
    dat[i]=data%10;
    data=data/10;
    HELLO[i] = dat[4-i] + '0';
    //---------------------------------------------------------------------------------------
  };
  //---------------------------------------------------------------------------------------
  UART_send_str(byteNum);
  //---------------------------------------------------------------------------------------
};

void UART_send_str(uint8_t * str){
  uint16_t i = 0;
  
  while(str[i] != 0)
  {
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
    {
    }
    USART_SendData8(USART1,str[i++]);
  }
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
  {
  }
  USART_SendData8(USART1,13);
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
  {
  }
  USART_SendData8(USART1,10);
}

void UART_send_buf(uint8_t * buf, uint8_t len){
    uint16_t i = 0;
    
    for(i = 0; i < len; i++){
      while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
      {
      }
      USART_SendData8(USART1,buf[i]);
    }
}
*/