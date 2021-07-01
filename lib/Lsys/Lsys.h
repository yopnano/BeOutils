#ifndef DEF_Lsys
#define DEF_Lsys

// C#
//#include <Arduino.h>
//#include <Global.h>
// Lsys

    #include "Lsys_Fimpulse\Lsys_Fimpulse.cpp"
    #include "Lsys_Fperiod\Lsys_Fperiod.cpp"

// Librairie système
class Lsys
{
    
    public:
    // Attributs publiques
    // Méthodes publiques
        // constructeurs
        /**************************************************************************/
        /*!
            @brief  Librairie systeme.

            Comporte des clocks de base 1 sec, 1 min ...
            un bit FirstScan, vrais, faux ...
        */
        /**************************************************************************/
        Lsys();


        //Bit d'horloge
            /**************************************************************************/
            /*!
                @brief  Horloge sur periode de 10Hz.
            */
            /**************************************************************************/
            bool clock10Hz();

            /**************************************************************************/
            /*!
                @brief  Impulsion sur periode de 10Hz.
            */
            /**************************************************************************/
            bool ft10Hz();
            
            /**************************************************************************/
            /*!
                @brief  Horloge sur periode de 2Hz.
            */
            /**************************************************************************/
            bool clock2Hz();
            
            /**************************************************************************/
            /*!
                @brief  Impulsion sur periode de 2Hz.
            */
            /**************************************************************************/
            bool ft2Hz();
            
            /**************************************************************************/
            /*!
                @brief  Horloge sur periode d'une seconde'.
            */
            /**************************************************************************/
            bool clock1Hz();
            
            /**************************************************************************/
            /*!
                @brief  Imulsion sur periode d'une seconde'.
            */
            /**************************************************************************/
            bool ft1Hz();
            
            /**************************************************************************/
            /*!
                @brief  Horloge sur periode d'une minute.
            */
            /**************************************************************************/
            bool clock1min();
            
            /**************************************************************************/
            /*!
                @brief  Impulsion sur periode d'une minute.
            */
            /**************************************************************************/
            bool ft1min();
            
        // Bits système
            
            // Bit toujours vrai
            bool alwaysTrue(); 

            // Bit toujours faux
            bool alwaysFalse(); 

            // Bit premier cycle
            bool firstScan();

        // Méthode Main, à appeler dans le loop
        void main();


    private:
    // Attributs privés       
        bool First;
        bool False;
        bool True;

        bool m_clock10Hz;
        bool m_ft10Hz;
                
        bool m_clock2Hz;
        bool m_ft2Hz;
        
        bool m_clock1Hz;
        bool m_ft1Hz;
        
        bool m_clock1min;
        bool m_ft1min;
      
    // instances de clock et pulse
        Lsys_Fperiod  iLsys_Fperiod10Hz;
        Lsys_Fimpulse iLsys_Fimpulse10Hz;

        Lsys_Fperiod  iLsys_Fperiod2Hz;
        Lsys_Fimpulse iLsys_Fimpulse2Hz;

        Lsys_Fperiod  iLsys_Fperiod1Hz;
        Lsys_Fimpulse iLsys_Fimpulse1Hz;

        Lsys_Fperiod  iLsys_Fperiod1min;
        Lsys_Fimpulse iLsys_Fimpulse1min;
};
static Lsys sys;
#endif