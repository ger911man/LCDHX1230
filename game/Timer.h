//
// Created by Gera on 27.01.2020.
//

#ifndef TIMER_H
#define TIMER_H

#include "Globals.h"

class Timer {
public:
    Timer();
    //uint32_t getTimer();
    void resetFrameTimer();

private:
    uint32_t  currTime = 0;
    uint32_t  prevTime = 0;
};


#endif //TIMER_H
