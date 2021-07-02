#ifndef Lctrl_Brushless_h
#define Lctrl_Brushless_h

#include <Arduino.h>
#include <Servo.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_Brushless_1sens : public LctrlMoteur
{
public:
    // Enumération  mode de fonctionnement moteur
    enum ModeBrushless
    {
        Arret_forcee,
        Marche_forcee,
        Mode_auto = 3,
        Defaut
    };
    
    Lctrl_Brushless_1sens(uint8_t pin, uint8_t mode, uint8_t rampeAcc = 5, uint16_t dtMin = 1000, uint16_t dtMax = 2000);

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false;}
    
    /*! @brief  Retourne true si le moteur est initialisé */
    boolean isReady() const {return m_initialized;}

    void main(void) override;
    void setup(void) override;
    bool m2sens() const override {return false;}

private:
    boolean m_initialized = false;
    uint16_t m_dtMin;
    uint16_t m_dtMax;

    LMoteurSpeed m_speed;
    Servo m_servo;
};



class Lctrl_Brushless_2sens : public LctrlMoteur
{
public:
    // Enumération  mode de fonctionnement moteur
    enum ModeBrushless
    {
        Arret_forcee,
        Marche_AV_forcee,
        Marche_AR_forcee,
        Mode_auto,
        Defaut
    };
    
    Lctrl_Brushless_2sens(uint8_t pin, uint8_t mode, uint8_t rampeAcc = 5, uint16_t dtMin = 1000, uint16_t dtMid = 1500, uint16_t dtMax = 2000);

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false;}

    /*! @brief  Retourne true si le moteur est initialisé */
    boolean isReady() const {return m_initialized;}

    void main(void) override;
    void setup(void) override;
    bool m2sens() const override {return true;}


private:
    
    boolean m_initialized = false;

    uint16_t m_dtMin;
    uint16_t m_dtMid;
    uint16_t m_dtMax;

    LMoteurSpeed m_speed;
    Servo m_servo;
};
#endif