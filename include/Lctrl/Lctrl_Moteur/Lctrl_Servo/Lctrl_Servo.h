#ifndef Lctrl_Servo_h
#define Lctrl_Servo_h

#include <Arduino.h>
#include <Servo.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_Servo : public LctrlMoteurCsg1cmd, private Servo
{
public:
    Lctrl_Servo(byte pin, unsigned short rampe_ms = 5, byte min = 0, byte max = 180);

    void operator=(const Lctrl_Servo &right);
    void synchro(Lctrl_Servo &right);

    void setup(void) override;

    void in(void) override;
    void out(void) override;

    bool posAtteinte(void);


    // bool autoRelease; // Detachement du servo lorsque consigne atteinte

private:
    byte m_pin; // Pin de sortie du signal pwm
};
#endif