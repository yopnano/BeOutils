#include "Lreg_PID.h"

Lreg_PID::Lreg_PID(double _Kp, double _Ki , double _Kd, int _POn, int _ControllerDirection) :
    PID(&input, &output, &setpoint, _Kp, _Ki, _Kd, _POn, _ControllerDirection)
    {}

Lreg_PID::Lreg_PID(double _Kp, double _Ki, double _Kd, int _ControllerDirection) :
    PID(&input, &output, &setpoint, _Kp, _Ki, _Kd, _ControllerDirection)
    {}