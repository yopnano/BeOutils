#include "Lcpt_Fpulse.h"

static Lcpt_Fpulse* sFpulse;
void outUpdateCptISR(void)
{
    sFpulse->m_pulseCount++;
}
    
Lcpt_Fpulse::Lcpt_Fpulse(unsigned char pin, unsigned char poidsPulse, unsigned short countPeriod) :
m_pulse_pin(pin),
m_pulseCount(0),
m_period(countPeriod),
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
    //Base de temps d'echantillonage
    if (millis() - m_lastMillis >= m_period)
    {
        m_lastMillis = millis();
        
        //Si un volume est passé
        if (m_pulseCount > 0)
        {
            m_flow = m_pulseCount * m_poidsPulse;   //Calul du débit sur la période
            m_cpt = m_cpt + m_flow ;                //Ajout aux compteur
            m_pulseCount = 0;                       //Remise à zéro du compteur d'impulsion
        }else{
            m_flow = 0;
        }
    }  
}