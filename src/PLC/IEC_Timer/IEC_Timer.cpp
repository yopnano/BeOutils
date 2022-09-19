#include <PLC\IEC_Timer\IEC_Timer.h>

/**************************************************************************/
/*!
    TIME
*/
/**************************************************************************/

    /**************************************************************************/
    /*!
        Constructeurs
    */
    /**************************************************************************/
    TIME::TIME(uint32_t value, uint32_t multiplier)
    {
        set(value * multiplier);
    }

    TIME::TIME(uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
    {
        set(day, hour, min, sec);
    }

    TIME::TIME(const TIME &copy)
    : ms(copy.ms), ss(copy.ss), mm(copy.mm),
      hh(copy.hh), d(copy.d) {}


    #ifdef UsingLib_RTC
        TIME::TIME(const DateTime &copy)
        : ms(0), ss(copy.second()), mm(copy.minute()),
            hh(copy.hour()) {}
    #endif

    /**************************************************************************/
    /*!
        Méthodes
    */
    /**************************************************************************/
    void TIME::reset()
    {
        set(0);
    }

    void TIME::set(uint32_t value, uint32_t multiplier)
    {
        uint32_t millisecond = value * multiplier;
        ms = (short) (millisecond % Secondes);
        ss = (short) ((millisecond / Secondes) % 60);
        mm = (short) ((millisecond / Minutes) % 60);
        hh = (short) ((millisecond / Heures) % 24);
        d  = (short) (millisecond / Jours);
    }

    void TIME::set(uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
    {
        d = day;
        hh = hour;
        mm = min;
        ss = sec;
    }

    char *TIME::toString()
    {
        char buffer[22] = "";
        return m_toString(buffer);
    }
    char *TIME::m_toString(char *buffer)
    {
            if (d)  sprintf(buffer, "%02dj %02dh %02dm %02ds %03dms ", d, hh, mm, ss, ms);

        else if (hh) sprintf(buffer, "%02dh %02dm %02ds %03dms ", hh, mm, ss, ms);

        else if (mm) sprintf(buffer, "%02dm %02ds %03dms ", mm, ss, ms);

        else if (ss) sprintf(buffer, "%02ds %03dms ", ss, ms);

        else if (ms) sprintf(buffer, "%03dms ", ms);

        return buffer;
    }

    /**************************************************************************/
    /*!
        OPERATORS
    */
    /**************************************************************************/

    /**************************************************************************/
    /*!
        @author Anton Rieutskyi
        @brief  Test if two DTL objects are equal.
        @warning if one or both DTL objects are invalid, returned value is
            meaningless
        @see use `isValid()` method to check if DTL object is valid
        @param right Comparison DTL object
        @return True if both DTL objects are the same, false otherwise.
    */
    /**************************************************************************/
    bool TIME::operator==(const TIME &right) const {
    return (    right.d == d &&
                right.hh == hh &&
                right.mm == mm &&
                right.ss == ss);
    }

    /**************************************************************************/
    /*!
        @author Yann Herledan
        @brief  Test if one DTL is less (earlier) than another.
        @warning if one or both DTL objects are invalid, returned value is
            meaningless
        @see use `isValid()` method to check if DTL object is valid
        @param right Comparison DTL object
        @return True if the left DTL is earlier than the right one,
            false otherwise.
    */
    /**************************************************************************/
    bool TIME::operator<(const TIME &right) const {
    return (    d <= right.d &&
                hh <= right.hh &&
                mm <= right.mm &&
                ss < right.ss);
    }

    /**************************************************************************/
    /*!
        @brief  Add a TIME from Another TIME object
        @param right TIME object
        @return New TIME object with TIME added from it.
    */
    /**************************************************************************/
    TIME TIME::operator+(const TIME &right) {   
    return TIME(totalMillis() + right.totalMillis());
    }

    /**************************************************************************/
    /*!
        @brief  Subtract a TIME from Another TIME object
        @param right TIME object
        @return New TIME object with TIME subtracted from it.
    */
    /**************************************************************************/
    TIME TIME::operator-(const TIME &right) {
    return TIME(totalMillis() - right.totalMillis());
    }


/**************************************************************************/
/*!
    TON
*/
/**************************************************************************/
TON::TON(TIME pt, bool in): IN(in),
                            PT(pt)
{
    main();
}

void TON::main()
{
    if (not IN)
    {
       q = false;
       startMillis = millis();
    }
    else if (not q)
    {
        et = ((millis() - startMillis));
        if (et >= PT.totalMillis())
            q = true;
    }
}

TIME TON::ET()
{
    main();
    return (TIME) et;
}

bool TON::Q()
{
    main();
    return q;
}


/**************************************************************************/
/*!
    TOF
*/
/**************************************************************************/

TOF::TOF(TIME pt, bool in): IN(in),
                            PT(pt)
{
    q = false;
    main();
}

void TOF::main()
{
    if (IN)
    {
        q = true;
        startMillis = millis();
    }
    else if (q)
    {
        et = (millis() - startMillis);
        if (et >= PT.totalMillis())
            q = false;
    }

}

TIME TOF::ET()
{
    main();
    return et;
}

bool TOF::Q()
{
    main();
    return (q);
}


/**************************************************************************/
/*!
    TP
*/
/**************************************************************************/
TP::TP(TIME pt, bool in): IN(in),
                            PT(pt)
{
    q = false;
}

void TP::main()
{
    inTrig.Analyse(IN);
    if (inTrig.R_trig())
    {
        startMillis = millis();
        q = true;
    }
    
    if (q)
    {   
        et = (millis() - startMillis);
        if (et >= PT.totalMillis())
            q = false;
    }
}

TIME TP::ET()
{
    main();
    return (TIME) et;
}

bool TP::Q()
{
    main();
    return q;
}