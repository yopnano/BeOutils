#ifndef Lcmd_Rampe_h
#define Lcmd_Rampe_h

#include <Arduino.h>

unsigned char 

class Lcmd_Rampe
{
private:
    unsigned long m_millisOld;

public:
    bool disable;
    unsigned short rampe;
    
    Lcmd_Rampe(unsigned short rampe_ms = 10);

    void main(unsigned char csg, unsigned char &csgActuelle);

};

#endif // Lcmd_Rampe_h