#include "Lsys_Fperiod.h"

// Constructeur
Lsys_Fperiod::Lsys_Fperiod(uint32_t periodMs) : Dlay(periodMs / 2), clk(false) , lastMillis(millis())
{
}

bool Lsys_Fperiod::clock()
{
    if (millis() - lastMillis >= Dlay)
    {
        lastMillis = millis();
        clk = !clk; // toggle clock
    }
    return clk;
}

void Lsys_Fperiod::restart() 
{
    lastMillis = millis();
}

void Lsys_Fperiod::changePeriod(uint32_t periodMs)
{
    Dlay = periodMs / 2;
}