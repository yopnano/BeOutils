#include <Lctrl\Lctrl_Moteur\Lctrl_Servo\Lctrl_Servo.h>

#ifdef UsingLib_Servo

Lctrl_Servo::Lctrl_Servo(byte pin, unsigned short rampe_ms, byte mini, byte maxi)
    : LctrlMoteurCsg1cmd(rampe_ms, max(0, mini), min(180, maxi)),
      //   autoRelease(false),
      m_pin(pin)
{
}

void Lctrl_Servo::operator=(const Lctrl_Servo &servo)
{
    this->cmd = servo.cmd;
    this->csg = servo.csg;
    this->in();
}

/// @brief Synchroniser deux servo entre eux
/// Doit être appelé après avoir définit les csg aux 2 moteurs.
/// Cela agit sur la rampe du moteur à synchroniser pour que les mouvements soient coordonnés
/// @param servo objet Lctrl_Servo sur lequel se synchroniser
void Lctrl_Servo::synchro(Lctrl_Servo &servo)
{
    this->in();
    servo.in();

    byte courseA = abs(servo.m_val - servo.csg);
    byte courseB = abs(this->m_val - this->csg);

    double ratio = (double)courseA / courseB;
    
    this->rampe = round(ratio * servo.rampe);
}

void Lctrl_Servo::setup(void)
{
}

/// @brief Gestion des entrées et mise à l'échelle
void Lctrl_Servo::in(void)
{
    // Contraite consigne sur min et max
    csg = constrain(csg, m_min, m_max);
}

/// @brief Gestion de la sortie
void Lctrl_Servo::out(void)
{
    if (cmd && !posAtteinte() && !this->attached())
        this->attach(m_pin);

    // if (!cmd && posAtteinte() && this->attached())
    //     this->detach();

    this->write(m_val);
}

bool Lctrl_Servo::posAtteinte(void)
{

    return (this->read() == csg);
}

#endif