#include <stm8s.h>
#include <stm8s_gpio.h>
#include <stm8s_clk.h>
#include <stm8s_tim2.h>
#include <stdlib.h>

#include "mirror.h"
#include "beep.h"
#include "delay.h"
#include "led_driver.h"
#include "eemem.h"

// Остчеты времени
volatile uint32_t tim_millis_counter = 0;
// Состояние экрана
uint8_t led_active = 1;

uint8_t update_temp = 0;

void show_temp(uint8_t num, int val, uint8_t minus) {
    uint8_t dec = val / 10;
    uint8_t smdec = val % 10;
    
    if(dec) {
        lcd_set_digit(num, 1, dec, FALSE);
    }
    
    if(minus)
        lcd_set_digit(num, dec ? 0 : 1, '-', FALSE);
    
    lcd_set_digit(num, 2, smdec, TRUE);
    lcd_set_digit(num, 3, 'c', FALSE);
}

void update_leds() {
    uint8_t minus = 0;
    int t1 = 0, t2 = 0;
    
    t1 = GetTemperature(0, &minus);
    show_temp(0, t1, minus);
    t2 = GetTemperature(1, &minus);
    show_temp(1, t2, minus);
}

// Выключить индикаторы
void deactivate_leds() {
    if(led_active) {
        lcd_shutdown(0, SET);
        lcd_shutdown(1, SET);
        led_active = 0;
    }
}

// Включить индикаторы
void activate_leds() {
    if(!led_active) {
        lcd_shutdown(0, RESET);
        lcd_set_intensity(0, eemem_get_intensity());
        lcd_shutdown(1, RESET);
        lcd_set_intensity(1, eemem_get_intensity());
        led_active = 1;
        tim_millis_counter = 0;
    }
}

void init_tim2() {
    /* Init TIMER 2 */
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
    
    /* Init TIMER 4 prescaler: 2M/2^4 = 125K / 1000 = 125 ARR для срабатываний в 1Гц */
    TIM2_TimeBaseInit(TIM2_PRESCALER_128, 125);
    
    /* Counter value: 2, to compensate the initialization of TIMER*/
   TIM2_SetCounter(0);
    
   /* Настройка прерывания по таймеру */
   TIM2_ITConfig (TIM2_IT_UPDATE, ENABLE);
   
    /* clear update flag */
    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
    
    /* Enable Counter */
    TIM2_Cmd(ENABLE);
}

void TIM2_UPD_Handler() {
    // Проверка на гашение экрана 10 сек
    ++tim_millis_counter;
    if(tim_millis_counter > 20000 && led_active)
        deactivate_leds();
    
    if(tim_millis_counter % 1000 == 0) {
        // Обновить значение температур
        update_temp = 1;
    }
}

// Сброс таймера для обработки интерфейса
void tim_reset() {
    /* Counter value: 2, to compensate the initialization of TIMER*/
    TIM2_SetCounter(0);
}

// Остановка таймера для обработки интерфейса
void tim_stop() {
    /* Disable Counter */
    TIM2_Cmd(DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
}

// Время в миллисекундах сначала старта таймера
uint16_t tim_millis() {
  return tim_millis_counter;
}

// Первичная настройка
void setup() {    
    lcd_init(0);
    lcd_shutdown(0, RESET);
    lcd_set_intensity(0, eemem_get_intensity());
    lcd_clear(0);
    
    lcd_init(1);
    lcd_shutdown(1, RESET);
    lcd_set_intensity(1, eemem_get_intensity());
    lcd_clear(1);
    
    // Настроить счетчик 500 мс (можно чаще)
    init_tim2();
    
    update_leds();
    
    beep_key();
}

void read_buttons() {
    // Нажата кнопка "-"
    if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) == RESET) {
        delay_ms(50);
        if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) == RESET) {
           beep_key();
           activate_leds();
           
           if(led_active) {
               eemem_set_intensity(eemem_get_intensity() - 1);
               lcd_set_intensity(0, eemem_get_intensity());
               lcd_set_intensity(1, eemem_get_intensity());
           }
           
           // Ждем пока отпустят
           while(GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) == RESET);
        }
    }
    
    // Нажата кнопка "+"
    if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_3) == RESET) {
        delay_ms(50);
        if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_3) == RESET) {
           beep_key();
           activate_leds();
           
           if(led_active) {
                eemem_set_intensity(eemem_get_intensity() + 1);
                lcd_set_intensity(0, eemem_get_intensity());
                lcd_set_intensity(1, eemem_get_intensity());
           }
           // Ждем пока отпустят
           while(GPIO_ReadInputPin(GPIOD, GPIO_PIN_3) == RESET);
        }
    }
    
    // Нажата кнопка "PWR"
    if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_3) == RESET) {
        delay_ms(50);
        if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_3) == RESET) {
           beep_key();
           if(!led_active)
               activate_leds();
           else
               deactivate_leds();
           
           // Ждем пока отпустят
           while(GPIO_ReadInputPin(GPIOC, GPIO_PIN_3) == RESET);
        }
    }
}

void loop() {
    // Необходимо обновить температуру
    if(update_temp) {
        update_leds();
        update_temp = 0;
    }
}
