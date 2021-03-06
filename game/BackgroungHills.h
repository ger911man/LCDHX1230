#ifndef BACKGROUNGHILLS_H
#define BACKGROUNGHILLS_H

#include "HX1230_FB.h"

#define MOUNTAINS_QUANTITY 3

class BackgroungHills {

public:
    BackgroungHills(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, HX1230_FB* lcd);

    void displayMountains(); //draw background to display's buffer

    void setFrame(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1); //change the size of background (scale)

    void displayMountainsShiftedBy(float n); //slide background

    void displayBackgroundFrame(); // TODO: remove? for developing purposes, to see where exactly the frame is located

private:
    float shift = 0;
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
    HX1230_FB* lcd;
    uint8_t *horizonArray;
    uint8_t horizonArraySize;
    uint8_t mountainMaxHeight;
    uint8_t mountainMinHeight;
};

#endif //BACKGROUNGHILLS_H