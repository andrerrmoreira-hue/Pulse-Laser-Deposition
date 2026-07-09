#include "encoder.h"



// ---------------- CONSTRUCTOR ----------------
KY040::KY040() {
    encoderState = ENC_NONE;
    encoderEvent = false;
    lastEncoded  = 0;
    value        = 0;

    lastState           = HIGH;
    debounceTimeButton  = 0;
    longPressEvent      = false;
    shortPressEvent     = false;
    timeLastPress       = 0;
}


/*******************************************************
                    ENCODER

*********************************************************/
void KY040::init() {
    pinMode(ENCODER_CLK, INPUT_PULLUP);
    pinMode(ENCODER_DT,  INPUT_PULLUP);
    pinMode(ENCODER_SW,  INPUT_PULLUP);
        
    int MSB = digitalRead(ENCODER_CLK);
    int LSB = digitalRead(ENCODER_DT);
    lastEncoded = (MSB << 1) | LSB; //critical fix

    int trash = isShortPressEvent();
}


/*******************************************************
                    BUTTON

*********************************************************/
void KY040::updateButtonState() {
    unsigned long now = millis();
    
    if( (now - debounceTimeButton) > BUTTON_DEBOUNCE_MS){
        uint8_t newState = digitalRead(ENCODER_SW);

        if (lastState == HIGH && newState == LOW) { // Detect press (HIGH → LOW)
            timeLastPress = now;
            longPressFired = false;
        }

        if (newState == LOW && !longPressFired) {
            if ((now - timeLastPress) >= SHORT_PRESS_TIME) {
                longPressEvent = true;
                longPressFired = true;
            }
        }

        if (lastState == LOW && newState == HIGH) {
            unsigned long pressTime = now - timeLastPress;
            if (pressTime < SHORT_PRESS_TIME && !longPressFired) { // Only generate short if long wasn't already fired
                shortPressEvent = true;
            }
        }

        debounceTimeButton = now;
        lastState   = newState;
    }
}


bool KY040::isShortPressEvent(){
   if (shortPressEvent) {
        shortPressEvent = false;   // consume
        return true;
   }
    return false;
}

bool KY040::isLongPressEvent(){
   if (longPressEvent) {
        longPressEvent = false;   // consume
        return true;
   }
    return false;
}



/*******************************************************
                    ENCODER

*********************************************************/
void KY040::updateEncoderState(){
    int MSB     = digitalRead(ENCODER_CLK);
    int LSB     = digitalRead(ENCODER_DT);
    int encoded = (MSB << 1) | LSB;
    int sum     = (lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011){
        value = value + 1;
    }
    else if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000){
        value = value - 1;
    }
    lastEncoded = encoded;


    if(value > 10){
        encoderState = ENC_RIGHT;
        value        = 0;
        encoderEvent = true;
    }
    else if(value < -10){
        encoderState = ENC_LEFT;
        value        = 0;
        encoderEvent = true;
    }
    else{
        encoderState = ENC_NONE;
        encoderEvent = false;
    }    
}


int KY040::didEncoderRotate(){
    if(encoderEvent){
        encoderEvent = false;
        return true;
    }
    else{
        return false;
    }
}

int KY040::getEncoderState(){
    if(didEncoderRotate()) return encoderState;
    return ENC_NONE;
}



