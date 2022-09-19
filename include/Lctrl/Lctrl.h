#ifndef Lctrl_h
#define Lctrl_h

#define pinIsDisable(pin) (pin == 255)
#define pinIsEnable(pin) (pin != 255)

class Lctrl
{
public:
    /*!
        @brief  Fonction d'initialisation.
        Execution au démmarrage
    */
    virtual void setup(void) =0;

    /*!
        @brief  Fonction principale.
        Execution à chaque tours de loop
    */
    virtual void main(void) =0;
};


    // Appel des Classes de la bibliothèque Lctrl
    #include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

#endif