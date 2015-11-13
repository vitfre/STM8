#include <stm8s.h>
#include <stm8s_beep.h>

#include "platform_config.h"
#include "delay.h"


void beep_low(uint16_t duration) {
    BEEP_Init(BEEP_FREQUENCY_1KHZ);
    BEEP_Cmd(ENABLE);
    delay_ms(duration);  
    BEEP_Cmd(DISABLE);
}

void beep_medium(uint16_t duration) {
    BEEP_Init(BEEP_FREQUENCY_2KHZ);
    BEEP_Cmd(ENABLE);
    delay_ms(duration);  
    BEEP_Cmd(DISABLE);
}

void beep_high(uint16_t duration) {
    BEEP_Init(BEEP_FREQUENCY_4KHZ);
    BEEP_Cmd(ENABLE);
    delay_ms(duration);  
    BEEP_Cmd(DISABLE);
}


// Нажатие клавиши
void beep_key() {
    beep_high(50);  
}

// Блокировка
void beep_lock() {
    beep_low(300);
}

// Разблокировка
void beep_unlock() {
    beep_low(200);
    delay_ms(200);
    beep_low(200);
}

// Ошибка
void beep_error() {
    beep_low(100);
    delay_ms(100);
    beep_low(100);
    delay_ms(100);
    beep_low(100);
}

// Сброс
void beep_reset() {
    beep_low(300);
    delay_ms(300);
    beep_low(300);
    delay_ms(300);
}