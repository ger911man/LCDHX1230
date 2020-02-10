#include <SPI.h>
#include "HX1230_FB.h"
#include "small5x6_font.h"

#include "Globals.h"
#include "Fps.h"
#include "Timer.h"
#include "BackgroungHills.h"
#include "Dood.h"
#include "Speaker.h"
#include "Button.h"
#include "Map.h"
#include "Maps.h"

// objects
HX1230_FB lcd(PIN_LCD_RST, PIN_LCD_CS);
Fps fps = Fps(&lcd);
Timer timer = Timer();
Speaker speaker = Speaker(PIN_SPEAKER);
Button buttonLeft = Button(PIN_BUTTON_LEFT, &speaker);
Button buttonRight = Button(PIN_BUTTON_RIGHT, &speaker);
Button buttonUp = Button(PIN_BUTTON_UP, &speaker);
BackgroungHills backgroungHills2 = BackgroungHills(BACKGROUND_X0, 10, BACKGROUND_X1, 20, &lcd);
BackgroungHills backgroungHills3 = BackgroungHills(BACKGROUND_X0, 5, BACKGROUND_X1, 25, &lcd);
BackgroungHills backgroungHills4 = BackgroungHills(BACKGROUND_X0, 0, BACKGROUND_X1, 30, &lcd);
Dood dood = Dood(10,30,&lcd,&speaker);
Map lvlMap = Map(map0, &lcd);

// vars
uint16_t frameCounter = 0;
uint32_t deltaTime = 0;
float cameraPosition = 0;

// tmp vars
float f = 4.5;
uint8_t mel = 0;

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

void scrollMap(float *x, float *dx, const uint8_t *map){
    *x+=deltaTime* *dx;
    uint16_t x0 = (8-(pgm_read_byte(map + 1)%8))*8;
    uint16_t x1 = pgm_read_byte(map + 1)*8-SCR_WD + x0;
    if(*x <= x0){
        *dx=-*dx;
        *x=x0*2-*x;
    }
    if(*x >= x1){
        *dx=-*dx;
        *x=x1*2-*x;
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
float speedMap = 0.007;


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
    // ----------------------------------------- BUTOON -----------------------------------------
    if(buttonLeft.getState() != buttonRight.getState()){
        if(buttonLeft.getPrevState()) dood.moveLeft();
        if(buttonRight.getPrevState()) dood.moveRight();
    } else {
        dood.brake();
    };
    //first check ifHit
    if(buttonUp.isHit()){
        dood.doodJump();
    }
    //then getState, else - it won't work
    if(buttonUp.getState()){
        dood.doodLongJump();
    } else {
        dood.doodRegularJump();
    }
    // ----------------------------------------- SPEAKER -----------------------------------------
    speaker.playMelody();
    if(frameCounter%2000 == 0){
        speaker.replaceCurrentlyPlayingNoteWith(400,100);
        speaker.setMelodyByNumber(mel++);
        if(mel > 5) mel = 0;
    }
    // ----------------------------------------- DRAWING -----------------------------------------
    drawFrame();
    backgroungHills2.displayMountainsShiftedBy(0.005*deltaTime);
    backgroungHills3.displayMountainsShiftedBy(0.010*deltaTime);
    backgroungHills4.displayMountainsShiftedBy(0.015*deltaTime);
    lcd.drawSprite(biker1 , xC, yC );
    lcd.drawSpriteMirror(biker2 , xM1, yM1);
    dood.display();
//    dood.display();


    lvlMap.drawMap(cameraPosition,sin(f*2)*8);
    scrollMap(&cameraPosition, &speedMap, map0);

    moveVertex(&xC,&yC,&speedXC,&speedYC);
    moveVertex(&xM1,&yM1,&speedXm,&speedYm);




    //FPS draw
    fps.draw();
//    char buf[8];
//    snprintf(buf, sizeof(buf),"UP:%d",buttonUp.getState());
//    lcd.printStr(3,50,buf);


    // ----------------------------------------- FINAL -----------------------------------------
    f+=deltaTime/2000.0;
    delay((sin(f)+1)*30);
    lcd.display();
}
