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
        /*!
            @brief  Horloge basculante sur une periode en ms.

            @see Lsys_Fimpulse.

            @param periodMs  Periode de temps de l'impulsion en millisecondes         
        */
        Lsys_Fdelay(uint32_t periodMs);

        /*!
            @brief  Signal d'horloge basculant sur demi-periode.

            @param periodMs  Periode de temps de basculement en millisecondes         
        */
        bool clock();
        
        /*!
            @brief  Sortie de l'impulsion.
            ne peut être appelée qu'une seule fois vu qu'elle génère un front
            @return Impulsion booleene           
        */
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
        Lsys(void);

        /*!
            @brief  Methode main.
            Gestion des bit système. 
            Doit être applelée dans la fonction loop()          
        */
        void main();

        bool ft10Hz
            ,ft2Hz
            ,ft1Hz
            ,cl1Hz;
                
        bool firstscan
            ,True
            ,False;
    private:
        
        // instances de clock et pulse
        Lsys_Fdelay i_d10Hz;
        Lsys_Fdelay i_d2Hz;
        Lsys_Fdelay i_d1Hz;
};

static Lsys sys;
#endif