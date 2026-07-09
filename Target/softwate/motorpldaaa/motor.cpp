
#include "motor.h"


// Step sequence
const byte stepSequence[4][4] = {
  {1,0,0,0},  // A 
  {0,1,0,0},  // B
  {0,0,1,0},  // C
  {0,0,0,1}   // D
};


/**************************************************
 * CONSTRUCTORS
 ***************************************************/
Motor::Motor() {
    stepIndex       = 0;
    lastStep        = 0;
    motorEnabled    = ROTATION_OFF;
    rotateDirection = CLOCKWISE;
    targetRotationSpeed = DEFAUT_RPM;   
    stepsRemaining   = 0;
    stepMoveActive  = false;

    movingToTarget = false;
    targetStateMachine = IDDLE;
    currentTarget = DEFAUT_TARGET;
    previewTarget = DEFAUT_TARGET;

    previewTargetRotationSpeed = DEFAUT_RPM; //previews not define the motor variables, only preview for dispaly
    previewtargetRotation = ROTATION_OFF;    //please use the step method to load the preview into motor
}


/**************************************************
 * INICILAIZATIONS
 ***************************************************/
void Motor::init(){
    pinMode(COILA, OUTPUT);
    pinMode(COILB, OUTPUT);
    pinMode(COILC, OUTPUT);
    pinMode(COILD, OUTPUT);
    setStep(stepIndex);
}


/*************************************************
    Update motor
 *************************************************/
void Motor::setStep(int index) {
  digitalWrite(COILA, stepSequence[index][0]);
  digitalWrite(COILB, stepSequence[index][1]);
  digitalWrite(COILC, stepSequence[index][2]);
  digitalWrite(COILD, stepSequence[index][3]);
}


void Motor::updateMotor(){
    if ( motorEnabled == ROTATION_OFF ) return;
    unsigned long now = millis(); 
    if (rotateDirection == CLOCKWISE) {
        if (now - lastStep >= targetRotationSpeed) {
            lastStep = now;
            stepIndex = (stepIndex + 3) & 0x03;
            setStep(stepIndex);
        }
    }
    else { // ANTICLOCKWISE
        if (now - lastStep >= CHANGE_TARGET__ROTATION_SPEED) {
            lastStep = now;
            stepIndex = (stepIndex + 1) & 0x03;
            setStep(stepIndex);

            if( (stepMoveActive) && (stepsRemaining>0) ) stepsRemaining --;
        }
    }
}


double outputRpsToStepDelay(double outputRPS)
{
    const int stepsPerDegree = 2;
    const int degreesPerRotation = 360;
    const int motorTeeth = 21;
    const int outputTeeth = 33;

    int stepsPerMotorRotation = stepsPerDegree * degreesPerRotation;
    
    double stepsPerOutputRotation = stepsPerMotorRotation * ((double)outputTeeth / motorTeeth);

    double stepsPerSecond = outputRPS * stepsPerOutputRotation;

    return 1000.0 / stepsPerSecond;  // milliseconds per step
}




/**************************************************
 * START and STOP
 ***************************************************/
void Motor::start(){ motorEnabled = ROTATION_ON; }
void Motor::stop() { motorEnabled = ROTATION_OFF; }


void Motor::setDirection(int dt){
    rotateDirection = dt;
}

int Motor::getDirection(){
    return rotateDirection;
}

void Motor::setTargetRotationSpeed(){
    targetRotationSpeed = previewTargetRotationSpeed;
}

void Motor::setTargetRotation(){ //ON or OFF
    motorEnabled = previewtargetRotation;
}






/*
/*************************************************
 *  UPDATE PARAMETERS
 *************************************************/


//------------------------ speed ------------------------------------
void Motor::previewSpeed(int encoder){ 
    if(encoder == ENC_RIGHT){
        /*if(previewTargetRotationSpeed == 1){ //1 means 2 hz
            previewTargetRotationSpeed = 2; //2 means 1.5hz
        }
        else{ 
            if(previewTargetRotationSpeed == 2){ 
                 previewTargetRotationSpeed = 4;
            }
            else{*/
                if(previewTargetRotationSpeed < MAX_SPEED){ 
                    previewTargetRotationSpeed = previewTargetRotationSpeed + 3;
                }
                else{
                    previewTargetRotationSpeed = MAX_SPEED; 
                }
            //}
        //}
    }

    if(encoder == ENC_LEFT){
      if(previewTargetRotationSpeed > 4){ //defaut is 10, minus 2 is 7  7>4, next cycle not enter here
            previewTargetRotationSpeed = previewTargetRotationSpeed-3;
        }
        //comentar este else se for descomentada a seccao a abaixo
        else{
            previewTargetRotationSpeed = previewTargetRotationSpeed;
        }

    /*    else{
            if(previewTargetRotationSpeed == 4){
                previewTargetRotationSpeed = 2;
            }
            else{
                if(previewTargetRotationSpeed == 2){
                    previewTargetRotationSpeed = 1;
                }
                else{
                    previewTargetRotationSpeed = 1;
                }
            }
        }*/
    }
}



int Motor::getSpeed(){
    return previewTargetRotationSpeed;
}

void Motor::updateSpeed(){
    targetRotationSpeed = previewTargetRotationSpeed;
}


//-------------------- preview motor enable -----------------------
void Motor::previewMotorEnable(int encoder){
    if( (encoder == ENC_LEFT) || (encoder == ENC_RIGHT) ){ 
        if(previewMotorenable ==  ROTATION_OFF){
            previewMotorenable  = ROTATION_ON;
        }
        else{                     
            previewMotorenable  = ROTATION_OFF; //if(shutState == SHUT_ON)
        }
    }
}

int Motor::getMotorEnable(){
    return previewMotorenable ;
}   

void Motor::updateMotorEnable(){
    if(previewMotorenable == ROTATION_OFF) stop();
    if(previewMotorenable == ROTATION_ON) start();
}



//---------------------- target ----------------------------------
void Motor::updateTarget(int encoder){
  if(encoder == ENC_RIGHT)
    if(previewTarget <= (NUMBER_OF_TARGETS-1) ) 
        previewTarget  ++;
    else 
        previewTarget  = 0 + 1;

  if(encoder == ENC_LEFT)
    if(previewTarget  >= 2)    
        previewTarget --;
    else
        previewTarget  = NUMBER_OF_TARGETS;
}


void Motor::previewTargetRotation(int encoder){
    if( (encoder == ENC_LEFT) || (encoder == ENC_RIGHT) ) 
        if(previewtargetRotation == ROTATION_OFF) 
            previewtargetRotation = ROTATION_ON;
        else                       
            previewtargetRotation = ROTATION_OFF; 
}



/****************************
    retrun tru only the steps where moved
*/
bool Motor::moveAngle(float angle){

    long steps = (long)((angle * STEPS_PER_REVOLUTION) / 360.0);

    if(steps <= 0)   return true;

    if(stepMoveActive){
        if(stepsRemaining > 0) return false;
        else{
            stepMoveActive = false;
            motorEnabled = storedEnableState;
            rotateDirection = CLOCKWISE;
            return true; //the movement was concluded
        }
    }

    else{
        storedEnableState = motorEnabled;
        stepsRemaining = steps;
        stepMoveActive = true;
        rotateDirection = ANTICLOCKWISE;
        motorEnabled = ROTATION_ON;
        return false; //it will start to move
    }
}




void Motor::moveAnticlock(){
    if( motorEnabled && (rotateDirection==ANTICLOCKWISE) ) return;
    storedEnableState = motorEnabled;
    rotateDirection  = ANTICLOCKWISE;
    motorEnabled = ROTATION_ON;
}

bool Motor::isMoveAnticlock(){
    if(  motorEnabled && (rotateDirection==ANTICLOCKWISE) ) return true;
    return false;
}

void Motor::stopAntiClock(){
    rotateDirection = CLOCKWISE;
    motorEnabled = storedEnableState;
}




/********************************************************************
this fuction controls the target.
the fuction stays in iddle, when the instruction to change the target is false (means exit the iddle when press the button)

when is gived the instrcution to change the target by pressing the button:
1. go to a thooth, that could be a 1, 2 or 3 tooth
2. move a little in order to exit the thoth
3. move until the switch be pressed, and you know you are in  a first thooth
4. move a little to count the number of thooth to know the current target you are
5. then move until the switch give the necessary amount of clicks to move ot the desier target
*/


void Motor::moveToTarget(bool buttonPressed, SW& sw){
  int timesSwitchPressed = sw.getNumberOfSwPress();

  switch(targetStateMachine){
    case IDDLE:
        if(buttonPressed){
            targetStateMachine = FINDPOSITIONTODISCARD;
        }
        movingToTarget = false;
    break;

    case FINDPOSITIONTODISCARD: //discard the first position, to avoid be in a middle of one hole
      if( (timesSwitchPressed >= 1) && isMoveAnticlock() ){
        stopAntiClock();
        sw.reset();
        targetStateMachine = DISCARDFIRSTPOS;
      }
      else{
        if(!isMoveAnticlock()) moveAnticlock();
      }
      movingToTarget = true;
    break;

    case DISCARDFIRSTPOS: //continue to discard, to ensure that will be in a not hole
      if( moveAngle(30) ){
        targetStateMachine = FINDPOSITION;
        sw.reset();
      }
      movingToTarget = true;
    break;


    case FINDPOSITION: //after discarding, since is impossible be in a hole, the next click of switch will be in the first hole
      if( (timesSwitchPressed >= 1) && isMoveAnticlock() ){
        stopAntiClock();
        sw.reset();
        targetStateMachine = FINDTARGET;
      }
      else{
        if(!isMoveAnticlock()) moveAnticlock();
      }
      movingToTarget = true;
    break;


    case FINDTARGET: //see what target you are moving a little and counting the number of holes
      if( moveAngle(30) ){
        currentTarget = timesSwitchPressed +1;
        targetStateMachine =  MOVETOCORRECTTARGET;
        sw.reset();
      }
      movingToTarget = true;
    break;


    case MOVETOCORRECTTARGET:
      if( ( timesSwitchPressed >=  nTimesSwToGoRightTarget() ) && isMoveAnticlock() ){
        stopAntiClock();
        sw.reset();
        currentTarget = previewTarget; //update the current target after reaching the correct target 
        targetStateMachine = IDDLE; // that update will do nothing since when selected a new target it will be seen again what is the current target then
        movingToTarget = false; // so is just here if one day you want to disable the research every times it goes to a new target ;)
      }
      else{
        if(!isMoveAnticlock()) moveAnticlock();
      }
    break;
  }
  return;
}


bool Motor::isMovingToTarget(){
    return movingToTarget;
}

int Motor::getTargetStateMachine(){
    return targetStateMachine;
}


int Motor::getTarget(){
    return previewTarget;
}

int Motor::getCurrentTarget(){
    return currentTarget;
}

int Motor::nTimesSwToGoRightTarget(){
    int nTimesSw = 0;
    if     ( (currentTarget == 3) && (previewTarget == 1) ) nTimesSw = 3; 
    else if( (currentTarget == 3) && (previewTarget == 2) ) nTimesSw = 1; 
    else if( (currentTarget == 3) && (previewTarget == 3) ) nTimesSw = 4; 

    else if( (currentTarget == 2) && (previewTarget == 1) ) nTimesSw = 1; 
    else if( (currentTarget == 2) && (previewTarget == 2) ) nTimesSw = 5;
    else if( (currentTarget == 2) && (previewTarget == 3) ) nTimesSw = 2; 

    else if( (currentTarget == 1) && (previewTarget == 1) ) nTimesSw = 6; 
    else if( (currentTarget == 1) && (previewTarget == 2) ) nTimesSw = 4;  
    else if( (currentTarget == 1) && (previewTarget == 3) ) nTimesSw = 1; 

  return nTimesSw;
}
