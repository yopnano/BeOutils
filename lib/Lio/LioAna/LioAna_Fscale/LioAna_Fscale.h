#ifndef LioAna_Fscale_h
#define LioAna_Fscale_h

#include <PLC.h>
//#include <UDT.h>
// Surcharge
/*!
      @brief  Mise à l'échelle analogique
      @param pin analog pin A0 par exemple
      @param LO_LIM borne inférieure valeur
      @param HI_LIM borne supérieure valeur
      @param offset décalage de la valeur (0 par défaut)
      @return valeur mise à l'échelle
  */
LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, double LO_LIM, double HI_LIM, double offset = 0.0);

/*!
      @brief  Mise à l'échelle analogique
      @param pin analog pin A0 par exemple
      @param LO_LIM borne inférieure valeur
      @param HI_LIM borne supérieure valeur
      @param LO_DEF borne inférieure défaut capteur
      @param HI_DEF borne supérieure défaut capteur
      @param offset décalage de la valeur (0 par défaut)
      @return valeur mise à l'échelle
  */
LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, double LO_LIM, double HI_LIM, int LO_DEF, int HI_DEF, double offset = 0.0);

// Variantes simplifiée
/*!
      @brief  Mise à l'échelle analogique sans scale
      @param pin analog pin A0 par exemple
      @param LO_LIM = 0
      @param HI_LIM = 1023
      @param offset décalage de la valeur (0 par défaut)
      @return valeur mise à l'échelle
  */
LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, double offset = 0.0) {return LioAna_Fscale(pin, 0.0, 1023.0, offset);}

/*!
      @brief  Mise à l'échelle analogique sans scale avec plage de défaut
      @param pin analog pin A0 par exemple
      @param LO_LIM borne inférieure valeur
      @param HI_LIM borne supérieure valeur
      @param LO_DEF borne inférieure défaut 0 >= LO_DEF < HI_DEF
      @param HI_DEF borne supérieure défaut LO_DEF > HI_DEF <= 1023
      @param offset décalage de la valeur (0 par défaut)
      @return valeur mise à l'échelle
  */
LioAna_udtAiScale LioAna_Fscale(const uint8_t pin, int LO_DEF, int HI_DEF, double offset = 0.0) {return LioAna_Fscale(pin, 0.0, 1023.0, LO_DEF, HI_DEF, offset);}
#endif