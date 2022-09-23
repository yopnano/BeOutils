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

    // Gestion sens de rotation &! à tester
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

LctrlMoteurOld::LctrlMoteurOld(unsigned char mode, unsigned char outMin, unsigned char outMax, unsigned char csgMin, unsigned char csgMax, unsigned char rampeAcc)
    : Lctrl(),
      m_pidMode(false),
      m_cmdAv(false),
      m_cmdAr(false),
      m_memCmd(false),
      m_KmAv(false),
      m_KmAr(false),
      m_modeFct(mode),
      m_modeFctOld(mode),
      m_csgAuto(outMin),
      m_csgManu(outMin),
      m_csgGlobale(0),
      m_csgActuelle(0),
      m_csgMin((csgMin > outMin) ? csgMin : outMin),
      m_csgMax((csgMax < outMax) ? csgMax : outMax),
      m_rampe(rampeAcc),
      m_outMin(outMin),
      m_outMax(outMax)
{
}

void LctrlMoteurOld::toggle(void)
{ // Fonction changement de sens AV -> STOP -> AR -> STOP -> AV ...

    // Moteur à l'arrêt
    if (!m_cmdAv && !m_cmdAr)
    {
        m_cmdAv = !m_memCmd;
        m_cmdAr = m_memCmd;
    }
    // Moteur en marche
    else if (m_cmdAv ^ m_cmdAr)
    {
        m_cmdAv = false;
        m_cmdAr = false;
        m_memCmd = !m_memCmd && m2sens(); /*&& m_pinDir != 255;*/
    }
}

void LctrlMoteurOld::modeFct(unsigned char mode)
{
    if (m_modeFct != mode && m_modeFct != Defaut)
    {
        m_modeFctOld = m_modeFct;
        m_modeFct = mode;
    }
}

bool LctrlMoteurOld::m_rearm(bool cdtRearm)
{
    if (m_modeFct == Defaut && cdtRearm)
        m_modeFct = m_modeFctOld;

    return m_modeFct != Defaut;
}

void LctrlMoteurOld::csgAuto(unsigned char csg)
{
    // Borne la consigne entre 0 et 255
    m_csgAuto = constrain(csg, m_csgMin, m_csgMax);
}

void LctrlMoteurOld::csgManu(unsigned char csg)
{
    // Borne la consigne entre 0 et 255
    m_csgManu = constrain(csg, m_outMin, m_outMax);
}

void LctrlMoteurOld::KM(void)
{
    m_KmAv = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto && m_cmdAv) || m_KmAv)) & !m_cmdAr || m_modeFct == Marche_AV_forcee;

    m_KmAr = (m_csgActuelle > m_csgMin && ((m_modeFct == Mode_auto && m_cmdAr) || m_KmAr)) & !m_cmdAv || m_modeFct == Marche_AR_forcee;
}

LMoteurSpeed::LMoteurSpeed() : m_disabled(false),
                               m_csgAtteinte(false),
                               m_lastMillis(0)
{
}

void LMoteurSpeed::main(unsigned char &csgGlobale, unsigned char &csgActuelle, unsigned short const &rampe)
{
    // Rampes désactivées
    if (m_disabled)
        csgActuelle = csgGlobale;

    m_csgAtteinte = csgActuelle == csgGlobale;

    // Gestion d'incrémentation
    if (m_csgAtteinte)
    {
        razTimer();
        return;
    }
    else
    {
        if (millis() - m_lastMillis >= rampe)
        {
            razTimer();
            csgActuelle += (csgGlobale > csgActuelle) ? 1 : -1;
        }
    }
}