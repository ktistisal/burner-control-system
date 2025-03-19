#ifndef MY_ADC_HEADER
#define MY_ADC_HEADER

#include "my_pins_types_defs.h"

void adc_init(void);
uint16_t my_adc(u_char ch);
uint8_t adc_100(u_char ch);

#endif