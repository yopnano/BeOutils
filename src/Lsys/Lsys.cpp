#include <Lsys\Lsys.h>

// ========================================== Clock et Front système ========================================== //

/// @brief Horloge basculante sur une periode en ms.
/// @param periodMs Periode de temps de l'horloge
Lsys_Fdelay::Lsys_Fdelay(uint32_t periodMs) : m_period(periodMs / 2), m_millisOld(millis())
{
}

/// @brief Horloge periodique
/// @return Signal d'horloge basculant sur demi-periode.
bool Lsys_Fdelay::clock()
{
    if (millis() - m_millisOld >= m_period)
    {
        m_millisOld = millis();
        m_bools[0] = !m_bools[0]; // toggle clock
    }
    return m_bools[0];
}

/// @brief Pulsation periodique
/// @return Impulsion à chaque periode.
bool Lsys_Fdelay::impulse()
{
    this->clock();
    m_bools[1] = m_bools[0] & !m_bools[2]; // Front montant de clock
    m_bools[2] = m_bools[0];               // Memo clock old

    return m_bools[1];
}

// ========================================== Librairie système ========================================== //

Lsys::Lsys() : i_d10Hz(100),
               i_d2Hz(500),
               i_d1Hz(1000),
               m_microsOld(micros())
{
}

/// @brief Methode main.
/// Gestion des bit système.
/// Doit être applelée dans la fonction loop()
void Lsys::main()
{
    // Temps de cycle
    m_tpsCycle = micros() - m_microsOld;
    m_microsOld = micros();

    // Cadences
    ft10Hz = i_d10Hz.impulse();
    ft2Hz = i_d2Hz.impulse();
    ft1Hz = i_d1Hz.impulse();
    cl1Hz = i_d1Hz.clock();

    // Bits système
    firstscan = not True;
    if (firstscan)
        True = true;
    if (False)
        False = false;
}


/// @brief Temps de cycle.
/// @param unite type de retour Lsys::TimeUnit
double Lsys::tpsCycle(Lsys::TimeUnit unite)
{
    switch (unite)
    {
    case microsecond:
        return m_tpsCycle;
        break;

    case millisecond:
        return (double) m_tpsCycle / 1000;
        break;

    case second:
        return (double) m_tpsCycle / 1000000;
        break;

    case minute:
        return (double) m_tpsCycle / 60000000;
        break;

    case hour:
        return (double) m_tpsCycle / 3600000000;
        break;

    default:
        return m_tpsCycle;
    }
}