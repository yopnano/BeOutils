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
        @brief  Bit de commande marche avant.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche avant à la consigne auto
    */
    /**************************************************************************/

    
    /**************************************************************************/
    /*!
        @brief  Bit de commande marche arrière.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière à la consigne auto
    */
    /**************************************************************************/

    void stop(void) {m_cmdAv = false; m_cmdAr = false;}

    /**************************************************************************/
    /*!
        @brief  Bit d'arret immédiat du moteur.
        
        Condition moteur en mode auto modeFct = Mode_auto
        Arrête le moteur snas phase de décélération
    */
    /**************************************************************************/
    void release(void);

    /**************************************************************************/
    /*!
        @brief  etat du moteur.        
        @param FALSE moteur à l'arrêt
        @param TRUE moteur en fonctionnement
          
    */
    /**************************************************************************/
    boolean isRunning(void) const{return (m_KmAv || m_KmAr);}


    /**************************************************************************/
    /*!
        @brief  Consigne de départ et d'arrêt moteur.
        Accélération de csgMini à csgAuto.
        Décélération de csgAuto à csgMini
        @param 0~255 vitesse mini ~ maxi
    */
    /**************************************************************************/
    //uint8_t csgMini; // faire en sorte de le dégager sinon le renommer en csgDemarrage

    /**************************************************************************/
    /*!
        @brief  Consigne envoyée au moteur
        @return 0~255 vitesse mini ~ maxi
    */
    /**************************************************************************/
 
    /**************************************************************************/
    /*!
        @brief  Consigne moteur atteinte
        @return true si la consigne actuelle à atteint la consigne de départ
    */
    /**************************************************************************/

    /**************************************************************************/
    /*!
        @brief  Fonction principale.
        Execution à chaque tours de loop
    */
    /**************************************************************************/
    void main(void) override;
    void setup(void) override;
    
    /**************************************************************************/
    /*!
        @brief  Changement d'état moteur en mode auto
        changement du sens de rotation avec passage à l'arrêt commutant
    */
    /**************************************************************************/
    bool m2sens() const override {return m_pinAr != 255;}

private:
    LMoteurSpeed m_speed;
    uint8_t m_pinAr;
};

#endif