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
}





float xC=22, yC=33, rC=15;
float xm=62, ym=13;

float speedXC = -0.015, speedYC = -0.010; //speed: pixels/sec/1000
float speedXm = -0.015, speedYm = -0.010; //speed: pixels/sec/1000
float backgroundSpeed = 0.003;


void moveVertex(float *x, float *y, float *dx, float *dy){
    *x+=deltaTime* *dx;
    *y+=deltaTime* *dy;
    if(*x <= 0){
        *dx=-*dx;
        *x=-*x;
    }
    if(*x >= LCD_NOKIA_WIDTH){
        *dx=-*dx;
        *x=LCD_NOKIA_WIDTH*2-*x;
    }
    if(*y <= 0){
        *dy=-*dy;
        *y=-*y;
    }
    if(*y >= LCD_NOKIA_HEIGHT){
        *dy=-*dy;
        *y=LCD_NOKIA_HEIGHT*2-*y;
    }
}

void drawFrame(){
    lcd.drawLineHfast(0,LCD_NOKIA_WIDTH,0,1);
    lcd.drawLineHfast(0,LCD_NOKIA_WIDTH,LCD_NOKIA_HEIGHT,1);
    lcd.drawLineVfast(0,0,LCD_NOKIA_HEIGHT,1);
    lcd.drawLineVfast(LCD_NOKIA_WIDTH,0,LCD_NOKIA_HEIGHT,1);
}



void loop()
{
    // ----------------------------------------- PRESETS -----------------------------------------
    timer.resetFrameTimer();
//    Serial.println(timer.getTimer());
    lcd.cls();

    frameCounter++;
    moveVertex(&xm, &ym, &speedXm, &speedYm);
    if(frameCounter%2){
        lcd.setDither(8);
        lcd.drawSprite(biker1,xm-10,ym-10);
    } else {
        lcd.setDither(-8);
        lcd.drawSprite(biker2,xm-10,ym-10);
    }

    // ----------------------------------------- DRAWING -----------------------------------------
//    if(frameCounter %2 == 0){
//        backgroungHills.displayMountainsShiftedBy(backgroundSpeed*timer.getTimer());
//    }
//    backgroungHills.displayMountainsShiftedBy(backgroundSpeed*deltaTime);
    backgroungHills2.displayMountainsShiftedBy(0.005*deltaTime);
    backgroungHills3.displayMountainsShiftedBy(0.010*deltaTime);
    backgroungHills4.displayMountainsShiftedBy(0.015*deltaTime);
//    dood.display();
    drawFrame();


    xC+=deltaTime*speedXC;
    yC+=deltaTime*speedYC;
    if(xC <= rC){
        speedXC=-speedXC;
        backgroundSpeed=-backgroundSpeed;
        xC=rC*2-xC;
    }
    if(xC >= LCD_NOKIA_WIDTH-rC){
        speedXC=-speedXC;
        backgroundSpeed=-backgroundSpeed;
        xC=(LCD_NOKIA_WIDTH-rC)*2-xC;
    }
    if(yC <= rC){
        speedYC=-speedYC;
        yC=rC*2-yC;
    }
    if(yC >= LCD_NOKIA_HEIGHT-rC){
        speedYC=-speedYC;
        yC= (LCD_NOKIA_HEIGHT-rC)*2-yC;
    }
    lcd.fillCircleD(xC, yC, rC, 1);
    lcd.fillCircle(xC, yC, rC-10, 1);




    //FPS draw
    fps.draw();


    // ----------------------------------------- FINAL -----------------------------------------
    f+=deltaTime/5000.0;
    delay((sin(f)+1)*50);
    lcd.display();
}

