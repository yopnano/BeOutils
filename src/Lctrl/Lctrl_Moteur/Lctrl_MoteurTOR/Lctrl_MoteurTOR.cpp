#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurTOR\Lctrl_MoteurTOR.h>

/// @brief Contrôle moteur par signal TOR.
/// Mettre cmd à true .
/// @param pin n° broche pour pilotage
/// @param inverted inversion des sorties logique ex : avec des relais
Lctrl_MoteurTOR_1sens::Lctrl_MoteurTOR_1sens(byte pin, bool inverted) :
    cmd(false),
    m_pin(pin),
    m_inverted(inverted)
    {        
    }

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_MoteurTOR_1sens::setup(void)
{
    pinMode(m_pin, OUTPUT);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void Lctrl_MoteurTOR_1sens::main(void)
{
    //Pilotage de la sortie
    digitalWrite(m_pin, cmd ^ m_inverted); 
}




/// @brief Contrôle moteur par signal TOR.
/// Mettre cmdAv ou cmdAr à true .
/// @param pinAv n° broche pour pilotage marche avant
/// @param pinAr n° broche pour pilotage marche arrière
/// @param inverted inversion des sorties logique ex : avec des relais
Lctrl_MoteurTOR_2sens::Lctrl_MoteurTOR_2sens(byte pinAv, byte pinAr, bool inverted) :
    cmdAv(false),
    cmdAr(false),
    m_pinAv(pinAv),
    m_pinAr(pinAr),
    m_inverted(inverted)
    {        
    }

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_MoteurTOR_2sens::setup(void)
{
    pinMode(m_pinAv, OUTPUT);
    pinMode(m_pinAr, OUTPUT);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void Lctrl_MoteurTOR_2sens::main(void)
{
    //Pilotage de la sortie
    digitalWrite(m_pinAv, (cmdAv && !cmdAr) ^ m_inverted);
    digitalWrite(m_pinAr, (cmdAr && !cmdAv) ^ m_inverted);
}