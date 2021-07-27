#ifndef Global_h
#define Global_h


#define ProjectName "LibBib DEV 0.2 [en cours de test]"


/* 
 * Includes
*/
#include <PLC.h>
#include <Lsys.cpp>


/*
 * Lib
 */

//Lcom
    #include <Lcom_433MHz\Lcom_433MHz.cpp>

//Lcpt
    #include <Lcpt_Fpulse\Lcpt_Fpulse.h>
    #include <Lcpt_Fcodeur\Lcpt_Fcodeur.h>
    

//Lctrl
    //Lctrl_Moteur
    #include <Lctrl_Moteur\Lctrl_MoteurPWM\Lctrl_MoteurPWM.h>
    #include <Lctrl_Moteur\Lctrl_MoteurTOR\Lctrl_MoteurTOR.h>
    #include <Lctrl_Moteur\Lctrl_DriveS500\Lctrl_DriveS500.h>
    #include <Lctrl_Moteur\Lctrl_Brushless\Lctrl_Brushless.h>
    #include <Lctrl_Moteur\Lctrl_Servo\Lctrl_Servo.h>
//Lio
    #include <LioTor\LioTor.cpp>
    #include <LioPwm\LioPwm.cpp>
    #include <LioAna\LioAna_Fscale\LioAna_Fscale.cpp>

//Lreg
    #include <LregPID\Lreg_PID.h>

//external
#include <RTClib.h>

#define StrLogo "\n\
##    ##    ###     ##    ##  ##    ##     ##     ##  ########  ########   ##        ########  ########      ###     ##    ## \n\
 ##  ##    ## ##    ###   ##  ###   ##     ##     ##  ##        ##     ##  ##        ##        ##     ##    ## ##    ###   ## \n\
  ####    ##   ##   ####  ##  ####  ##     ##     ##  ##        ##     ##  ##        ##        ##     ##   ##   ##   ####  ## \n\
   ##    ##     ##  ## ## ##  ## ## ##     #########  ######    ########   ##        ######    ##     ##  ##     ##  ## ## ## \n\
   ##    #########  ##  ####  ##  ####     ##     ##  ##        ##   ##    ##        ##        ##     ##  #########  ##  #### \n\
   ##    ##     ##  ##   ###  ##   ###     ##     ##  ##        ##    ##   ##        ##        ##     ##  ##     ##  ##   ### \n\
   ##    ##     ##  ##    ##  ##    ##     ##     ##  ########  ##     ##  ########  ########  ########   ##     ##  ##    ## "
#define ProjectInfos() Serial.println (F(StrLogo)); Serial.print (F(ProjectName)); Serial.print (F(", Uploaded : ")); Serial.print (F(__DATE__)); Serial.print (F(" ")); Serial.println (F(__TIME__)); Serial.println()


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