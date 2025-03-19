
#include "my_adc.h"

void adc_init(void) {
    ADCON1 = 0x06;
    ADCON0 = 0x01;
}

uint16_t my_adc(u_char ch) {
    ADCON0 &= 0xC3; // clear selected channel
    ADCON0 |= (ch << 2); // set new channel
    
    // convert
    __delay_ms(1);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);

    // combine result and return
    return ((uint16_t)ADRESH << 2) | (ADRESL >> 6);
}

// 0-1023 -> 0-100
uint8_t adc_100(u_char ch){
    return (uint8_t)((my_adc(ch) * 100UL) / 1023);
}