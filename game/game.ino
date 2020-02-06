#include <SPI.h>
#include "HX1230_FB.h"
#include "small5x6_font.h"

#include "Globals.h"
#include "Fps.h"
#include "Timer.h"
#include "BackgroungHills.h"
#include "Dood.h"

// objects
HX1230_FB lcd(PIN_LCD_RST, PIN_LCD_CS);
Fps fps = Fps(&lcd);
Timer timer = Timer();
//BackgroungHills backgroungHills = BackgroungHills(BACKGROUND_X0, BACKGROUND_Y0, BACKGROUND_X1, BACKGROUND_Y1, &lcd);
BackgroungHills backgroungHills2 = BackgroungHills(BACKGROUND_X0, 10, BACKGROUND_X1, 20, &lcd);
BackgroungHills backgroungHills3 = BackgroungHills(BACKGROUND_X0, 5, BACKGROUND_X1, 25, &lcd);
BackgroungHills backgroungHills4 = BackgroungHills(BACKGROUND_X0, 0, BACKGROUND_X1, 30, &lcd);
Dood dood = Dood(10,30,&lcd);

// vars
uint32_t frameCounter = 0;
uint32_t deltaTime = 0;
float f = 4.5;
#define ARR 20
float arr[ARR];

void setup()
{
    pinMode(PIN_BUTTON_LEFT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_SPEAKER, OUTPUT);

//    Serial.begin(115200);

    lcd.init();
    lcd.cls();
    lcd.setFont(Small5x6PL);

    for(int i=0; i< ARR; i++){
        arr[i]=random(95);
    }
}




void moveVertex(float *x, float *y, float *dx, float *dy){
    *x+=deltaTime* *dx;
    *y+=deltaTime* *dy;
    float x0=-10;
    float x1=SCR_WD-10;
    float y0=-10;
    float y1=SCR_HT-10;
    if(*x <= x0){
        *dx=-*dx;
        *x=x0*2-*x;
    }
    if(*x >= x1){
        *dx=-*dx;
        *x=x1*2-*x;
    }
    if(*y <= y0){
        *dy=-*dy;
        *y=y0*2-*y;
    }
    if(*y >= y1){
        *dy=-*dy;
        *y=y1*2-*y;
    }
}

void drawFrame(){
    lcd.drawLineHfast(0,LCD_NOKIA_WIDTH,0,1);
    lcd.drawLineHfast(0,LCD_NOKIA_WIDTH,LCD_NOKIA_HEIGHT,1);
    lcd.drawLineVfast(0,0,LCD_NOKIA_HEIGHT,1);
    lcd.drawLineVfast(LCD_NOKIA_WIDTH,0,LCD_NOKIA_HEIGHT,1);
}


float xC=22, yC=33;
float speedXC = -0.015, speedYC = -0.010; //speed: pixels/sec/1000
float xM1=22, yM1=33;
float speedXm = 0.010, speedYm = 0.007;

float backgroundSpeed = 0.003;


void bikerTest(){
    for(int i=0; i< ARR; i++){
        arr[i]+=0.05+i*0.009;
        if(arr[i]>96) arr[i]=-16;
        lcd.drawSprite(biker1,arr[i],25+i*2);
    }
}


void loop()
{
    // ----------------------------------------- PRESETS -----------------------------------------
    lcd.cls();
    timer.resetFrameTimer();
    frameCounter++;
//    Serial.println(timer.getTimer());
    if(frameCounter%2){
        lcd.setDither(8);
    } else {
        lcd.setDither(-8);
    }

    // ----------------------------------------- DRAWING -----------------------------------------
    drawFrame();
    backgroungHills2.displayMountainsShiftedBy(0.005*deltaTime);
    backgroungHills3.displayMountainsShiftedBy(0.010*deltaTime);
    backgroungHills4.displayMountainsShiftedBy(0.015*deltaTime);
//    for(int i=0;i<50;i++) lcd.drawSprite(biker1 , xC, yC );
//    for(int i=0;i<50;i++) lcd.drawSpriteMirror(biker2 , xM1, yM1);
//    dood.display();



    moveVertex(&xC,&yC,&speedXC,&speedYC);
    moveVertex(&xM1,&yM1,&speedXm,&speedYm);

    bikerTest();





    //FPS draw
    fps.draw();


    // ----------------------------------------- FINAL -----------------------------------------
//    f+=deltaTime/5000.0;
//    delay((sin(f)+1)*50);
    lcd.display();
}

