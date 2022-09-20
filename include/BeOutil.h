#ifndef BeOutil_h
#define BeOutil_h


#include <Arduino.h>
#include <BeOutilsConfig.h>

#include <PLC\PLC.h>
#include <UDT\UDT.h>
#include <Lsys\Lsys.h>


#include <Lcalc\Lcalc.h>
#include <Lcmd\Lcmd.h>
#include <Lcom\Lcom.h>
#include <Lcpt\Lcpt.h>
#include <Lctrl\Lctrl.h>
#include <Lhw\Lhw.h>
#include <Lio\Lio.h>
#include <Lreg\Lreg.h>


#ifdef UsingLib_Serial
#define StrLogo "\n\
##    ##    ###     ##    ##  ##    ##     ##     ##  ########  ########   ##        ########  ########      ###     ##    ## \n\
 ##  ##    ## ##    ###   ##  ###   ##     ##     ##  ##        ##     ##  ##        ##        ##     ##    ## ##    ###   ## \n\
  ####    ##   ##   ####  ##  ####  ##     ##     ##  ##        ##     ##  ##        ##        ##     ##   ##   ##   ####  ## \n\
   ##    ##     ##  ## ## ##  ## ## ##     #########  ######    ########   ##        ######    ##     ##  ##     ##  ## ## ## \n\
   ##    #########  ##  ####  ##  ####     ##     ##  ##        ##   ##    ##        ##        ##     ##  #########  ##  #### \n\
   ##    ##     ##  ##   ###  ##   ###     ##     ##  ##        ##    ##   ##        ##        ##     ##  ##     ##  ##   ### \n\
   ##    ##     ##  ##    ##  ##    ##     ##     ##  ########  ##     ##  ########  ########  ########   ##     ##  ##    ## "
#define ProjectInfos() Serial.println (F(StrLogo)); Serial.print (F(ProjectName)); Serial.print (F(", Uploaded : ")); Serial.print (F(__DATE__)); Serial.print (F(" ")); Serial.println (F(__TIME__)); Serial.println()
#endif //UsingLib_Serial

/* 
 * Macro
*/

//COMMENTEE, JE LES AI MIS DANS ARDUINO.H CAR RAZ LE BOL

// #define SerialInfo Serial.print (F(__FILE__)); Serial.print (F(" F : ")); Serial.print (__FUNCTION__); Serial.print (F(" L : ")); Serial.print (__LINE__)
// // Message d'erreur
//     #define error(msg) if(DebugLevel >= 1) {SerialInfo; Serial.print (F(" => Error : ")); Serial.println(msg);}

// // Message d'avertissement
//     #define warning(msg) if(DebugLevel >= 2) {SerialInfo; Serial.print(F(" => Warning : ")); Serial.println(msg));}

// // Message de debug
//     #define debug(msg) if(DebugLevel >= 3) {SerialInfo; Serial.print(F(" => Debug : ")); Serial.println(msg);}

// // Message journal
//     #define logs(msg) if(DebugLevel >= 4) {SerialInfo; Serial.print(F(" => Log : ")); Serial.println(msg);}

/* 
 * Variables
*/

    /**************************************************************************/
    /*! @brief  Filtrer les messages de debug.
        1 : Erreur
        2 : Warning
        3 : Debug
        4 : Logs
    */
    /**************************************************************************/
short DebugLevel = 4;
#endif