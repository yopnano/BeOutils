#ifndef Lctrl_h
#define Lctrl_h

#include <Arduino.h>

#define pinIsDisable(pin) (pin == 255)
#define pinIsEnable(pin) (pin != 255)

class Lctrl
{
public:
    virtual void setup(void) =0;
    virtual void main(void) =0;
};




#endif