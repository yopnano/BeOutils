#include "Lctrl_Servo.h"

Lctrl_Servo::Lctrl_Servo(unsigned char pin, unsigned char mode, unsigned char rampeAcc, unsigned char posMin, unsigned char posMax):
    LctrlMoteur(mode, 0, 180, posMin, posMax, rampeAcc),
    m_autoRelease(false)
    {
        m_pin = pin;
    }

void Lctrl_Servo::setup(void)
{
    if (!m_servo.attached()) m_servo.attach(m_pin);
    m_csgAuto = m_servo.read();
}

void Lctrl_Servo::main(void)
{
    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (m_modeFct == Marche_forcee) * m_csgManu +      //Mode manu
                    (m_modeFct == Mode_vitessePos) * m_csgAuto +    //Mode auto (acceleration)
                    (m_modeFct == Mode_auto) * m_csgAuto;           //Mode auto (positionment auto)
    
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);
    
    if (m_autoRelease && m_speed.csgAtteinte()) m_servo.detach();
    if (m_autoRelease &! m_speed.csgAtteinte()) m_servo.attach(m_pin);

    m_servo.write(m_csgActuelle);
}