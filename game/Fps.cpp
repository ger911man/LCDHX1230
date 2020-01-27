//
// Created by Gera on 27.01.2020.
//

#include "Fps.h"

//Constructor
Fps::Fps(HX1230_FB* lcd) {
    prevFpsTime = millis();
    fpsCounter = 0;
    fps = 0;
    this->lcd = lcd;
}

void Fps::draw() {
    fpsCounter++;
    if(millis() - prevFpsTime >= FPS_DISPLAY_RATE){
        fps = fpsCounter;
        prevFpsTime = millis();
        fpsCounter = 0;
    }
    snprintf(buf, sizeof(buf),"FPS:%d",fps);
    lcd->printStr(FPS_X_POS,FPS_Y_POS,buf);
}