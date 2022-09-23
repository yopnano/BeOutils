#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurTOR\Lctrl_MoteurTOR.h>

Lctrl_MoteurTOR::Lctrl_MoteurTOR(unsigned char pinAv, unsigned char pinAr, unsigned char mode, bool inverted) :
    //Constructeur
    LctrlMoteurOld(mode, 0, 0, 0, 0, 0)
    {
        m_pin = pinAv;
        m_pinAr = pinAr;
    }

void Lctrl_MoteurTOR::setup(void)
{
    pinMode(m_pin, OUTPUT);
    pinMode(m_pinAr, OUTPUT);
    m_modeFct = Mode_auto;
}

//Fonction principale moteur
void Lctrl_MoteurTOR::main(void)
{
    //Pilotage des sorties
    m_KmAv = ((m_modeFct == Mode_auto && m_cmdAv &! m_cmdAr) || m_modeFct == Marche_AV_forcee) ^ m_inverted;
    m_KmAr = ((m_modeFct == Mode_auto && m_cmdAr &! m_cmdAv) || m_modeFct == Marche_AR_forcee) ^ m_inverted;
    
    digitalWrite(m_pin, m_KmAv);
    digitalWrite(m_pinAr, m_KmAr); 
}