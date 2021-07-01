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

     /*! @brief  Bit de commande marche.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche à la consigne auto
    */
    boolean cmdAv;
    void setCmdAv(void) {cmdAv = true;}

    /*! @brief  Arrêt moteur avec décélération */
    void stop(void) {cmdAv = false;}
    
    /*! @brief  Arrêt moteur sans décélération */
    void release(void) {cmdAv = false; m_sens = false;}

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false; m_initCycles = 7000 / rampe();}
    
    /*! @brief  Retourne true si le moteur est initialisé */
    boolean isReady() const {return m_initialized;}

    /*! @brief  Changement d'état moteur en mode auto */
    void toggle(void) {cmdAv = !cmdAv;}

    void main(void);
    void setup(void);


private:
    boolean m_initialized = false;
    boolean m_sens = false;
    
    uint16_t m_initCycles = 1000;
    uint16_t m_dtMin;
    uint16_t m_dtMax;

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

    /*! @brief  Bit de commande marche avant.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche avant à la consigne auto
    */
    boolean cmdAv;
    void setCmdAv(void) {cmdAr = false; cmdAv = true;}
    
    /*! @brief  Bit de commande marche arrière.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière à la consigne auto
    */
    boolean cmdAr;
    void setCmdAr(void) {cmdAv = false; cmdAr = true;}

    /*! @brief  Arrêt moteur avec décélération */
    void stop(void) {cmdAv = false; cmdAr = false;}

    /*! @brief  Arrêt moteur sans décélération */
    void release(void) { cmdAr = false; cmdAv = false; m_sensHor = false; m_sensTri = false;}

    /*! @brief  Initialise le moteur automatiquement executé lors du setup */
    void init(void) {m_initialized = false; m_initCycles = 7000 / rampe();}

    /*! @brief  Retourne true si le moteur est initialisé */
    boolean isReady() const {return m_initialized;}

    /*! @brief  Changement d'état moteur en mode auto changement du sens de rotation avec passage à l'arrêt commutant */
    void toggle(void);

    void main(void);
    void setup(void);


private:
    
    boolean m_initialized = false;
    boolean m_memCmd = false;
    boolean m_sensHor = false;
    boolean m_sensTri = false;

    uint16_t m_dtMin;
    uint16_t m_dtMid;
    uint16_t m_dtMax;
    uint16_t m_initCycles = 1000;

    Servo m_servo;
};
#endif