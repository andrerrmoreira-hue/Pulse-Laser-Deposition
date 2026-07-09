
#ifndef SWITCH_H
#define SWITCH_H

#define SW_MIN
#define SW_MAX

#define SW_M1 10
#define SW_M2 11

#include <Arduino.h>


class SW {
public:
    SW(int pin);
    void init();
    bool getState();

private:
    bool swState;
    int  swPin;
};

#endif