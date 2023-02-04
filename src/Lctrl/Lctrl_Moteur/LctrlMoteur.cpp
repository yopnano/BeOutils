#include <Lctrl\Lctrl_Moteur\LctrlMoteur.h>

/// @brief Gestion de moteur 1 sens de rotation
/// @param rampe_ms Temps Accélération / décélération en ms : 10 = 2.5 sec de 0 à 255
/// @param min consigne minimum la sortie PWM ne descend pas sous cette valeur
/// @param max consigne maximum la sortie PWM ne dépasse pas cette valeur
LctrlMoteurCsg1cmd::LctrlMoteurCsg1cmd(unsigned short rampe_ms, byte min, byte max)
    : // Lctrl(),
      Lcmd_Rampe(rampe_ms),
      cmd(false),
      rampe(rampe_ms),
      csg(0),
      m_val(0),
      m_min(min),
      m_max(max)
{
}

/// @brief Gestion des entrées et mise à l'échelle
void LctrlMoteurCsg1cmd::in(void)
{
    // Contraite consigne sur min et max
    if (csg)
        csg = constrain(csg, m_min, m_max);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void LctrlMoteurCsg1cmd::main(void)
{
    // Gestion des entrées et mise à l'échelle
    in();

    // Gestion rampe accélération / décélération
    Lcmd_Rampe::main(csg * cmd, m_val);
    Lcmd_Rampe::rampe = (m_val && m_val < m_min) ? 0 : rampe;

    // Mise à jour de la sortie
    out();
}

/// @brief Mode PID.
/// Les rampes d'accélération et décélération sont désactivées
/// @param enable False / True Activation du mode PID
void LctrlMoteurCsg1cmd::pidMode(bool enable)
{
    Lcmd_Rampe::disable = enable;
}

/// @brief Gestion de moteur 2 sens de rotation
/// @param rampe_ms Temps Accélération / décélération en ms : 10 = 2.5 sec de 0 à 255
/// @param min consigne minimum la sortie PWM ne descend pas sous cette valeur
/// @param max consigne maximum la sortie PWM ne dépasse pas cette valeur
LctrlMoteurCsg2cmd::LctrlMoteurCsg2cmd(unsigned short rampe_ms, byte min, byte max)
    : // Lctrl(),
      Lcmd_Rampe(rampe_ms),
      cmdAv(false),
      cmdAr(false),
      rampe(rampe_ms),
      csg(0),
      m_arr(true),
      m_val(0),
      m_min(min),
      m_max(max)
{
}

/// @brief Gestion des entrées et mise à l'échelle
void LctrlMoteurCsg2cmd::in(void)
{
    // Contraite consigne sur min et max
    if (csg)
        csg = constrain(csg, m_min, m_max);
}

/// @brief Gestion de fonctionnement du moteur
/// Appeler dans la fonction modMain()
void LctrlMoteurCsg2cmd::main(void)
{
    // Gestion des entrées et mise à l'échelle
    in();

    // Faux si cmd ne correpond pas au sens de fonctionnement
    bool cmdEqSens = ((cmdAv && !m_arr) || (cmdAr && m_arr));

    // Gestion rampe accélération / décélération
    // Sécu si cmdAv et cmdAr = true
    Lcmd_Rampe::main(csg * (cmdAv ^ cmdAr) * cmdEqSens, m_val);
    Lcmd_Rampe::rampe = (m_val && m_val < m_min && (cmdEqSens || LctrlMoteurSeuilReprise)) ? 0 : rampe;
    // NOTES :
    // Si on veut que lors d'un changement de sens
    // le moteur reprenne dans l'autre sens dès que l'on atteint le m_min
    // il suffit d'ajouter "#define LctrlMoteurSeuilReprise 0" dans le fichier config

    // Gestion sens de rotation
    if (!m_val)
        m_arr = (!m_arr && cmdAr) || (m_arr && !cmdAv);

    // Mise à jour des sorties
    out();
}

/// @brief Mode PID.
/// Les rampes d'accélération et décélération sont désactivées
/// @param enable False / True Activation du mode PID
void LctrlMoteurCsg2cmd::pidMode(bool enable)
{
    Lcmd_Rampe::disable = enable;
}

/// @brief // Permutation Avant / Arrêt / Arrière / Arrêt ...
/// @param sansArret permet de ne pas faire d'arrêt entre chaque sens
void LctrlMoteurCsg2cmd::toggle(bool sansArret)
{

    if (!sansArret)
    {
        cmdAv = (!cmdAv && !m_val) && m_arr;
        cmdAr = (!cmdAr && !m_val) && !cmdAv;
    }
    else
    {
        cmdAv = !cmdAv;
        cmdAr = !cmdAv;
    }
}