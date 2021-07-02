#include "Lctrl_Brushless.h"

/*
    brushless 1 sens de rotation
*/

Lctrl_Brushless_1sens::Lctrl_Brushless_1sens(unsigned char pin, unsigned char mode, unsigned char rampeAcc, unsigned short dtMin, unsigned short dtMax):
    LctrlMoteur(mode, 0, 255, 0, 255, rampeAcc),
    m_dtMin(dtMin),
    m_dtMax(dtMax)
    {
        m_pin = pin;
    }

void Lctrl_Brushless_1sens::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin, m_dtMin, m_dtMax);
    init();
}

void Lctrl_Brushless_1sens::main(void)
{
    //Condition d'arrêt
    if (m_modeFct == Arret_forcee) m_servo.detach();
    if ((m_modeFct != Arret_forcee) &! m_servo.attached())
    {
        m_servo.attach(m_pin);
        init();
    }

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (m_modeFct == Marche_forcee) * m_csgManu +   //Mode manu avant
                    (m_modeFct == Mode_auto) * m_csgAuto;           //Mode auto

    //Initialisation du moteur
    if (!m_initialized)
    {
        m_servo.write(0);
        delay(5000);
        m_initialized = true;
    }

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);

    //Gestions KmAv KmAr
    KM();

    //Calcul de la consigne en microsecondes
    unsigned short csgMicroseconds;
    if(m_KmAv) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMin, m_dtMax);
    if((!m_KmAv) |! m_initialized) csgMicroseconds = m_dtMin;

    //Pilotage de la sortie
    if (m_initialized) m_servo.writeMicroseconds(csgMicroseconds);
}


/*
    brushless 2 sens de rotation
*/

Lctrl_Brushless_2sens::Lctrl_Brushless_2sens(unsigned char pin, unsigned char mode, unsigned char rampeAcc, unsigned short dtMin, unsigned short dtMid, unsigned short dtMax):
    LctrlMoteur(mode, 0, 255, 0, 255, rampeAcc),
    m_dtMin(dtMin),
    m_dtMid(dtMid),
    m_dtMax(dtMax)
    {
        m_pin = pin;
    }

void Lctrl_Brushless_2sens::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin, m_dtMin, m_dtMax);
    init();
}

void Lctrl_Brushless_2sens::main(void)
{
    //Condition d'arrêt
    if (m_modeFct == Arret_forcee) m_servo.detach();
    if ((m_modeFct != Arret_forcee) &! m_servo.attached())
    {
        m_servo.attach(m_pin);
        m_servo.writeMicroseconds(m_dtMid);
        init();
    }

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (m_modeFct == Marche_AV_forcee) * m_csgManu + //Mode manu avant
                    (m_modeFct == Marche_AR_forcee) * m_csgManu + //Mode manu arriere
                    (m_modeFct == Mode_auto) * (m_cmdAv ^ m_cmdAr) * m_csgAuto; //Mode auto avant XOR arriere

    //Initialisation du moteur
    if (!m_initialized)
    {
        m_servo.write(90); //m_servo.writeMicroseconds(m_dtMid);
        delay(7000);
        m_initialized = true;
    }

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);

    //Gestions KmAv KmAr
    KM();

    //Calcul de la consigne en microsecondes
    unsigned short csgMicroseconds;
    if(m_KmAv) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMid, m_dtMax);
    if(m_KmAr) csgMicroseconds = map(m_csgActuelle, m_csgMin, m_csgMax, m_dtMid, m_dtMin);
    if((!m_KmAv &! m_KmAr) |! m_initialized) csgMicroseconds = m_dtMid;

    //Pilotage de la sortie
    if (m_initialized) m_servo.writeMicroseconds(csgMicroseconds);
}