#ifndef LctrlMoteur_h
#define LctrlMoteur_h

#include <Arduino.h>
#include <Lctrl.h>

class LctrlMoteur : public Lctrl
{
public:
    LctrlMoteur(uint8_t mode, uint8_t outMin, uint8_t outMax, uint8_t csgMin, uint8_t csgMax, uint8_t rampeAcc);

    /// @brief  Changement de sens moteur FW -> STOP -> BW -> STOP -> FW ...
    void toggle(void);

    /*! @brief  Arrêt moteur sans décélération */
    void stop(void) {m_cmdAv = false; m_cmdAr = false; m_KmAv = false; m_KmAr = false;}
    bool stopped(void) const {return !m_KmAv &! m_KmAr;}

    /*! @brief  Arrêt moteur avec décélération */
    void release(void) {m_cmdAv = false; m_cmdAr = false;}

    void pidMode(bool enable) {m_pidMode = enable;}
    
    /*! @brief  Bit de commande marche avant.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche avant à la consigne auto
    */
    void cmdAv(bool enable) {m_cmdAv = enable; if(enable) m_cmdAr = false;}
    ///@return retourne l'état de la commande
    bool cmdAv(void) const {return m_cmdAv;}
    
    /*! @brief  Bit de commande marche arrière.
        
        Condition moteur en mode auto modeFct = Mode_auto
        
        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière à la consigne auto
    */
    void cmdAr(bool enable) {m_cmdAr = enable; if(enable) m_cmdAv = false;}
    ///@return retourne l'état de la commande
    bool cmdAR(void) const {return m_cmdAr;}

    /*! @brief  Mode de fonctionnement moteur.
        
        Mode de fonctionement automatique = 3
        liste des modes classname::Mode...
    */
    void modeFct(uint8_t mode);
    uint8_t modeFct(void) const {return m_modeFct;}
    
    /// @brief Consigne de vitesse en mode auto de 0 à 255
    void csgAuto(uint8_t csg);
    /// @return retourne la valeur de consigne
    uint8_t csgAuto(void) const {return m_csgAuto;}

    /// @brief Consigne de vitesse en mode manuel de 0 à 255
    void csgManu(uint8_t csg);
    /// @return retourne la valeur de consigne
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

    //! @brief  Bool indiquant s'il sagit d'un moteur 1 ou 2 sens
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