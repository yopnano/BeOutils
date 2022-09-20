#include <Lio\LioPwm\LioPwm.h>

LioPwm::LioPwm(uint8_t pin, bool inverted) : // Constructeur
                                             m_inverted(inverted),
                                             m_pin(pin),
                                             m_oldValue(0),
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

void LioPwm::main(void)
{
    // Borne la consigne entre 0 et 255
    val = constrain(val, 0, 255);

    // Ecriture de la sortie
    analogWrite(m_pin, abs((m_inverted ? 255 : 0) - val));
}

// ======================= Lio Pwm Tor ======================= //
void LioPwmTor::turnOff(void)
{
    if (val)
        m_oldValue = val;
    val = 0;
}

void LioPwmTor::turnOn(void)
{
    if (!val)
        val = (m_oldValue) ? m_oldValue : 255;
}

void LioPwmTor::toggle(void)
{
    if (val)
        turnOff();
    else
        turnOn();
}

// ======================= Lio Pwm Rampe ======================= //
LioPwmRampe::LioPwmRampe(uint8_t pin, unsigned short rampe_ms, bool inverted) : LioPwm(pin, inverted),
                                                                                Lcmd_Rampe(rampe_ms),
                                                                                csg(0){};

void LioPwmRampe::main(void)
{
    Lcmd_Rampe::main(csg, val);
    LioPwm::main();
}