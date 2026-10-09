#include "stm8L15x.h"
#include "stm8L15x_clk.h"
#include "stm8L15x_gpio.h"
#include "LCD.h"


const uint8_t lcd_ram[6] = {0xFF, 0xAF, 0xEB, 0x70, 0x1F, 0x0C};
uint8_t counter;
unsigned long i;


void CLK_Init(void)
{
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1); //Выключаем предделитель. Теперь МК работает на частоте 16МГц.
  CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE); //Подаем тактовый сигнал на LCD.
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE); //Подаем такт на RTC
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1); //Убираем прескллер RTC
};


void LCDs_Init(void)
{
 LCD->CR1 = (3<<1) + (5<<3); //Duty = 1/4, Blink Freq = LCDclk/256
 LCD->CR2 = (6<<1) | LCD_CR2_HD; //Контрастность = 6 (из 7), низкоомный драйвер.
 LCD->FRQ = (2<<4); //LCDclk = 32768/2/(2^1*16) = 512Hz
 //Задействованы все сегменты:
 LCD->PM[0] = 0xFF; 
 LCD->PM[1] = 0xFF;
 LCD->PM[2] = 0xFF;
 LCD->CR3 |= LCD_CR3_LCDEN | 2; //ВКЛ и deadtime = 2 
};

void main( void )
{
  
 CLK_Init();
 LCDs_Init();
  
 GPIOC->CR1 |= GPIO_Pin_1; //Подтяжку на кнопку
 //Настраиваем синий светодиод
 GPIOC->DDR |= GPIO_Pin_7; //На выход..
 GPIOC->CR1 |= GPIO_Pin_7; //Push-pull режим
 GPIOC->ODR ^= GPIO_Pin_7; 
 
 //Настраиваем зеленый светодиод
 GPIOE->DDR |= GPIO_Pin_7; //На выход
 GPIOE->CR1 |= GPIO_Pin_7; //Push-pull режим 
 GPIOE->ODR ^= GPIO_Pin_7;
 
 //Настраиваем кнопки
 GPIOC->CR1 |= GPIO_Pin_1 | GPIO_Pin_2; //Включаем подтяжку к питанию
 GPIOC->CR2 |= GPIO_Pin_1 | GPIO_Pin_2; //Разрешаем прерывания
 
 


 
 

 
 //Перегоняем массив в LCD RAM
 //for (counter=0; counter<6; counter++) LCD->RAM[counter] = lcd_ram[counter]; 
  LCD_Write_String("TEST ");
 for(i=0; i<200000; i++){asm("nop");};
 LCD_Write_String("17:32:59");
 for(i=0; i<100000; i++){asm("nop");};  
   
  
  while(1)
  {
    while ((GPIOC->IDR & GPIO_Pin_1) != 0); //Ждем, пока нажмут кнопку
    LCD->CR1 ^= 0xC0; //Инвертируем биты, отвечающие за мигалку
     GPIOE->ODR ^= GPIO_Pin_7;
    while ((GPIOC->IDR & GPIO_Pin_1) == 0); //Теперь ждем, пока кнопку отпустят
  };  
}
