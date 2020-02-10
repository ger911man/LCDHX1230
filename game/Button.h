#ifndef BUTTON_H
#define BUTTON_H

/*
 * Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
 * HIGH when it's open, and LOW when it's pressed
 */

#include "Globals.h"
#include "Speaker.h"

class Button {
public:
    //constructor
    Button(uint8_t pin, Speaker *speaker);

    boolean isHit(); //Exactly when the button was hit

    boolean isReleased(); //Exactly when the button was released

    boolean getState(); // Check the button state, returns true if button remain pressed, false if unpressed

    boolean getPrevState(); // Check prev button state

private:
    boolean currentState;
    boolean prevState;
    uint8_t pin;
    Speaker *speaker;


};
#endif //BUTTON_H
