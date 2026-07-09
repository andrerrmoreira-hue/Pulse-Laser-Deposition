#ifndef SHUT_H
#define SHUT_H

#include <Arduino.h>
#include "maindefinitions.h"

class Shut{
    public:
        Shut();
        void init();
        void previewShut(int);
        bool getShut();
        void updateShut();

    private:
        int shutState;
        static Shut* instance;
};

#endif
