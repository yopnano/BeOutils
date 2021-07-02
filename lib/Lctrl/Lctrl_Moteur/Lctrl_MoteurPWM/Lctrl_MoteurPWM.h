#ifndef Lctrl_MoteurPWM_h
#define Lctrl_MoteurPWM_h

#include <Arduino.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_MoteurPWM : public LctrlMoteur
{
public:
    /**************************************************************************/
    /*!
        @brief  Contrôle moteur par signal pwm

        Mettre cmdAv ou cmdAr à true et appliquer une vitesse de consigne (0 - 255).
        Acceleration / Deceleration automatique parametrable ainsi qu'une consigne mini
        @see Lctrl_MotreurTOR

        @param pinAv n° broche pour marche avant
        @param pinAr n° broche pour marche arrière (-1 pour disable) Défaut désactivé
        @param vitesseMini consigne de vitesse de démarrage et d'arrêt moteur Defaut 0
        @param rampeAcc temps en milliseconde changement vitesse Defaut 0
    */
    /**************************************************************************/
    Lctrl_MoteurPWM(uint8_t pinAv, uint8_t pinAr = 0, uint8_t mode = Mode_auto, uint8_t csgMin = 0, uint8_t csgMax = 0, uint8_t rampeAcc = 0);

    /**************************************************************************/
    /*!
        @brief  etat du moteur.        
        @param FALSE moteur à l'arrêt
        @param TRUE moteur en fonctionnement
          
    */
    /**************************************************************************/
    boolean isRunning(void) const{return (m_KmAv || m_KmAr);}

    void main(void) override;
    void setup(void) override;
    
    bool m2sens() const override {return m_pinAr != 255;}

private:
    LMoteurSpeed m_speed;
    uint8_t m_pinAr;
};

#endif