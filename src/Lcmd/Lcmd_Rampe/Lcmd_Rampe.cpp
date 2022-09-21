#include <Lcmd\Lcmd_Rampe\Lcmd_Rampe.h>


Lcmd_Rampe::Lcmd_Rampe(unsigned short rampe_ms) :   m_millisOld(millis()),
                                                    rampe(rampe_ms),
                                                    disable(false)
{}


void Lcmd_Rampe::main(unsigned char csg, unsigned char &csgActuelle)
{
    // Rampe désactivée
    if (disable) csgActuelle = csg;

    // Rampe inactive
    if (csgActuelle == csg)
    {
        m_millisOld = millis();
    }

    // Rampe incrémentation / décrémentation
    else if (rampe == 0 || (millis() >= m_millisOld + rampe))
    {
        m_millisOld += rampe;
        csgActuelle += (csg > csgActuelle) ? 1 : -1;
    }
}