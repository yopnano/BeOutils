#ifndef IEC_Timer_h
#define IEC_Timer_h

#include <Arduino.h>
#include "Trigger\Trigger.h"

class TIME
{
    public:
        enum TimeMultiplier
        {
            Millisecondes = 1U,
            Secondes = 1000U,
            Minutes = 60000U,
            Heures = 3600000U,
            Jours = 86400000U
        };


        TIME(uint32_t value, uint32_t multiplier =  Millisecondes);
        TIME(uint8_t day, uint8_t hour, uint8_t min = 0, uint8_t sec = 0);
        TIME(const TIME &copy);
        
        void reset();

        /*! @brief  Entrée d'une valeur.

            Met le type à la valeur souhaitée avec un multiplicateur par défaut = 1

            @param value valeur
            @param multiplier multiplicateur pour valeur en sec, min, voir enum TimeMultiplier
            @return .
        */
        void set(uint32_t value, uint32_t multiplier = Millisecondes);
        void set(uint8_t day, uint8_t hour, uint8_t min = 0, uint8_t sec = 0);

        char *toString();        

        uint32_t totalMillis() const {return (d * Jours) + (hh * Heures) + (mm * Minutes) + (ss * Secondes);}
        uint16_t totalSecond();
        uint16_t totalMinute();
        uint16_t totalHour();
        uint8_t totalDay();

        uint16_t millis() const {return ms;}
        uint8_t second() const {return ss;}
        uint8_t minute() const {return mm;}
        uint8_t hour() const {return hh;}
        uint8_t day() const {return d;}

        //OPERATORS


        TIME operator+(const TIME &right);
        TIME operator-(const TIME &right);
        
        bool operator<(const TIME &right) const;

        /*! @brief  Test if one TIME is greater (later) than another.
            @warning if one or both TIME objects are invalid, returned value is
                meaningless
            @see use `isValid()` method to check if TIME object is valid
            @param right TIME object to compare
            @return True if the left TIME is later than the right one,
                false otherwise
        */
        bool operator>(const TIME &right) const { return right < *this; }

        /*! @brief  Test if one TIME is less (earlier) than or equal to another
            @warning if one or both TIME objects are invalid, returned value is
                meaningless
            @see use `isValid()` method to check if TIME object is valid
            @param right TIME object to compare
            @return True if the left TIME is earlier than or equal to the
                right one, false otherwise
        */
        bool operator<=(const TIME &right) const { return !(*this > right); }

        /*! @brief  Test if one TIME is greater (later) than or equal to another
            @warning if one or both TIME objects are invalid, returned value is
                meaningless
            @see use `isValid()` method to check if TIME object is valid
            @param right TIME object to compare
            @return True if the left TIME is later than or equal to the right
                one, false otherwise
        */
        bool operator>=(const TIME &right) const { return !(*this < right); }
        bool operator==(const TIME &right) const;

        /*! @brief  Test if two TIME objects are not equal.
            @warning if one or both TIME objects are invalid, returned value is
                meaningless
            @see use `isValid()` method to check if TIME object is valid
            @param right TIME object to compare
            @return True if the two objects are not equal, false if they are
        */
        bool operator!=(const TIME &right) const { return !(*this == right); }
                
    protected:
        uint16_t ms;
        uint8_t ss;
        uint8_t mm;
        uint8_t hh;
        uint8_t d;

    private:
        char *m_toString(char *buffer);
};

class TON
{
    public:
        /*! @brief  TON Retard à la montée.

            Permet de retarder la mise à 1 de la sortie Q d'une durée programmée PT. L'instruction est démarrée lorsque le paramètre IN passe à "1".
            La durée programmée PT commence à s'écouler au démarrage de l'instruction.
            Une fois que la durée PT est écoulée, le paramètre Q fournit l'état de signal "1".
            Le paramètre Q reste à 1 tant que l'entrée de démarrage IN est à "1".
            Lorsque l'état logique à l'entrée de démarrage passe de 1 à 0, le paramètre Q est remis à 0.
            La fonction de temporisation est redémarrée lorsqu'un nouveau front montant est détecté à l'entrée de démarrage.

            Vous pouvez interroger la valeur de temps actuelle au niveau de la sortie ET.
            La valeur commence à 0ms et s'achève lorsque la valeur de la durée PT est atteinte. Le paramètre ET est mis à 0 dès que l'état logique à l'entrée IN passe à "0".

            @see Les TOF et TP sont d'autres type de temporisation.

            @param PT Durée avant l'activation de la sortie Q
            @param IN signal d'entrée compte tant que IN = true jusqu'à la durée PT
        */
        TON(TIME pt = 0, bool in = false);

        /*! @brief  Entrée de comptage.

            Entrée de démarrage, doit être à true durant toute la durée PT pour obtenir Q
        */
        bool IN;

        /*! @brief  Durée en millisecondes de la tempo.

            Durée avant que la sortie Q ne passe à true.
            La valeur doit être positive et se compte en millisecondes

            @see TIME object.
        */
        TIME PT;
        
        /*! @brief Temps écoulé depuis l'activation de IN.
            @return TIME object @see TIME.
        */
        TIME ET();
        
        /*! @brief  Sortie Q Retardée de la durée PT.

            Verifie que la durée est atteinte puis retourne l'état de Q

            @see return_Q() pour obtenir la valeur de Q sans effectuer de vérification.
        */
        bool Q();

        /*! @brief  Sortie Q Retardée de la durée PT.

            Retourne simplement la valeur de Q sans vérifier l'état de la tempo.
            Utile dans certains cas pour faire une tempo cyclique
            @example    TON tempo(10000);
                        if (tempo.Q())
                        {
                            // if statement
                        }
                        tempo.IN = NOT tempo.return_Q()

            @see Q() Pour la plupart des cas il est recommandé d'utiliser la méthode Q().
        */
        bool return_Q() const {return q;}

    protected:
        bool q;
        unsigned long startMillis;
        unsigned long et;
        void main();
};

class TOF
{
    public:
        /*! @brief  TOF Retard à la retombée.

            Permet de retarder la mise à 0 de la sortie Q d'une durée programmée PT.
            Le paramètre Q est mis à 1 lorsque le paramètre IN passe à "1".
            La temps programmée PT commence à s'écouler lorsque l'état logique au paramètre IN passe de nouveau à 0.
            Le paramètre Q reste à 1 tant que la temporisation PT s'exécute.
            Une fois la durée PT écoulé, le paramètre Q est remis à 0. Si l'état logique du paramètre IN passe à "1" avant que la durée PT ne soit écoulé,
            le temps est remis à 0. L'état logique du paramètre Q reste à 1.

            La valeur de temps actuelle peut être interrogée au paramètre ET. La valeur commence à 0ms et s'achève lorsque la valeur de la durée PT est atteinte.
            Une fois la durée PT écoulée, le paramètre ET conserve la valeur actuelle jusqu'à ce que le paramètre IN passe de nouveau à "1".
            Si l'entrée IN passe à "1" avant que la durée PT soit écoulée, la sortie ET est remise à la valeur 0s.

            @see Les TON et TP sont d'autres type de temporisation.

            @param PT Durée de maintien de la sortie Q
            @param IN signal d'entrée compte dès que IN = false jusqu'à la durée PT
        */
        TOF(TIME pt = 0, bool in = false);

        /*! @brief  Entrée de comptage.

            Entrée de démarrage, sur front descendantpour obtenir Q pendant la durée PT
        */    
        bool IN;

        /*! @brief  Durée en millisecondes de maintien de la tempo.

            Durée pendant la quelle la sortie Q est maintenue.
            La valeur doit être positive et se compte en millisecondes

            @see TIME object.
        */
        TIME PT;

        /*! @brief Temps écoulé depuis le front descendant de IN.
            @return TIME object @see TIME.
        */
        TIME ET();

        /*! @brief  Sortie Q Prolongée de la durée PT.

            Verifie que la durée est atteinte puis retourne l'état de Q

            @see return_Q() pour obtenir la valeur de Q sans effectuer de vérification.
        */
        bool Q();

        /*! @brief  Sortie Q prolongée de la durée PT.

            Retourne simplement la valeur de Q sans vérifier l'état de la tempo.
            Utile dans certains cas pour faire une tempo cyclique
            @example    TOF tempo(10000);
                        if (tempo.Q())
                        {
                            // if statement
                        }
                        tempo.IN = NOT tempo.return_Q()

            @see Q() Pour la plupart des cas il est recommandé d'utiliser la méthode Q().
        */
        bool return_Q() const {return q;}

    protected:
        bool q;
        unsigned long startMillis;
        unsigned long et;
        void main();
};

class TP
{
    public:
        /*! @brief  TP Tempo à impulsion.

           Permet de mettre la sortie Q à 1 pour une durée programmée. L'instruction est démarrée lorsque le paramètre IN passe de "0" à "1" (front montant).
           La durée programmée PT commence à s'écouler au démarrage de l'instruction. Le paramètre Q est mis à 1 pour la durée PT,
           sans tenir compte de l'évolution du signal d'entrée. Tant que la durée PT s'écoule, l'état logique du paramètre Q n'est pas non plus influencé
           par la détection d'un nouveau front montant.

            Vous pouvez interroger la valeur de temps actuelle au niveau du paramètre ET.
            La valeur commence à 0ms et s'achève lorsque la valeur de la durée PT est atteinte.
            Le paramètre ET est remis à zéro lorsque la durée PT est atteinte.

            @see Les TON et TOF sont d'autres type de temporisation.

            @param PT Durée totale de la sortie Q
            @param IN signal d'entrée démarre au front montant
        */
        TP(TIME pt = 0, bool in = false);

        /*! @brief  Entrée de l'impulsion.

            Entrée de démarrage, Maintiens la sortie Q pendant la durée PT au front montant de IN
        */
        bool IN;

        /*! @brief  Durée en millisecondes de l'impulsion de Q.

            Durée pendant laquelle la sortie Q sera à True.
            La valeur doit être positive et se compte en millisecondes

            @see TIME object.
        */
        TIME PT;

        /*! @brief Temps écoulé depuis l'activation de Q.
            @return TIME object @see TIME.
        */
        TIME ET();

        /*! @brief  Impulsion Q de la durée PT.

            Verifie que la durée de Q est atteinte puis retourne l'état de Q

            @see return_Q() pour obtenir la valeur de Q sans effectuer de vérification.
        */
        bool Q();

        /*! @brief  Impulsion Q de la durée PT.

            Retourne simplement la valeur de Q sans vérifier l'état de la tempo.
            Utile dans certains cas pour faire une tempo cyclique
            @example    TP tempo(10000);
                        if (tempo.Q())
                        {
                            // if statement
                        }
                        tempo.IN = NOT tempo.return_Q()

            @see Q() Pour la plupart des cas il est recommandé d'utiliser la méthode Q().
        */
        bool return_Q() const {return q;}

    protected:
        bool q;
        unsigned long startMillis;
        unsigned long et;
        Trigger inTrig;
        void main();
};
#endif