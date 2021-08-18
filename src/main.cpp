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

  moteur.pidMode(true);
  //double vitesse = codeur.vitesseAbs() * 0.233;

  if (sys.ft2Hz())
  {
    Serial.print("volume : " + (String) debitmetre.volume());
    Serial.println("  debit : " + (String) debitmetre.debit());
  }

  if (sys.ft1Hz()) tempo1s ++;

  if (g7 == 0)
  {
    tempo1s = 0;
    g7 = 1;
  }

  if (g7 == 1 && tempo1s >= 1)
  {
    tempo1s = 0;
    g7 = 2;
  }

  if (g7 == 2 && tempo1s >= 1)
  {
    tempo1s = 0;
    g7 = 0;
  }
}