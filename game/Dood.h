#ifndef DOOD_H
#define DOOD_H

#include "Globals.h"
#include "Vector.h"
#include "Speaker.h"
#include "HX1230_FB.h"

#define GRAVITY_VELOCITY 0.0001
#define BRAKING_VELOCITY 0.0001
#define THROTTLE_VELOCITY 0.0001
#define JUMP_IMPULSE_SPEED (-0.05)
#define DOOD_MAX_SPEED 0.03
#define DOOD_WIDTH 16
#define DOOD_HEIGHT 16
#define FORWARD 0
#define UPWARD 1
#define BACKWARD 2
#define DOWNWARD 3

class Dood {
public:
    //constructor
    Dood(uint8_t x0, uint8_t y0, HX1230_FB* lcd, Speaker* speaker);

    //calculate coordinates of dood according to it's speeds & velocities, put it's sprite to the screen buffer
    void display();

    //dood jumps
    void doodJump(); //jump start speed on button hit
    void doodLongJump(); //long jump if button remain pressed
    void doodRegularJump(); //jump will not so high and long if button released

    //dood moves
    void moveRight();
    void moveLeft();
    void brake(); //Dood slowdown/stop if move buttons are not pressed

    //teleports dood to
    void setCoordinates(uint8_t x0, uint8_t y0);

    //pushes dood in any direction
    void setSpeedX(float x);  //for kickback etc...
    void setSpeedY(float y);  //for jumping or falling
    void setSpeedVector(float x, float y);

    //gaging || loosing speed in any direction
    void setVelocityX(float x);
    void setVelocityY(float y);
    void setVelocityVector(float x, float y);

private:
    Vector speed = Vector(0, 0);
    Vector velocity = Vector(0, GRAVITY_VELOCITY);
    Vector coordinates0;
    Vector coordinates1;
    Vector size;
    uint8_t prevDoodSpriteChangeAtX = 0;
    uint8_t spriteNumber = 0;
    uint32_t counterDisplayed = 0;
    uint8_t doodOrientation = FORWARD;
//    boolean isAlive = true;
//    boolean isRiding = false; //isMooving
//    boolean isJumping = false;
    HX1230_FB* lcd;
    Speaker* speaker;

    void doodStayOnSurface();
};
#endif //DOOD_H