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
 *
**************************************************/

#ifndef _GLOBALS_H
#define _GLOBALS_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
#endif

#include "Sprites.h"

// ----------------------------------------- CONSTS -----------------------------------------
//#define LCD_CONTRAST 40
#define LCD_NOKIA_WIDTH 95                // 0..95
#define LCD_NOKIA_HEIGHT 67               // 0..67
#define GAME_SPEED_DELAY 50
#define BACKGROUND_X0 2
#define BACKGROUND_Y0 10
#define BACKGROUND_X1 93
#define BACKGROUND_Y1 30
//physics
#define GRAVITY_VELOCITY 0.2
#define BRAKING_VELOCITY 0.05
#define THROTTLE_VELOCITY 0.3
#define JUMP_IMPULSE_SPEED -1.75


// ----------------------------------------- PINOUTS -----------------------------------------
#define PIN_LCD_RST 6
#define PIN_LCD_CS 7
#define PIN_LCD_BACKLIGHT 8

#define PIN_BUTTON_LEFT 2
#define PIN_BUTTON_RIGHT 3
#define PIN_BUTTON_UP 4

#define PIN_SPEAKER 12

// ----------------------------------------- GLOBAL VARS -----------------------------------------
extern uint32_t deltaTime;
#endif //_GLOBALS_H
