// HX1230 library example
// (c) 2019 Pawel A. Hernik

/*
  HX1230 96x68 LCD connections (header on bottom, from left):
  #1 RST - D6 or any digital
  #2 CE  - D7 or any digital
  #3 N/C
  #4 DIN - D11/MOSI
  #5 CLK - D13/SCK
  #6 VCC - 3V3
  #7 BL  - 3V3 or any digital
  #8 GND - GND
*/

#include "Arduino.h"

#define LCD_RST 6
#define LCD_CS  7
#define LCD_BL  8
#define LCD_DIN 11
#define LCD_CLK 13

#include "HX1230_SPI.h"
// define USESPI in above header for HW 9-bit SPI

//HX1230_SPI lcd(LCD_RST, LCD_CS, LCD_DIN, LCD_CLK);
HX1230_SPI lcd(LCD_RST, LCD_CS);

#if USESPI==1
#include <SPI.h>
#endif

#include "term8x14_font.h"

void setup()
{
    Serial.begin(9600);
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);
    lcd.init();
    lcd.clrScr();
    lcd.setFont(Term8x14PL);
    lcd.printStr(3, 3, "Hello World");
}

uint8_t x = 0, y = 0, contrast = 0;
uint8_t frameCounter = 0;
void loop()
{
    lcd.clrScr();
    lcd.printStr(3, 1, "Hello World");
    frameCounter++;
    if(frameCounter>1){
        frameCounter = 0;
        lcd.printStr(3, 3, "DOOD");
    }

//    lcd.setContrast(contrast);
//    if(contrast>=31) contrast=0;
//    if(x>80) x=0;
//    if(y>5) y=0;
    delay(10);
}
