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

  pid.input = codeur.position() * 14.0;
  pid.SetOutputLimits(-255, 255);
  moteur.pidMode(true);

  moteur.cmdAr (pid.output < 0);
  moteur.cmdAv (pid.output > 0);
  moteur.csgAuto (36 + abs(pid.output));
  //double vitesse = codeur.vitesseAbs() * 0.233;

  if (sys.ft2Hz())
  {
    Serial.print("position : " + (String) pid.input);
    Serial.println("  pid out : " + (String) pid.output);
  }

  if (sys.ft1Hz()) tempo1s ++;

  if (g7 == 0)
  {
    tempo1s = 0;
    pid.setpoint = 0;
    g7 = 1;
  }

  if (g7 == 1 && tempo1s >= 1)
  {
    tempo1s = 0;
    pid.setpoint = 100;
    g7 = 2;
  }

  if (g7 == 2 && tempo1s >= 1)
  {
    tempo1s = 0;
    g7 = 0;
  }
}