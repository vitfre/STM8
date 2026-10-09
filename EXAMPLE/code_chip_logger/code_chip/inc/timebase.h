#include "stm8s.h"

#ifndef _TIMEBASE
#define _TIMEBASE

void set_delay_timer(uint16_t value);
void set_uart_timer(uint16_t value);
void set_alarm_timer(uint16_t value);


bool delay_timer_elapsed(void);
bool uart_timer_elapsed(void);
bool alarm_timer_elapsed(void);

void delay(uint16_t time);

#endif