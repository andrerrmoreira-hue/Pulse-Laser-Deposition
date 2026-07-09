
#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "motor.h"
#include "lcd.h"
#include "encoder.h"
#include "maindefinitions.h"
#include "shut.h"
#include "switch.h"


class Menu{
    public:
        Menu();
        void menuTarget  (KY040&, MyLCD&, Motor&, SW&);
        void menuSpeed   (KY040&, Motor&);
        void menuRotation(KY040&, Motor&);
        void menuShut    (KY040&, Shut&);

        void Menu::changeMenu(bool) ;
        int  getMenuState();
        bool isInEditMode();
        void setEditMode(bool);

    private:
        bool paramDefined;
        int param;
        bool editMode;
        int  menuState;
        static Menu* instance;
};

#endif