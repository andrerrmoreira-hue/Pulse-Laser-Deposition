
//#include <Arduino.h>
#include "encoder.h"
#include "motor.h"
#include "lcd.h"
#include "maindefinitions.h"
#include "menu.h"  
#include "shut.h"
#include "switch.h"

Motor motor;
KY040 ky040;
MyLCD Mylcd;
Menu  menu;
Shut  shut;
SW    sw;

int state        = BUTTON_RELEASE; 
int target       = FINDPOSITIONTODISCARD;
int numberTarget = 1;
int currentTarget = 0;
int nTimesSw = 0;


void setup() {
  Mylcd.init();
  Mylcd.mainScreen();
  
  motor.init();
  ky040.init();
  shut.init();
  sw.init();

  motor.moveToTarget(true, sw);
  while(1){
    motor.updateMotor();
    sw.updateSwitchState();
    motor.moveToTarget(true, sw);
    if(motor.isMovingToTarget() == false) break;
  }

  
}


void loop() {
  ky040.updateButtonState();
  motor.updateMotor();
  ky040.updateEncoderState();
  Mylcd.updateDisplay(menu.isInEditMode(), menu.getMenuState(), motor.getMotorEnable(), motor.getSpeed(), shut.getShut(), motor.getTarget());
  sw.updateSwitchState();


  switch (menu.getMenuState()) {
    case MENU_TARGET:
      menu.menuTarget(ky040, Mylcd, motor, sw);
      if(ky040.isShortPressEvent()) menu.changeMenu(false);
    break;

    case MENU_SHUT:
      menu.menuShut(ky040, shut);
      if(ky040.isShortPressEvent()) menu.changeMenu(false);
    break;

    case MENU_MOTOR_SPEED:
      menu.menuSpeed(ky040, motor);
      if(ky040.isShortPressEvent()) menu.changeMenu(false);
    break;

    case MENU_MOTOR_ROTATE:
      menu.menuRotation(ky040, motor);
      if(ky040.isShortPressEvent()) menu.changeMenu(false);
    break;
  }
}

