//
// Created by Gera on 06.02.2020.
//

#include "Map.h"
#include "Sprites.h"

//Constructor
Map::Map(const uint8_t* map, HX1230_FB* lcd){
    this->lcd=lcd;
    currentMap=map+2;
    mapH = pgm_read_byte(map + 0);
    mapW = pgm_read_byte(map + 1);
}

void Map::drawMap(float mapShiftX) {
    drawMap(mapShiftX, 0);
}

void Map::drawMap(float mapShiftX, float mapShiftY) {
    uint32_t cameraPositionX = mapShiftX;
    uint8_t cameraPositionY = SCR_HT + mapShiftY;
    uint8_t mapW = (this->mapW+7)/8;

    uint8_t xFirst = mapW - cameraPositionX / 64, xLast = mapW - (cameraPositionX + SCR_WD) / 64;
    int16_t firstSpritePosition = - (cameraPositionX & 7);
    uint8_t firstBiteShift = (cameraPositionX & 63) / 8 ;
    uint8_t lastBiteShift = ((cameraPositionX + SCR_WD) & 63) /8 ;
    uint8_t mapByte;
    uint8_t bitFirst, bitLast;

    uint8_t xx=0;
    for(uint8_t y=1; y <= mapH; y++) {
        xx=0;
        for (int8_t x = xFirst; x >= xLast; x--) {
            mapByte = pgm_read_byte(currentMap + x*mapH - y);
            if(x == xFirst) {
                mapByte <<= firstBiteShift;
                bitFirst = firstBiteShift;
                bitLast = 7;
            } else if(x==xLast){
                bitFirst = 0;
                bitLast = lastBiteShift;
            } else {
                bitFirst=0;
                bitLast=7;
            }
            for(uint8_t bit = bitFirst; bit <= bitLast; bit++){
                if(mapByte & B10000000){
                    lcd->drawSprite(platform, firstSpritePosition + xx*8,cameraPositionY - y*8);
                }
                xx++;
                mapByte <<= 1;
            }
        }
    }
}