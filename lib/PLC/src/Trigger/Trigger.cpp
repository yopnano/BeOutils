#include "Trigger.h"

// Constructeurs
Trigger::Trigger(){}
Trigger::Trigger(bool *trigBool) : pointeur(trigBool) {}

void Trigger::Attach(bool *trigBool) {pointeur = trigBool;}

void Trigger::Analyse()
{
    F_trigQ = F_trig(*pointeur);
    R_trigQ = R_trig(*pointeur);
    Change_trigQ = Change_trig(*pointeur);
}

void Trigger::Analyse(bool trigBool)
{
    Change_trigQ = Change_trig(trigBool);
    F_trigQ = F_trig(trigBool);
    R_trigQ = R_trig(trigBool);
}

bool Trigger::F_trig (bool value)
{
    // Détection du front descendant
    bool falling = value < memStateFalling;
    
    // Met à jour l'ancienne valeur
    memStateFalling = value;

    // Retourne le résultat
    return falling;
}

bool Trigger::R_trig (bool value)
{
    // Détection du front montant
    bool rising  = value > memStateRising;
    
    // Met à jour l'ancienne valeur
    memStateRising = value;

    // Retourne le résultat
    return rising;
}

bool Trigger::Change_trig (bool value)
{
    // Détection du front
    bool changed = value != memStateChange;
    
    // Met à jour l'ancienne valeur
    memStateChange = value;

    // Retourne le résultat
    return changed;
}