
#ifndef MY_LCD_HEADER
#define MY_LCD_HEADER

#include "my_pins_types_defs.h"
#include "my_adc.h"

void lcd_send_half_byte(u_char data, u_char rs);
void lcd_send_byte(u_char data, u_char rs);
void lcd_clear(void);
void lcd_send_string(char *str);
void lcd_init(void);
bool lcd_print(void);

#endif