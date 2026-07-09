
#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>
#include "maindefinitions.h"

class SW {   // switch to the target
public:
    SW();
    void init();
    bool isPressed();
    int getNumberOfSwPress();
    void updateSwitchState();
    void reset();

private:
    uint8_t pressCount;
    uint8_t lastState;
    unsigned long debounceTimeSw;
};

#endif