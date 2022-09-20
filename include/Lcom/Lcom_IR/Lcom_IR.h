#ifndef Lcom_IR_h
#define Lcom_IR_h

#include <Arduino.h>
#include <BeOutilsConfig.h>

/*! @brief  Récepteur 433 MHz.*/
class Lcom_RX_IR
{
private:
    uint8_t m_pin;
    uint16_t m_repeatedValue;
    uint32_t m_value;
    uint32_t m_oldValue;
    
    boolean compareCodeValue(uint32_t value1, uint32_t value2) const {return(value1 == value2);}
public:
    /*! @brief  Récepteur 433 MHz.
        @param pin pin de réception data (doit être interruptible)
    */
    Lcom_RX_IR(uint8_t pin);
    void setup(void);
    void main(void);

    /*! @brief  Comparaison du code reçu avec un code 433 MHz.
        @param code code_433 à comparer avec le code reçu
        @return true si le code reçu correspond au code à tester
    */
    boolean correspondingTo(uint32_t code) const {return compareCodeValue(code, m_value);}
    
    /*! @brief  Affichage des codes reçu dans le moniteur serie.
        Utile pour déboguage et ajout de ligne rapide tableau de code.
    */
    void printCode(void);

    /*! @brief  Récupération des données de la structure.
        @return code_433
    */
    uint32_t getData(void) const {return m_value;}
    
    /*! @brief  Comparaison avec un tableau de code.
        @param codeArray tableau avec la liste de code_433
        @param lenght taille du tableau de code
        @return index du tableau correspondant au code, sinon 255
    */
    uint8_t indexOf(uint32_t codeArray[], uint8_t lenght);

    bool newCode() const { return m_value != 0;}
    bool repeated() const { return m_repeatedValue;}
    uint8_t repeatCount() const { return m_repeatedValue;}

};
#endif