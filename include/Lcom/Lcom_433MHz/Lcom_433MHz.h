#ifndef Lcom_433MHz_h
#define Lcom_433MHz_h

#include <Arduino.h>
#include <RCSwitch.h>
#include <Lcom\Lcom_IR\Lcom_IR.h>

/*! @brief  Structure code 433 MHz.
        Structure contenant la valeur, la logueur de bit, et le protocole.
*/
struct code_433
{
    unsigned long value;
    unsigned int bitLengt;
    unsigned int protocol;
};

/*! @brief  Récepteur 433 MHz.*/
class Lcom_RX_433MHz
{
private:
    uint8_t m_pin;
    code_433 m_data;
    RCSwitch m_mySwitch;
    boolean compareCodeStruct(code_433 data1, code_433 data2) const {return(data1.value == data2.value && data1.bitLengt == data2.bitLengt && data1.protocol == data2.protocol);}
    
public:
    /*! @brief  Récepteur 433 MHz.
        @param pin pin de réception data (doit être interruptible)
    */
    Lcom_RX_433MHz(uint8_t pin);
    void setup(void);
    void main(void);

    /*! @brief  Comparaison du code reçu avec un code 433 MHz.
        @param code code_433 à comparer avec le code reçu
        @return true si le code reçu correspond au code à tester
    */
    boolean correspondingTo(code_433 code) const {return compareCodeStruct(code, m_data);}
    
    /*! @brief  Affichage des codes reçu dans le moniteur serie.
        Utile pour déboguage et ajout de ligne rapide tableau de code.
    */
    void printCode(void);

    /*! @brief  Récupération des données de la structure.
        @return code_433
    */
    code_433 getData(void) const {return m_data;}
    
    /*! @brief  Comparaison avec un tableau de code.
        @param codeArray tableau avec la liste de code_433
        @param lenght taille du tableau de code
        @return index du tableau correspondant au code, sinon 255
    */
    uint8_t indexOf(code_433 codeArray[], uint8_t lenght);

    unsigned int getBitLenght(void) const {return m_data.bitLengt;}
    unsigned int getProtocole(void) const {return m_data.protocol;}
    unsigned long getValue(void) const {return m_data.value;}
};
#endif