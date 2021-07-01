#ifndef Lctrl_MoteurPWM_h
#define Lctrl_MoteurPWM_h

#include <Arduino.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_MoteurPWM : public LctrlMoteur
{
public:
    // Enumération  mode de fonctionnement moteur
    enum ModeMoteur
        {
            Arret_forcee,
            Marche_AV_forcee,
            Marche_AR_forcee,
            Mode_auto,
            Defaut
        };
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
    boolean cmdAv = false;
    void setCmdAv(void) {cmdAr = false; cmdAv = true;}
    
    /**************************************************************************/
    /*!
        @brief  Bit de commande marche arrière.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière à la consigne auto
    */
    /**************************************************************************/
    boolean cmdAr = false;
    void setCmdAr(void) {cmdAv = false; cmdAr = true;}

    void stop(void) {cmdAv = false; cmdAr = false;}

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
    boolean isRunning(void) const{return (m_sensHor || m_sensTri);}


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
    uint8_t csgActuelle(void) const {return m_csgActuelle;}

    /**************************************************************************/
    /*!
        @brief  Consigne moteur atteinte
        @return true si la consigne actuelle à atteint la consigne de départ
    */
    /**************************************************************************/
    uint8_t csgAtteinte(void) const {return m_csgAtteinte;}

    /**************************************************************************/
    /*!
        @brief  Fonction principale.
        Execution à chaque tours de loop
    */
    /**************************************************************************/
    void main(void);
    void setup(void);
    
    /**************************************************************************/
    /*!
        @brief  Changement d'état moteur en mode auto
        changement du sens de rotation avec passage à l'arrêt commutant
    */
    /**************************************************************************/
    void toggle(void);
    

private:
    boolean m_memCmd = 0;
    boolean m_sensHor = 0;
    boolean m_sensTri = 0;

    uint8_t m_pinAr;
};

#endif