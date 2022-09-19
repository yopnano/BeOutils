#ifndef Lctrl_Stepper_h
#define Lctrl_Stepper_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class LctrlStepper : public LctrlMoteur
{
private:
    LMoteurSpeed m_speed;
    
    bool m2sens() const override {return m_pinDir;}
    bool m_keepEnable;

    unsigned char m_pinDir, m_pinEnable;
    
    unsigned short m_stepsPerRevolution;
    unsigned short m_vMax, m_vitesse;

    int m_step;
    unsigned long m_lastMicros;

public:
    // Enumération mode de fonctionnement moteur
    enum Mode
    {
        Arret_forcee,
        Marche_AV_forcee,
        Marche_AR_forcee,
        Mode_auto,
        Defaut,
        Mode_vitesse,
        Mode_step
    };

    LctrlStepper(unsigned char pinStep, unsigned char pinDir = -1, unsigned char pinEnable = -1, unsigned short stepsRevolution = 200, unsigned short vMax = 1000, unsigned char mode = Mode_auto,  unsigned char csgMin = 0, unsigned char csgMax = 0, unsigned char rampeAcc = 0);
    void setup(void) override;
    void main(void) override;
    
    void setSpeed(unsigned short vitesse) {m_vitesse = vitesse;}
    void step(int nStep = 1) {m_step = nStep; m_csgActuelle = 1; m_KmAr = m_step < 0;}
    void keepEnable(bool enable) {m_keepEnable = enable;}

    bool running(void) const {return m_csgGlobale;}
};
#endif