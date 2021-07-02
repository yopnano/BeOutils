#ifndef Lctrl_Servo_h
#define Lctrl_Servo_h

#include <Servo.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_Servo : public LctrlMoteur
{
public:
    // Enumération  mode de fonctionnement moteur
    enum ModeServo
        {
            Arret_forcee,
            Marche_forcee,
            Mode_vitessePos,
            Mode_auto,
            Defaut
        };

    Lctrl_Servo(unsigned char pin, unsigned char mode, unsigned char rampeAcc = 5, unsigned char posMin = 0, unsigned char posMax = 180);

    void main(void) override;
    void setup(void) override;
    void autoRelease(bool enable) {m_autoRelease = enable;}

private:
    LMoteurSpeed m_speed;
    Servo m_servo;
    
    bool m2sens() const override {return false;}
    bool m_autoRelease;
};
#endif