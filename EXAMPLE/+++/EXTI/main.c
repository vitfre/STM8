//#include "iostm8l152c6.h"

#include "STM8L15x.h"
#include "STM8L15x_clk.h"
#include "STM8L15x_gpio.h"
#include "STM8L15x_exti.h"
#include "STM8L15x_itc.h"
#include "stm8l15x_usart.h"
#include "delay.h"

unsigned long i=0;
unsigned long u=1;

unsigned char HELLO[16]={0};
unsigned char *byteNum = HELLO; // Указатель на передаваемый байт.


/* Private function prototypes -----------------------------------------------*/
void UART_send_buf(uint8_t * buf, uint8_t len);
void UART_send_str(uint8_t * str);
void send_int(uint16_t);

//Еще одна кнопка на C2
INTERRUPT_HANDLER(EXTI0_IRQHandler, 8)
{
  GPIO_SetBits(GPIOE, GPIO_Pin_7);
  delay_10us(20);
  GPIO_ResetBits(GPIOE, GPIO_Pin_7);
  u++; 
  EXTI_ClearITPendingBit(EXTI_IT_Pin0);
}

//User button
INTERRUPT_HANDLER(EXTI1_IRQHandler, 9)
{
  //for(i=0; i<u; i++)
  //{
    //GPIO_SetBits(GPIOC, GPIO_Pin_7);
    //delay_ms(10);
    //GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    //delay_ms(50);
  //};
  send_int(u);
  EXTI_ClearITPendingBit(EXTI_IT_Pin1);
}

__interrupt void UART1_TXE(void)
{

}

__interrupt void USART1_RXE(void)
{
          //USART1_DR=USART1_DR; //Отправляем тоже, что и приняли (эхо)
}



void CLK_Init(void)
{
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1); //Выключаем предделитель. Теперь МК работает на частоте 16МГц.
  
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE); //Подаем тактовый сигнал на USART1.
  //CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE); //Подаем тактовый сигнал на LCD.
  //CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE); //Подаем такт на RTC
  //CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1); //Убираем прескллер RTC
};

void UART_Init(void)
{
  
  //PC_DDR|=0<<2; //PC2 RX USART1 receive (вход)
  //PC_DDR|=1<<3; //PC3 TX USART1 transmit (выход)
  GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);
  GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Slow);
  //CLK_PCKENR1_bit.PCKEN15 = 1;
  //UART1_CR2_REN=UART1_CR2_TEN=1; // Разрешить выводы TX, RX.
  //UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08; // BaudRate = 115200.
  //__enable_interrupt(); //Разрешаем прерывания.
  //UART1_CR2_TIEN=1; // Разрешить прерывание по TXE. Начало передачи.
  // UART1 CONFIGURATION
USART_DeInit(USART1);
USART_Init(USART1, (uint32_t) 9200, USART_WordLength_8b, USART_StopBits_1,USART_Parity_No, USART_Mode_Tx);
USART_Cmd(USART1,ENABLE);
};

void GP_IO_Init(void)
{
  //Настраиваем синий светодиод
   GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_High_Slow);
 //GPIOC->DDR |= GPIO_Pin_7; //На выход..
 //GPIOC->CR1 |= GPIO_Pin_7; //Push-pull режим
 
 //Настраиваем зеленый светодиод
 GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);
 //GPIOE->DDR |= GPIO_Pin_7; //На выход
 //GPIOE->CR1 |= GPIO_Pin_7; //Push-pull режим 
 
 //Настраиваем кнопки
 GPIO_Init(GPIOC,GPIO_Pin_1,GPIO_Mode_In_PU_IT);
  GPIO_Init(GPIOE,GPIO_Pin_0,GPIO_Mode_In_PU_IT);
 //GPIOC->CR1 |= GPIO_Pin_1 | GPIO_Pin_2; //Включаем подтяжку к питанию
 //GPIOC->CR2 |= GPIO_Pin_1 | GPIO_Pin_2; //Разрешаем прерывания
 
 delay_ms(10);
 
  //Настраиваем прерывания
 EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Falling); //Для 1го пина по спаду напряжения
 EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling); //Так-же для 2го.
 
 ITC_SetSoftwarePriority(EXTI0_IRQn, ITC_PriorityLevel_1); //Настраиваем приоритет для
 //прерывания от 2го пина. Он будет ниже, чем для 1го
};


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

int main( void )
{
  
  CLK_Init();
  UART_Init();
  GP_IO_Init();
 
 for (uint8_t i=0;i<5;i++)
  {
    //---------------------------------------------------------------------------------------
    HELLO[i] = i;
    //---------------------------------------------------------------------------------------
  };

 
 enableInterrupts(); //Разрешаем прерывания.
 
 
 
 
 while(1)
 {
  //send_int(u);
  //UART_send_str(byteNum);
  delay_ms(2500); 
 }
 
 //return 0;
}





void UART_send_str(uint8_t * str){
  int i = 0;
  
  while(str[i] != 0)
  {
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
    {
    }
    USART_SendData8(USART1,str[i++]);
  }
}

void UART_send_buf(uint8_t * buf, uint8_t len){
    int i = 0;
    
    for(i = 0; i < len; i++){
      while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET)
      {
      }
      USART_SendData8(USART1,buf[i]);
    }
}
