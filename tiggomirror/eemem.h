#ifndef EEMEM_H
#define EEMEM_H

// Макрос преборазования адреса из int в указатель на регистр
#define HWADDR(x)       ((volatile uint8_t *)(x))
#define HWREG8(x)       (*((volatile uint8_t *)(x)))
#define HWREG16(x)      (*((volatile uint16_t *)(x)))
#define HWREG32(x)      (*((volatile uint16_t *)(x)))

// Макрос поиска смещения поля внутри структуры
// Нулевой указатель, чтобы обмануть компилятор для вычисления смещения поля
// внутри структуры карты памяти
#define OFFSETOF(type, member)  ((int)(&(((type *)(0))->member)))

// Базовый адрес начала EEPROM в устройстве
#define EEMEM_BASE_ADDR         0x4000

/**
 * Карта памяти EEPROM для работы с полями и переменными
 */
typedef struct _eemem_map_t {
    uint8_t temp1_delta;        /*< Поправка измерения 1 датчика*/
    uint8_t temp2_delta;        /*< Поправка измерения 2 датчика*/
    uint8_t intensity;          /*< Яркость */
    uint8_t state;              /*< Состояние экрана */
} eemem_map_t;

/**
 * Получение поправки измерения 1 датчика
 */
uint8_t eemem_get_temp1_delta();

/**
 * Записать поправку измерения 1 датчика
 */
void eemem_set_temp1_delta(uint8_t delta);

/**
 * Получение поправки измерения 1 датчика
 */
uint8_t eemem_get_temp2_delta();

/**
 * Записать поправку измерения 1 датчика
 */
void eemem_set_temp2_delta(uint8_t delta);

/**
 * Получение состояния индикаторов
 */
uint8_t eemem_get_state();

/**
 * Записать состояние индикаторов
 */
void eemem_set_state(uint8_t state);

/**
 * Получение состояния индикаторов
 */
uint8_t eemem_get_intensity();

/**
 * Записать состояние индикаторов
 */
void eemem_set_intensity(uint8_t intensity);

#endif  /* EEMEM_H */
