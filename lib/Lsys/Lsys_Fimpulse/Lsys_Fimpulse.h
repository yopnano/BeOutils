#ifndef DEF_Lsys_Fimpulse
#define DEF_Lsys_Fimpulse

#include "Lsys_Fperiod\Lsys_Fperiod.h"
#include "Trigger\Trigger.h"

class Lsys_Fimpulse
{
    // Attributs publics
    public:
        /**************************************************************************/
        /*!
            @brief  Générateur d'impulsion sur une periode en ms.

            @see Lsys_Fperiod.

            @param periodMs  Periode de temps de l'impulsion           
        */
        /**************************************************************************/
        Lsys_Fimpulse(uint32_t periodMs);
        
        /**************************************************************************/
        /*!
            @brief  Sortie de l'impulsion.
            @return Impulsion booleene           
        */
        /**************************************************************************/
        bool impulse();
        
        /**************************************************************************/
        /*!
            @brief  Reset de la periode.          
        */
        /**************************************************************************/
        void restart();
        
        /**************************************************************************/
        /*!
            @brief  Changement de la periode.
            @param periodMs nouvelle periode en millisecondes           
        */
        /**************************************************************************/
        void changePeriod(uint32_t periodMs);
        
    private:
        Lsys_Fperiod iLsys_Fperiod;
        Trigger iTrigger;
};
#endif