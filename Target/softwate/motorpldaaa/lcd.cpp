#include "lcd.h"

// ---------------- CUSTOM CHARACTERS ----------------
const uint8_t MyLCD::arrowRight[8] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B00110,
  B00100,
  B00000,
  B00000
};

const uint8_t MyLCD::arrowUD[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};



MyLCD* MyLCD::instance = nullptr;
displayInfo MyLCD::current;
displayInfo MyLCD::last;

// ---------------- CONSTRUCTOR ----------------
MyLCD::MyLCD() : lcd(0x27, 16, 2) {
    current.menuEditMode = false;
    current.menuState    = DEFAUT_MENU;
    current.target       = DEFAUT_TARGET;
    current.rotation     = DEFAUT_ROTATION;
    current.shut         = SHUT_OFF;
    current.speed        = DEFAUT_RPM;
    last = current;
}


// ---------------- INIT ----------------
void MyLCD::init() {
    lcd.init();
    lcd.createChar(0, (uint8_t*)arrowRight);
    lcd.createChar(1, (uint8_t*)arrowUD);
    lcd.backlight();
}



// ---------------- MAIN SCREEN ----------------
void MyLCD::mainScreen( ) {
    //lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print("Targ:");
    lcd.setCursor(6, 0);
    lcd.print(current.target);

    lcd.setCursor(9, 0);
    lcd.print("Shut:");
    lcd.setCursor(14, 0);
    if (current.shut == SHUT_OFF) lcd.print("C");
    else                 lcd.print("O");

    lcd.setCursor(1, 1);
    lcd.print("Rot:");
    lcd.setCursor(5, 1);
    if (current.rotation == ROTATION_ON) lcd.print("ON");
    else                   lcd.print("OF");

    lcd.setCursor(9, 1);
    lcd.print("RPS:");
    lcd.setCursor(13, 1);

    lcd.print("1/"); //experimental 16RPM on of cuurrent speed corrspod a completed rotation of 5 seg. so pela regra 3 simples,
    int segPerVolta = (current.speed*5) / 16; //quantos segundos demora a dar uma volta     
    lcd.setCursor(15, 1);
    lcd.print(segPerVolta); // em um segundo quanto de volta da

    switch(current.menuState){
        case MENU_TARGET:
            lcd.setCursor(0, 0);
            lcd.write((uint8_t)0);  // arrowRight
            break;

        case MENU_SHUT:
            lcd.setCursor(8, 0);
            lcd.write((uint8_t)0);  // arrowRight
            break;

        case MENU_MOTOR_ROTATE:
            lcd.setCursor(0, 1);
            lcd.write((uint8_t)0);  // arrowRight
            break;

        case MENU_MOTOR_SPEED:
            lcd.setCursor(8, 1);
            lcd.write((uint8_t)0);  // arrowRight
            break;
    }
}



//******* LCD target state */ */
void MyLCD::targetFinding(){
    lcd.setCursor(7, 0);
    lcd.print("E");
}

void MyLCD::targetReached(){
    lcd.setCursor(7, 0);
    lcd.print("K");
}



/******************************************************
 *               UPDATE DISPLAY 
 * 
 ******************************************************/

void MyLCD::updateDisplay(bool editMode, int menuState, int motorenable, int speed, int shut, int target){
    current.menuEditMode = editMode;
    current.menuState    = menuState;
    current.rotation     = motorenable;
    current.speed        = speed;
    current.shut         = shut;
    current.target       = target;
/*
    if( (current.menuEditMode == true) && (last.menuEditMode != current.menuEditMode) ){ // entering edit mode
        putEditModeIndicator();
    }

    if( current.menuEditMode == false && (last.menuEditMode != current.menuEditMode) ){ // exiting edit mode
        takeOutEditModeIndicator();
    }
*/
    if( current.menuState != last.menuState ){ // menu changed
        updateSelectMenuIndicator();
    }

    if( current.target != last.target ){
        updateTarget();
    }
    
    if( current.rotation != last.rotation ){
        updateRotation();
    }
    if( current.speed != last.speed ){
        updateSpeed();
    }

    if( current.shut != last.shut ){
        updateShut();
    }

    last = current;
}



void MyLCD::putEditModeIndicator(){

    switch(current.menuState){
        case MENU_TARGET:
            lcd.setCursor(7, 0);
            lcd.write((uint8_t)1); // arrowUD
            break;

        case MENU_SHUT:
            lcd.setCursor(15, 0);
            lcd.write((uint8_t)1); // arrowUD
            break;

        case MENU_MOTOR_ROTATE:
            lcd.setCursor(7, 1);
            lcd.write((uint8_t)1); // arrowUD
            break;

        case MENU_MOTOR_SPEED:
            lcd.setCursor(15, 1);
            lcd.write((uint8_t)1); // arrowUD
            break;
    }
}



void MyLCD::takeOutEditModeIndicator(){
    switch(current.menuState){
        case MENU_TARGET:
            lcd.setCursor(7, 0);
            lcd.print(" ");
            break;

        case MENU_SHUT:
            lcd.setCursor(15, 0);
            lcd.print(" ");
            break;

        case MENU_MOTOR_ROTATE:
            lcd.setCursor(7, 1);
            lcd.print(" ");
            break;

        case MENU_MOTOR_SPEED:
            //lcd.setCursor(15, 1);
            //lcd.print(" ");
            break;
    }
}


void MyLCD::updateSelectMenuIndicator(){
    
    switch(last.menuState){
        case MENU_TARGET:
            lcd.setCursor(0, 0);
            lcd.print(" ");
            break;

        case MENU_SHUT:
            lcd.setCursor(8, 0);
            lcd.print(" ");
            break;

        case MENU_MOTOR_ROTATE:
            lcd.setCursor(0, 1);
            lcd.print(" ");
            break;

        case MENU_MOTOR_SPEED:
            lcd.setCursor(8, 1);
            lcd.print(" ");
            break;
    }


    switch(current.menuState){
        case MENU_TARGET:
            lcd.setCursor(0, 0);
            lcd.write((uint8_t)0);  // arrowRight
            lcd.setCursor(7,0);
            lcd.print(" ");
            break;

        case MENU_SHUT:
            lcd.setCursor(8, 0);
            lcd.write((uint8_t)0);  // arrowRight
            lcd.setCursor(15, 0);
            lcd.print(" ");
            break;

        case MENU_MOTOR_ROTATE:
            lcd.setCursor(0, 1);
            lcd.write((uint8_t)0);  // arrowRight
            lcd.setCursor(8, 1);
            lcd.print(" ");
            break;

        case MENU_MOTOR_SPEED:
            lcd.setCursor(8, 1);
            lcd.write((uint8_t)0);  // arrowRight
            break;
        
        default:
            break;  
    }
}

//---------------- UPDATE PARAMETERS ----------------

void MyLCD::updateTarget(){
    lcd.setCursor(6, 0);
    lcd.print(" ");     
    lcd.setCursor(6, 0);
    lcd.print(current.target);
}

void MyLCD::updateShut(){
    lcd.setCursor(14,0);
    if (current.shut == SHUT_OFF) lcd.print("C");
    else                     lcd.print("O");
}

void MyLCD::updateSpeed(){
    int segPerVolta;
    lcd.setCursor(13, 1);
    lcd.print("   ");
    
    if(current.speed  == 2){
        lcd.setCursor(13, 1);
        lcd.print("1.5");
    }
    else{
        if(current.speed ==  1){
            lcd.setCursor(13, 1);
            lcd.print("3");
        }
        else{
            if(current.speed == 4){
                lcd.setCursor(13, 1);
                lcd.print("1");
            }
            else{
                //experimental 16RPM on of cuurrent speed corrspod a completed rotation of 5 seg. so pela regra 3 simples,
                segPerVolta = (current.speed*5) / 16; //quantos segundos demora a dar uma volta     
                lcd.setCursor(13, 1);
                lcd.print("1/");
                lcd.setCursor(15, 1);
                lcd.print(segPerVolta); // em um segundo quanto de volta da
            }
        }
    }
}

void MyLCD::updateRotation(){
    lcd.setCursor(5, 1);
    if (current.rotation == ROTATION_ON) lcd.print("ON");
    else                                 lcd.print("OF");
}
