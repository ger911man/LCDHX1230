#include <SPI.h>
#include "HX1230_FB.h"
#include "small5x6_font.h"

#include "Globals.h"
#include "Fps.h"
#include "Timer.h"
#include "BackgroungHills.h"

// objects
HX1230_FB lcd(PIN_LCD_RST, PIN_LCD_CS);
Fps fps = Fps(&lcd);
Timer timer = Timer();
BackgroungHills backgroungHills = BackgroungHills(BACKGROUND_X0, BACKGROUND_Y0, BACKGROUND_X1, BACKGROUND_Y1, &lcd);

// vars
uint32_t frameCounter = 0;
float f = 4.5;

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
}





float xC=22, yC=33, rC=15;
float speedXC = -0.015, speedYC = -0.010; //speed: pixels/sec/1000
float backgroundSpeed = 0.003;


void moveRectVertex(float *x, float *y, float *dx, float *dy){
    if(*x <= 0 || *x >= LCD_NOKIA_WIDTH) *dx=-*dx;
    if(*y <= 0 || *y >= LCD_NOKIA_HEIGHT) *dy=-*dy;
    *x += *dx;
    *y += *dy;
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
    if(frameCounter%2){
        lcd.setDither(8);
    } else {
        lcd.setDither(-8);
    }

    // ----------------------------------------- DRAWING -----------------------------------------
//    if(frameCounter %2 == 0){
//        backgroungHills.displayMountainsShiftedBy(backgroundSpeed*timer.getTimer());
//    }
    backgroungHills.displayMountainsShiftedBy(backgroundSpeed*timer.getTimer());

    drawFrame();


    xC+=timer.getTimer()*speedXC;
    yC+=timer.getTimer()*speedYC;
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
    lcd.fillCircle(xC, yC, rC-5, 1);


    //FPS draw
    fps.draw();


    // ----------------------------------------- FINAL -----------------------------------------
    f+=timer.getTimer()/10000.0;
    delay((sin(f)+1)*50);
    lcd.display();
}

