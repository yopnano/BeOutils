#ifndef Lctrl_Stepper_h
#define Lctrl_Stepper_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class LctrlStepper : public LctrlMoteurCsg2cmd
{
public:
    LctrlStepper(byte pinStep, byte pinDir = -1, byte pinEnable = -1, unsigned short stepsRevolution = 200, unsigned short vMax = 1000, unsigned short rampe_ms = 0, byte min = 0, byte max = 255);

    void setup(void) override;

    void step(int nStep = 1);
    bool running(void) const;

    bool keepEnable;        // Verrouillage du moteur à l'arrêt
    bool modeVitesse;       // Mode de fonctionnement Step / Vitesse
    unsigned short vitesse; // Definir la vitesse en tr/min

private:
    void out(void) override;

    byte m_pin;       // Pin de sortie de pas
    byte m_pinDir;    // Pin de sortie de la direction
    byte m_pinEnable; // Pin de sortie d'excitation

    unsigned short m_stepsPerRevolution, m_vMax;

    int m_step;                 // Nombre de pas
    unsigned long m_lastMicros; // Memo microsecondes gestion vitesse
};
#endif