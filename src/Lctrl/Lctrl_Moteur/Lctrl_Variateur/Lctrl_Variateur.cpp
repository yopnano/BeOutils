#include <Lctrl\Lctrl_Moteur\Lctrl_Variateur\Lctrl_Variateur.h>

/// @brief Contrôle moteur par variateur de fréquence en Tout Ou Rien
/// @param pinRdy n° broche variateur prêt
/// @param pinRun n° broche retour de marche
/// @param pinStf n° broche marche avant
/// @param pinStr n° broche marche arrière
/// @param pinSpd n° broche commande de vitesse fixe TOR (possiblilité de faire 2 vitesses en cablant RH sur le 24v et en commuttant RM ou RL)
Lctrl_VariateurTOR::Lctrl_VariateurTOR(byte pinRdy, byte pinRun, byte pinStf, byte pinStr, byte pinSpd, bool deuxVitesses) :
    f(false),
    rm(false),
    cmdAv(false),
    cmdAr(false),
    m_vitesse1(false),
    m_vitesse2(deuxVitesses),
    m_deuxVitesses(deuxVitesses),
    m_pinRdy(pinRdy),
    m_pinRun(pinRun),
    m_pinStf(pinStf),
    m_pinStr(pinStr),
    m_pinSpd(pinSpd)
    {}

/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_VariateurTOR::setup(void)
{
    if (pinIsEnable(m_pinRdy))
        pinMode(m_pinRdy, INPUT_PULLUP);

    if (pinIsEnable(m_pinRun))
        pinMode(m_pinRun, INPUT_PULLUP);

    if (pinIsEnable(m_pinStf))
        pinMode(m_pinStf, OUTPUT);

    if (pinIsEnable(m_pinStr))
        pinMode(m_pinStr, OUTPUT);

    if (pinIsEnable(m_pinSpd))
        pinMode(m_pinSpd, OUTPUT);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void Lctrl_VariateurTOR::main(void)
{
    // Gestion Pin entrées
    f = pinIsEnable(m_pinRdy) ? digitalRead(m_pinRdy) : false;
    rm = pinIsEnable(m_pinRun) ? digitalRead(m_pinRun) == LOW : digitalRead(m_pinStf) ^ digitalRead(m_pinStr) ;
    
    // Pilotage de la sortie
    digitalWrite(m_pinStf, (cmdAv && !cmdAr) && !f);
    digitalWrite(m_pinStr, (cmdAr && !cmdAv) && !f);
    digitalWrite(m_pinSpd, (cmdAr ^ cmdAv) && (!m_deuxVitesses ^ m_vitesse1) && !f);
    
}

void Lctrl_VariateurTOR::vitesse1(void)
{
    m_vitesse1 = m_deuxVitesses;
    m_vitesse2 = !m_vitesse1;
}

void Lctrl_VariateurTOR::vitesse2(void)
{
    m_vitesse2 = true;
    m_vitesse1 = !m_vitesse2;
}


/// @brief Contrôle moteur par variateur de fréquence en PWM
/// @param pinRdy n° broche variateur prêt
/// @param pinRun n° broche retour de marche
/// @param pinStf n° broche marche avant
/// @param pinStr n° broche marche arrière
/// @param pinSpd n° broche commande de vitesse PWM
Lctrl_VariateurPWM::Lctrl_VariateurPWM(byte pinRdy, byte pinRun, byte pinStf, byte pinStr, byte pinSpd) :
    LctrlMoteurCsg2cmd(0, 0, 255),
    f(false),
    rm(false),
    m_pinRdy(pinRdy),
    m_pinRun(pinRun),
    m_pinStf(pinStf),
    m_pinStr(pinStr),
    m_pinSpd(pinSpd)
    {}


/// @brief Paramétrage initial du moteur
/// Appeler dans la fonction modSetup()
void Lctrl_VariateurPWM::setup(void)
{
    if (pinIsEnable(m_pinRdy))
        pinMode(m_pinRdy, INPUT_PULLUP);

    if (pinIsEnable(m_pinRun))
        pinMode(m_pinRun, INPUT_PULLUP);

    if (pinIsEnable(m_pinStf))
        pinMode(m_pinStf, OUTPUT);

    if (pinIsEnable(m_pinStr))
        pinMode(m_pinStr, OUTPUT);

    if (pinIsEnable(m_pinSpd))
        pinMode(m_pinSpd, OUTPUT);
}

/// @brief Gestion de la sortie
void Lctrl_VariateurPWM::out(void)
{
    // Gestion Pin entrées
    f = pinIsEnable(m_pinRdy) ? digitalRead(m_pinRdy) : false;
    rm = pinIsEnable(m_pinRun) ? digitalRead(m_pinRun) == LOW : digitalRead(m_pinStf) ^ digitalRead(m_pinStr) ;
    
    // Désactivation rampe (c'est au variateur de gérer l'accélération et la décélération)
    Lcmd_Rampe::disable = true;

    // Pilotage des sorties
    digitalWrite(m_pinStf, cmdAv && !m_arr);
    digitalWrite(m_pinStr, cmdAr && m_arr);
    
    analogWrite(m_pinSpd, m_val);
}