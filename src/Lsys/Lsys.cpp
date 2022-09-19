#include <Lsys\Lsys.h>

// ========================================== Clock et Front système ========================================== //

// Constructeur
Lsys_Fdelay::Lsys_Fdelay(uint32_t periodMs) : m_period(periodMs / 2)
                                            , m_millisOld(millis())
{
}

bool Lsys_Fdelay::clock()
{
    if (millis() - m_millisOld >= m_period)
    {
        m_millisOld = millis();
        m_bools[0] = !m_bools[0]; // toggle clock
    }
    return m_bools[0];
}

bool Lsys_Fdelay::impulse()
{
    this->clock();
    m_bools[1] = m_bools[0] &! m_bools[2]; // Front montant de clock
    m_bools[2] = m_bools[0]; // Memo clock old

    return m_bools[1];
}




// ========================================== Librairie système ========================================== //

    Lsys::Lsys() :
        i_d10Hz(100),
        i_d2Hz(500),
        i_d1Hz(1000)
    {}

    // Main
    void Lsys::main()
    {

        // Cadences
        ft10Hz = i_d10Hz.impulse();
        ft2Hz = i_d2Hz.impulse();
        ft1Hz = i_d1Hz.impulse();
        cl1Hz = i_d1Hz.clock();


        // Bits système
        firstscan = not True;
        if (firstscan) True = true;
        if (False) False = false;
    }

  