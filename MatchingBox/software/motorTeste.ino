#include "motor.h"
#include "switch.h"

Motor motor1(COILA_M1, COILB_M1, COILC_M1, COILD_M1);
Motor motor2(COILA_M2, COILB_M2, COILC_M2, COILD_M2);

SW    swMotor1(SW_M1);
SW    swMotor2(SW_M2);

// ------------------- SETUP -------------------
void setup() {  
  motor1.init();
  swMotor1.init();
  
  motor2.init();
  swMotor2.init();

  motor1.start();
  motor2.start();

}


void loop() {
  motor1.update();
  motor2.update();
  
  /*
  if( (swMotor1.getState() == true)  && (motor1.getState() == true) && (motor1.getDirection() == ANTICLOCK) )                                motor1.setDirection(CLOCK);
  if( (swMotor1.getState() == false) && (motor1.getState() == true) && (motor1.getNumberSteps() > 500) && (motor1.getDirection() == CLOCK) ) motor1.setDirection(ANTICLOCK);
  
  if( (swMotor2.getState() == true)  && (motor2.getState() == true) && (motor2.getDirection() == ANTICLOCK) )                                motor2.setDirection(CLOCK);
  if( (swMotor2.getState() == false) && (motor2.getState() == true) && (motor2.getNumberSteps() > 500) && (motor2.getDirection() == CLOCK) ) motor2.setDirection(ANTICLOCK);
  */


  if( (swMotor1.getState() == true)  && (motor1.getState() == true) && (motor1.getDirection() == ANTICLOCK) )   
    motor1.stop();

  if( (swMotor2.getState() == true)  && (motor2.getState() == true) && (motor2.getDirection() == ANTICLOCK) )  
    motor2.stop();

  if( (motor1.getState() == false) &&  (motor2.getState() == false) ){
    motor1.setDirection(CLOCK); 
    motor2.setDirection(CLOCK);   
    motor1.start();
    motor2.start();
  }

  if( (swMotor1.getState() == false) && (motor1.getState() == true) && (motor1.getNumberSteps() > 500) && (motor1.getDirection() == CLOCK) )
     motor1.setDirection(ANTICLOCK);

  if( (swMotor2.getState() == false) && (motor2.getState() == true) && (motor2.getNumberSteps() > 500) && (motor2.getDirection() == CLOCK) )
    motor2.setDirection(ANTICLOCK);

}
