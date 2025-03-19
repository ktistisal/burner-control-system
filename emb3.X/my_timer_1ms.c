
#include "my_timer_1ms.h"

// configure timer and interrupts
void timer_init(void) {
    TMR0 = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0x03;
    
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    timer_configured = true;
}

// find task with fn = fn
bool task_existis(func fn) {
    for(uint8_t i = 0; i < MAX_TASKS; i ++) {
        if(task_list[i].fn == fn) {
            return true;
        }
    }
    return false;
}

// find empty slot and save function ptr, ms and counter
bool create_task(func fn, uint16_t ms) {
    for (uint8_t i = 0; i < MAX_TASKS; i++) {
        if (task_list[i].fn == NULL) {
            task_list[i].fn = fn;
            task_list[i].ms = ms;
            task_list[i].cnt = 0;
            return true;
        }
    }
    return false;
}

// find task with fn = fn and set fn to NULL
void drop_task(func fn) {
    for (uint8_t i = 0; i < MAX_TASKS; i++) {
        if (task_list[i].fn == fn) {
            task_list[i].fn = NULL;
        }
    }
}

// check which tasks cnt >= ms and execute fn
void __interrupt() timer_isr(void) {
    if (INTCONbits.T0IF) {
        for (uint8_t i = 0; i < MAX_TASKS; i++) {
            if (task_list[i].fn != NULL) {
                task_list[i].cnt ++;
                if (task_list[i].cnt >= task_list[i].ms) {
                    task_list[i].fn();
                    task_list[i].cnt = 0;
                }
            }
        }
        INTCONbits.T0IF = 0;  // clear timer interrupt flag
    }
}