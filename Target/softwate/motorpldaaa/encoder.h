#ifndef KY_040_H
#define KY_040_H

#include <Arduino.h>
#include "maindefinitions.h"


struct ButtonState {
    uint8_t lastState;
    uint16_t timeLastPress;
};


class KY040 {
public:
    KY040();
    void        init();

    void        updateEncoderState();
    int         getEncoderState();

    void        updateButtonState();
    bool        isShortPressEvent();
    bool        isLongPressEvent();

private:
    int didEncoderRotate();
    int           encoderState;
    volatile int  lastEncoded;
    bool          encoderEvent;
    signed int    value;
    unsigned long debounceTimeEncoder;

    bool          longPressEvent; 
    bool          longPressFired;
    bool          shortPressEvent;
    uint8_t       lastState;
    unsigned long timeLastPress;
    unsigned long debounceTimeButton;
   
};

#endif
