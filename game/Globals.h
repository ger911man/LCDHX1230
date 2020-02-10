/*************************************************
 * Public Constants
 *
 * ****************
 *   LCD pinouts
 * ****************
 * HX1230 96x68 LCD connections:
 * #1 RST - D6 or any digital
 * #2 CE  - D7 or any digital
 * #3 N/C
 * #4 DIN - D11/MOSI
 * #5 CLK - D13/SCK
 * #6 VCC - 3V3
 * #7 BL  - 3V3 or any digital + resistor (BackLight)
 * #8 GND - GND
 *
 * ****************
 *  BUTTONS
 * ****************
 * UP 4
 * LEFT 2
 * RIGHT 3
 *
 * *****************
 *  SPEAKER
 * ****************
 * PIN 12
**************************************************/

#ifndef _GLOBALS_H
#define _GLOBALS_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
#endif

#include "Sprites.h"

// ----------------------------------------- CONSTS -----------------------------------------
#define LCD_NOKIA_WIDTH 95                // 0..95
#define LCD_NOKIA_HEIGHT 67               // 0..67
#define BACKGROUND_X0 2
#define BACKGROUND_Y0 10
#define BACKGROUND_X1 93
#define BACKGROUND_Y1 30

// ----------------------------------------- PINOUTS -----------------------------------------
#define PIN_LCD_RST 6
#define PIN_LCD_CS 7
#define PIN_LCD_BACKLIGHT 8

#define PIN_BUTTON_LEFT 3
#define PIN_BUTTON_RIGHT 2
#define PIN_BUTTON_UP 4

#define PIN_SPEAKER 8

// ----------------------------------------- GLOBAL VARS -----------------------------------------
extern uint32_t deltaTime;
#endif //_GLOBALS_H
