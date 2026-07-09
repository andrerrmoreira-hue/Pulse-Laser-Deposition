
#include "menu.h"

Menu* Menu::instance = nullptr;

Menu::Menu() {
  paramDefined = false;
  param        = 0;
  editMode     = false;
  menuState    = DEFAUT_MENU;
}


void Menu::changeMenu(bool print) {
  switch(menuState){
    case MENU_TARGET:
      menuState = MENU_SHUT;
    break;

    case MENU_SHUT:
      menuState = MENU_MOTOR_ROTATE;
    break;

    case MENU_MOTOR_ROTATE:
      menuState = MENU_MOTOR_SPEED;
    break;

    case MENU_MOTOR_SPEED:
      menuState = MENU_TARGET;
    break;

    default:
      menuState = DEFAUT_MENU;
    break;
  }
}


int Menu::getMenuState(){
  return menuState;
}

bool Menu::isInEditMode(){
  return editMode;
}

void Menu::setEditMode(bool state){
  editMode = state;
}


void Menu::menuTarget(KY040& ky040, MyLCD& Mylcd, Motor& motor, SW& sw){
  // the target is update only if is not currently moving to a target
  if(! motor.isMovingToTarget() ){ 
    motor.updateTarget( ky040.getEncoderState() ); 
    if( motor.getCurrentTarget() == motor.getTarget() ) return;
  }
  // see more notes in the method, despite the names it isnt always moving to the target,
  // most of the time is in the iddle state waiting for the button to be pressed
  motor.moveToTarget(ky040.isShortPressEvent(), sw); 
  
  return;
}



void Menu::menuSpeed(KY040& ky040, Motor& motor){
  motor.previewSpeed( ky040.getEncoderState() );
  motor.updateSpeed();
}

void Menu::menuRotation(KY040& ky040, Motor& motor){
  motor.previewMotorEnable(ky040.getEncoderState());
  motor.updateMotorEnable();
}

void Menu::menuShut(KY040& ky040, Shut& shut){
  shut.previewShut( ky040.getEncoderState() );
  shut.updateShut();
}


