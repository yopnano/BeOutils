#include "Lctrl_MoteurTOR.h"

Lctrl_MoteurTOR::Lctrl_MoteurTOR(uint8_t pinAv, uint8_t pinAr, boolean inverted) :
    cmdAv(false),
    cmdAr(false),
    modeFct(Arret_forcee),
    m_memCmd(false),
    m_KmAv(false),
    m_KmAr(false),
    m_inverted(inverted),
    m_pinAv(pinAv),
    m_pinAr(pinAr)
    {}


void Lctrl_MoteurTOR::setup(void)
{
    pinMode(m_pinAv, OUTPUT);
    pinMode(m_pinAr, OUTPUT);
    modeFct = Mode_auto;
}

//Fonction d'iversion sens de rotation
void Lctrl_MoteurTOR::toggle(void)
{   //Fonction changement de sens AV -> STOP -> AR -> STOP -> AV ...

    //Moteur à l'arrêt
    if (!cmdAv && !cmdAr)
    {
      cmdAv = !m_memCmd; 
      cmdAr = m_memCmd; 
    }
    //Moteur en marche
    else if (cmdAv ^ cmdAr)
    {
        cmdAv = false; 
        cmdAr = false; 
        m_memCmd = !m_memCmd;
    }
}

//Fonction principale moteur
void Lctrl_MoteurTOR::main(void)
{
    //Pilotage des sorties
    m_KmAv = ((modeFct == Mode_auto && cmdAv &! cmdAr) || modeFct == Marche_AV_forcee) ^ m_inverted;
    m_KmAr = ((modeFct == Mode_auto && cmdAr &! cmdAv) || modeFct == Marche_AR_forcee) ^ m_inverted;
    
    digitalWrite(m_pinAv, m_KmAv);
    digitalWrite(m_pinAr, m_KmAr); 
}