
#ifndef MY_TIMER_1MS_HEADER
#define MY_TIMER_1MS_HEADER

#include "my_pins_types_defs.h"

#define MAX_TASKS 5

typedef void (*func)(void);

typedef struct {
    func fn;
    uint16_t ms;
    uint16_t cnt;
} task;

static task task_list[MAX_TASKS];
static bool timer_configured = false;

void timer_init(void);
bool create_task(func fn, uint16_t ms);
void drop_task(func fn);
void __interrupt() timer_isr(void);

#endif