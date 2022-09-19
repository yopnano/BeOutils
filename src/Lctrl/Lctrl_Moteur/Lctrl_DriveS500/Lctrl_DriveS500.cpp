#include <Lctrl\Lctrl_Moteur\Lctrl_DriveS500\Lctrl_DriveS500.h>

Lctrl_DriveS500::Lctrl_DriveS500(unsigned char pinReady, unsigned char pinRun, unsigned char pinStf, unsigned char pinStr,
                                 unsigned char pinSpeed, unsigned char mode, unsigned char rampeAcc) :
    //Constructeur
    LctrlMoteur(mode, 0, 255, 0, 255, rampeAcc),
    m_pinRdy(pinReady),
    m_pinRun(pinRun),
    m_pinStf(pinStf),
    m_pinStr(pinStr)
    {
        m_pin = pinSpeed;
    }


void Lctrl_DriveS500::setup(void)
{   //Setup des IOs
    
    if (pinIsEnable(m_pinRdy)) pinMode(m_pinRdy, INPUT_PULLUP);
    if (pinIsEnable(m_pinRun)) pinMode(m_pinRun, INPUT_PULLUP);
    
    //Verifie si la pin speed est PWM
    if (digitalPinToTimer(m_pin  ) == NOT_ON_TIMER && m_modeFct == Mode_auto_Ana)
    {
        Serial.print (F("Lctrl_DriveS500 Warning : Pin speed > "));
        Serial.print (m_pin);
        Serial.println (F(" isn't PWM"));
    }
    else pinMode(m_pin, OUTPUT);
    
    if(pinIsEnable(m_pinStf)) pinMode(m_pinStf, OUTPUT);
    if(pinIsEnable(m_pinStr)) pinMode(m_pinStr, OUTPUT);    
}

void Lctrl_DriveS500::main(void)
{   //Fonction principale moteur
    
    //Calcul de la consigne en fonction de l'état de marche
    m_csgGlobale =  (m_modeFct == Marche_AV_forcee) * m_csgManu + //Mode manu avant
                    (m_modeFct == Marche_AR_forcee) * m_csgManu + //Mode manu arriere
                    (m_modeFct == Mode_auto_Ana) * (m_cmdAv ^ m_cmdAr) * m_csgAuto; //Mode auto avant XOR arriere
    
    //Mode PID
    m_speed.disable(m_pidMode);

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_speed.main(m_csgGlobale, m_csgActuelle, m_rampe);

    //Gestions KmAv KmAr
    KM();

    //Si variateur non prêt
    if (! isReady() )
    {
        stop();
        modeFct(Defaut);
        m_KmAv = false;
        m_KmAr = false;
        m_csgActuelle = 0;
    }
    
    //Pilotage des sorties
    if (pinIsEnable(m_pinStf)) digitalWrite(m_pinStf, m_KmAv);
    if (pinIsEnable(m_pinStr)) digitalWrite(m_pinStr, m_KmAr);

    if (m_modeFct == Mode_auto_Ana)
        analogWrite(m_pin  , m_csgActuelle * m_KmAv ^ m_KmAr);

    if (m_modeFct == Mode_auto_Tor)
        digitalWrite(m_pin, m_KmAv ^ m_KmAr);
       
}

void Lctrl_DriveS500::KM(void)
{
    m_KmAv = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto_Ana && m_cmdAv) || m_KmAv))
             ||  m_modeFct == Marche_AV_forcee
             || (m_modeFct == Mode_auto_Tor && m_cmdAv);

    m_KmAr = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto_Ana && m_cmdAr) || m_KmAr))
             ||  m_modeFct == Marche_AR_forcee
             || (m_modeFct == Mode_auto_Tor && m_cmdAr);
}