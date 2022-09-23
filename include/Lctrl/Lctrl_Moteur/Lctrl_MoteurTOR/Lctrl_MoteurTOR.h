#ifndef Lctrl_MoteurTOR_h
#define Lctrl_MoteurTOR_h

#include <Arduino.h>
#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

class Lctrl_MoteurTOR  : public LctrlMoteurOld
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
    Lctrl_MoteurTOR(unsigned char pinAv, unsigned char pinAr = -1, unsigned char mode = Mode_auto, bool inverted = false);
    
    /**************************************************************************/
    /*!
        @brief  etat du moteur.        
        @param FALSE moteur à l'arrêt
        @param TRUE moteur en fonctionnement
          
    */
    /**************************************************************************/
    bool isRunning(void) const{return m_KmAv || m_KmAr;}
    
    void main(void) override;
    void setup(void) override;
    
private:
    bool m2sens() const override {return m_pinAr != 255;}
    bool m_inverted;
    
    unsigned char m_pinAr;
};

#endif