#include "BackgroungHills.h"

BackgroungHills::BackgroungHills(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, HX1230_FB* lcd){
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->horizonArraySize = x1 - x0 + 1;
    this->horizonArray = new uint8_t[this->horizonArraySize];
    this->lcd = lcd;
    this->mountainMaxHeight = (this->y1 - this->y0);
    this->mountainMinHeight = (this->y1 - this->y0)*0.15;
    for(int i = 1; i < horizonArraySize;){
        uint8_t p = random(mountainMinHeight, mountainMaxHeight);
        for(int j = y1; j >= y1 - p && i < horizonArraySize; j--){
            horizonArray[i] = j;
            i++;
        }
        for(int j = y1 - p; j <= y1 && i < horizonArraySize; j++){
            horizonArray[i] = j;
            i++;
        }
    }
    if(horizonArray[horizonArraySize-1]+1<y1){
        horizonArray[1]=horizonArray[horizonArraySize-1]+1;
        for(int i=2; i < y1 - horizonArray[horizonArraySize - 1]-2; i++){
            horizonArray[i]=horizonArray[i-1]+1;
        }
    }

}

void BackgroungHills::displayMountains()
{
    for(int i = 1; i < horizonArraySize; i++){
        lcd->drawLineVfastD(x0+i,horizonArray[i],y1,1);
//        this->lcd->drawPixel(x0+i,horizonArray[i],1);

//        if (this->horizonArray[i]%2 == 0){
//            //Magic formula to draw a mountain: line [ix0,iy0,ix1+n*2,iy1+n] + ...
//            //tang = 2/1 = 2.0
//            uint8_t ix1 = this->x0 + i + (this->y1 - this->horizonArray[i]) / 2;
//            //Draw mountains only inside the frame (Right side, even)
//            if(ix1 <= this->x1){
//                this->lcd->drawLine(this->x0 + i, this->horizonArray[i], ix1, this->y1, 1);
//            } else {
//                this->lcd->drawLine(this->x0 + i, this->horizonArray[i], this->x1,  this->y1 - (ix1 - this->x1)*2, 1);
//            }
//            //Draw mountains only inside the frame (Left side, even)
//            if(i == 0){
//                for(int iy0 = this->horizonArray[i] + 6; iy0 < this->y1; iy0 += 6){
//                    uint8_t  ix1 = this->x0 + (this->y1 - iy0) / 2;
//                    this->lcd->drawLine(this->x0, iy0, ix1, this->y1, 1);
//                }
//            }
//        } else {
//            this->lcd->drawPixel(this->x0 + i,this->horizonArray[i], 1);
//            //Draw mountains only inside the frame (Left side, odd)
//            if(i == 0){
//                for(int iy0 = this->horizonArray[i] + 3; iy0 < this->y1; iy0 += 6){
//                    uint8_t  ix1 = this->x0 + (this->y1 - iy0) / 2;
//                    this->lcd->drawLine(this->x0, iy0, ix1, this->y1, 1);
//                }
//            }
//        }
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
    float k;
    shift += n;
    shift = modff(shift, &k);
    if(k > 0){
        for (int j = 1; j <= k; j++) {
            for (int i = 1; i < horizonArraySize; i++) {
                horizonArray[i-1] = horizonArray[i];
            }
            horizonArray[horizonArraySize-1] = horizonArray[0];
        }
    }
    if(k < 0){
        for (int j = -1; j >= k; j--) {
            horizonArray[0] = horizonArray[horizonArraySize - 1];
            for (int i = horizonArraySize - 1; i > 0 ; i--) {
                horizonArray[i] = horizonArray[i-1];
            }
        }
    }
//        if(k < 0) {
//            for (int j = -1; j >= k; j--) {
//                //The first pixel of the horizon array never displayed, it's used to create the landscape...
//                for (int i = 1; i < this->horizonArraySize; i++) {
//                    this->horizonArray[i] = this->horizonArray[i + 1];
//                }
//
//                //Check if the last pixel of the horizon is on bottom. If so: create the uphill.
//                if (this->horizonArray[this->horizonArraySize] >= this->y1) {
//                    this->isUphill = true;
//                    this->nextMountainTop = this->y1 - random(this->mountainMinHeight, this->mountainMaxHeight);
//                }
//
//                //Check if the last pixel of the horizon is on top of the mountain. If so: downhill.
//                if (this->horizonArray[this->horizonArraySize] <= this->nextMountainTop) {
//                    this->isUphill = false;
//                }
//
//                //Move the last pixel up/down(decr/incr) according to the "isUphill" var
//                if (this->isUphill) {
//                    this->horizonArray[this->horizonArraySize] -= 1;
//                } else {
//                    this->horizonArray[this->horizonArraySize] += 1;
//                }
//            }
//        }

    displayMountains();
}

void BackgroungHills::displayBackgroundFrame(){
    // TODO: for developing purposes, to see where exactly the frame is located
    this->lcd->drawLineHfast(this->x0, this->y0, this->x1 - this->x0, 1);
    this->lcd->drawLineHfast(this->x0, this->y1, this->x1 - this->x0, 1);
    this->lcd->drawLineVfast(this->x0, this->y0, this->y1 - this->y0, 1);
    this->lcd->drawLineVfast(this->x1, this->y0, this->y1 - this->y0, 1);
}

