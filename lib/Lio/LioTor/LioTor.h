#ifndef LioTor_h
#define LioTor_h

#include <Arduino.h>


#define ON true
#define on true
#define OFF false
#define off false

class LioTorIn
{
    private:
        uint8_t m_pinNumber;
        boolean m_inverted;

    public:
    
        /**************************************************************************/
        /*!
            @brief  Entrée tout ou rien.

            @see LioTorOut.

            @param num  n° broche entrée TOR
            @param PullUp Mettre à true si besoin pullUp
            @param Inverted pour inverser l'état logique de l'entrée
            
        */
        /**************************************************************************/
        LioTorIn(uint8_t num, boolean PullUp = false, boolean inverted = false);

        /**************************************************************************/
        /*!
            @brief  Etat de l'entrée

            @return retourne l'état de l'entrée 
        */
        /**************************************************************************/
        int read() {return digitalRead(m_pinNumber) ^ m_inverted;}

};

class LioTorOut
{
    protected:
        uint8_t m_pinNumber;
        boolean m_inverted;

    public:
        /**************************************************************************/
        /*!
            @brief  Sortie tout ou rien.

            @see LioTorIn.

            @param num  n° broche sortie TOR
            @param Inverted pour inverser l'état logique de la sortie
        */
        /**************************************************************************/
        LioTorOut(uint8_t num, boolean inverted = false);

        /**************************************************************************/
        /*!
            @brief  Etat de la sortie

            @return retourne l'état de la sortie 
        */
        /**************************************************************************/
        int read() {return digitalRead(m_pinNumber) ^ m_inverted;}
        
        /**************************************************************************/
        /*!
            @brief  Ecriture de la sortie

            @param EQ ecriture de la sortie avec equation booleene
        */
        /**************************************************************************/
        boolean write(boolean EQ);

        /**************************************************************************/
        /*!
            @brief  Activer l'actionneur
        */
        /**************************************************************************/
        boolean turnOn() {return write(ON);}
        
        /**************************************************************************/
        /*!
            @brief  Desactiver l'actionneur
        */
        /**************************************************************************/
        boolean turnOff() {return write(OFF);}

        /**************************************************************************/
        /*!
            @brief  Inverser l'état de l'actionneur
        */
        /**************************************************************************/
        boolean toggle() {return write(!read());}
};

class relayTor : public LioTorOut
{
    public :
    /**************************************************************************/
    /*!
        @brief  Sortie relais.

        @param pin  n° broche de commande du relais
        @param Inverted pour inverser l'état logique du relais
    */
    /**************************************************************************/
    relayTor(uint8_t pin, boolean inverted = false);
};

class ledTor : public LioTorOut
{
    public:
    /**************************************************************************/
    /*!
        @brief  Sortie led simple TOR.

        @param pin  n° broche de la led
        @param Inverted pour inverser l'état logique de la led
    */
    /**************************************************************************/
    ledTor(uint8_t pin, boolean inverted = false);
};

#endif