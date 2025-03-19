#ifndef MY_PINS_TYPES_DEFS_HEADER
#define MY_PINS_TYPES_DEFS_HEADER

#include <xc.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// lcd pins b0-5
#define LCD_RS PORTBbits.RB0
#define LCD_EN PORTBbits.RB1
#define LCD_D4 PORTBbits.RB2
#define LCD_D5 PORTBbits.RB3
#define LCD_D6 PORTBbits.RB4
#define LCD_D7 PORTBbits.RB5

// buttons c0-3
#define BTN_S1 PORTCbits.RC0
#define BTN_S2 PORTCbits.RC1
#define BTN_S3 PORTCbits.RC2
#define BTN_S4 PORTCbits.RC3

// leds c4-7, b6-7
#define LED_1 PORTCbits.RC4
#define LED_2 PORTCbits.RC5
#define LED_3 PORTCbits.RC6
#define LED_4 PORTCbits.RC7
#define LED_5 PORTBbits.RB6
#define LED_6 PORTBbits.RB7

// other output a4-6
#define IGNITION PORTAbits.RA4
#define MOTOR PORTAbits.RA5
#define BUZZER PORTAbits.RA6

// analog input
#define SENS_FLAM 0
#define SENS_TEMP 1
#define SENS_IGNI 2

typedef unsigned char u_char;

#define _XTAL_FREQ 16000000
#define BUTTON_DEBOUCE_TIME_MS 100

// temprature
#define MAX_TEMPRATURE 50
#define MIN_TEMPRATURE 10
uint8_t GLOBAL_TEMPERATURE = 25;

// system
uint8_t LOCK_MODE = 1;
uint8_t SYSTEM_RUNNING = 0;
uint8_t IGN_ERROR = 0;
uint8_t FLA_ERROR = 0; 

#endif