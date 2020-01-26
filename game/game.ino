#include <stdlib.h>
#include <SPI.h>

#include "Globals.h"
#include "HX1230_FB.h"
#include "small5x6_font.h"
//#include "tiny3x7_font.h"

HX1230_FB lcd(PIN_LCD_RST, PIN_LCD_CS);

// from PropFonts library
//#include "c64enh_font.h"
//#include "term8x14_font.h"

// vars
uint32_t frameCounter = 0;

uint32_t  currTime = 0;
uint32_t  prevTime = 0;
uint32_t  deltaTime = 0;

uint32_t  prevFpsTime = 0;
uint32_t  fpsCounter = 0;
uint32_t  fps = 0;
#define FPS_DISPLAY_RATE 1000   //ms


void setup()
{
    pinMode(PIN_BUTTON_LEFT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_SPEAKER, OUTPUT);

    Serial.begin(115200);

    lcd.init();
    lcd.cls();
    lcd.setFont(Small5x6PL);
    lcd.display();
    prevTime = millis();
    prevFpsTime = prevTime;
}





float xC=22, yC=33;
float dxC = -0.3, dyC = -0.1;

float x1R=5,  y1R=5;
float x2R=50, y2R=20;
float x3R=10, y3R=50;
float dx1R = -0.3, dy1R = -0.1;
float dx2R = -0.2, dy2R = -0.2;
float dx3R = -0.1, dy3R = -0.3;

void moveCircle(float *x, float *y, float *dx, float *dy){
    if(*x <= 16 || *x >= SCR_WD-16) *dx=-*dx;
    if(*y <= 16 || *y >= SCR_HT-16) *dy=-*dy;
    *x += *dx;
    *y += *dy;
}

void moveRectVertex(float *x, float *y, float *dx, float *dy){
    if(*x <= 0 || *x >= SCR_WD) *dx=-*dx;
    if(*y <= 0 || *y >= SCR_HT) *dy=-*dy;
    *x += *dx;
    *y += *dy;
}

char buf[10];

void loop()
{
    currTime = millis();
    deltaTime = currTime - prevTime;


    lcd.cls();
    frameCounter++;
    if(frameCounter%2){
        lcd.setDither(8);
    } else {
        lcd.setDither(-8);
    }
//    lcd.drawLineVfastD(0,0,50,1);
//    lcd.drawLineVfastD(1,0,50,1);
//    lcd.drawLineVfastD(2,0,50,1);
//    lcd.drawLineHfastD(0,50,0,1);
//    lcd.drawLineHfastD(0,50,1,1);
//    lcd.drawLineHfastD(0,50,2,1);
//    lcd.drawLineHfast(0,SCR_WD-1,1,1);
//    lcd.drawLineHfastD(0,SCR_WD-1,2,1);
//    lcd.fillRectD(4,4,20,1,1);

    moveRectVertex(&x1R,&y1R,&dx1R,&dy1R);
    moveRectVertex(&x2R,&y2R,&dx2R,&dy2R);
    moveRectVertex(&x3R,&y3R,&dx3R,&dy3R);
    lcd.fillTriangle(x2R,y2R,x3R,y3R,x1R,y1R,1);
    lcd.fillTriangleD(x1R,y1R,7,7,x2R,y2R,1);
    lcd.fillTriangleD(LCD_NOKIA_WIDTH,LCD_NOKIA_HEIGHT,x3R,y3R,x2R,y2R,1);
    lcd.fillTriangleD(LCD_NOKIA_WIDTH,0,x3R,y3R,x1R,y1R,1);








    moveCircle(&xC, &yC, &dxC, &dyC);
    lcd.fillCircle(xC, yC, 13, 1);








    //FPS display
    fpsCounter++;
    if(currTime - prevFpsTime >= FPS_DISPLAY_RATE){
        fps = fpsCounter;
        prevFpsTime = currTime;
        fpsCounter = 0;
    }
    //    char bufFloat[10];
    //    snprintf(buf, sizeof(buf),"f:%s",dtostrf(xC,5,2,bufFloat));
    snprintf(buf, sizeof(buf),"FPS:%d",fps);
    lcd.printStr(1,1,buf);

    lcd.display();
    prevTime = currTime;
}

