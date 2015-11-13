#ifndef EEMEM_H
#define EEMEM_H

// ������ �������������� ������ �� int � ��������� �� �������
#define HWADDR(x)       ((volatile uint8_t *)(x))
#define HWREG8(x)       (*((volatile uint8_t *)(x)))
#define HWREG16(x)      (*((volatile uint16_t *)(x)))
#define HWREG32(x)      (*((volatile uint16_t *)(x)))

// ������ ������ �������� ���� ������ ���������
// ������� ���������, ����� �������� ���������� ��� ���������� �������� ����
// ������ ��������� ����� ������
#define OFFSETOF(type, member)  ((int)(&(((type *)(0))->member)))

// ������� ����� ������ EEPROM � ����������
#define EEMEM_BASE_ADDR         0x4000

/**
 * ����� ������ EEPROM ��� ������ � ������ � �����������
 */
typedef struct _eemem_map_t {
    uint8_t temp1_delta;        /*< �������� ��������� 1 �������*/
    uint8_t temp2_delta;        /*< �������� ��������� 2 �������*/
    uint8_t intensity;          /*< ������� */
    uint8_t state;              /*< ��������� ������ */
} eemem_map_t;

/**
 * ��������� �������� ��������� 1 �������
 */
uint8_t eemem_get_temp1_delta();

/**
 * �������� �������� ��������� 1 �������
 */
void eemem_set_temp1_delta(uint8_t delta);

/**
 * ��������� �������� ��������� 1 �������
 */
uint8_t eemem_get_temp2_delta();

/**
 * �������� �������� ��������� 1 �������
 */
void eemem_set_temp2_delta(uint8_t delta);

/**
 * ��������� ��������� �����������
 */
uint8_t eemem_get_state();

/**
 * �������� ��������� �����������
 */
void eemem_set_state(uint8_t state);

/**
 * ��������� ��������� �����������
 */
uint8_t eemem_get_intensity();

/**
 * �������� ��������� �����������
 */
void eemem_set_intensity(uint8_t intensity);

#endif  /* EEMEM_H */
