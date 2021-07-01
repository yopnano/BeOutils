#ifndef Lctrl_MoteurTOR_h
#define Lctrl_MoteurTOR_h

#include <Arduino.h>

class Lctrl_MoteurTOR
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
        @brief  Contrôle moteur par signal tout ou rien

        @see Lctrl_MotreurPWM

        @param pinAv n° broche pour marche avant
        @param pinAr n° broche pour marche arrière (-1 pour disable) Défaut désactivé
        @param inverted inversion des sorties logique ex : avec des relais
    */
    /**************************************************************************/
    Lctrl_MoteurTOR(uint8_t pinAv, uint8_t pinAr = -1, boolean inverted = false);
    
    /**************************************************************************/
    /*!
        @brief  Bit de commande marche avant.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche avant
    */
    /**************************************************************************/
    boolean cmdAv;

    /**************************************************************************/
    /*!
        @brief  Bit de commande marche arrière.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière
    */
    /**************************************************************************/
    boolean cmdAr;

    /**************************************************************************/
    /*!
        @brief  etat du moteur.        
        @param FALSE moteur à l'arrêt
        @param TRUE moteur en fonctionnement
          
    */
    /**************************************************************************/
    boolean isRunning(void) const{return m_KmAv || m_KmAr;}
    
    /**************************************************************************/
    /*!
        @brief  Mode de fontionnement du moteur.
        @param Lctrl_MoteurPWM::ModeMoteur
        @param 0 Arrêt forcé
        @param 1 Forçage marche avant
        @param 2 Forçage marche arrière
        @param 3 Mode Auto (cmdAv, cmdAr)
        @param 4 Défaut
    */
    /**************************************************************************/
    uint8_t modeFct;
    
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
    boolean m_memCmd;
    boolean m_KmAv;
    boolean m_KmAr;
    boolean m_inverted;
    
    uint8_t m_pinAv;
    uint8_t m_pinAr;
    
};

#endif