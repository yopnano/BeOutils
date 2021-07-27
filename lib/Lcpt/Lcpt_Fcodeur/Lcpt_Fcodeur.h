#ifndef Lcpt_Fcodeur_h
#define Lcpt_Fcodeur_h

#include <Arduino.h>

class Lcpt_Fcodeur
{
private:
    friend void outUpdateCptISR();
    unsigned char m_pulse_pin;
    unsigned char m_dir_pin;
    
    short m_pulseCount;
    unsigned short m_period;

    unsigned long m_lastMillis;

    double m_poidsPulse; //= 1 / (poidsPulse * 60)
    double m_pos;
    double m_speed;
public:
    Lcpt_Fcodeur(unsigned char pulsepin, unsigned char dirpin, double poidsPulse = 0.11, unsigned short countPeriod = 1000);
    ~Lcpt_Fcodeur();

    void setup(void);
    void main (void);

    double position (void) const {return m_pos;} //Position en nombre de tour
    short vitesse  (void) const {return (short) m_speed * (60000/m_period);} //vitesse en tr/min
    short vitesseAbs (void) const;
};
#endif