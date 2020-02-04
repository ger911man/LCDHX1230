#ifndef DOOD_H
#define DOOD_H

#include "Vector.h"
#include "Globals.h"
#include "HX1230_FB.h"


#define DOOD_MAX_SPEED 1
#define DOOD_SIZE_X 16
#define DOOD_SIZE_Y 16

class Dood {
public:
    //constructor
    Dood(uint8_t x0, uint8_t y0, HX1230_FB* lcd);

    //calculate coordinates of dood according to it's speeds & velocities, put it's sprite to the screen buffer
    void display();

    //dood jumps
    void doodJump(); //jump start speed on button hit
    void doodLongJump(); //long jump if button remain pressed
    void doodRegularJump(); //jump will not so high and long if button released

    //dood moves
    void moveRight();
    void moveLeft();
    void brake(); //Dood slowdown/stop if buttons are not pressed

    //teleports dood to
    void setCoordinates(uint8_t x0, uint8_t y0);

    //pushes dood in any direction
    void setSpeedX(float x);  //for kickback etc...
    void setSpeedY(float y);  //for jumping or falling
    void setSpeedVector(float x, float y);

    //gain || loosing speed in any direction
    void setVelocityX(float x);
    void setVelocityY(float y);
    void setVelocityVector(float x, float y);

private:
    Vector speed = Vector(0, 0);
    Vector velocity = Vector(0, GRAVITY_VELOCITY);
    Vector coordinates0;
    Vector coordinates1;
    Vector size;
    uint8_t prevRideSpriteChangeAtX = 0;
    uint8_t spriteNumber = 0;
    uint32_t counterDisplayed = 0;
    float speedModifier = 1;
//    boolean isAlive = true;
//    boolean isRiding = false; //isMooving
//    boolean isJumping = false;
    HX1230_FB* lcd;

    void doodStayOnSurface();
};
#endif //DOOD_H