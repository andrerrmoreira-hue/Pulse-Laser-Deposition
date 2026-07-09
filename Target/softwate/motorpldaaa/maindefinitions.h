

/**********************
       MOTOR
***********************/

//pins
#define COILA  7
#define COILB  8
#define COILC  9
#define COILD  10
#define SW_PIN 5

#define STEPS_PER_REVOLUTION 180
#define MAX_SPEED 30
#define MIN_SPEED 4
#define SPEED_CHANGE_TARGET 30
#define TIME_TO_REACH_TARGET 10000
#define DEGREES_TO_FIND_TARGET 20
#define SW_DEBOUNCE_MS 20
#define CHANGE_TARGET__ROTATION_SPEED 25
#define DEFAUT_RPM      10
/**********************
       ENCODER
***********************/
#define ENCODER_CLK 2
#define ENCODER_DT  3
#define ENCODER_SW  4
#define SHORT_PRESS_TIME 1000
#define ENC_READ_INTERVAL 1000
#define BUTTON_DEBOUNCE_MS 100

/**********************
       SHUT
***********************/
#define SHUT_PIN_1A A0
#define SHUT_PIN_2A A1

//rotation
#define ROTATION_OFF 0
#define ROTATION_ON  1
//defaut parameters
#define DEFAUT_SHUT     SHUT_OFF        // SHUT_OFF  OR SHUT_ON
#define DEFAUT_TARGET   1
#define DEFAUT_ROTATION ROTATION_OFF   // ROTATION_OFF  OR ROTATION_ON
#define DEFAUT_MENU     MENU_TARGET


#define DEBOUNCE_TIME 50 

/*************************************************************
   FROM HERE TO THE END ARE PRIVATA DEFINITIOS. DO NOT CHANGE
***************************************************************/

//shut
#define SHUT_OFF 0
#define SHUT_ON  1

//encoder
#define ENC_NONE  0
#define ENC_RIGHT 1
#define ENC_LEFT  2

//motor
#define CLOCKWISE 0
#define ANTICLOCKWISE 1
#define NUMBER_OF_TARGETS 3

//state machines states
#define BUTTON_RELEASE 0
#define BUTTON_PRESSED 1
#define CHANGE_MENU    2
#define LONG_PRESS     3
#define EDIT_MENU      4


//menus
#define MENU_TARGET        0
#define MENU_SHUT          1
#define MENU_MOTOR_SPEED   2
#define MENU_MOTOR_ROTATE  3


#define SW_PRESSED     1
#define SW_NOT_PRESSED 0


#define FINDTARGET 1
#define FINDPOSITION 0
#define FINISHREACHTARGET 3
#define CHECKTARGET 4
#define DISCARDFIRSTPOS 5
#define FINDPOSITIONTODISCARD 6
#define MOVETOCORRECTTARGET 7
#define IDDLE 8

