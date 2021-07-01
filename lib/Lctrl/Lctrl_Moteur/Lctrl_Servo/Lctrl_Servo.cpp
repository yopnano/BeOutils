#include "Lctrl_Servo.h"

Lctrl_Servo::Lctrl_Servo(uint8_t pin, uint8_t mode, uint8_t rampeAcc, uint8_t posMin, uint8_t posMax):
    LctrlMoteur(mode, 0, 180, posMin, posMax, rampeAcc)
    {
        m_pin = pin;
    }

void Lctrl_Servo::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin);
    csgAuto = m_servo.read();
}

void Lctrl_Servo::main(void)
{
    //Vérifie et corrige les attributs
    checkAttr();

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (modeFct == Marche_forcee) * csgManu +      //Mode manu
                    (modeFct == Mode_vitessePos) * csgAuto +    //Mode auto (acceleration)
                    (modeFct == Mode_auto) * csgAuto;           //Mode auto (positionment auto)
    
    //Ajustements consigne
    mainCommon();
    
    //Shunt Accelration en mode PID externe
    if (pidMode || modeFct == Mode_auto) m_csgActuelle = m_csgGlobale;

    //Si changement de consigne et front xxx Hz acceleration ou deceleration
    if (!m_csgAtteinte && pulseRampe()) m_csgActuelle += (m_csgGlobale > m_csgActuelle) ? 1 : -1;;
    
    if (autoRelease && m_csgAtteinte) m_servo.detach();
    if (autoRelease &! m_csgAtteinte) m_servo.attach(m_pin);

    m_servo.write(m_csgActuelle);
}