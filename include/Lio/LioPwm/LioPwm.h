#ifndef LioPwm_h
#define LioPwm_h

#include <Arduino.h>
#include <Lcmd\Lcmd_Rampe\Lcmd_Rampe.h>

class LioPwm
{
protected:
    bool m_inverted;
    uint8_t m_pin;

public:
    /*! @brief  Sortie PWM.

        @param pin  n° broche sortie PWM
        @param Inverted pour inverser l'état de la sortie
    */
    LioPwm(uint8_t pin, bool inverted = false);

    /*! @brief  Main PWM.
        Gestion de la sortie PWM
    */
    void main(void);
    void setup(void);

    /*! @brief  Valeur de la sortie
     */
    uint8_t val;
};

class LioPwmTor : public LioPwm
{
private:
    uint8_t m_oldValue;

public:
    /*! @brief  Activer l'actionneur
        La consigne retourne à la valeur précedente
     */
    void turnOn();

    /*! @brief  Desactiver l'actionneur
     */
    void turnOff();

    /*! @brief  Inverser l'état de l'actionneur
        si actionneur en marche -> arrêt
        si actionneur à l'arrêt -> dernière consigne utilisée
    */
    void toggle();
};

class LioPwmRampe : public LioPwm, public Lcmd_Rampe
{
public:
    LioPwmRampe(uint8_t pin, unsigned short rampe_ms = 10, bool inverted = false);

    void main(void);

    /*! @brief  Consigne de la sortie
     */
    uint8_t csg;
};
#endif