#include "Lsys.h"

// Constructeur
Lsys::Lsys() :
                iLsys_Fperiod10Hz   (100),
                iLsys_Fimpulse10Hz  (100),

                iLsys_Fperiod2Hz    (500),
                iLsys_Fimpulse2Hz   (500),

                iLsys_Fperiod1Hz    (1000),
                iLsys_Fimpulse1Hz   (1000),

                iLsys_Fperiod1min   (60000),
                iLsys_Fimpulse1min  (60000) {}

// GETTER (output)
        bool Lsys::clock10Hz() {return m_clock10Hz;}    // Bit clock10Hz
        bool Lsys::ft10Hz() {return m_ft10Hz;}          // Bit ft10Hz
        bool Lsys::clock2Hz() {return m_clock2Hz;}      // Bit clock2Hz
        bool Lsys::ft2Hz() {return m_ft2Hz;}            // Bit ft2Hz
        bool Lsys::clock1Hz() {return m_clock1Hz;}      // Bit clock1Hz
        bool Lsys::ft1Hz() {return m_ft1Hz;}            // Bit ft1Hz
        bool Lsys::clock1min() {return m_clock1min;}    // bit clock1min
        bool Lsys::ft1min() {return m_ft1min;}          // Bit ft1min

        bool Lsys::firstScan() {return First;}      // FirstScan
        bool Lsys::alwaysTrue() {return True;}      // AlwaysTrue
        bool Lsys::alwaysFalse() {return False;}    // AlwaysFalse

// SETTER (input)

// METHODES
    //Main
    void Lsys::main()
    {
        // Bits système
        First = not True;
        if (First) True = true;
        if (False) False = false;

        // Bits horloges
        m_clock10Hz = iLsys_Fperiod10Hz.clock();
        m_ft10Hz = iLsys_Fimpulse10Hz.impulse();

        m_clock2Hz = iLsys_Fperiod2Hz.clock();
        m_ft2Hz = iLsys_Fimpulse2Hz.impulse();

        m_clock1Hz = iLsys_Fperiod1Hz.clock();
        m_ft1Hz = iLsys_Fimpulse1Hz.impulse();

        m_clock1min = iLsys_Fperiod1min.clock();
        m_ft1min = iLsys_Fimpulse1min.impulse();
    }

  