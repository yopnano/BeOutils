#ifndef LioPwm_h
#define LioPwm_h

#include <Arduino.h>

class LioPwm
{
    protected:
        boolean m_inverted;
        uint8_t m_pinNumber;
        uint8_t m_oldValue;

    public:
        /*! @brief  Etat de la sortie
        */
        uint8_t value;

        
        /*! @brief  Sortie PWM.

            @param pin  n° broche sortie PWM
            @param Inverted pour inverser l'état de la sortie
        */
        LioPwm(uint8_t pin, boolean inverted = false);

        /*! @brief  Main PWM.

            Gestion de la sortie PWM
        */
        void main(void);
        void setup(void);

        /*! @brief  Ecriture de la sortie

            @param newVal nouvelle valeur à appliquer
        */
        void write(boolean newVal) {value = newVal;}

        
        /*! @brief  Activer l'actionneur
        */
        void turnOn() {value = 255;}
        
        /*! @brief  Desactiver l'actionneur
        */
        void turnOff(){value = 0;}

        /*! @brief  Inverser l'état de l'actionneur
            si actionneur en marche -> arrêt
            si actionneur à l'arrêt -> dernière consigne utilisée
        */
        void toggle();
};

#endif