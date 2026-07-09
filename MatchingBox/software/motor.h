
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define COILA_M2 8 //coil 1
#define COILB_M2 9 //coil 4
#define COILC_M2 7 //coil 3
#define COILD_M2 6 //coil 2

#define COILA_M1 2  //coil 1  
#define COILB_M1 3  //coil 4  
#define COILC_M1 4  //coil 3   
#define COILD_M1 5  //coil 2  


#define CLOCK 0
#define ANTICLOCK 1

class Motor {
public:
    Motor(int coilA, int coilB, int coilC, int coilD);
    void init();
    void update();
    void start();
    void stop();
    bool getState();
    void setDirection(int);
    int  getDirection();
    int  getNumberSteps();

private:
    void setStep(int stepIndex);

    int coilApin;
    int coilBpin;
    int coilCpin;
    int coilDpin;

    bool enable;
    int direction;
    int stepIndex;
    int numberSteps;
    unsigned long timeLastStep;
    unsigned long delayBetweenSteps;
};

#endif