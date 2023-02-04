#ifndef Lctrl_MoteurTOR_h
#define Lctrl_MoteurTOR_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_MoteurTOR_1sens
{
public:

    Lctrl_MoteurTOR_1sens(byte pin, bool inverted = false);
    
    bool cmd;    // Commande marche / arrêt moteur (True / False)

    void setup(void);
    void main(void);

private:
    byte m_pin;
    bool m_inverted;
    
};


class Lctrl_MoteurTOR_2sens
{
public:

    Lctrl_MoteurTOR_2sens(byte pinAv, byte pinAr, bool inverted = false);

    bool cmdAv;    // Commande marche avant / arrêt moteur (True / False)
    bool cmdAr;    // Commande marche arrière / arrêt moteur (True / False)

    void setup(void);
    void main(void);

protected:
    byte m_pinAv;
    byte m_pinAr;
    bool m_inverted;
    
};
#endif