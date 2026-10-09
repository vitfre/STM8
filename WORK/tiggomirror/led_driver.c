#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_beep.h>

#include "led_driver.h"

/*
 * Segments to be switched on for characters and digits on
 * 7-Segment Displays
 */

const static uint8_t charTable [] = {
    
    0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,
    
    0x7F,0x7B,0x77,0x1F,0x0D,0x3D,0x4F,0x47,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x00,
    
    0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,
    
    0x7F,0x7B,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x00,
    
    0x37,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,
    
    0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
    
    0x00,0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x00,
    
    0x37,0x00,0x00,0x00,0x0E,0x00,0x15,0x1D,
    
    0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void lcd_spi_transfer(uint8_t data) {
    SPI_SendData(data);
    while(SPI_GetFlagStatus(SPI_FLAG_BSY) == SET);
}


void lcd_send(uint8_t device, uint8_t opcode, uint8_t data) {
    // Начать транзакцию
    CS_LOW(device);
    
    // Передать код команды
    lcd_spi_transfer(opcode);
    // Передать данные
    lcd_spi_transfer(data);
    
    // Зафиксировать данные
    CS_HIGH(device);
}

void lcd_init(uint8_t device) {
    lcd_send(device, LCD_OP_DISAPLYTEST, 0);
    // Установить максимальное значение опроса
    lcd_set_scan_limit(device, 7);
    // Установить режим декодирования
    lcd_send(device, LCD_OP_DECODEMODE, 0);
    // Очистить экран
    lcd_clear(device);
    // Сброс экрана
    lcd_shutdown(device, SET);
}

void lcd_set_scan_limit(uint8_t device, uint8_t level) {
    if(level >= 0 && level < 8)
        
        lcd_send(device, LCD_OP_SCANLIMIT, level);
}

void lcd_clear(uint8_t device){
    for(int i = 0; i < 8; ++i) {       
        lcd_send(device, i + 1, 0);
    
    }
}

void lcd_shutdown(uint8_t device, uint8_t mode) {
    if(mode)
        lcd_send(device, LCD_OP_SHUTDOWN, 0);
    else
        lcd_send(device, LCD_OP_SHUTDOWN, 1);
}

void lcd_set_intensity(uint8_t device, uint8_t intensity){
    if(intensity >= 0 && intensity < 16)	
        
        lcd_send(device, LCD_OP_INETNSITY, intensity);
}

void lcd_set_digit(uint8_t device, uint8_t digit, uint8_t value, uint8_t dp) {
    uint8_t v;
    
    if(digit < 0 || digit > 7)
        return;
    
    v = charTable[value];
    
    if(dp) // Точка в сегменте
        v |= 0x80;
    
    lcd_send(device, digit + 1, v);
}
