#include <Lio\LioTor\LioTor.h>

LioTorIn::LioTorIn(uint8_t num, boolean PullUp, boolean inverted) : m_pinNumber(num), m_inverted(inverted)
{
    pinMode(m_pinNumber, PullUp ? INPUT_PULLUP : INPUT);
}

LioTorOut::LioTorOut(uint8_t num, boolean inverted) : m_pinNumber(num), m_inverted(inverted)
{
    pinMode(m_pinNumber, OUTPUT);
}

boolean LioTorOut::write(boolean EQ)
{
    digitalWrite(m_pinNumber, EQ ^ m_inverted);
    return read();
}



relayTor::relayTor (uint8_t pin, boolean inverted) : LioTorOut(pin, inverted)
{
}

ledTor::ledTor (uint8_t pin, boolean inverted) : LioTorOut(pin, inverted)
{
}