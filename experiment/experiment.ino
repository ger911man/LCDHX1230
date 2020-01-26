// HX1230 96x68 LCD FB library example
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

#define LCD_RST 6
#define LCD_CS  7
#define LCD_BL  8

#include "HX1230_FB.h"
#include <SPI.h>
HX1230_FB lcd(LCD_RST, LCD_CS);

// from PropFonts library
#include "c64enh_font.h"
#include "term8x14_font.h"

char buf[20];

void setup()
{
    Serial.begin(9600);
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);
    lcd.init();
    lcd.cls();
    int dx = SCR_WD/16;
    for(int j=1;j<17;j++) { lcd.setDither(j); lcd.fillRectD((j-1)*dx,0,dx,SCR_HT,1); }
    lcd.display();
    delay(500);
}

void sample(int s)
{
    lcd.cls();
    lcd.setDither(s);
    lcd.setFont(c64enh);
    snprintf(buf,20,"Pattern: %02d",s);
    lcd.printStr(ALIGN_CENTER, 2, buf);
    lcd.fillRectD(6,13,44,32,1);
    lcd.fillCircleD(96-24,28,16,1);
    int dx = SCR_WD/16;
    for(int j=1;j<17;j++) {
        lcd.setFont(c64enh);
        buf[0]=(j>9) ? j-10+'A' : j+'0';
        buf[1]=0;
        lcd.printStr(2+(j-1)*dx, SCR_HT-8*2, buf);
        lcd.setDither(j);
        lcd.fillRectD((j-1)*dx,SCR_HT-8,dx,8,1);
    }
    lcd.display();
    delay(500);
}

uint8_t frameCounter = 0;
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


void loop()
{
    lcd.cls();
    lcd.setDither(8);
    frameCounter++;
    if(frameCounter%2){
        lcd.setDither(8);
    } else {
        lcd.setDither(-8);
    }
    lcd.drawLineVfastD(0,0,50,1);
    lcd.drawLineVfastD(1,0,50,1);
    lcd.drawLineVfastD(2,0,50,1);
    lcd.drawLineHfastD(0,50,0,1);
    lcd.drawLineHfastD(0,50,1,1);
    lcd.drawLineHfastD(0,50,2,1);
//    lcd.drawLineHfast(0,SCR_WD-1,1,1);
//    lcd.drawLineHfastD(0,SCR_WD-1,2,1);
//    lcd.fillRectD(4,4,20,1,1);

    moveRectVertex(&x1R,&y1R,&dx1R,&dy1R);
    moveRectVertex(&x2R,&y2R,&dx2R,&dy2R);
    moveRectVertex(&x3R,&y3R,&dx3R,&dy3R);
    lcd.fillTriangle(x2R,y2R,x3R,y3R,x1R,y1R,1);
    lcd.fillTriangleD(x1R,y1R,7,7,x2R,y2R,1);


    moveCircle(&xC, &yC, &dxC, &dyC);
    lcd.fillCircle(xC, yC, 13, 1);
    lcd.display();
//    for(int i=0;i<=16;i++){
//        lcd.cls();
//        lcd.setDither(i);
//        lcd.drawLineD(0,20,i*2,1);
//        lcd.fillRectD(0+5*i,0,5,50,1);
//        lcd.fillTriangleD(0,0,40,40,60,15,1);
//        lcd.display();
//        delay(50);
//    }

//    for(int i=0;i<=16;i++) sample(i);
//    for(int i=16;i>0;i--) sample(i);
}

