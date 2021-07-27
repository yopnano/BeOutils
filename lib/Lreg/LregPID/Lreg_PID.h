#ifndef Lreg_PID_h
#define Lreg_PID_h

#include <Arduino.h>
#include <PID_v1.h>

class Lreg_PID : public PID
{
public:
    Lreg_PID(double _Kp, double _Ki, double _Kd, int _POn, int _ControllerDirection = DIRECT);
    
    Lreg_PID(double _Kp, double _Ki, double _Kd, int _ControllerDirection = DIRECT);

    void setup (void) {SetMode(AUTOMATIC);}
    void main (void) {Compute();}

    double input, output, setpoint;
};
#endif