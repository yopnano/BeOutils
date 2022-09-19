#ifndef Trigger_h
#define Trigger_h

#include <Arduino.h>

//macro for detection af rising edge
//state must be a byte
#define RE(signal, state) (state=(state<<1)|((signal&1)&3))==1

//macro for detection af falling edge
//state must be a byte
#define FE(signal, state) (state=(state<<1)|(signal&1)&3)==2



class Trigger
{
    // Attributs publics
    public:

        // Liaison de variable sans pointeur
        Trigger();
        // Liaison de variable par pointeur
        Trigger(bool *trigBool);

        // Lier un &bool au trigger
        void Attach(bool *trigBool);
        
        // Analyse de la variable pointée
        void Analyse();

        // analyser un bool
        void Analyse(bool trigBool);

        //Front descencant
        bool F_trig() const {return F_trigQ;}
        //Front montant
        bool R_trig() const {return R_trigQ;}
        //Front changement d'état
        bool T_trig() const {return Change_trigQ;}


    // Attributs privés
    private:
        bool *pointeur;
        bool valeur;
        bool F_trigQ;
        bool R_trigQ;
        bool Change_trigQ;      
        bool memStateChange;
        bool memStateFalling;
        bool memStateRising;

        // Détection front descendant
        bool F_trig(bool value);

        // Détection front montant
        bool R_trig(bool value);

        // Détection changement d'état
        bool Change_trig(bool value);
};

#endif