
#include "my_lcd.h"
#include "my_timer_1ms.h"
#include "my_tasks.h"
#include "my_adc.h"

void ignition_system(void);
void pins_init(void);

void main(void){
    pins_init();
    adc_init();
    timer_init();
    lcd_init();
    
    create_task(&blink, 1000);
    create_task(&debounce, 1);
    create_task(&led_set, 1);
    
    while(1){
        if(lcd_print() && !LOCK_MODE && SYSTEM_RUNNING) {
            ignition_system();
        }
    }
    
    return;
}

void pins_init(void) {
    TRISA = 0b00000111; // r0-2 inputs
    //PORTA = 0b00000000;
    ANSEL = 0b00000111; // r0-2 analog
    
    TRISB = 0b00000000; // all outputs
    PORTB = 0b00000000;
    
    TRISC = 0b00001111; // c0-4 i c5-7 o
    PORTC = 0b00000000;
}

void ignition_system(void){
    uint16_t tmr = 0;
    
    // nothing to do...
    if(GLOBAL_TEMPERATURE < adc_100(SENS_TEMP) - 5) {
        LED_2 = 0;
    }
    
    // increase temperature
    else if(GLOBAL_TEMPERATURE > adc_100(SENS_TEMP) + 5) {
        
        LED_2 = 0;
        
        for(uint8_t i = 0; i < 3; i ++){
            
            // check ignition
            tmr = 0;
            IGNITION = 1;
            while(tmr < 100) {
                if(adc_100(SENS_IGNI) > 50) {
                    break;
                }
                tmr += 10;
                __delay_ms(10);
            }
            
            // handle no ignition
            if(tmr >= 100){
                IGNITION = 0;
                IGN_ERROR = 1;
                LOCK_MODE = 1;
                return;
            }
            
            // ignition working :)
            LED_3 = 1;
            
            // check pump
            tmr = 0;
            MOTOR = 1;
            while(tmr < 500) {
                if(adc_100(SENS_FLAM) > 50) {
                    break;
                }
                tmr += 10;
                __delay_ms(10);
            }
            
            // turn off
            IGNITION = 0;
            LED_3 = 0;
            MOTOR = 0;
            
            // handle no flame
            if(tmr >= 300) {
                FLA_ERROR = 1;
                if(i == 2) {
                    LOCK_MODE = 1;
                    return;
                }
                __delay_ms(1000);
            }
            
            // handle flame
            else {
                FLA_ERROR = 0;
                return;
            }
        }
    }
    
    // :)
    else {
        LED_2 = 1;
    }
}

