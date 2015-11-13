/**
  ******************************************************************************
  * @file    delay.h
  * @author  Microcontroller Division
  * @version V1.2.0
  * @date    09/2010
  * @brief   delay functions header
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


//------------------------------------------------------------------------------
// Function Name : delay_ms
// Description   : delay for some time in ms unit
// Input         : n_ms is how many ms of time to delay
//------------------------------------------------------------------------------
void delay_ms(u16 n_ms) ;


//------------------------------------------------------------------------------
// Function Name : delay_10us
// Description   : delay for some time in 10us unit(partial accurate)
// Input         : n_10us is how many 10us of time to delay
//------------------------------------------------------------------------------
void delay_10us(u16 n_10us);
void _delay_15us(u16 n_15us);

// Запуск базового таймера для обработки интерфейса
void tim_start();

// Сброс таймера для обработки интерфейса
void tim_reset();

// Остановка таймера для обработки интерфейса
void tim_stop();

// Время в миллисекундах сначала старта таймера
uint16_t tim_millis();

// Врем в секундах с начала старта
uint32_t rtc_uptime();

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
