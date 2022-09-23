#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurPWM\Lctrl_MoteurPWM.h>

/// @brief Contrôle moteur par signal PWM.
/// Mettre cmd à true et appliquer une de consigne de (0 - 255).
/// Accélération / Décélération automatique paramétrable ainsi qu'un bornage consignes
/// @param pin n° broche pour pilotage
/// @param rampe_ms temps en milliseconde changement vitesse Defaut 0
/// @param min consigne de vitesse de démarrage et d'arrêt moteur Defaut 0
/// @param max consigne de vitesse maximale moteur Defaut 255
Lctrl_MoteurPWM_1sens::Lctrl_MoteurPWM_1sens(byte pin, unsigned short rampe_ms, byte min, byte max)
    : LctrlMoteurCsg1sens(rampe_ms, min, max),
      m_pin(pin)
{
}

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_MoteurPWM_1sens::setup(void)
{
    pinMode(m_pin, OUTPUT);
}

/// @brief Gestion de la sortie
void Lctrl_MoteurPWM_1sens::out(void)
{
    analogWrite(m_pin, m_val);
}

/// @brief Contrôle moteur 2 sens par signal PWM.
/// Mettre cmdAv ou cmdAr à true et appliquer une consigne de (0 - 255).
/// Accélération / Décélération automatique paramétrable ainsi qu'un bornage consignes
/// @param pinAv n° broche pour marche avant
/// @param pinAr n° broche pour marche arrière
/// @param rampe_ms temps en milliseconde changement vitesse Defaut 0
/// @param min consigne de vitesse de démarrage et d'arrêt moteur Defaut 0
/// @param max consigne de vitesse maximale moteur Defaut 255
Lctrl_MoteurPWM_2sens::Lctrl_MoteurPWM_2sens(byte pinAv, byte pinAr, unsigned short rampe_ms, byte min, byte max)
    : LctrlMoteurCsg2sens(rampe_ms, min, max),
      m_pinAv(pinAv),
      m_pinAr(pinAr)
{
}

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_MoteurPWM_2sens::setup(void)
{
    pinMode(m_pinAv, OUTPUT);
    pinMode(m_pinAr, OUTPUT);
}

/// @brief Gestion des sorties
void Lctrl_MoteurPWM_2sens::out(void)
{
    analogWrite(m_pinAv, m_val * !m_arr);
    analogWrite(m_pinAr, m_val * m_arr);
}