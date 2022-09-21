#include <Lio\LioPwm\LioPwm.h>

/// @brief Sortie PWM.
/// @param pin N° broche sortie PWM
/// @param inverted Inverser la valeur de la sortie 0 -> 255
LioPwm::LioPwm(byte pin, bool inverted) : m_inverted(inverted),
                                          m_pin(pin),
                                          cmd(false),
                                          val(0)
{
}

void LioPwm::setup(void)
{
    // Verifie si la pin est PWM
    if (digitalPinToTimer(m_pin) == NOT_ON_TIMER)
    {
        Serial.print(F("LioPwm Warning : pin > "));
        Serial.print(m_pin);
        Serial.println(F(" isn't PWM"));
    }
    else
        pinMode(m_pin, OUTPUT);
}

/// @brief Main PWM.
/// Gestion de la sortie PWM
void LioPwm::main(void)
{
    // Ecriture de la sortie
    analogWrite(m_pin, abs((m_inverted ? 255 : 0) - (val * enable())));
}

// ======================= Lio Pwm Tor ======================= //

/// @brief OBSOLETE utilisez LioPwm.cmd à la place
/// @param pin
/// @param inverted
LioPwmTor::LioPwmTor(byte pin, bool inverted) : LioPwm(pin, inverted),
                                                m_oldValue(0)
{
}

/// @brief Desactiver l'actionneur
void LioPwmTor::turnOff(void)
{
    if (val)
        m_oldValue = val;
    val = 0;
}

/// @brief Activer l'actionneur.
/// La consigne retourne à la valeur précedente
/// ATTENTION : la sortie peut passer à 255
void LioPwmTor::turnOn(void)
{
    if (!val)
        val = (m_oldValue) ? m_oldValue : 255;
}

/// @brief description l'état de l'actionneur
/// si actionneur en marche -> arrêt
/// si actionneur à l'arrêt -> dernière consigne utilisée
void LioPwmTor::toggle(void)
{
    if (val)
        turnOff();
    else
        turnOn();
}

// ======================= Lio Pwm Rampe ======================= //

/// @brief Sortie PWM avec rampe.
/// @param pin N° broche sortie PWM
/// @param rampe_ms Rampe d'accélération en ms
/// @param inverted Inverser la valeur de la sortie 0 -> 255
LioPwmRampe::LioPwmRampe(byte pin, byte rampe_ms, bool inverted) : LioPwm(pin, inverted),
                                                                   Lcmd_Rampe(rampe_ms),
                                                                   csg(0){};

/// @brief Main PWM.
/// Gestion de la sortie PWM
void LioPwmRampe::main(void)
{
    Lcmd_Rampe::main(csg * enable(), val);
    LioPwm::main();
}