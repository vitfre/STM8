#ifndef _DS18B20_H_
#define _DS18B20_H_

#define THERM_PORT GPIOB
#define THERM_PIN  GPIO_PIN_5

#define THERM_INPUT_MODE()  THERM_PORT->DDR &= ~THERM_PIN
#define THERM_OUTPUT_MODE() THERM_PORT->DDR |=  THERM_PIN
#define THERM_LOW()         THERM_PORT->ODR &= (uint8_t)(~THERM_PIN)
#define THERM_HIGH()        THERM_PORT->ODR |= (uint8_t)THERM_PIN

#define THERM1_PORT GPIOA
#define THERM1_PIN  GPIO_PIN_1

#define THERM1_INPUT_MODE()  THERM1_PORT->DDR &= ~THERM1_PIN
#define THERM1_OUTPUT_MODE() THERM1_PORT->DDR |=  THERM1_PIN
#define THERM1_LOW()         THERM1_PORT->ODR &= (uint8_t)(~THERM1_PIN)
#define THERM1_HIGH()        THERM1_PORT->ODR |= (uint8_t)THERM1_PIN

#define THERM_READ(NUM)              NUM != 0 ? (THERM1_PORT->IDR & (volatile uint8_t)THERM1_PIN) : (THERM_PORT->IDR & (volatile uint8_t)THERM_PIN)

// ???????
#define THERM_CMD_CONVERTTEMP   0x44
#define THERM_CMD_RSCRATCHPAD   0xBE
#define THERM_CMD_WSCRATCHPAD   0x4E
#define THERM_CMD_CPYSCRATCHPAD 0x48
#define THERM_CMD_RECEEPROM     0xB8
#define THERM_CMD_RPWRSUPPLY    0xB4
#define THERM_CMD_SEARCHROM     0xF0
#define THERM_CMD_READROM       0x33
#define THERM_CMD_MATCHROM      0x55
#define THERM_CMD_SKIPROM       0xCC
#define THERM_CMD_ALARMSEARCH   0xEC
 
#define THERM_DECIMAL_STEPS_12BIT 625 //.0625

// Режим работы
typedef enum
{
  THERM_MODE_9BIT  = 0x1F,
  THERM_MODE_10BIT = 0x3F,
  THERM_MODE_11BIT = 0x5F,
  THERM_MODE_12BIT = 0x7F
} THERM_MODE;

int GetTemperature(uint8_t num, uint8_t *minus);

#endif /* _DS18B20_H_ */
