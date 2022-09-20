#include <Lcom\Lcom_IR\Lcom_IR.h>

#ifdef UsingLib_IR
    #include <IRremote.h> // appeleé dans le CPP car l'instance est dans la bibliothèque

    Lcom_RX_IR::Lcom_RX_IR(uint8_t pin) :
    m_pin(pin)
    {}

    void Lcom_RX_IR::setup()
    {
        
        //Warning conflict with tone function
        // change the timer use by IRremote
        // in \IRremote\boarddefs.h or \private\IRtimerCpp.h
        //  comment #define IR_USE_TIMER2
        // and uncomment #define IR_USE_TIMER1
        pinMode(m_pin, INPUT_PULLUP);
        IrReceiver.begin(m_pin, DISABLE_LED_FEEDBACK);

    }

    void Lcom_RX_IR::main()
    {
        m_value = 0;

        //Si réception de données
        if (IrReceiver.decode())
        {
            //if (IrReceiver.decodedIRData.decodedRawData != 0)
                m_value = IrReceiver.decodedIRData.decodedRawData;

            IrReceiver.resume();
            
            if (m_value != m_oldValue)
            {
                m_oldValue = m_value;
                m_repeatedValue = 0;
            }else{
                m_repeatedValue ++;
            }        
        }
    }


    uint8_t Lcom_RX_IR::indexOf(uint32_t codeArray[], uint8_t lenght)
    {//Parcours le tableau des codes enregistré si il y a correspondance retourne l'index sinon retourne 255
        if (newCode())
        {
            for (uint8_t index = 0; index < lenght; index++)
            
                if (compareCodeValue(codeArray[index], m_value)) return index;
            
        }
        return -1; //return 255
    }

    void Lcom_RX_IR::printCode(void)
    {
        if (m_value != 0)
        {
            Serial.print("Decoding  ");
            Serial.println (m_value, HEX);

            Serial.print("  Address : ");
            Serial.println(IrReceiver.decodedIRData.address);

            Serial.print("  Flags : ");
            Serial.println(IrReceiver.decodedIRData.flags);

            Serial.print("  Num of bits : ");
            Serial.println(IrReceiver.decodedIRData.numberOfBits);

            Serial.print("  Protocol : ");
            Serial.println(IrReceiver.decodedIRData.protocol);

            Serial.print("  Command : ");
            Serial.println(IrReceiver.decodedIRData.command);
            
            Serial.print("  Add to array : 0x");
            Serial.print(m_value, HEX);
            Serial.println(",\n\n");
        }
    }
#endif