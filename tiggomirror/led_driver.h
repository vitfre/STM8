#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

#define LCD_OP_NOOP             0
#define LCD_OP_DIGIT0           1
#define LCD_OP_DIGIT1           2
#define LCD_OP_DIGIT2           3
#define LCD_OP_DIGIT3           4

#define LCD_OP_DIGIT4           5
#define LCD_OP_DIGIT5           6
#define LCD_OP_DIGIT6           7
#define LCD_OP_DIGIT7           8
#define LCD_OP_DECODEMODE       9
#define LCD_OP_INETNSITY        10

#define LCD_OP_SCANLIMIT        11
#define LCD_OP_SHUTDOWN         12
#define LCD_OP_DISAPLYTEST      15

#define CS_LOW(num) (num == 1 ? GPIO_WriteLow(GPIOC, GPIO_PIN_4) : GPIO_WriteLow(GPIOA, GPIO_PIN_3))
#define CS_HIGH(num) (num == 1 ? GPIO_WriteHigh(GPIOC, GPIO_PIN_4) : GPIO_WriteHigh(GPIOA, GPIO_PIN_3))

void lcd_init(uint8_t device);
void lcd_set_scan_limit(uint8_t device, uint8_t level);
void lcd_clear(uint8_t device);
void lcd_shutdown(uint8_t device, uint8_t mode);
void lcd_set_intensity(uint8_t device, uint8_t intensity);
void lcd_set_digit(uint8_t device, uint8_t digit, uint8_t value, uint8_t dp);

#endif /* _LED_DRIVER_H_ */
