#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "maindefinitions.h"
#include "switch.h"


class Motor {
public:
    Motor();
    void init();
    void updateMotor();
    
    int  getDirection();
    void setDirection(int);
    void start();
    void stop();
    void setTargetRotationSpeed();
    void setTargetRotation();

    void previewTargetRotation(int);

    void updateTarget(int);
    void moveToTarget(bool, SW&);
    bool isMovingToTarget();
    int  getTargetStateMachine();
    int  nTimesSwToGoRightTarget();
    int  getTarget();
    int  getCurrentTarget();

    
    int  getMotorEnable();
    void previewMotorEnable(int);
    void updateMotorEnable();

    int  getSpeed();
    void previewSpeed(int);
    void updateSpeed();

    bool moveAngle(float);
    bool isMoveAnticlock();
    void moveAnticlock();
    void stopAntiClock();


private:
    void setStep(int);
    
    int  currentTarget;
    int  stepIndex;
    int  motorEnabled;
    int  rotateDirection;
    int  targetRotationSpeed;
    unsigned long lastStep;

    int  previewTargetRotationSpeed;
    int previewtargetRotation;
    int previewMotorenable;
    int previewTarget;

    int stepsRemaining;
    bool stepMoveActive;
    int storedEnableState;

    int  targetStateMachine;
    bool movingToTarget;
};

/*

    Motor();
    void init();
  
    void start();
    void stop();
    
    void setSpeedRotateTarget( );           
    int  getSpeed( );
    void updateSpeed(int);

    void updateRotation(int);
    void setRotation();
    int  getRotation();
    int  getRotationDirection();
    void setRotateDirection(int direction);
    void setSpeedChangeTarget();
    
    void setTarget(SW sw);
    int  getTarget();
    void updateTarget(int);
    
    void updateMotor();
    static void updateStep();     // Called from ISR THIS METHOD IS PRIVATE! is only public due to problems with ISR routine      

private:







    void setStep(int index);      // Non-static, private
    void moveToFarTarget(SW);
    void moveToCloseTarget(SW);
    void moveToSameTarget(SW sw);
    void moveDegrees(int);
    int stepIndex;
    int stepInterval;             // timer compare value
    int direction;
    int speedRPM;
    int target;
    int rotate;
    volatile long stepsRemaining;
    static Motor* instance;       // static pointer to ISR

    int speedClockWise;
    int speedAntioClockWise;
    int motorEnabled;
};
*/

#endif
