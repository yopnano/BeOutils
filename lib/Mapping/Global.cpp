#include "Global.h"
//Instances
ledTor led(LED_BUILTIN);


// Lctrl_MoteurPWM moteur[] 
// {    
//     //Lctrl_MoteurPWM (11, 10, 40, 7),
//     //Lctrl_MoteurPWM (9, 5, 40, 10)
// };

// Lctrl_Servo moteur(2, Lctrl_Servo::Mode_vitessePos, 5, 15, 170);
 Lctrl_MoteurPWM moteur(10, 11, Lctrl_MoteurPWM::Mode_auto, 0, 255, 10);
// Lctrl_DriveS500 moteur(2, 3, 4, 5, 6, Lctrl_DriveS500::Mode_auto, 40);
// Lctrl_Brushless_2sens moteur(2, Lctrl_Brushless_2sens::Mode_auto, 40, 1000, 1500, 2000);

//Lcpt_Fpulse debitmetre(2);
Lcpt_Fcodeur codeur(2, 3, 0.11, 55);

//Lreg_PID pid(0.7, 0, 0.1);
//Lreg_PID pid(1.213, 0, 0);
//Lreg_PID pid(0.7, 0.1, 0.04);
//0.68 0.1 0.03


void Modsetup(void)
{
    Serial.begin(9600);
    ProjectInfos();
    //for (auto &&iMoteur : moteur) iMoteur.setup();
    moteur.setup();
    codeur.setup();
}

void ModMain(void)
{
    //for (auto &&iMoteur : moteur) iMoteur.main();
    moteur.main();
    codeur.main();
}