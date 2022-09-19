#include <Lio\LioPwm\LioPwm.h>

LioPwm::LioPwm(uint8_t pin, boolean inverted):
    //Constructeur
    m_inverted(inverted),
    m_pinNumber(pin),
    m_oldValue(0),
    value(0)
    {}

void LioPwm::setup(void)
{
    //Verifie si la pin est PWM
    if (digitalPinToTimer(m_pinNumber) == NOT_ON_TIMER) {Serial.print (F("LioPwm Warning : pin > ")); Serial.print (m_pinNumber); Serial.println (F(" isn't PWM"));}
    else pinMode(m_pinNumber, OUTPUT);
}

void LioPwm::main(void)
{
    //Borne la consigne entre 0 et 255
    value = constrain(value, 0, 255);

    //Ecriture de la sortie
    analogWrite(m_pinNumber, abs((m_inverted ? 255 : 0) - value));
}

void LioPwm::toggle(void)
{
    if (!m_oldValue &! value) value = 255;

    //Sauvegarde et apllication l'ancienne consigne
    uint8_t retain = value;
    value = m_oldValue;
    m_oldValue = retain;
}