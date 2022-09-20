#ifndef LioPwm_h
#define LioPwm_h

#include <Arduino.h>
#include <Lcmd\Lcmd_Rampe\Lcmd_Rampe.h>

class LioPwm
{
protected:
    bool m_inverted;
    byte m_pin;

public:
    LioPwm(byte pin, bool inverted = false);

    void main(void);
    void setup(void);

    /// @brief Commande de la sortie (false - true)
    bool cmd;

    /// @brief Valeur de la sortie (0 - 255)
    byte val;
};

class LioPwmTor : public LioPwm
{
private:
    byte m_oldValue;

public:
    LioPwmTor(byte pin, bool inverted = false);

    void turnOn();
    void turnOff();
    void toggle();
};

class LioPwmRampe : public LioPwm, public Lcmd_Rampe
{
public:
    LioPwmRampe(byte pin, byte rampe_ms = 10, bool inverted = false);

    void main(void);

    /// @brief  Consigne de la sortie (0 - 255)
    byte csg;
};
#endif