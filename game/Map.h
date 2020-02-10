//
// Created by Gera on 06.02.2020.
//

#ifndef MAP_H
#define MAP_H

#include "Maps.h"
#include "HX1230_FB.h"

class Map {
public:
    Map(const uint8_t* map, HX1230_FB* lcd);
    void drawMap(float mapShiftX, float mapShiftY);
    void drawMap(float mapShiftX);
//    boolean isColided();

private:
    HX1230_FB* lcd;
    const uint8_t* currentMap;
    uint8_t mapH;
    uint8_t mapW;
};


#endif //MAP_H
