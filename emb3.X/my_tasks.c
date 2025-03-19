
#include "my_tasks.h"

void debounce(void) {    
    static uint8_t debounceS1 = 0; 
    static uint8_t debounceS2 = 0; 
    static uint8_t debounceS3 = 0; 
    static uint8_t debounceS4 = 0; 
    
    // button 1 start system
    if(BTN_S1 == 1) {
        if(debounceS1 == 0) {
            SYSTEM_RUNNING = !SYSTEM_RUNNING;
        }
        debounceS1 = BUTTON_DEBOUCE_TIME_MS;
    } else {
        if(debounceS1 > 0){
            debounceS1--;
        }
    }
    
    // button 2 increase temperature
    if(BTN_S2 == 1 && !LOCK_MODE && SYSTEM_RUNNING) {
        if(debounceS2 == 0) {
            if(GLOBAL_TEMPERATURE < MAX_TEMPRATURE){
                GLOBAL_TEMPERATURE ++;
            }
        }
        debounceS2 = BUTTON_DEBOUCE_TIME_MS;
    } else {
        if(debounceS2 > 0){
            debounceS2--;
        }
    }
    
    // button 3 decrease temperature
    if(BTN_S3 == 1 && !LOCK_MODE && SYSTEM_RUNNING) {
        if(debounceS3 == 0) {
            if(GLOBAL_TEMPERATURE > MIN_TEMPRATURE){
                GLOBAL_TEMPERATURE --;
            }
        }
        debounceS3 = BUTTON_DEBOUCE_TIME_MS;
    } else {
        if(debounceS3 > 0){
            debounceS3--;
        }
    }
    
    // button 4 exit lock mode
    if(BTN_S4 == 1 && LOCK_MODE && SYSTEM_RUNNING) {
        if(debounceS4 == 0) {
            LOCK_MODE = 0;
            FLA_ERROR = 0;
            IGN_ERROR = 0;
            BUZZER = 0;
        }
        debounceS4 = BUTTON_DEBOUCE_TIME_MS;
    } else {
        if(debounceS4 > 0){
            debounceS4--;
        }
    }
}

void blink(void) {
    if(SYSTEM_RUNNING && !LOCK_MODE) LED_1 = !LED_1;
}

void led_set(void) {
    LED_6 = LOCK_MODE && SYSTEM_RUNNING;
    LED_5 = FLA_ERROR && SYSTEM_RUNNING;
    LED_4 = IGN_ERROR && SYSTEM_RUNNING;
    LED_3 = LED_3 && SYSTEM_RUNNING && (!LOCK_MODE);
    LED_2 = LED_2 && SYSTEM_RUNNING && (!LOCK_MODE);
    LED_1 = LED_1 && SYSTEM_RUNNING && (!LOCK_MODE);
}