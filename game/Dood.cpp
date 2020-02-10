#include "Dood.h"

// Sprite
const uint8_t PROGMEM spriteDood[6][32] = {
        {
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B11000000,
            B11100000, B11111110,
            B11111111, B11111111,
            B00111011, B00011110,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000111,
            B11111111, B11111111,
            B11111111, B10000111,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000
        },

        {
            B00000000, B00000000,
            B00000000, B00000000,
            B10000000, B11000000,
            B11100000, B11111110,
            B11111111, B11111111,
            B10111011, B00011110,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B11000011,
            B11110111, B10111111,
            B10011111, B00001111,
            B11011111, B11111101,
            B10111011, B10010111,
            B00000110, B00000000,
            B00000000, B00000000
        },

        {
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B10000000,
            B11000000, B11100000,
            B11100000, B11111110,
            B11111111, B00111111,
            B10110111, B10011110,
            B00000000, B00000000,
            B00000000, B01000000,
            B11100010, B10111001,
            B00011111, B00011111,
            B00001111, B00101111,
            B01111111, B01011111,
            B00001011, B00000001,
            B00000001, B00000000,
            B00000000, B00000000
        },

        {
            B00000000, B01100000,
            B01110000, B00110000,
            B00110000, B01110000,
            B11111110, B11111111,
            B11101111, B11111111,
            B11101110, B01111000,
            B01110011, B01111111,
            B00111100, B00000000,
            B00000000, B00000100,
            B00000100, B00001110,
            B00011110, B00111000,
            B00111100, B00011111,
            B00001111, B00100111,
            B01110111, B11111111,
            B10011110, B00001110,
            B00000100, B00000000
        },

        {
            B00011111, B00111011,
            B01110000, B11111110,
            B11111111, B11110111,
            B11111111, B11110110,
            B11100000, B11110110,
            B01111110, B00011100,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000000, B00000000,
            B00000001, B11100011,
            B11101111, B01111111,
            B00111111, B00011111,
            B00111100, B01111000,
            B11110000, B11100000,
            B01110000, B00110000
        },

        {   // TODO: not used sprite, modify or delete
            B00000000, B01100000,
            B11110000, B11110000,
            B10110000, B11110000,
            B11111110, B11111111,
            B11101111, B11111111,
            B11101110, B01111000,
            B01110011, B01111111,
            B00111100, B00000000,
            B00010000, B00111000,
            B01111000, B01111001,
            B00111011, B00111111,
            B00111111, B00011111,
            B00001111, B00100111,
            B01110111, B11111111,
            B10111110, B00111100,
            B00011100, B00000000
        }
};

//Constructor
Dood::Dood(uint8_t x0, uint8_t y0, HX1230_FB* lcd, Speaker* speaker){
//    uint8_t prevWalkSpriteChangeAtX = x0;
    coordinates0 =  Vector(x0, y0);
    coordinates1 =  Vector(x0 + DOOD_WIDTH, y0 + DOOD_HEIGHT);
    size = Vector(DOOD_WIDTH, DOOD_HEIGHT);
    doodOrientation=FORWARD;
    this->lcd = lcd;
    this->speaker = speaker;
}

void Dood::display(){
    counterDisplayed++;

    // ----------------------------------------- PHYSICS -----------------------------------------
//    speedModifier = deltaTime / 42.0;
    if(speed.getY() !=0){             // Because you can't move in X axis while jumping
        velocity.setX(0);
    }
    speed+=velocity*deltaTime;
    if(speed.getX() > DOOD_MAX_SPEED){
        speed.setX(DOOD_MAX_SPEED);
    }
    if(speed.getX() < -DOOD_MAX_SPEED){
        speed.setX(-DOOD_MAX_SPEED);
    }
    coordinates0 += speed * deltaTime;
    coordinates1 += size;

    // ----------------------------------------- Manage collisions -----------------------------------------
    doodStayOnSurface();

    // ----------------------------------------- Chose the sprite to display -----------------------------------------
    if(speed.getY() == 0 ){                                 // if on surface
        if(speed.getX() == 0){                              // not moving
            spriteNumber = 0;
        } else {                                            // moving
            if(abs(prevDoodSpriteChangeAtX - coordinates0.getX()) > 3){
                if(spriteNumber == 0) {
                    spriteNumber = 1;
                    prevDoodSpriteChangeAtX = coordinates0.getX();
                } else {
                    spriteNumber = 0;
                    prevDoodSpriteChangeAtX = coordinates0.getX();
                }
            }
        }
    } else {                                                // if jumping
        if(speed.getY() < 0){
            spriteNumber = 2;
        } else {
            spriteNumber = 4;
        }
        if(abs(speed.getY()) < 0.01){
            spriteNumber = 3;
        }
    }

    // ----------------------------------------- Display -----------------------------------------
    if(doodOrientation == FORWARD) {
        lcd->drawSprite(spriteDood[spriteNumber], coordinates0.getX(), coordinates0.getY(), DOOD_WIDTH, DOOD_HEIGHT);
    }
    if(doodOrientation == BACKWARD) {
        lcd->drawSpriteMirror(spriteDood[spriteNumber], coordinates0.getX(), coordinates0.getY(), DOOD_WIDTH, DOOD_HEIGHT);
    }
    for(int i=0;i<6;i++){
        lcd->drawSprite(spriteDood[i], i * 16, 20, DOOD_WIDTH, DOOD_HEIGHT);
    }
}

void Dood::doodJump(){
    if(speed.getY() == 0){
        speaker->soundJump();
        speed.setY(JUMP_IMPULSE_SPEED);
        velocity.setY(GRAVITY_VELOCITY);
    }
}

void Dood::doodLongJump(){
    //make jump longer by decreasing the gravity
    if(speed.getY() != 0){
        velocity.setY(GRAVITY_VELOCITY / 3.5); //gravity/3.5 allows you to jump almost to the top of the screen
    }
}

void Dood::doodRegularJump(){
    if(speed.getY() != 0){
        velocity.setY(GRAVITY_VELOCITY);
    }
}

void Dood::moveRight(){
    velocity.setX( THROTTLE_VELOCITY);
    doodOrientation = FORWARD;
}

void Dood::moveLeft(){
    velocity.setX(-THROTTLE_VELOCITY);
    doodOrientation = BACKWARD;
}

void Dood::brake(){
    if(speed.getX() != 0){
        if(abs(speed.getX()) <= BRAKING_VELOCITY*deltaTime){
            speed.setX(0);
            velocity.setX(0);
        } else {
            if(speed.getX() > 0){
                velocity.setX(-BRAKING_VELOCITY);
            } else {
                velocity.setX(BRAKING_VELOCITY);
            }
        }
    }
}

void Dood::setCoordinates(uint8_t x0, uint8_t y0){
    coordinates0.setXY(x0, y0);
}

void Dood::setSpeedX(float x){
    this->speed.setX(x);
}

void Dood::setSpeedY(float y){
    this->speed.setY(y);
}

void Dood::setVelocityX(float x){
    this->velocity.setX(x);
}

void Dood::setVelocityY(float y){
    this->velocity.setY(y);
}

void Dood::setSpeedVector(float x, float y){
    this->speed.setXY(x, y);
}

void Dood::setVelocityVector(float x, float y){
    this->velocity.setXY(x, y);
}

void Dood::doodStayOnSurface(){
    if(coordinates0.getX() > LCD_NOKIA_WIDTH - DOOD_WIDTH) {
        coordinates0.setX(LCD_NOKIA_WIDTH - DOOD_WIDTH);
        speed.setX(0);
        velocity.setX(0);
    }
    if(coordinates0.getX() < 0) {
        coordinates0.setX(0);
        speed.setX(0);
        velocity.setX(0);
    }
    if(coordinates0.getY() > LCD_NOKIA_HEIGHT - DOOD_HEIGHT){
        coordinates0.setY(LCD_NOKIA_HEIGHT - DOOD_HEIGHT - 1);
        speed.setY(0);
        velocity.setY(0);
        speaker->soundLand();
    }
    if(coordinates0.getY() < 0){
        coordinates0.setY(0);
        speed.invertY();
        speaker->soundLand();
    }
}