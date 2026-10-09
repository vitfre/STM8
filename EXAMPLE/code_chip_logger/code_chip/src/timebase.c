#include "timebase.h"
#include "stm8s.h"
#include "init.h"


#define TIM4_OVR_UIF_vector                  0x19

volatile static uint16_t delay_timer = 0;
volatile static uint16_t uart_timer = 0;
volatile static uint16_t alarm_timer = 0;

volatile uint16_t sens_counter = 0;
volatile uint16_t mes_time = 0;//сюда помещаетс€ измеренное значение периода

volatile uint8_t sens_flag = 0;//дл€ фиксации фронтов
volatile uint8_t updatae_flag = 0;


#pragma vector = TIM4_OVR_UIF_vector
__interrupt void base_timer(void)
{
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
  if (delay_timer != 0) {delay_timer--;}
  if (uart_timer != 0) {uart_timer--;}
  if (alarm_timer != 0) {alarm_timer--;}
  if (sens_counter < 0xFFF0) {sens_counter++;}
  
  if (GPIO_ReadInputPin(SENSOR_PORT,SENSOR_PIN) == RESET)
  {
    //вспышка светодиода на счетчике
    if (sens_flag == 0)
    {
      mes_time = sens_counter;
      sens_counter = 0;
      updatae_flag = 1;
    }
    sens_flag = 1;
    
  }
  else
  {
    sens_flag = 0;
  }
  
}

//задать задержку в милисекундах
void set_delay_timer(uint16_t value)
{
  delay_timer = value;
}

//задать задержку в милисекундах
void set_alarm_timer(uint16_t value)
{
  alarm_timer = value;
}




//задать задержку в милисекундах
void set_uart_timer(uint16_t value)
{
  uart_timer = value;
}


//*****************************************************************************


//проверка
bool delay_timer_elapsed(void)
{
  asm("nop");
  
  if (delay_timer == 0) 
  {
    asm("nop");
    return TRUE;
  } 
  else 
  {
    asm("nop");
    return FALSE;
  }
  
  
}



//проверка
bool uart_timer_elapsed(void)
{
  if (uart_timer == 0) {return TRUE;} else {return FALSE;}
}

//проверка
bool alarm_timer_elapsed(void)
{
  if (alarm_timer == 0) {return TRUE;} else {return FALSE;}
}


void delay(uint16_t time)
{
  set_delay_timer(time);
  while (delay_timer_elapsed() == FALSE)
  {
    asm("nop");
  }
}



