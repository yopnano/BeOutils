#ifndef Lctrl_Brushless_h
#define Lctrl_Brushless_h

#include <Arduino.h>
#include <Servo.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_Brushless_1sens : public LctrlMoteurCsg1cmd, private Servo
{
public:
    Lctrl_Brushless_1sens(byte pin, unsigned short rampe_ms = 30, byte min = 0, byte max = 255, unsigned short dtMin = 1000, unsigned short dtMax = 2000);

    void setup(void) override;

private:
    void out(void) override;
    
    byte m_pin;
    unsigned short m_dtMin, m_dtMax;
};

class Lctrl_Brushless_2sens : public LctrlMoteurCsg2cmd, private Servo
{
public:
    Lctrl_Brushless_2sens(byte pin, unsigned short rampe_ms = 30, byte min = 0, byte max = 255, unsigned short dtMin = 1000, unsigned short dtMid = 1500, unsigned short dtMax = 2000);

    void setup(void) override;

private:
    void out(void) override;
    
    byte m_pin;
    unsigned short m_dtMin, m_dtMid, m_dtMax;
};
#endif