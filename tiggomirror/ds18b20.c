#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_beep.h>

#include "ds18b20.h"
#include "delay.h"

int iCurrentTemp = 0;

//static inline void x_delay(uint16_t i)
//{
//  while (--i) nop();
//}
// 
////#define delay_1us()   _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
#define delay_1us()   nop();
//#define delay_15us()  x_delay(2)
//#define delay_45us()  x_delay(12)
//#define delay_60us()  x_delay(17)
//#define delay_480us() x_delay(110)

/**
  * @brief Сброс термодатчика
  * @par
  * Параметры отсутствуют
  * @retval
  * false - Неисправность; true - Норма
*/
FlagStatus therm_reset(uint8_t num)
{
  unsigned char i = 0xFF;
 
  if(num) {
      THERM1_OUTPUT_MODE();
      THERM1_LOW();
  } else {
      THERM_OUTPUT_MODE();
      THERM_LOW();
  }
 
  _delay_15us(32);//delay_480us();
 
  if(num)
      THERM1_INPUT_MODE();
  else
      THERM_INPUT_MODE();
 
  _delay_15us(4);//delay_60us();
 
  i = THERM_READ(num);
 
  _delay_15us(32);//delay_480us();
  // 0 означает правильный сброс, 1 - ошибка
  return (0 == i) ? SET : RESET;
}
 
/**
  * @brief Запись бита
  * @param[in] bBit бит
  * @retval
  * Возвращаемое значение отсутствует
*/
void therm_write_bit(uint8_t num, FlagStatus bBit)
{
  if(num) {
      THERM1_OUTPUT_MODE();
      THERM1_LOW();
  } else {
      THERM_OUTPUT_MODE();
      THERM_LOW();
  }
 
  delay_1us();
 
  if (bBit)
  {
      if(num)
        THERM1_INPUT_MODE();
      else
        THERM_INPUT_MODE();  
  }
   
  _delay_15us(4);//delay_60us();
   
  if(num)
    THERM1_INPUT_MODE();
  else
    THERM_INPUT_MODE(); 
}
 
/**
  * @brief Чтение бита
  * @par
  * Параметры отсутствуют
  * @retval
  * Значение бита.
*/
FlagStatus therm_read_bit(uint8_t num)
{
  FlagStatus bBit = RESET;
 
  if(num) {
      THERM1_OUTPUT_MODE();
      THERM1_LOW();
  } else {
      THERM_OUTPUT_MODE();
      THERM_LOW();
  }
 
  delay_1us();
 
  if(num)
    THERM1_INPUT_MODE();
  else
    THERM_INPUT_MODE();  
 
  _delay_15us(1);//delay_15us();
   
  if (THERM_READ(num))
  {
    bBit = SET;
  }
 
  _delay_15us(3);//delay_45us();
 
  return bBit;
}
 
/**
  * @brief Чтение байта
  * @par
  * Параметры отсутствуют
  * @retval
  * Значение байта.
*/
static unsigned char therm_read_byte(uint8_t num)
{
  unsigned char i = 8;
  unsigned char n = 0;
  while (i--)
  {   
    // Сдвинуть на одну позицию вправо и сохранить значение бита
    n >>= 1;
    n |= (therm_read_bit(num) << 7);
  }
  return n;
}
 
/**
  * @brief Запись байта
  * @param[in] byte байт
  * @retval
  * Возвращаемое значение отсутствует
*/
void therm_write_byte(uint8_t num, unsigned char byte)
{
  unsigned char i = 8;
 
  while (i--)
  {
    // Записать текущий бит и сдвинуть на 1 позицию вправо
    // для доступа к следующему биту
    therm_write_bit(num, byte & 1);
    byte >>= 1;
  } 
}
 
/**
  * @brief Установить режим работы термодатчика
  * @param[in] mode Режим работы
  * @retval
  * Возвращаемое значение отсутствует
*/
void therm_init_mode(uint8_t num, THERM_MODE mode)
{
  therm_reset(num);
  therm_write_byte(num, THERM_CMD_SKIPROM);
  therm_write_byte(num, THERM_CMD_WSCRATCHPAD);
  therm_write_byte(num, 0);
  therm_write_byte(num, 0);
  therm_write_byte(num, mode);
}

/*void therm_search() {
  char iResult = 0;
  uint8_t id[8];
    // Сброс и сразу переход к преобразованию температуры
  iResult = therm_reset();
  therm_write_byte(THERM_CMD_SEARCHROM);

  for(uint8_t i = 0; i < 64; ++i) {
      therm_read_bit()
      therm_read_bit()
  }
  
  return;
}*/

/**
  * @brief Чтение температуры.
  * @par
  * Параметры отсутствуют
  * @retval
  * Температура.
*/
int GetTemperature(uint8_t num, uint8_t *minus)
{
  uint8_t iResult = 0;
  unsigned char temperature[2] = {0, 0};
  unsigned char digit;
  short iReadLimit;
  
  // Запрет прерываний во время опроса датчика
  disableInterrupts();
  
  // Сброс и сразу переход к преобразованию температуры
  iResult = therm_reset(num);
  therm_write_byte(num, THERM_CMD_SKIPROM);
  therm_write_byte(num, THERM_CMD_CONVERTTEMP);
   
  // Ожидание завершения преобразования
  /*iReadLimit = 20;
  while (!therm_read_bit(num) && (--iReadLimit > 0)) { nop(); }*/
  _delay_15us(32);
   
  // Сброс и чтение байт температуры
  therm_reset(num);
  therm_write_byte(num, THERM_CMD_SKIPROM);
  therm_write_byte(num, THERM_CMD_RSCRATCHPAD); 
  temperature[0] = therm_read_byte(num);
  temperature[1] = therm_read_byte(num);
 
  // Разрешить прерывания
  enableInterrupts(); 
   
  digit = 0;
 
  digit  = (  temperature[0]         >> 4 ) & 0x0F; 
  digit |= ( (temperature[1] & 0x0F) << 4 ) & 0xF0; 
 
  // Отрицательная температура - инвертировать и прибавить 1
  if (temperature[1] & 0x80)
  {
    iResult = ~digit;
    ++iResult;
    *minus = 1;
  } else {
    iResult = digit;
    *minus = 0;
  }
   
  iCurrentTemp = iResult;
   
  return iResult;
}
