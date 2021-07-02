#ifndef Lctrl_DriveS500_h
#define Lctrl_DriveS500_h

#include <Arduino.h>
#include <Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_DriveS500 : public LctrlMoteur
{
public:
    // Enumération  mode de fonctionnement moteur
    enum Mode
    {
        Arret_forcee,
        Marche_AV_forcee,
        Marche_AR_forcee,
        Mode_auto_Ana,
        Defaut,
        Mode_auto_Tor
    };

    /**************************************************************************/
    /*!
        @brief  Contrôle moteur par variateur de fréquence type S500

        Mettre cmdAv ou cmdAr à true et appliquer une vitesse de consigne (0 - 255).
        Acceleration / Deceleration automatique parametrable ainsi qu'une consigne mini

        @param pinReady n° broche variateur prêt
        @param pinRun n° broche moteur run
        @param pinStf n° broche marche avant
        @param pinStr n° broche marche arrière
        @param pinSpeed n° broche commande de vitesse (TOR / ANA) configurer le variateur en fonction
    
        @param vitesseMini consigne de vitesse de démarrage et d'arrêt moteur Defaut 0
        @param rampeAcc temps en milliseconde changement vitesse Defaut 0
    */
    /**************************************************************************/
    Lctrl_DriveS500(uint8_t pinReady = -1, uint8_t pinRun = -1, uint8_t pinStf = -1, uint8_t pinStr = -1, uint8_t pinSpeed = -1, uint8_t mode = Mode_auto_Ana, uint8_t rampeAcc = 0);

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
    boolean isRunning(void) const{ return pinIsEnable(m_pinRun) ? digitalRead(m_pinRun) == LOW : (m_KmAv || m_KmAr);}


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
    bool rearm() {return m_rearm(m_ready);}
    bool isReady(void) {m_ready = digitalRead(m_pinRdy) || pinIsDisable(m_pinRdy); return m_ready;}

    /**************************************************************************/
    /*!
        @brief  Changement d'état moteur en mode auto
        changement du sens de rotation avec passage à l'arrêt commutant
    */
    /**************************************************************************/
    bool m2sens() const override {return pinIsEnable(m_pinStr);}

private:
    LMoteurSpeed m_speed;

    boolean m_ready;
    boolean m_running;

    uint8_t m_pinRdy;
    uint8_t m_pinRun;
    uint8_t m_pinStf;
    uint8_t m_pinStr;

    void KM(void) override;
};

#endif