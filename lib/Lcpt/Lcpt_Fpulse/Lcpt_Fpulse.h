#ifndef Lcpt_Fpulse_h
#define Lcpt_Fpulse_h

#include <Arduino.h>

class Lcpt_Fpulse
{
private:
    friend void outUpdateCptISR();
    unsigned char m_pulse_pin;

    unsigned short m_pulseCount;
    unsigned short m_period;

    unsigned long m_lastMillis;

    double m_poidsPulse; //= 1 / (poidsPulse * 60)
    double m_cpt;
    double m_flow;
public:
    Lcpt_Fpulse(unsigned char pin, unsigned char poidsPulse = 23, unsigned short countPeriod = 1000);
    ~Lcpt_Fpulse();

    void setup(void);
    void main (void);

    double volume(void) const {return m_cpt;} //Volume en L
    double debit (void) const {return m_flow * (60000/m_period);} //Débit en L/min
};
#endif