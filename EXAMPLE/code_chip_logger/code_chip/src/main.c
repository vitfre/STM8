//chip is stm8s105s6
//iar compiller
//by iliasam

#include "init.h"
#include "stm8s.h"
#include "timebase.h"
#include "handler_assert_parameter_error.h"


#define MSG_LNG 6
#define ECONST (uint32_t)2000 // имп/(квт-ч)
//#define CONST2 (uint32_t)(3600*1000*1000 / ECONST) //3600сек * 1000 Вт * 1000 мсек / ECONST
#define CONST2 (uint32_t)(1800000)
#define ALARM_POWER (uint16_t)4700 //Вт

uint8_t uart_buf[MSG_LNG] = {65,67,0,0,13,10};

extern volatile uint8_t updatae_flag;
extern volatile uint16_t mes_time;//сюда помещается измеренное значение периода

void uart_send_byte(uint8_t data);
void uart_send_msg(void);
uint16_t find_power(uint16_t time);
void prepare_data(uint16_t power);


void main( void )
{
  uint16_t power;
  
  enableInterrupts();
  init_all();
  
  
  
  while (1) 
  { 
    if (updatae_flag == 1)
    {
      power = find_power(mes_time);
      if ((power > ALARM_POWER) && (alarm_timer_elapsed()) ) {
        GPIO_WriteHigh(ALARM_PORT,ALARM_PIN);//включить звонок
        set_alarm_timer(3000);
      } 
      else 
      {
        //выключить звонок
        if (alarm_timer_elapsed())
        {
          GPIO_WriteLow(ALARM_PORT,ALARM_PIN);
        }
        
      }
    }
      
    if (uart_timer_elapsed())
    {
      set_uart_timer(10000);
      prepare_data(power);
      uart_send_msg();
    }
    
  IWDG_ReloadCounter();
  
  }//end while
}

//передает 1 байт
void uart_send_byte(uint8_t data)
{
  UART1_SendData8(data);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}

//передает посылку
void uart_send_msg(void)
{
  uint8_t i;
  for (i=0;i<MSG_LNG;i++)
  {
    uart_send_byte(uart_buf[i]);
  }
}

void prepare_data(uint16_t power)
{
  uint16_t tpower;
  if (updatae_flag == 1)//за время с последней передачи появились новые данные
  {
    tpower = power;
    updatae_flag = 0;
  }
  else
  {
    tpower = 0;
  }
  
  
  uart_buf[2] = (uint8_t)(tpower >> 8);
  uart_buf[3] = (uint8_t)(tpower & 0x00FF);
}

//возвращает мощность в Вт (time - период в мс)
uint16_t find_power(uint16_t time)
{
  uint16_t power = 0;
  if (time > 200) //9000 Вт
  {
    power = (uint16_t)((uint32_t)CONST2 / (uint32_t)time);
  }
  
  return power;
}



