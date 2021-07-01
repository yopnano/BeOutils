#include ".\LioAna_Fscale.h"

// fonction privée mise à l'échelle
double scale(double val, double LO_LIM, double HI_LIM)
{
    return( ((val / 1023.0) * (HI_LIM - LO_LIM) ) + LO_LIM );
}


LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, double LO_LIM, double HI_LIM, double offset)
{
    LioAna_udtAiScale analog;
        analog.def = false;
        analog.val = scale((double)analogRead(pin), LO_LIM + offset, HI_LIM + offset);
    return analog;
}

LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, double LO_LIM, double HI_LIM, int LO_DEF, int HI_DEF, double offset)
{
    int value = analogRead(pin);
    LioAna_udtAiScale analog;
        analog.def = (value < LO_DEF || value > HI_DEF);
        analog.val = scale((double)analogRead(pin), LO_LIM + offset, HI_LIM + offset);
    return analog;
}