#ifndef Lctrl_Brushless_h
#define Lctrl_Brushless_h

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
    
    Lctrl_Brushless_1sens(unsigned char pin, unsigned char mode, unsigned char rampeAcc = 5, unsigned short dtMin = 1000, unsigned short dtMax = 2000);

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false;}
    
    /*! @brief  Retourne true si le moteur est initialisé */
    bool isReady() const {return m_initialized;}

    void main(void) override;
    void setup(void) override;

private:
    bool m2sens() const override {return false;}
    bool m_initialized = false;
    unsigned short m_dtMin;
    unsigned short m_dtMax;

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
    
    Lctrl_Brushless_2sens(unsigned char pin, unsigned char mode, unsigned char rampeAcc = 5, unsigned short dtMin = 1000, unsigned short dtMid = 1500, unsigned short dtMax = 2000);

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false;}

    /*! @brief  Retourne true si le moteur est initialisé */
    bool isReady() const {return m_initialized;}

    void main(void) override;
    void setup(void) override;


private:
    LMoteurSpeed m_speed;
    Servo m_servo;
    
    bool m2sens() const override {return true;}
    bool m_initialized = false;

    unsigned short m_dtMin;
    unsigned short m_dtMid;
    unsigned short m_dtMax;
};
#endif