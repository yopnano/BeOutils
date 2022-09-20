#ifndef Lcmd_Rampe_h
#define Lcmd_Rampe_h

#include <Arduino.h>

class Lcmd_Rampe
{
private:
    unsigned long m_millisOld;

public:
    Lcmd_Rampe(unsigned short rampe_ms = 10);
    
    void main(unsigned char csg, unsigned char &csgActuelle);
    
    unsigned short rampe;
    bool disable;
};

#endif // Lcmd_Rampe_h