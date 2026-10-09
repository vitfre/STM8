/**
  ******************************************************************************
  * @file    delay.c
  * @author  Microcontroller Division
  * @version V1.2.0
  * @date    09/2010
  * @brief   delay functions
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/

#include "stm8s_clk.h"
#include "stm8s_tim2.h"
#include "stm8s_tim3.h"
#include "stm8s_tim4.h"

volatile uint32_t rtc_uptime_counter = 0;

/**
  * @brief  delay for some time in ms unit
  * @caller auto_test
  * @param  n_ms is how many ms of time to delay
  * @retval None
  */
void    delay_ms(u16 n_ms)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);

  /* Init TIMER 4 prescaler: 2M/2^3 = 250K */
  /* Init TIMER 4 prescaler: 16M/2^6 = 250K */
  TIM4->PSCR = 6;

/* HSI div by 1 --> Auto-Reload value: 2M / 8  = 250К / 1k = 250*/
  TIM4->ARR = 250;
  
/* Counter value: 2, to compensate the initialization of TIMER*/
  TIM4->CNTR = 2;

/* clear update flag */
  TIM4->SR1 &= ~TIM4_SR1_UIF;

/* Enable Counter */
  TIM4->CR1 |= TIM4_CR1_CEN;

  while(n_ms--)
  {
    while((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
  }

/* Disable Counter */
  TIM4->CR1 &= ~TIM4_CR1_CEN;
}

/**
  * @brief  delay for some time in 10us unit(partial accurate)
  * @caller auto_test
  * @param n_10us is how many 10us of time to delay
  * @retval None
  */
void delay_10us(u16 n_10us)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);

/* prescaler: / (8^0) = /1 */
  TIM4->PSCR = 0;

/* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 8 = 2M, 2M / 100k = 20 */
  TIM4->ARR = 20;
 
/* Counter value: 10, to compensate the initialization of TIMER */
  TIM4->CNTR = 10;

/* clear update flag */
  TIM4->SR1 &= ~TIM4_SR1_UIF;

/* Enable Counter */
  TIM4->CR1 |= TIM4_CR1_CEN;

  while(n_10us--)
  {
    while((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
  }

/* Disable Counter */
  TIM4->CR1 &= ~TIM4_CR1_CEN;
 CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);

}

/**
  * @brief  delay for some time in 10us unit(partial accurate)
  * @caller auto_test
  * @param n_10us is how many 10us of time to delay
  * @retval None
  */
void _delay_15us(u16 n_15us)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);

/* prescaler: / (8^0) = /1 */
   TIM4->PSCR = 3;

/* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 8 = 2M, 2M / 100k = 20 */
  /* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 1 = 16M, 16M / 100k = 160 */
  TIM4->ARR = 29;
 
/* Counter value: 15, to compensate the initialization of TIMER */
  TIM4->CNTR = 29;

/* clear update flag */
  TIM4->SR1 &= ~TIM4_SR1_UIF;

/* Enable Counter */
  TIM4->CR1 |= TIM4_CR1_CEN;

  while(n_15us--)
  {
    while((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
  }

/* Disable Counter */
  TIM4->CR1 &= ~TIM4_CR1_CEN;
 CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}

//void TIM2_UPD_Handler() {
//    ++tim_millis_counter;
//}

void RTC_AWU_Handler() {
    ++rtc_uptime_counter;
}

//// Запуск базового таймера для обработки интерфейса
//void tim_start() {
//    /* Init TIMER 2 */
//    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
//    
//    /* Init TIMER 4 prescaler: 2M/2^4 = 125K / 1000 = 125 ARR для срабатываний в 1Гц */
//    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 125);
//    
//    /* Counter value: 2, to compensate the initialization of TIMER*/
//   TIM2_SetCounter(0);
//    
//   /* Настройка прерывания по таймеру */
//   TIM2_ITConfig (TIM2_IT_UPDATE, ENABLE);
//   
//    /* clear update flag */
//    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
//    
//    /* Enable Counter */
//    TIM2_Cmd(ENABLE);
//}
//
//// Сброс таймера для обработки интерфейса
//void tim_reset() {
//    /* Counter value: 2, to compensate the initialization of TIMER*/
//    TIM2_SetCounter(0);
//}
//
//// Остановка таймера для обработки интерфейса
//void tim_stop() {
//    /* Disable Counter */
//    TIM2_Cmd(DISABLE);
//    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
//}
//
//// Время в миллисекундах сначала старта таймера
//uint16_t tim_millis() {
//  return tim_millis_counter;
//}

// Врем в секундах с начала старта
uint32_t rtc_uptime() {
  return rtc_uptime_counter;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
