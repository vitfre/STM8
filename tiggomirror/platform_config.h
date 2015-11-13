#ifndef PLATFORM_CONFIG
#define PLATFORM_CONFIG

// -----------------------------------------------------------------------------
// ���������� �������� �������
// -----------------------------------------------------------------------------
#define CODE_LEN            4               // ����� ���� �������������
#define INPUT_BUFFER_LEN    12//CODE_LEN + 1    // ����� ������ ������� ������ ���� ����������� � ������ \0
// ���-��� ��-���������
#define DEFAULT_PIN_CODE    1234

// -----------------------------------------------------------------------------
// ��������� ���������
// -----------------------------------------------------------------------------
#define GREEN_LED_PIN           GPIO_PIN_4
#define GREEN_LED_PORT          GPIOB

#define RED_LED_PIN             GPIO_PIN_5
#define RED_LED_PORT            GPIOB

#define RELE_PIN                GPIO_PIN_3
#define RELE_PORT               GPIOA

// -----------------------------------------------------------------------------
// ????????? ??????????
// -----------------------------------------------------------------------------
#define KBD_ROWS_PORT       GPIOC
#define KBD_COLS1_PINS      GPIOD
#define KBD_COLS_PINS       GPIOC

// ?????????? ??????? ??????????
#define KBD_COLS_COUNT      3
// ???? ??????? ??????????
#define KBD_COL_0           GPIO_PIN_3
#define KBD_COL_1           GPIO_PIN_2
#define KBD_COL_2           GPIO_PIN_7

// ?????????? ????? ??????????
#define KBD_ROWS_COUNT      4
// ???? ????? ??????????
#define KBD_ROW_0           GPIO_PIN_6
#define KBD_ROW_1           GPIO_PIN_5
#define KBD_ROW_2           GPIO_PIN_4
#define KBD_ROW_3           GPIO_PIN_3

// ?????? ?????? ?????
#define KBD_CANCEL_CHAR     '#'

#endif /* PLATFORM_CONFIG */
