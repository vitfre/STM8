#ifndef BEEP_H
#define BEEP_H

// ������� �������
void beep_key();
// ����������
void beep_lock();
// �������������
void beep_unlock();
// ������
void beep_error();
// �����
void beep_reset();

void beep_low(uint16_t duration);
void beep_medium(uint16_t duration);
void beep_high(uint16_t duration);

#endif /* BEEP_H */
