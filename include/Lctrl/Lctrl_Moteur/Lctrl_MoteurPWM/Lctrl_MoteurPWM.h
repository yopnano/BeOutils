#ifndef Lctrl_MoteurPWM_h
#define Lctrl_MoteurPWM_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_MoteurPWM_1sens : public LctrlMoteurCsg1sens
{
public:
    Lctrl_MoteurPWM_1sens(byte pin, unsigned short rampe_ms = 0, byte min = 0, byte max = 255);

    void setup(void) override;
    void out(void) override;

private:
    byte m_pin; // Pin de sortie du signal pwm
};

class Lctrl_MoteurPWM_2sens : public LctrlMoteurCsg2sens
{
public:
    Lctrl_MoteurPWM_2sens(byte pinAv, byte pinAr, unsigned short rampe_ms = 0, byte min = 0, byte max = 255);

    void setup(void) override;
    void out(void) override;

private:
    byte m_pinAv; // Pin de sortie du signal pwm avant
    byte m_pinAr; // Pin de sortie du signal pwm arrière
};
#endif