
#include "my_lcd.h"
#include "my_adc.h"

void lcd_send_half_byte(u_char data, u_char rs) {
    LCD_RS = rs; // set mode 1: data, 0: cmd
    LCD_D4 = (data >> 0) & 0x01;
    LCD_D5 = (data >> 1) & 0x01;
    LCD_D6 = (data >> 2) & 0x01;
    LCD_D7 = (data >> 3) & 0x01;
    
    LCD_EN = 1;
    __delay_ms(1);
    LCD_EN = 0;
    __delay_ms(1);
}

void lcd_send_byte(u_char data, u_char rs){
    lcd_send_half_byte((data >> 4) & 0x0f, rs); // send 4x msb
    lcd_send_half_byte(data & 0x0f, rs); // send 4x lsb
}

void lcd_clear(void) {
    lcd_send_byte(0x01, 0); __delay_ms(4); // clear
    lcd_send_byte(0x80, 0); __delay_ms(1); // move cursor to 0, 0
}

void lcd_send_string(char *str) {
    while(*str) lcd_send_byte(*str ++, 1);
}

/* init sequence source:
 * https://web.alfredstate.edu/faculty/weimandn/lcd/lcd_initialization/
 * lcd_initialization_index.html
 */
void lcd_init(void) {
    __delay_ms(150);
    lcd_send_half_byte(0x03, 0); __delay_ms(5);
    lcd_send_half_byte(0x03, 0); __delay_ms(2);
    lcd_send_half_byte(0x03, 0); __delay_ms(2);
    lcd_send_half_byte(0x02, 0); __delay_ms(2);
    lcd_send_byte(0x28, 0); __delay_ms(1);
    lcd_send_byte(0x08, 0); __delay_ms(1);
    lcd_send_byte(0x01, 0); __delay_ms(4);
    lcd_send_byte(0x06, 0); __delay_ms(1);
    lcd_send_byte(0x0c, 0); __delay_ms(1);
    lcd_send_byte(0x80, 0); __delay_ms(1);
}

bool lcd_print(void){
    static uint8_t lcdMode = 0;
    
    char buf[3];
    
    // clear on system reset
    if(!SYSTEM_RUNNING && lcdMode != 0){
        lcdMode = 0;
        lcd_clear();
        return true;
    }
    
    // print message on lock mode
    if(LOCK_MODE && SYSTEM_RUNNING && lcdMode != 1) {
        lcdMode = 1;
        lcd_clear();
        lcd_send_string("LOCK MODE");
        return true;
    }
    
    // update according to desired temperature
    if(!LOCK_MODE && SYSTEM_RUNNING && lcdMode != GLOBAL_TEMPERATURE) {
        lcdMode = GLOBAL_TEMPERATURE;
        lcd_clear();
        lcd_send_string("18390227   ");
        sprintf(buf, "%u", GLOBAL_TEMPERATURE);
        lcd_send_string(buf);
        lcd_send_string("C");
        return true;
    }
    
    return true;
}
