#ifndef MYLCD_H
#define MYLCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "maindefinitions.h"
#include "encoder.h"
#include "motor.h"


struct displayInfo{
    bool   menuEditMode;
    int    menuState;
    int    target;
    bool   rotation;
    bool   shut;
    int    speed; 
};

class MyLCD {
public:
    MyLCD();                  
    void init();               
    void mainScreen( );
    void updateDisplay(bool, int, int, int, int, int);
    void targetFinding();
    void targetReached();

private:
    void updateTarget();
    void updateShut();
    void updateSpeed();
    void updateRotation();
    void putEditModeIndicator();
    void takeOutEditModeIndicator();
    void updateSelectMenuIndicator();
    LiquidCrystal_I2C lcd;

    // Custom characters
    static const uint8_t arrowRight[8];
    static const uint8_t arrowUD[8];

    static displayInfo current;
    static displayInfo last;
    static MyLCD* instance;
};

#endif


