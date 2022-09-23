#include <Lctrl\Lctrl_Moteur\Lctrl_Stepper\Lctrl_Stepper.h>


LctrlStepper::LctrlStepper(unsigned char pinStep, unsigned char pinDir, unsigned char pinEnable, unsigned short stepsRevolution, unsigned short vMax, unsigned char mode,  unsigned char csgMin, unsigned char csgMax, unsigned char rampeAcc) :
    LctrlMoteurOld(mode, 0, 255, csgMin, csgMax, rampeAcc),
    m_speed(),
    m_keepEnable(false),
    m_pinDir(pinDir),
    m_pinEnable(pinEnable),
    m_stepsPerRevolution(stepsRevolution),
    m_vMax(vMax),
    m_vitesse(0),
    m_step(0),
    m_lastMicros(0)
{
    m_pin = pinStep; 
}

void LctrlStepper::setup(void)
{   //Setup des IOs

    if (m_pinEnable != 255) pinMode(m_pinEnable, OUTPUT);
    
    if (m_pinDir != 255) pinMode(m_pinDir, OUTPUT);

    if (m_pin == 255){Serial.print (F("LctrlStepper Warning : Pin step > ")); Serial.print (m_pin); Serial.println (F(" must be indicated"));}
    else pinMode(m_pin, OUTPUT);
}

void LctrlStepper::main(void)
{
    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =
        (m_modeFct == Marche_AV_forcee) * m_csgManu + //Mode manu avant
        (m_modeFct == Marche_AR_forcee) * m_csgManu + //Mode manu arriere
        (m_modeFct == Mode_auto) * (m_cmdAv ^ m_cmdAr) * m_csgAuto + //Mode auto avant XOR arriere
        (m_modeFct == Mode_step) * (m_step != 0) * m_csgAuto; //Mode pas à pas

    //Mode PID
    m_speed.disable(m_pidMode);

    //Mode Auto calcul de la vitesse
    if (m_modeFct != Mode_vitesse) m_vitesse = map(m_csgActuelle, m_csgMin, m_csgMax, 0, m_vMax);

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);
    
    //Gestion KmAv KmAr
    KM();
    
    //Conversion tr/min en periode µsec
    // 33M / (vitesse * nbre pas/rev)
    if (m_vitesse > 0)
    {
        unsigned long microDelay = 33333333 / (m_vitesse * (uint32_t) m_stepsPerRevolution);
        if (micros() - m_lastMicros >= microDelay)
        {
            m_lastMicros = micros();
            bool pinState = digitalRead(m_pin);

            digitalWrite(m_pin, !pinState);

            //Si mode step => Mise à jour du nombre de step restant
            if (m_modeFct == Mode_step and pinState)
            {
                if (m_step > 0) m_step --;
                if (m_step < 0) m_step ++;
            }
        }
    }
    digitalWrite(m_pinDir, m_KmAr);
    digitalWrite(m_pinEnable, !(m_vitesse > 0 || m_keepEnable));
}