#include "Lcpt_Fpulse.h"

static Lcpt_Fpulse* sFpulse;
void outUpdateCptISR(void)
{
    sFpulse->m_pulseCount++;
}
    
Lcpt_Fpulse::Lcpt_Fpulse(unsigned char pin, unsigned char poidsPulse, unsigned short pulseCalc) :
m_pulse_pin(pin),
m_pulseCount(0),
m_pulseCalc(pulseCalc),
m_lastMillis(0),
m_poidsPulse(1.0 / (poidsPulse * 60.0)),
m_cpt(0),
m_flow(0)
{}

Lcpt_Fpulse::~Lcpt_Fpulse()
{
    detachInterrupt(digitalPinToInterrupt(m_pulse_pin));
}

void Lcpt_Fpulse::setup(void)
{
    sFpulse = this;
    pinMode(m_pulse_pin, INPUT_PULLUP);
    if (digitalPinToInterrupt(m_pulse_pin) == NOT_AN_INTERRUPT) {Serial.print (F("Lcpt_Fpulse Warning : Pulse Pin > ")); Serial.print (m_pulse_pin); Serial.println (F(" isn't Interrupt"));}
    else attachInterrupt(digitalPinToInterrupt(m_pulse_pin), outUpdateCptISR, CHANGE);
}

void Lcpt_Fpulse::main(void)
{
    unsigned short deltaT = millis() - m_lastMillis;    //Calcul du delta T depuis le dernier calcul
    
    //Calcul tous les x impulsions
    if (m_pulseCount >= m_pulseCalc)
    {
        double volInst = m_pulseCount * m_poidsPulse;   //Calul du volume sur la période
        m_flow = volInst * (60000 / deltaT);            //Calcul du débit en L/min
        m_cpt = m_cpt + volInst;                        //Ajout au compteur
        m_pulseCount -= m_pulseCalc;                    //Soustraction de la limite de trigger
        m_lastMillis = millis();
    }
    
    //Si le dt entre 2 calculs est > à 1 sec, on considère que le débit est nul
    if (deltaT >= 1000) m_flow = 0.0;
    
    //Si le débit est nul on réinitialise le delta T
    if (m_flow == 0) m_lastMillis = millis();
}