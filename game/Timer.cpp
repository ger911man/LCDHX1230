//
// Created by Gera on 27.01.2020.
//

#include "Timer.h"

// constructor
Timer::Timer() {
    currTime = millis();
    prevTime = currTime;
    deltaTime = 0;
}

void Timer::resetFrameTimer() {
    currTime = millis();
    deltaTime = currTime - prevTime;
    prevTime = currTime;
}

uint32_t Timer::getTimer() {
    return deltaTime;
}