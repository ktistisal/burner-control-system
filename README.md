# burner-control-system

## Overview
Embedded system that manages burner operations with real-time temperature regulation, ignition control, and safety monitoring. It includes fault detection and a LOCK MODE for critical failures.

Built using a PIC16F883 microcontroller and simulated in SimulIDE.

## Features
- Automatic temperature regulation
- Ignition and fuel pump control logic
- Flame and spark detection
- Retry mechanism for ignition failures
- LOCK MODE on repeated errors
- LCD display (4-bit mode) for system status
- Button input with debounce handling
- Timer-based task scheduling (interrupt-driven)

## Hardware
- PIC16F883 microcontroller
- LCD 16x2 display
- LEDs for status indication
- Push buttons (user input)
- Potentiometers simulating sensors (temperature, flame, spark)
- DC motor (fuel pump simulation)
- Ignition LED (spark simulation)
- Buzzer

## System Logic
1. System initializes peripherals and waits for user start
2. Reads temperature and compares with target
3. If below target, ignition sequence starts
4. Checks spark and flame sensors
5. Retries ignition up to 3 times
6. On failure, enters LOCK MODE

## Tools
- MPLAB X IDE
- XC8 Compiler
- SimulIDE (simulation)
- EasyEDA (circuit design)

## Screenshots
<img width="575" height="394" alt="Screenshot_29-4-2026_23332_" src="https://github.com/user-attachments/assets/7a59dd54-68fa-4f7b-860a-063f7a773716" />\
<img width="643" height="330" alt="Screenshot_29-4-2026_23414_" src="https://github.com/user-attachments/assets/75f06818-51fc-4f2a-b573-3de8be33043a" />\
<img width="641" height="359" alt="Screenshot_29-4-2026_23434_" src="https://github.com/user-attachments/assets/1d6b9c17-ae72-4b30-8b94-bea0f2cbace5" />
