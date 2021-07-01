#ifndef Lctrl_Servo_h
#define Lctrl_Servo_h

#include <Arduino.h>
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

    Lctrl_Servo(uint8_t pin, uint8_t mode, uint8_t rampeAcc = 5, uint8_t posMin = 0, uint8_t posMax = 180);

    void main(void);
    void setup(void);
    boolean autoRelease = false;


private:
    Servo m_servo;
};


#endif