#include "Lctrl_MoteurPWM.h"

Lctrl_MoteurPWM::Lctrl_MoteurPWM(uint8_t pinAv, uint8_t pinAr, uint8_t mode, uint8_t csgMin, uint8_t csgMax, uint8_t rampeAcc) :
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
    
    modeFct = Mode_auto;
}

void Lctrl_MoteurPWM::release(void)
{   //Methode pour relâcher le moteur
    cmdAr = false;
    cmdAv = false;
    m_sensHor = false;
    m_sensTri = false;
}

void Lctrl_MoteurPWM::toggle(void)
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
        m_memCmd = !m_memCmd && m_pinAr != 255;
    }
}


void Lctrl_MoteurPWM::main(void)
{   //Fonction principale moteur
    
    //Vérifie et corrige les attributs
    checkAttr();

    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (modeFct == Marche_AV_forcee) * csgManu + //Mode manu avant
                    (modeFct == Marche_AR_forcee) * csgManu + //Mode manu arriere
                    (modeFct == Mode_auto) * (cmdAv ^ cmdAr) * csgAuto; //Mode auto avant XOR arriere
    
    //Ajustements consigne
    mainCommon();

    if (pidMode) m_csgActuelle = m_csgGlobale;

    //Si changement de consigne et front rampe => acceleration/deceleration
    if (!m_csgAtteinte && pulseRampe()) m_csgActuelle += (m_csgGlobale > m_csgActuelle) ? 1 : -1;

    m_sensHor = (m_csgActuelle > m_csgMin && ((modeFct == Mode_auto && cmdAv) || m_sensHor))
                || modeFct == Marche_AV_forcee;

    m_sensTri = (m_csgActuelle > m_csgMin && ((modeFct == Mode_auto && cmdAr) || m_sensTri))
                || modeFct == Marche_AR_forcee;

    //Pilotage des sorties
    analogWrite(m_pin  , m_csgActuelle * m_sensHor);
    analogWrite(m_pinAr, m_csgActuelle * m_sensTri); 
}