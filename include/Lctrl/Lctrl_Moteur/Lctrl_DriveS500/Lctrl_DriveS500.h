#ifndef Lctrl_DriveS500_h
#define Lctrl_DriveS500_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

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
    Lctrl_DriveS500(unsigned char pinReady = -1,
                    unsigned char pinRun = -1,
                    unsigned char pinStf = -1,
                    unsigned char pinStr = -1,
                    unsigned char pinSpeed = -1,
                    unsigned char mode = Mode_auto_Ana,
                    unsigned char rampeAcc = 0);

    /**************************************************************************/
    /*!
        @brief  etat du moteur.        
        @param FALSE moteur à l'arrêt
        @param TRUE moteur en fonctionnement
          
    */
    /**************************************************************************/
    bool isRunning(void) const{ return pinIsEnable(m_pinRun) ? digitalRead(m_pinRun) == LOW : (m_KmAv || m_KmAr);}

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

private:
    LMoteurSpeed m_speed;

    void KM(void) override;
    
    bool m2sens() const override {return pinIsEnable(m_pinStr);}
    bool m_ready;
    bool m_running;

    unsigned char m_pinRdy;
    unsigned char m_pinRun;
    unsigned char m_pinStf;
    unsigned char m_pinStr;

};

#endif