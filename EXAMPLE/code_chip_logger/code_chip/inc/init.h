#ifndef _INIT
#define _INIT

#define ALARM_PIN GPIO_PIN_2
#define ALARM_PORT GPIOB

#define SENSOR_PIN GPIO_PIN_6
#define SENSOR_PORT GPIOB

#define UART_PIN GPIO_PIN_5
#define UART_PORT GPIOD

void init_all(void);
void init_clk(void);
void init_gpio(void);
void init_timers(void);
void init_uart(void);
void IWDG_Config(void);

#endif