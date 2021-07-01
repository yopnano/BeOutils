#include "LctrlMoteur.h"


LctrlMoteur::LctrlMoteur(uint8_t mode, uint8_t outMin, uint8_t outMax, uint8_t csgMin, uint8_t csgMax, uint8_t rampeAcc):
modeFct(mode),
m_csgMin(csgMin),
m_csgMax(csgMax),
m_outMin(outMin),
m_outMax(outMax),
m_rampe(rampeAcc),
iLsys_Fimpulse(rampeAcc)
{}


void LctrlMoteur::checkAttr(void)
{
    //Borne la consigne entre 0 et 255
    csgAuto = constrain(csgAuto, m_csgMin, m_csgMax);
    csgManu = constrain(csgManu, m_outMin, m_outMax);
}

void LctrlMoteur::mainCommon(void)
{
    //Shunt acceleration décélération si rampe nulle
    if (m_rampe <= 0) m_csgActuelle = m_csgGlobale;

    //Consigne atteinte
    m_csgAtteinte = (m_csgActuelle == m_csgGlobale);
}