#include "switch.h"


/**************************************************
 * CONSTRUCTORS
 ***************************************************/
SW::SW() {
    pressCount = 0;
    lastState = LOW;
    debounceTimeSw = 0;
}

/**************************************************
 * INICILAIZATIONS
 ***************************************************/
void SW::init() {
    pinMode(SW_PIN, INPUT_PULLUP);
    lastState = digitalRead(SW_PIN);
}

/*********************************************
 * GET PARAMETERS
 ********************************************/
int SW::getNumberOfSwPress() {
    int count = pressCount;
    //pressCount = 0; // reset counter after reading
    return count;
}

void SW::reset(){
    pressCount = 0;
    return;
}



bool SW::isPressed() {
    return pressCount > 0;
}

/*********************************************
 * Update Switch
 ********************************************/
void SW::updateSwitchState() {
    unsigned long now = millis();
    
    if( (now - debounceTimeSw) > SW_DEBOUNCE_MS){
        uint8_t newState = digitalRead(SW_PIN);

        if (lastState == LOW && newState == HIGH) { //detects when switch presed
            pressCount ++;

        }
        debounceTimeSw = now;
        lastState   = newState;
    }
}