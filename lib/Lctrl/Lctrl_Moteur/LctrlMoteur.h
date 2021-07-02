#ifndef LctrlMoteur_h
#define LctrlMoteur_h

#include <Arduino.h>
#include <Lctrl.h>
#include <Lsys_Fimpulse\Lsys_Fimpulse.h>

class LctrlMoteur : public Lctrl
{
public:
    LctrlMoteur(uint8_t mode, uint8_t outMin, uint8_t outMax, uint8_t csgMin, uint8_t csgMax, uint8_t rampeAcc);

    void toggle(void);
    bool stop(void) {m_cmdAv = false; m_cmdAr = false; return m_cmdAv || m_cmdAr;}

    void pidMode(bool enable) {m_pidMode = enable;}
    
    void cmdAv(bool enable) {m_cmdAv = enable; if(enable) m_cmdAr = false;}
    bool cmdAv(void) const {return m_cmdAv;}
    
    void cmdAr(bool enable) {m_cmdAr = enable; if(enable) m_cmdAv = false;}
    bool cmdAR(void) const {return m_cmdAr;}

    void modeFct(uint8_t mode);
    uint8_t modeFct(void) const {return m_modeFct;}
    
    void csgAuto(uint8_t csg);
    uint8_t csgAuto(void) const {return m_csgAuto;}

    void csgManu(uint8_t csg);
    uint8_t csgManu(void) const {return m_csgManu;}

    // Enumération mode de fonctionnement moteur
    enum Mode
    {
        Arret_forcee,
        Marche_AV_forcee,
        Marche_AR_forcee,
        Mode_auto,
        Defaut = 4
    };
    
protected:
    virtual void KM(void);
    virtual bool m2sens() const = 0;
    
    bool m_rearm(bool cdtRearm);
    
    bool m_pidMode;
    bool m_cmdAv, m_cmdAr, m_memCmd;
    bool m_KmAv, m_KmAr;

    uint8_t m_modeFct;
    uint8_t m_modeFctOld;
    uint8_t m_csgAuto, m_csgManu;
    uint8_t m_csgGlobale, m_csgActuelle;
    uint8_t m_csgMin, m_csgMax;
    uint8_t m_rampe;
    uint8_t m_pin;

private:
    uint8_t m_outMin, m_outMax;
};



class LMoteurSpeed
{
private:
    void razTimer() {m_lastMillis = millis();}
    
    bool m_disabled;
    bool m_csgAtteinte;

    unsigned long m_lastMillis;

public:
    //Constructeur
    LMoteurSpeed();

    //Accesseurs
    bool csgAtteinte(void) const {return m_csgAtteinte;}

    //Manipulateur
    void disable(bool Disable) {m_disabled = Disable;}

    //Méthodes
    void main(uint8_t &csgGlobale, uint8_t &csgActuelle, unsigned short const& rampe);
};


#endif