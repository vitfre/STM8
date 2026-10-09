#include "init.h"
#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s.h"
#include "stm8s_uart2.h"
#include "stm8s_tim4.h"

void init_all(void)
{
  init_gpio();
  init_timers();
  init_uart();
  IWDG_Config();
}




void init_gpio(void)
{
  GPIO_DeInit(GPIOB);
    
  GPIO_Init(ALARM_PORT, ALARM_PIN, GPIO_MODE_OUT_PP_LOW_FAST);//alarm
  GPIO_WriteLow(ALARM_PORT,ALARM_PIN);
    
  GPIO_Init(SENSOR_PORT, SENSOR_PIN, GPIO_MODE_IN_FL_NO_IT);//sensor
  
  GPIO_Init(UART_PORT, UART_PIN, GPIO_MODE_OUT_PP_LOW_FAST);//uart
  
}


void init_timers(void)
{
  //системный таймер
  TIM4_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
  TIM4_TimeBaseInit(TIM4_PRESCALER_16,124);//2M / 16 / 125 = 1000
  TIM4_SetAutoreload(124);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);     
}


void init_uart(void)
{
  UART1_DeInit();
  UART1_Init((uint32_t)1200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);
  UART1_Cmd(ENABLE);
}

void IWDG_Config(void)
{
  IWDG_Enable();
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  IWDG_SetReload(255);
  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  
}