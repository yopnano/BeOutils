#include "LctrlMoteur.h"

LctrlMoteur::LctrlMoteur(unsigned char mode, unsigned char outMin, unsigned char outMax, unsigned char csgMin, unsigned char csgMax, unsigned char rampeAcc)
:   Lctrl(),
    m_pidMode(false),
    m_cmdAv(false),
    m_cmdAr(false),
    m_memCmd(false),
    m_KmAv(false),
    m_KmAr(false),
    m_modeFct(mode),
    m_modeFctOld(mode),
    m_csgAuto(outMin),
    m_csgManu(outMin),
    m_csgGlobale(0),
    m_csgActuelle(0),
    m_csgMin((csgMin > outMin) ? csgMin : outMin),
    m_csgMax((csgMax < outMax) ? csgMax : outMax),
    m_rampe(rampeAcc),
    m_outMin(outMin),
    m_outMax(outMax)
{}

void LctrlMoteur::toggle(void)
{   //Fonction changement de sens AV -> STOP -> AR -> STOP -> AV ...
    
    //Moteur à l'arrêt
    if (!m_cmdAv && !m_cmdAr)
    {
        m_cmdAv = !m_memCmd; 
        m_cmdAr = m_memCmd; 
    }
    //Moteur en marche
    else if (m_cmdAv ^ m_cmdAr)
    {
        m_cmdAv = false; 
        m_cmdAr = false; 
        m_memCmd = !m_memCmd && m2sens();/*&& m_pinDir != 255;*/
    }
}

void LctrlMoteur::modeFct(unsigned char mode)
{
    if (m_modeFct != mode && m_modeFct != Defaut)
    {
        m_modeFctOld = m_modeFct;
        m_modeFct = mode;
    }
}

bool LctrlMoteur::m_rearm(bool cdtRearm) 
{
    if (m_modeFct == Defaut && cdtRearm)
        m_modeFct = m_modeFctOld;
    
    return m_modeFct != Defaut;
}

void LctrlMoteur::csgAuto(unsigned char csg)
{
    //Borne la consigne entre 0 et 255
    m_csgAuto = constrain(csg, m_csgMin, m_csgMax);
}

void LctrlMoteur::csgManu(unsigned char csg)
{
    //Borne la consigne entre 0 et 255
    m_csgManu = constrain(csg, m_outMin, m_outMax);
}

void LctrlMoteur::KM(void)
{
    m_KmAv = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto && m_cmdAv) || m_KmAv))
             || m_modeFct == Marche_AV_forcee;

    m_KmAr = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto && m_cmdAr) || m_KmAr))
             || m_modeFct == Marche_AR_forcee;
}


LMoteurSpeed::LMoteurSpeed() :
m_disabled(false),
m_csgAtteinte(false),
m_lastMillis(0)
{}

void LMoteurSpeed::main(unsigned char &csgGlobale, unsigned char &csgActuelle, unsigned short const& rampe)
{
    //Rampes désactivées
    if (m_disabled) csgActuelle = csgGlobale;

    m_csgAtteinte = csgActuelle == csgGlobale;

    //Gestion d'incrémentation
    if (m_csgAtteinte)
    {
        razTimer();
        return;
    }
    else
    {
        if (millis() - m_lastMillis >= rampe)
        {
            razTimer();
            csgActuelle += (csgGlobale > csgActuelle) ? 1 : -1;
        }
    }
}