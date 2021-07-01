#ifndef Lcalc_MAE_h
#define Lcalc_MAE_h

#include <PLC.h>
/**************************************************************************/
/*!
    @brief  Mise à l'échelle de valeurs.

    equivalent de la fonction Map mais gère les flotants

    @param In valeur à convertir
    @param InMin valeur minimum
    @param InMax valeur maximum
    @param OutMin sortie minimum (pas de dépassement)
    @param In sortie maximum (pas de dépassement)
    
    @return Double : valeur mise à l'échelle
*/
/**************************************************************************/
double Lcalc_MAE(double In, double InMin, double InMax, double OutMin, double OutMax);

#endif