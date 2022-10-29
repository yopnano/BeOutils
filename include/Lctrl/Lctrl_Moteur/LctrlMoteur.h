#ifndef LctrlMoteur_h
#define LctrlMoteur_h

#include <Arduino.h>
#include <BeOutilsConfig.h>
#include <Lctrl\Lctrl.h>
#include <Lcmd\Lcmd_Rampe\Lcmd_Rampe.h>

#ifndef LctrlMoteurSeuilReprise
#define LctrlMoteurSeuilReprise 0
#endif

class LctrlMoteurCsg1cmd : /*public Lctrl, */ protected Lcmd_Rampe
{
public:
    LctrlMoteurCsg1cmd(unsigned short rampe_ms = 10, byte min = 0, byte max = 255);

    virtual void setup(void) = 0;
    void main(void);

    void pidMode(bool enable = true);



    bool cmd;   // Commande marche / arrêt moteur (True / False)
    byte rampe; // Rampe d'accélération / décélération. Temps en ms entre chaque maj de consigne
    byte csg;   // Consigne vitesse (0 - 255)
    byte m_val;        // Valeur de pilotage

protected:
    virtual void in(void);
    virtual void out(void) = 0;

    byte m_min, m_max; // Limite de consigne
};

class LctrlMoteurCsg2cmd : protected Lcmd_Rampe
{
public:
    LctrlMoteurCsg2cmd(unsigned short rampe_ms = 10, byte min = 0, byte max = 255);

    virtual void setup(void) = 0;
    void main(void);

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

class LctrlMoteurOld : public Lctrl
{
public:
    LctrlMoteurOld(unsigned char mode, unsigned char outMin, unsigned char outMax, unsigned char csgMin, unsigned char csgMax, unsigned char rampeAcc);

    /// @brief  Changement de sens moteur FW -> STOP -> BW -> STOP -> FW ...
    void toggle(void);

    /*! @brief  Arrêt moteur sans décélération */
    void stop(void)
    {
        m_cmdAv = false;
        m_cmdAr = false;
        m_KmAv = false;
        m_KmAr = false;
    }
    bool stopped(void) const { return !m_KmAv & !m_KmAr; }

    /*! @brief  Arrêt moteur avec décélération */
    void release(void)
    {
        m_cmdAv = false;
        m_cmdAr = false;
    }

    void pidMode(bool enable) { m_pidMode = enable; }

    /*! @brief  Bit de commande marche avant.

        Condition moteur en mode auto modeFct = Mode_auto

        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche avant à la consigne auto
    */
    void cmdAv(bool enable)
    {
        m_cmdAv = enable;
        if (enable)
            m_cmdAr = false;
    }
    ///@return retourne l'état de la commande
    bool cmdAv(void) const { return m_cmdAv; }

    /*! @brief  Bit de commande marche arrière.

        Condition moteur en mode auto modeFct = Mode_auto

        @param  FALSE > moteur à l'arrêt
        @param  TRUE  > marche arrière à la consigne auto
    */
    void cmdAr(bool enable)
    {
        m_cmdAr = enable;
        if (enable)
            m_cmdAv = false;
    }
    ///@return retourne l'état de la commande
    bool cmdAr(void) const { return m_cmdAr; }

    /*! @brief  Mode de fonctionnement moteur.

        Mode de fonctionement automatique = 3
        liste des modes classname::Mode...
    */
    void modeFct(unsigned char mode);
    unsigned char modeFct(void) const { return m_modeFct; }

    /// @brief Consigne de vitesse en mode auto de 0 à 255
    void csgAuto(unsigned char csg);
    /// @return retourne la valeur de consigne
    unsigned char csgAuto(void) const { return m_csgAuto; }

    /// @brief Consigne de vitesse en mode manuel de 0 à 255
    void csgManu(unsigned char csg);
    /// @return retourne la valeur de consigne
    unsigned char csgManu(void) const { return m_csgManu; }

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

    unsigned char m_modeFct;
    unsigned char m_modeFctOld;
    unsigned char m_csgAuto, m_csgManu;
    unsigned char m_csgGlobale, m_csgActuelle;
    unsigned char m_csgMin, m_csgMax;
    unsigned char m_rampe;
    unsigned char m_pin;

private:
    unsigned char m_outMin, m_outMax;
};

class LMoteurSpeed
{
private:
    void razTimer() { m_lastMillis = millis(); }

    bool m_disabled;
    bool m_csgAtteinte;

    unsigned long m_lastMillis;

public:
    // Constructeur
    LMoteurSpeed();

    // Accesseurs
    //! @return True si consigne atteinte
    bool csgAtteinte(void) const { return m_csgAtteinte; }

    // Manipulateur
    //! @brief Désactivation rampes @param Boolean
    void disable(bool Disable) { m_disabled = Disable; }

    // Méthodes
    //! @brief Gestion de la consigne
    void main(unsigned char &csgGlobale, unsigned char &csgActuelle, unsigned short const &rampe);
};

#ifdef UsingLib_Servo
    #include <Lctrl\Lctrl_Moteur\Lctrl_Brushless\Lctrl_Brushless.h>
    #include <Lctrl\Lctrl_Moteur\Lctrl_Servo\Lctrl_Servo.h>
#endif

#include <Lctrl\Lctrl_Moteur\Lctrl_DriveS500\Lctrl_DriveS500.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurPWM\Lctrl_MoteurPWM.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_MoteurTOR\Lctrl_MoteurTOR.h>
#include <Lctrl\Lctrl_Moteur\Lctrl_Stepper\Lctrl_Stepper.h>

#endif