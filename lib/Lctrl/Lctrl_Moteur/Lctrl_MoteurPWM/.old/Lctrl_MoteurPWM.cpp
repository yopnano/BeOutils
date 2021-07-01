#include "Lctrl_MoteurPWM.h"

Lctrl_MoteurPWM::Lctrl_MoteurPWM(uint8_t pinAv, uint8_t pinAr, uint8_t vitesseMini, uint16_t rampeAcc) :
    //Constructeur
    cmdAv(false),
    cmdAr(false),
    pidMode(false),
    modeFct(Arret_forcee),
    csgAuto(0),
    csgManu(0),
    csgMini(vitesseMini),
    m_memCmd(false),
    m_sensHor(false),
    m_sensTri(false),
    m_csgAtteinte(false),
    m_demarrage(false),
    m_pinAv(pinAv),
    m_pinAr(pinAr),
    m_csgActuelle(0),
    m_csgGlobale(0),
    m_rampe(rampeAcc),
    iLsys_Fimpulse(rampeAcc)
    {}


void Lctrl_MoteurPWM::setup(void)
{   //Setup des IOs
    
    //Verifie si les pins sont PWM
    if (digitalPinToTimer(m_pinAv) == NOT_ON_TIMER) {Serial.print (F("LctrlMoteurPWM Warning : Pin cmdAv > ")); Serial.print (m_pinAv); Serial.println (F(" isn't PWM"));}
    else pinMode(m_pinAv, OUTPUT);
    
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
        m_memCmd = !m_memCmd;
    }
}


void Lctrl_MoteurPWM::main(void)
{   //Fonction principale moteur
    
    //Borne la consigne entre 0 et 255
    csgAuto = constrain(csgAuto, 0, 255);
    csgManu = constrain(csgManu, 0, 255);
    csgMini = constrain(csgMini, 0, 255);
    
    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (modeFct == Marche_AV_forcee) * csgManu + //Mode manu avant
                    (modeFct == Marche_AR_forcee) * csgManu + //Mode manu arriere
                    (modeFct == Mode_auto) * (cmdAv ^ cmdAr) * csgAuto; //Mode auto avant XOR arriere
    
    
    //Si changement de consigne et front xxx Hz acceleration ou deceleration
    if (m_csgGlobale != m_csgActuelle && iLsys_Fimpulse.impulse()) accDec();

    //Pilotage des sorties
    analogWrite(m_pinAv, m_csgActuelle * m_sensHor);
    analogWrite(m_pinAr, m_csgActuelle * m_sensTri); 
}

void Lctrl_MoteurPWM::accDec(void)
{   //Fonction qui gère le changement de vitesse
    
    
    //Acceleration
    if (m_csgGlobale > m_csgActuelle)
    {
        //Demarrage SET
        if (!m_sensHor &! m_sensTri) m_demarrage = true;
        
        //Set sens pour acceleration 
        m_sensHor = ((modeFct == Mode_auto && cmdAv) || modeFct == Marche_AV_forcee);
        m_sensTri = ((modeFct == Mode_auto && cmdAr) || modeFct == Marche_AR_forcee);

        //Incrementation consigne
        m_csgActuelle ++;

        //Vitesse minimale
        if (m_csgActuelle < csgMini) m_csgActuelle = csgMini;       
        
        //Demarrage RESET
        if (m_demarrage && m_csgAtteinte) m_demarrage = false;
        
        //Shunt acceleration si pas de rampe d'acceleration
        if (m_rampe == 0)  m_csgActuelle = m_csgGlobale;
        
        //Shunt acceleration si moteur en rotation et mode PID
        if (!m_demarrage && pidMode)
        {
            m_csgActuelle = m_csgGlobale;
        }
    }
         
    
    //Deceleration
    if (m_csgGlobale < m_csgActuelle)
    {
        //Decrementation consigne
        m_csgActuelle --;

        //Si Vitesse mini atteinte Reset sens pour deceleration automatique
        if (m_csgActuelle < csgMini)
        {
            m_csgActuelle = 0;
            m_sensHor = false;
            m_sensTri = false;
        }
        
        
        //Shunt deceleration si pas de rampe de deceleration
        if (m_rampe == 0)  m_csgActuelle = m_csgGlobale;

        //Shunt deceleration si changement de consigne en mode PID
        if ((cmdAv || cmdAr) && pidMode)
        {
            m_csgActuelle = m_csgGlobale;
        }
    }
}