#ifndef LctrlMoteur_h
#define LctrlMoteur_h

#include <Arduino.h>
#include <BeOutilsConfig.h>
#include <Lctrl\Lctrl.h>
#include <Lcmd\Lcmd_Rampe\Lcmd_Rampe.h>

#ifndef LctrlMoteurSeuilReprise
    #define LctrlMoteurSeuilReprise 0
#endif

class LctrlMoteurCsg1cmd : protected Lcmd_Rampe
{
public:
    LctrlMoteurCsg1cmd(unsigned short rampe_ms = 10, byte min = 0, byte max = 255);

    virtual void setup(void) = 0;
    void main(void);

    void pidMode(bool enable = true);

    bool cmd;   // Commande marche / arrêt moteur (True / False)
    byte rampe; // Rampe d'accélération / décélération. Temps en ms entre chaque maj de consigne
    byte csg;   // Consigne vitesse (0 - 255)

protected:
    virtual void in(void);
    virtual void out(void) = 0;

    byte m_val;        // Valeur de pilotage
    byte m_min, m_max; // Limite de consigne
};

class LctrlMoteurCsg2cmd : protected Lcmd_Rampe
{
public:
    LctrlMoteurCsg2cmd(unsigned short rampe_ms = 10, byte min = 0, byte max = 255);

    virtual void setup(void) = 0;
    virtual void main(void);

    void pidMode(bool enable = true);

    void toggle(bool sansArret = false);

    bool cmdAv; // Commande marche avant (True / False)
    bool cmdAr; // Commande marche arrière (True / False)

    byte rampe; // Rampe d'accélération / décélération. Temps en ms entre chaque maj de consigne
    byte csg;   // Consigne vitesse (0 - 255)

protected:
    virtual void in(void);
    virtual void out(void) = 0;

    bool m_arr;        // Sens de rotation inverse
    byte m_val;        // Valeur de pilotage
    byte m_min, m_max; // Limite de consigne
};

#ifdef UsingLib_Servo
    #include <Lctrl\Lctrl_Moteur\Lctrl_Brushless\Lctrl_Brushless.h>
    #include <Lctrl\Lctrl_Moteur\Lctrl_Servo\Lctrl_Servo.h>
#endif

#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurPWM\Lctrl_MoteurPWM.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurTOR\Lctrl_MoteurTOR.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_Variateur\Lctrl_Variateur.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_Stepper\Lctrl_Stepper.h>

#endif