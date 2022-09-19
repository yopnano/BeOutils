#include <Lcalc\Mae\Lcalc_Mae.h>

double Lcalc_MAE(double In, double InMin, double InMax, double OutMin, double OutMax)
{
    double normX = NORM_X(InMin, In, InMax);
    double Out = SCALE_X(OutMin, normX, OutMax);
    if (normX < 0.0) Out = OutMin;
    if (normX > 1.0) Out = OutMax;

    return Out;
}