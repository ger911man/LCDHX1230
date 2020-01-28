//
// Created by Gera on 27.01.2020.
//

#ifndef FPS_H
#define FPS_H

#include "HX1230_FB.h"

#define FPS_DISPLAY_RATE 1000   //ms
#define FPS_X_POS 2
#define FPS_Y_POS 1

class Fps {
public:
    explicit Fps(HX1230_FB* lcd);
    void draw();
private:
    char buf[8];
    uint32_t  prevFpsTime = 0;
    uint32_t  fpsCounter = 0;
    uint32_t  fps = 0;
    HX1230_FB* lcd;
};


#endif //FPS_H
