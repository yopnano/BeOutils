#ifndef Lctrl_Stepper_h
#define Lctrl_Stepper_h

#include <Arduino.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class LctrlStepper : public LctrlMoteur
{
private:
    LMoteurSpeed m_speed;
    
    bool m_keepEnable;

    uint8_t m_pinDir, m_pinEnable;
    
    uint16_t m_stepsPerRevolution;
    uint16_t m_vMax, m_vitesse;

    int m_step;
    unsigned long m_lastMicros;

    //void accDec(void);
    bool m2sens() const override {return m_pinDir;}
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

    LctrlStepper(uint8_t pinStep, uint8_t pinDir = -1, uint8_t pinEnable = -1, uint16_t stepsRevolution = 200, uint16_t vMax = 1000, uint8_t mode = Mode_auto,  uint8_t csgMin = 0, uint8_t csgMax = 0, uint8_t rampeAcc = 0);
    void setup(void) override;
    void main(void) override;
    
    void setSpeed(uint16_t vitesse) {m_vitesse = vitesse;}
    void step(int nStep = 1) {m_step = nStep; m_csgActuelle = 1; m_KmAr = m_step < 0;}
    bool running(void) const {return m_csgGlobale;}
    void keepEnable(bool enable) {m_keepEnable = enable;}
};



#endif