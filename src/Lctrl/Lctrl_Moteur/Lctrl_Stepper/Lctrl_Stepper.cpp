#include <Lctrl\Lctrl_Moteur\Lctrl_Stepper\Lctrl_Stepper.h>

/// @brief Contrôle moteur pas à pas avec driver DRV8825.
/// Mettre cmdAv ou cmdAr à true et appliquer une consigne de (0 - 255).
/// OU utiliser la methode step(nbre de pas à effectuer)
/// Accélération / Décélération automatique paramétrable ainsi qu'un bornage consignes
/// @param pinStep n° broche pour éxécuter un pas
/// @param pinDir n° broche pour sélection de la direction
/// @param pinEnable n° broche pour excitation du moteur
/// @param stepsRevolution nombre de pas par tour (appliquer le ratio si vous travaillez en micro-steps)
/// @param vMax vitesse maximum en tours / min
/// @param rampe_ms temps en milliseconde changement vitesse Defaut 0
/// @param min consigne de vitesse de démarrage et d'arrêt moteur Defaut 0
/// @param max consigne de vitesse maximale moteur Defaut 255
LctrlStepper::LctrlStepper(byte pinStep, byte pinDir, byte pinEnable, unsigned short stepsRevolution, unsigned short vMax, unsigned short rampe_ms, byte min, byte max)
:   LctrlMoteurCsg2cmd(rampe_ms, min, max),
    keepEnable(true),
    modeVitesse(false),
    vitesse(0),
    m_pin(pinStep),
    m_pinDir(pinDir),
    m_pinEnable(pinEnable),
    m_stepsPerRevolution(stepsRevolution),
    m_vMax(vMax),
    m_step(0),
    m_lastMicros(0)
{
}

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void LctrlStepper::setup(void)
{ // Setup des IOs

    if (m_pinEnable != 255)
        pinMode(m_pinEnable, OUTPUT);

    if (m_pinDir != 255)
        pinMode(m_pinDir, OUTPUT);

    pinMode(m_pin, OUTPUT);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void LctrlStepper::main(void)
{
    // Gestion des entrées et mise à l'échelle
    in();

    // Faux si cmd ne correpond pas au sens de fonctionnement
    bool cmdEqSens = ((cmdAv  && !m_arr) || (cmdAr && m_arr));

    // Gestion rampe accélération / décélération
    // Sécu si cmdAv et cmdAr = true
    bool step = abs(m_step) > (Lcmd_Rampe::disable ? 0 : 1);
    Lcmd_Rampe::main(csg * (((cmdAv ^ cmdAr) && cmdEqSens) || step ), m_val);
    Lcmd_Rampe::rampe = (m_val && m_val < m_min && (cmdEqSens || LctrlMoteurSeuilReprise)) ? 0 : rampe;
    // NOTES :
    // Si on veut que lors d'un changement de sens
    // le moteur reprenne dans l'autre sens dès que l'on atteint le m_min
    // il suffit d'ajouter "#define LctrlMoteurSeuilReprise 0" dans le fichier config

    // Gestion sens de rotation
    if (!m_val)
        m_arr = (!m_arr && cmdAr) || (m_arr && !cmdAv) || m_step < 0;

    // Mise à jour des sorties
    out();
}

/// @brief Gestion des sorties
void LctrlStepper::out(void)
{
    // Calcul vitesse
    if (!modeVitesse)
    {
        vitesse = map(m_val, 0, 255, 0, m_vMax);   
    }

    // Conversion tr/min en periode µsec
    //  30M (30000000) / (vitesse * nbre pas/rev)
    if (vitesse > 0)
    {
        unsigned long microDelay = 30000000 / (vitesse * (uint32_t)m_stepsPerRevolution);
        // Serial.println(microDelay);
        if (micros() - m_lastMicros >= microDelay)
        {
            m_lastMicros = micros();
            bool pinState = digitalRead(m_pin);

            digitalWrite(m_pin, !pinState);

            // Si mode step => Mise à jour du nombre de step restant
            if (!modeVitesse && pinState)
            {
                if (m_step > 0) m_step--;
                if (m_step < 0) m_step++;
            }
        }
    }else{
        m_lastMicros = micros();
    }
    
    digitalWrite(m_pinDir, m_arr);
    digitalWrite(m_pinEnable, !(vitesse > 0 || keepEnable));
}


/// @brief Effectuer un nombre de pas
/// @param nStep nombre de pas à effectuer (+1 par defaut)
void LctrlStepper::step(int nStep)
{
    m_step = nStep;
    // m_val = 1;
    m_arr = m_step < 0;
}


/// @brief Retourne l'état de fonctionnement du moteur
/// @return Bool (TRUE : Marche | FALSE : Arrêt)
bool LctrlStepper::running(void) const
{
    return m_val;
}