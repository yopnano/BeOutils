#ifndef PLC_h
#define PLC_h

    // Appel des Classes de la bibliothèque PLC
    #include <PLC\IEC_Timer\IEC_Timer.h>
    #include <PLC\Trigger\Trigger.h>


    //MACRO PLC

    // NORM_X Normaliser
    #define NORM_X(MIN, VALUE, MAX) ((VALUE - MIN) / (MAX - MIN))

    // SCALE_X Mise à l'échelle
    #define SCALE_X(MIN, VALUE, MAX) ((VALUE * (MAX - MIN)) + MIN)

    // LIMIT Contraindre une valeur
    #define LIMIT(MIN, VALUE, MAX) (VALUE)<(MIN)?(MIN):((VALUE)>(MAX)?(MAX):(VALUE))


#endif