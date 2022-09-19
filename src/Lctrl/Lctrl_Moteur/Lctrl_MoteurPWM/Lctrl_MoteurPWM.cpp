#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurPWM\Lctrl_MoteurPWM.h>

Lctrl_MoteurPWM::Lctrl_MoteurPWM(unsigned char pinAv, unsigned char pinAr, unsigned char mode, unsigned char csgMin, unsigned char csgMax, unsigned char rampeAcc) :
    //Constructeur
    LctrlMoteur(mode, 0, 255, csgMin, csgMax, rampeAcc)
    {
        m_pin = pinAv;
        m_pinAr = pinAr;
    }


void Lctrl_MoteurPWM::setup(void)
{   //Setup des IOs
    
    //Verifie si les pins sont PWM
    if (digitalPinToTimer(m_pin  ) == NOT_ON_TIMER) {Serial.print (F("LctrlMoteurPWM Warning : Pin cmdAv > ")); Serial.print (m_pin  ); Serial.println (F(" isn't PWM"));}
    else pinMode(m_pin, OUTPUT);
    
    if (digitalPinToTimer(m_pinAr) == NOT_ON_TIMER) {Serial.print (F("LctrlMoteurPWM Warning : Pin cmdAr > ")); Serial.print (m_pinAr); Serial.println (F(" isn't PWM"));}
    else pinMode(m_pinAr, OUTPUT);
}

void Lctrl_MoteurPWM::main(void)
{   //Fonction principale moteur
    
    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (m_modeFct == Marche_AV_forcee) * m_csgManu + //Mode manu avant
                    (m_modeFct == Marche_AR_forcee) * m_csgManu + //Mode manu arriere
                    (m_modeFct == Mode_auto) * (m_cmdAv ^ m_cmdAr) * m_csgAuto; //Mode auto avant XOR arriere
    

    //Mode PID
    m_speed.disable(m_pidMode);

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);

    //Gestions KmAv KmAr
    KM();

    //Pilotage des sorties
    analogWrite(m_pin  , m_csgActuelle * m_KmAv);
    analogWrite(m_pinAr, m_csgActuelle * m_KmAr); 
}