//
// Created by Gera on 27.01.2020.
//

#ifndef FPS_H
#define FPS_H

#include "../HX1230_FB.h"

#define FPS_DISPLAY_RATE 1000   //ms

class Fps {
public:
    Fps(HX1230_FB* lcd);
    void draw();
private:
    char buf[4];
    uint32_t  prevFpsTime = 0;
    uint32_t  fpsCounter = 0;
    uint32_t  fps = 0;
    HX1230_FB* lcd;
};


#endif //FPS_H
