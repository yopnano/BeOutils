#include <Lctrl\Lctrl_Moteur\Lctrl_Brushless\Lctrl_Brushless.h>
#ifdef UsingLib_Servo

/// @brief Controle moteur brushless 1 sens avec ESC
/// @param pin n° broche du signal
/// @param rampe_ms Temps Accélération / décélération en ms : 10 = 2.5 sec de 0 à 255
/// @param min consigne minimum la sortie PWM ne descend pas sous cette valeur
/// @param max consigne maximum la sortie PWM ne dépasse pas cette valeur
/// @param dtMin valeur ou le moteur est à l'arrêt
/// @param dtMax valeur ou le moteur est au maximum
Lctrl_Brushless_1sens::Lctrl_Brushless_1sens(byte pin, unsigned short rampe_ms, byte min, byte max, unsigned short dtMin, unsigned short dtMax)
    : LctrlMoteurCsg1cmd(rampe_ms, min, max),
      Servo(),
      m_pin(pin),
      m_dtMin(dtMin),
      m_dtMax(dtMax)
{
}

/*! @brief  Initialiser le moteur */
void Lctrl_Brushless_1sens::setup(void)
{
    this->attach(m_pin, m_dtMin, m_dtMax);
    this->write(180);
    delay(2500);
    this->write(0);
    delay(2500);
}

/// @brief Pilotage de la sortie
void Lctrl_Brushless_1sens::out(void)
{
    this->writeMicroseconds(map(m_val, m_min, m_max, m_dtMin, m_dtMax));
}

/// @brief Controle moteur brushless 2 sens avec ESC
/// @param pin n° broche du signal
/// @param rampe_ms Temps Accélération / décélération en ms : 10 = 2.5 sec de 0 à 255
/// @param mini consigne minimum la sortie PWM ne descend pas sous cette valeur
/// @param maxi consigne maximum la sortie PWM ne dépasse pas cette valeur
/// @param dtMin valeur ou le moteur est au maximum sens inverse
/// @param dtMid valeur ou le moteur est à l'arrêt
/// @param dtMax valeur ou le moteur est au maximum
Lctrl_Brushless_2sens::Lctrl_Brushless_2sens(byte pin, unsigned short rampe_ms, byte min, byte max, unsigned short dtMin, unsigned short dtMid, unsigned short dtMax)
    : LctrlMoteurCsg2cmd(rampe_ms, min, max),
      Servo(),
      m_pin(pin),
      m_dtMin(dtMin),
      m_dtMid(dtMid),
      m_dtMax(dtMax)
{
}

/*! @brief  Initialiser le moteur */
void Lctrl_Brushless_2sens::setup(void)
{
    this->attach(m_pin, m_dtMin, m_dtMax);
    this->write(180);
    delay(2500);
    this->write(0);
    delay(1000);
    this->write(90);
    delay(2500);
}

/// @brief Pilotage de la sortie
void Lctrl_Brushless_2sens::out(void)
{
    if (m_arr)
        this->writeMicroseconds(map(m_val, m_min, m_max, m_dtMid, m_dtMin));
    else
        this->writeMicroseconds(map(m_val, m_min, m_max, m_dtMid, m_dtMax));
}
#endif