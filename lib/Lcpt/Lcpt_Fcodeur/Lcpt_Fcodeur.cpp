#include "Lcpt_Fcodeur.h"

static Lcpt_Fcodeur* sFcodeur;
void outUpdateCptISR(void)
{
    sFcodeur->m_pulseCount += digitalRead(sFcodeur->m_dir_pin) ? -1 : 1;
}
    
Lcpt_Fcodeur::Lcpt_Fcodeur(unsigned char pulsepin, unsigned char dirpin, double poidsPulse, unsigned short pulseCalc) :
m_pulse_pin(pulsepin),
m_dir_pin(dirpin),
m_pulseCount(0),
m_pulseCalc(pulseCalc),
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
    unsigned short deltaT = millis() - m_lastMillis;    //Calcul du delta T depuis le dernier calcul
    
    //Calcul tous les x impulsions
    if ((unsigned short) abs(m_pulseCount) >= m_pulseCalc)
    {
        double mvInst = m_pulseCount * m_poidsPulse;    //Calul du déplacement sur la période
        m_speed = mvInst * (60000 / deltaT);            //Calcul de la vitesse en tr/min
        m_pos += mvInst;                                //Mise à jour de la position        
        m_pulseCount += (m_pulseCount < 0 ? m_pulseCalc : -m_pulseCalc);    //Soustraction de la limite de trigger
        m_lastMillis = millis();
    }

    //Si le dt entre 2 calculs est > à 1 sec, on considère que la vitesse est nulle
    if (deltaT >= 1000) m_speed = 0.0;
    
    //Si la vitesse est nulle on réinitialise le delta T
    if (m_speed == 0) m_lastMillis = millis();
}