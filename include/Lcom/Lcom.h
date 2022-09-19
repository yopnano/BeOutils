#ifndef Lcom_h
#define Lcom_h

#include <BeOutilsConfig.h>

    // Appel des Classes de la bibliothèque Lcom
    #ifdef UsingLib_IR
        #include <Lcom\Lcom_433MHz\Lcom_433MHz.h>
    #endif

    #ifdef UsingLib_433MHz
        #include <Lcom\Lcom_IR\Lcom_IR.h>
    #endif
    

#endif