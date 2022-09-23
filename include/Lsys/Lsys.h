#ifndef Lsys_h
#define Lsys_h

// #include "../BeOutil.h"
#include <Arduino.h>
#include <UDT\BitBool\BitBool.h>
// Appel des Classes de la bibliothèque Lsys

// ========================================== Clock et Front système ========================================== //
class Lsys_Fdelay
{
    // Attributs publics
public:
    Lsys_Fdelay(uint32_t periodMs);

    bool clock();
    bool impulse();

private:
    BitBool<8> m_bools;

    unsigned long m_period;
    unsigned long m_millisOld;
};

// ========================================== Librairie système ========================================== //

class Lsys
{
public:
    enum TimeUnit : byte // Base de temps
    { 
        microsecond, 
        millisecond, 
        second, 
        minute,
        hour 
    };

    Lsys(void);

    void main();

    bool ft10Hz, ft2Hz, ft1Hz, cl1Hz; // Bit de cadence système

    bool firstscan, True, False; // Bit système

    double tpsCycle(Lsys::TimeUnit unite = microsecond);

private:
    Lsys_Fdelay i_d10Hz, i_d2Hz, i_d1Hz; // Clock et pulse

    unsigned long m_microsOld, m_tpsCycle; // Temps de cycle en microsecondes
};

static Lsys sys;
#endif