#ifndef Lctrl_VFD_h
#define Lctrl_VFD_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_VariateurTOR
{
public:

    Lctrl_VariateurTOR(byte pinRdy, byte pinRun, byte pinStf, byte pinStr, byte pinSpd, bool deuxVitesses = false);

    void setup(void);
    void main(void);

    void vitesse1(void); // Passage vitesse 1 Low (fonctionne si RH est cablée sur +24V)
    void vitesse2(void); // Passage vitesse 2 High

    bool f;        // Variateur en défaut
    bool rm;       // Retour de marche (moteur en fonctionnement)
    bool cmdAv;    // Commande marche avant / arrêt moteur (True / False)
    bool cmdAr;    // Commande marche arrière / arrêt moteur (True / False)


private:

    bool m_vitesse1;
    bool m_vitesse2;
    bool m_deuxVitesses;

    byte m_pinRdy;
    byte m_pinRun;
    byte m_pinStf;
    byte m_pinStr;
    byte m_pinSpd;
};


class Lctrl_VariateurPWM : public LctrlMoteurCsg2cmd
{
public:

    Lctrl_VariateurPWM(byte pinRdy, byte pinRun, byte pinStf, byte pinStr, byte pinSpd);

    void setup(void) override;
    
    bool f;        // Variateur en défaut
    bool rm;       // Retour de marche (moteur en fonctionnement)

private:

    void out(void) override;
    
    byte m_pinRdy;
    byte m_pinRun;
    byte m_pinStf;
    byte m_pinStr;
    byte m_pinSpd;
};

#endif