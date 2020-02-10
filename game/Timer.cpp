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
    // Game slowdown if low FPS. 15FPS: time delay between frames = 67 millis (1000/15=~67);
    if(deltaTime>67) deltaTime = 67;
    prevTime = currTime;
}

//uint32_t Timer::getTimer() {
//    return deltaTime;
//}