#ifndef BEEP_H
#define BEEP_H

// Нажатие клавиши
void beep_key();
// Блокировка
void beep_lock();
// Разблокировка
void beep_unlock();
// Ошибка
void beep_error();
// Сброс
void beep_reset();

void beep_low(uint16_t duration);
void beep_medium(uint16_t duration);
void beep_high(uint16_t duration);

#endif /* BEEP_H */
