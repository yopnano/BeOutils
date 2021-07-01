#include "Lctrl_Brushless.h"

/*
    brushless 1 sens de rotation
*/

Lctrl_Brushless_1sens::Lctrl_Brushless_1sens(uint8_t pin, uint8_t mode, uint8_t rampeAcc, uint16_t dtMin, uint16_t dtMax):
    LctrlMoteur(mode, 0, 255, 0, 255, rampeAcc),
    m_dtMin(dtMin),
    m_dtMax(dtMax)
    {
        m_pin = pin;
    }

void Lctrl_Brushless_1sens::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin);
    init();
}

void Lctrl_Brushless_1sens::main(void)
{
    //Vérifie et corrige les attributs
    checkAttr();

    //Condition d'arrêt
    if (modeFct == Arret_forcee) m_servo.detach();
    if ((modeFct != Arret_forcee) &! m_servo.attached())
    {
        m_servo.attach(m_pin);
        init();
    }

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (modeFct == Marche_forcee) * csgManu +   //Mode manu avant
                    (modeFct == Mode_auto) * csgAuto;           //Mode auto

    //Ajustements consigne
    mainCommon();
    
    //Initialisation du moteur
    if (!m_initialized and pulseRampe())
    {
        m_servo.writeMicroseconds(m_dtMin);
        m_initCycles --;
        m_initialized = m_initCycles <= 0;
    }

    //Shunt Acceleration en mode PID externe
    if (pidMode) m_csgActuelle = m_csgGlobale;

    //Si changement de consigne et front xxx Hz acceleration ou deceleration
    if (!m_csgAtteinte && pulseRampe()) m_csgActuelle += (m_csgGlobale > m_csgActuelle) ? 1 : -1;;
    
    m_sens = (m_csgActuelle > m_csgMin && ((modeFct == Mode_auto && cmdAv) || m_sens))
                || modeFct == Marche_forcee;

    //Calcul de la consigne en microsecondes
    uint16_t csgMicroseconds;
    if(m_sens) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMin, m_dtMax);
    if((!m_sens) |! m_initialized) csgMicroseconds = m_dtMin;

    //Pilotage de la sortie
    if (m_initialized) m_servo.writeMicroseconds(csgMicroseconds);
}


/*
    brushless 2 sens de rotation
*/

Lctrl_Brushless_2sens::Lctrl_Brushless_2sens(uint8_t pin, uint8_t mode, uint8_t rampeAcc, uint16_t dtMin, uint16_t dtMid, uint16_t dtMax):
    LctrlMoteur(mode, 0, 255, 0, 255, rampeAcc),
    m_dtMin(dtMin),
    m_dtMid(dtMid),
    m_dtMax(dtMax)
    {
        m_pin = pin;
    }

void Lctrl_Brushless_2sens::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin);
    init();
}

void Lctrl_Brushless_2sens::toggle(void)
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

void Lctrl_Brushless_2sens::main(void)
{
    //Vérifie et corrige les attributs
    checkAttr();

    //Condition d'arrêt
    if (modeFct == Arret_forcee) m_servo.detach();
    if ((modeFct != Arret_forcee) &! m_servo.attached())
    {
        m_servo.attach(m_pin);
        m_servo.writeMicroseconds(m_dtMid);
        init();
    }

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (modeFct == Marche_AV_forcee) * csgManu + //Mode manu avant
                    (modeFct == Marche_AR_forcee) * csgManu + //Mode manu arriere
                    (modeFct == Mode_auto) * (cmdAv ^ cmdAr) * csgAuto; //Mode auto avant XOR arriere

    //Ajustements consigne
    mainCommon();
    
    //Shunt Acceleration en mode PID externe
    if (pidMode) m_csgActuelle = m_csgGlobale;
    
    //Initialisation du moteur
    if (!m_initialized and pulseRampe())
    {
        m_servo.writeMicroseconds(m_dtMid);
        m_initCycles --;
        m_initialized = m_initCycles <= 0;
    }

    //Si changement de consigne et front xxx Hz acceleration ou deceleration
    if (!m_csgAtteinte && pulseRampe()) m_csgActuelle += (m_csgGlobale > m_csgActuelle) ? 1 : -1;
    
    m_sensHor = (m_csgActuelle > m_csgMin && ((modeFct == Mode_auto && cmdAv) || m_sensHor))
                || modeFct == Marche_AV_forcee;

    m_sensTri = (m_csgActuelle > m_csgMin && ((modeFct == Mode_auto && cmdAr) || m_sensTri))
                || modeFct == Marche_AR_forcee;

    //Calcul de la consigne en microsecondes
    uint16_t csgMicroseconds;
    if(m_sensHor) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMid, m_dtMax);
    if(m_sensTri) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMid, m_dtMin);
    if((!m_sensHor &! m_sensTri) |! m_initialized) csgMicroseconds = m_dtMid;

    //Pilotage de la sortie
    if (m_initialized) m_servo.writeMicroseconds(csgMicroseconds);
}


