#include "Arduino.h"
int led = 13;
int voltTest = 12;

// the setup routine runs once when you press reset:
void setup() {
    // initialize the digital pin as an output.
    pinMode(led, OUTPUT);
    pinMode(voltTest, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(voltTest, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(voltTest, LOW);    // turn the LED off by making the voltage LOW
    delay(2000);               // wait for a second
}
