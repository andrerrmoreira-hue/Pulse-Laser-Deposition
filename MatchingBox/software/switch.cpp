#include "Arduino.h"
#include "switch.h"


/**************************************************
 * CONSTRUCTORS
 ***************************************************/
SW::SW(int pin) {
    swState = false;
    swPin   = pin;
}

/**************************************************
 * INICILAIZATION
 ***************************************************/
void SW::init() {
    pinMode(swPin, INPUT);
}


/**************************************************
 * GET
 ***************************************************/

 bool SW::getState(){
    return digitalRead(swPin);
 }

