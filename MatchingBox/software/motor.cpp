#include "Arduino.h"
#include "motor.h"

const byte stepSequence[4][4] = {
  {1,0,0,0}, 
  {0,1,0,0}, 
  {0,0,1,0}, 
  {0,0,0,1}
};

/**************************************************
 * CONSTRUCTORS
 ***************************************************/
Motor::Motor(int coilA, int coilB, int coilC, int coilD) {
    coilApin = coilA;
    coilBpin = coilB;
    coilCpin = coilC;
    coilDpin = coilD;

    enable = false;
    direction = ANTICLOCK;
    stepIndex = 0;
    timeLastStep = 0;
    numberSteps = 0;
    delayBetweenSteps = 11; // Default delay between steps (in milliseconds)
}


/**************************************************
 * INICILAIZATION
 ***************************************************/
void Motor::init() {
  pinMode(coilApin, OUTPUT);
  pinMode(coilBpin, OUTPUT);
  pinMode(coilCpin, OUTPUT);
  pinMode(coilDpin, OUTPUT);
}


/*************************************************
    Update motor
 *************************************************/
void Motor::setStep(int stepIndex) {
  digitalWrite(coilApin, stepSequence[stepIndex][0]);
  digitalWrite(coilBpin, stepSequence[stepIndex][1]);
  digitalWrite(coilCpin, stepSequence[stepIndex][2]);
  digitalWrite(coilDpin, stepSequence[stepIndex][3]);
}


void Motor::update(){
    if (!enable) return;

    unsigned long now = millis(); 

    if (now - timeLastStep >= delayBetweenSteps) {
        if(direction == CLOCK){
            stepIndex = (stepIndex + 3) & 0x03;
            numberSteps = numberSteps +1;
        }   
        else{
            stepIndex = (stepIndex + 1) & 0x03;
            if(numberSteps > 0) numberSteps = numberSteps - 1;
        }       

        timeLastStep = now;
        setStep(stepIndex);
    }
}


void Motor::start(){
    enable = true;
}


void Motor::stop(){
    enable = false;
    numberSteps = 0;
}


void Motor::setDirection(int motorDirection){
    direction = motorDirection;
}

int Motor::getDirection( ){
    return direction;
}

bool Motor::getState(){
    return enable;
}

int Motor::getNumberSteps(){
    return numberSteps;
}







