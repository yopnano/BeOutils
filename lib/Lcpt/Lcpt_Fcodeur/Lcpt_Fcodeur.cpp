#include "Lcpt_Fcodeur.h"

static Lcpt_Fcodeur* sFcodeur;
void outUpdateCptISR(void)
{
    sFcodeur->m_pulseCount += digitalRead(sFcodeur->m_dir_pin) ? -1 : 1;
}
    
Lcpt_Fcodeur::Lcpt_Fcodeur(unsigned char pulsepin, unsigned char dirpin, double poidsPulse, unsigned short countPeriod) :
m_pulse_pin(pulsepin),
m_dir_pin(dirpin),
m_pulseCount(0),
m_period(countPeriod),
m_lastMillis(0),
m_poidsPulse(poidsPulse),
m_pos(0),
m_speed(0)
{}

Lcpt_Fcodeur::~Lcpt_Fcodeur()
{
    detachInterrupt(digitalPinToInterrupt(m_pulse_pin));
}

void Lcpt_Fcodeur::setup(void)
{
    sFcodeur = this;
    pinMode(m_pulse_pin, INPUT_PULLUP);
    pinMode(m_dir_pin, INPUT_PULLUP);
    if (digitalPinToInterrupt(m_pulse_pin) == NOT_AN_INTERRUPT) {Serial.print (F("Lcpt_Fpulse Warning : Pulse Pin > ")); Serial.print (m_pulse_pin); Serial.println (F(" isn't Interrupt"));}
    else attachInterrupt(digitalPinToInterrupt(m_pulse_pin), outUpdateCptISR, RISING);
}

void Lcpt_Fcodeur::main(void)
{
    //Base de temps d'echantillonage
    if (millis() - m_lastMillis >= m_period)
    {
        m_lastMillis = millis();
        
        //Si un volume est passé
        if (m_pulseCount != 0)
        {
            m_speed = m_pulseCount * m_poidsPulse;  //Calul du débit sur la période
            m_pos = m_pos + m_speed ;               //Ajout aux compteur
            m_pulseCount = 0;                       //Remise à zéro du compteur d'impulsion
        }else{
            m_speed = 0;
        }
    }  
}

short Lcpt_Fcodeur::vitesseAbs(void) const
{
    short vtemp = vitesse();
    return abs(vtemp);
}