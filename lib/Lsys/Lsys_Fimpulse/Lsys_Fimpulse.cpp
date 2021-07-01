#include "Lsys_Fimpulse.h"

// Constructeur
Lsys_Fimpulse::Lsys_Fimpulse(uint32_t periodMs) :    iLsys_Fperiod(periodMs) {}

bool Lsys_Fimpulse::impulse()
{
    iTrigger.Analyse(iLsys_Fperiod.clock());
    return iTrigger.R_trig();
}

void Lsys_Fimpulse::restart() 
{
    iLsys_Fperiod.restart();
}

void Lsys_Fimpulse::changePeriod(uint32_t periodMs)
{
    iLsys_Fperiod.changePeriod(periodMs);
}