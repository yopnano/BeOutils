#ifndef LctrlMoteur_h
#define LctrlMoteur_h

#include <Arduino.h>
#include <Lsys_Fimpulse\Lsys_Fimpulse.h>


class LctrlMoteur
{
public:
    /*! @brief Configuration de l'actionneur
        @param outMin Limite extrême de l'actionneur 0 en général
        @param outMax Limite extrême de l'actionneur 255 PWM; 180° Servo ...
        @param csgMin Consigne mode Auto minimum appliquée à l'actionneur
        @param csgMin Consigne mode Auto maximum appliquée à l'actionneur
        @param rampeAcc  Fréquence d'éxécution de la rampe d'accélération, millisecondes
    */
    LctrlMoteur(uint8_t mode, uint8_t outMin, uint8_t outMax, uint8_t csgMin, uint8_t csgMax, uint8_t rampeAcc);

    //! @brief Configuration de l'actionneur pour pouvoir fonctionner avec un PID externe
    boolean pidMode = false;
    
    //! @brief Mode de fonctionnement de l'actionneur coir les énumérations 
    uint8_t modeFct = 3;

    /*! @brief Consigne de l'actionneur en mode auto
        @param valeur devant respecter la plage de consigne min/max (cf. constructeur)
    */
    uint8_t csgAuto = 0;

    /*! @brief Consigne de l'actionneur en mode manuel
        @param valeur devant respecter les limites min/max (cf. constructeur)
    */
    uint8_t csgManu = 0;

protected:
    //! @brief Fonction commune aux différent type d'actionneurs
    void checkAttr(void);

    //! @brief Fonction commune aux différent type d'actionneurs
    void mainCommon(void);
    
    //! @brief Bit d'impulsion pour changement de vitesse acc/déc
    boolean pulseRampe(void) {return iLsys_Fimpulse.impulse();}
    
    //! @brief = TRUE si la consigne Actuelle est = consigne Globale 
    boolean m_csgAtteinte = false;

    //! @brief Consigne à atteindre (acc/déc ...)
    uint8_t m_csgGlobale = 0;
    
    //! @brief Consigne envoyée à l'actionneur
    uint8_t m_csgActuelle = 0;
    
    //! @brief Pin de commande de l'actionneur
    uint8_t m_pin;
    
    //! @brief Limite de consigne auto
    uint8_t m_csgMin, m_csgMax;

    uint8_t rampe() const {return m_rampe;}

private:

    //! @brief Limites extrêmes de la sortie (0-255 PWM, 0-180 Servo, etc...)
    uint8_t m_outMin, m_outMax;

    //! @brief Fréquence d'éxécution de la rampe d'accélération, millisecondes
    uint8_t m_rampe;

    // Instance de la fonction d'impulsion
    Lsys_Fimpulse iLsys_Fimpulse;
};
#endif