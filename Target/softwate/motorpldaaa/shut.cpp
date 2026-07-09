#include "shut.h"


Shut::Shut() {
    shutState = SHUT_OFF;
}

void Shut::init() {
    pinMode(SHUT_PIN_1A, OUTPUT);
    pinMode(SHUT_PIN_2A, OUTPUT);
    updateShut();
}


void Shut::previewShut(int encoder){
    if( (encoder == ENC_LEFT) || (encoder == ENC_RIGHT) ){ 
        if(shutState == SHUT_OFF){
            shutState = SHUT_ON;
        }
        else{                     
            shutState = SHUT_OFF; //if(shutState == SHUT_ON)
        }
    }
}

bool Shut::getShut(){
    return shutState;
}   

void Shut::updateShut(){
    if ( shutState == SHUT_ON) {
        digitalWrite(SHUT_PIN_1A, LOW);
        digitalWrite(SHUT_PIN_2A, HIGH);
    } 
    else {
        digitalWrite(SHUT_PIN_1A, HIGH);
        digitalWrite(SHUT_PIN_2A, LOW);
    }
}