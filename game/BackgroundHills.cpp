#include "BackgroungHills.h"

BackgroungHills::BackgroungHills(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, HX1230_FB* lcd){
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->lcd = lcd;
    mountainMaxHeight = (this->y1 - this->y0);
    mountainMinHeight = (this->y1 - this->y0)*0.15;

    uint8_t mountain[MOUNTAINS_QUANTITY];
    for(uint8_t i = 0; i < MOUNTAINS_QUANTITY; i++){
        mountain[i] = random(mountainMinHeight, mountainMaxHeight);
        horizonArraySize += mountain[i] * 2 - 1;
    }
    horizonArraySize++;
    horizonArray = new uint8_t[horizonArraySize];

    uint8_t k = 1;
    for(uint8_t i = 0; i < MOUNTAINS_QUANTITY; i++) {
        horizonArray[k] = y1;
        k++;
        for (uint8_t j = 1; j < mountain[i]; j++) {
            horizonArray[k] = horizonArray[k - 1] - 1;
            k++;
        }
        for (uint8_t j = 1; j < mountain[i]; j++) {
            horizonArray[k] = horizonArray[k - 1] + 1;
            k++;
        }
    }
//    horizonArray[1] = 8;
//    horizonArray[horizonArraySize-1] = 8;
}

void BackgroungHills::displayMountains()
{
    uint8_t k = 1 + shift;
    for(uint8_t i = x0; i <= x1; i++){
        lcd->drawLineVfastD(i,horizonArray[k],y1,1);
        k++;
        if(k >= horizonArraySize) k = 1;
    }
}

void BackgroungHills::setFrame(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    uint8_t dy = this->y1 - y1;
    int dx = (x1 - x0) - (this->x1 - this->x0);
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->horizonArraySize = x1 - x0 + 1;
    this->mountainMaxHeight = (this->y1 - this->y0);
    this->mountainMinHeight = (this->y1 - this->y0)*0.25;
    for(int i = 0; i <= this->horizonArraySize; i++){
        this->horizonArray[i] = (this->horizonArray[i] - dy);
    }
    if(dx > 0){
        for(int j = 0; j <= dx; j++){
            this->horizonArray[0] = this->y1;
            for(int i = this->horizonArraySize; i > 0; i--) {
                this->horizonArray[i] = this->horizonArray[i-1];
            }
        }
    }
}

void BackgroungHills::displayMountainsShiftedBy(float n){
    shift += n;
    if(shift>horizonArraySize-1) shift -= (horizonArraySize-1);
    if(shift<0) shift += (horizonArraySize-1);
    displayMountains();
}

void BackgroungHills::displayBackgroundFrame(){
    // TODO: for developing purposes, to see where exactly the frame is located
    this->lcd->drawLineHfast(this->x0, this->y0, this->x1 - this->x0, 1);
    this->lcd->drawLineHfast(this->x0, this->y1, this->x1 - this->x0, 1);
    this->lcd->drawLineVfast(this->x0, this->y0, this->y1 - this->y0, 1);
    this->lcd->drawLineVfast(this->x1, this->y0, this->y1 - this->y0, 1);
}

