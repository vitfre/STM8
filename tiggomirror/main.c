
#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_beep.h>

#include <string.h>

#include "platform_config.h"
#include "mirror.h"
#include "beep.h"
#include "delay.h"
#include "led_driver.h"
#include "ds18b20.h"

/* Private variables ---------------------------------------------------------*/

extern void setup();

/* Private function prototypes -----------------------------------------------*/
void init_mcu();

// Инициализция системы тактирования
void init_clk() {
    // RM0016: At startup the system clock source is automatically selected as HSI RC 
    // clock output divided 8 (HSI/8).
    // Соответственно после запуска процессор работает автоматом на
    //// SYSCLK = HSI / 8 = 16МГц / 8 = 2МГц
    // SYSCLK = HSI / 8 = 16МГц / 1 = 16МГц
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    CLK_HSICmd(ENABLE);
    while (((CLK->ICKR)& 0x02)!=0x02);
    
    CLK_LSICmd(ENABLE); // Включить LSI
    while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY) != SET);

    // Переключиться на HSI    
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, ENABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
    CLK_ClockSwitchCmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == 0);
}

// Инициализция портов ввода и вывода
void init_gpio() {
    /* ---------------------------------------------------------------------------
    * Настройка порта A
    * -------------------------------------------------------------------------*/
    GPIO_DeInit(GPIOA);
    //GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);    // Читать д1
    GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);    // Читать д1
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);    // Разрешить индикатор 1
    
    GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
    GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
    
  /* ---------------------------------------------------------------------------
    * Настройка порта B
    * -------------------------------------------------------------------------*/
    GPIO_DeInit(GPIOB);
    /*GPIO_Init(GPIOB, RED_LED_PIN, GPIO_MODE_OUT_OD_LOW_FAST );   // Светоиод красный
    GPIO_Init(GPIOB, GREEN_LED_PIN, GPIO_MODE_OUT_OD_LOW_FAST ); // Светоиод зеленый
    
    GPIO_WriteHigh(GPIOB, GREEN_LED_PIN);
    GPIO_WriteHigh(GPIOB, GREEN_LED_PIN);*/
    
    /* ---------------------------------------------------------------------------
    * Настройка порта С
    * -------------------------------------------------------------------------*/
    GPIO_DeInit(GPIOC);
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT );       // Кнопка PWR
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);   // Разрешить индикатор 2
    
    GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
    /* ---------------------------------------------------------------------------
    * Настройка порта D
    * -------------------------------------------------------------------------*/
    GPIO_DeInit(GPIOD);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);   // Кнопка "-"
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);   // Кнопка "+"
}

void init_spi() {
    // Сброс примопередатчика
    SPI_DeInit();
    
    // Включить тактирование
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE);
    
    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_8, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_1LINE_TX, SPI_NSS_SOFT, 0);
    SPI_Cmd(ENABLE);
}

// Инициализция процессора
void init_mcu() {
    // Тактирование
    init_clk();
    // Порты ввода вывода
    init_gpio();
    // Инициализировать SPI
    init_spi();
    
    // Инициализация пишалки
    BEEP_DeInit();
    //BEEP_LSICalibrationConfig(2000000);
    
}

int main( void )
{   
    // Начальная инициализация
    init_mcu();
    // Разрешить прерывания
    __enable_interrupt();
    
    // Настройка после загрузки
    setup();
    
    while(1) {  
//        // Запрет прерываний во время опроса датчика
//      disableInterrupts();
//      GPIO_WriteLow(GPIOA, GPIO_PIN_2);
//      GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
//      _delay_15us(3);
//      GPIO_WriteLow(GPIOA, GPIO_PIN_2);
//            // Разрешить прерывания
//        __enable_interrupt();
        
        // Обработчики кнопок
        read_buttons();
        // Основной цкил
        loop();
    }
    
    /* return 0; */
}

// Для реализации printf через USART
/*int putchar(int ch)
{
    uart_putc(ch);
    
    return ch;
}*/

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif