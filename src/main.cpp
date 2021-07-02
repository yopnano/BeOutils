#include <global.cpp>
int tempo1s = 0;
int g7 = 0;

void setup()
{
  Modsetup();
}

void loop()
{  
  
  // fonction main des méthodes
  sys.main();
  ModMain();
 
  // gestion tempo1s
  if (sys.ft1Hz()) {tempo1s++;}

  // Etape 0
  if (g7 == 0)
  {
    tempo1s = 0;
    g7 = 1;
    // changement d'état de la led
    led.toggle();
    moteur.cmdAv(true);
    moteur.cmdAr(false);
    moteur.csgAuto(255);
  }


  // Etape 1
  if (tempo1s >= 5 && g7 == 1)
  {
    tempo1s = 0;
    g7 = 2;
    // changement d'état de la led
    led.toggle();
    moteur.cmdAv(false);
  }

  // Etape 2
  if (tempo1s >= 5 && g7 == 2)
  {
    g7 = 3;
    tempo1s = 0;
    // changement d'état de la led
    led.toggle();
    moteur.cmdAr(true);
  }

  // Etape 3
  if (tempo1s >= 5 && g7 == 3)
  {
    tempo1s = 0;
    g7 = 4;
    // changement d'état de la led
    led.toggle();
    moteur.cmdAr(false);
  }

  if (tempo1s > 5 && g7 == 4) g7 = 0;

}