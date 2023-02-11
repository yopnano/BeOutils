#include <Lcom\Lcom_433MHz\Lcom_433MHz.h>

#ifdef UsingLib_433MHz

    Lcom_RX_433MHz::Lcom_RX_433MHz(uint8_t pin) :
    m_pin(pin)
    {}

    void Lcom_RX_433MHz::setup()
    {
        int8_t interruptsPin = digitalPinToInterrupt(m_pin);
        if (interruptsPin == NOT_AN_INTERRUPT) {Serial.print (F("Lcom_RX_433MHz Warning : RX Pin > ")); Serial.print (m_pin); Serial.println (F(" isn't Interrupt"));}
        else m_mySwitch.enableReceive(interruptsPin);

    }

    void Lcom_RX_433MHz::main()
    {
        //Initialise les données
        m_data = {0, 0, 0};

        //Si réception de données
        if (m_mySwitch.available())
        {
            m_data.value = m_mySwitch.getReceivedValue();
            m_data.bitLengt = m_mySwitch.getReceivedBitlength();
            m_data.protocol = m_mySwitch.getReceivedProtocol();
            m_mySwitch.resetAvailable();
        }   
    }


    uint8_t Lcom_RX_433MHz::indexOf(code_433 codeArray[], uint8_t lenght)
    {//Parcours le tableau des codes enregistré si il y a correspondance retourne l'index sinon retourne 255
        if (!compareCodeStruct({0,0,0}, m_data))
        {
            for (uint8_t index = 0; index < lenght; index++)
            
                if (compareCodeStruct(codeArray[index], m_data)) return index;
            
        }
        return -1; //return 255
    }

    void Lcom_RX_433MHz::printCode(void)
    {
        if (!compareCodeStruct({0,0,0}, m_data))
        {
            Serial.print("val : ");
            Serial.print(m_data.value);

            Serial.print(" bit lenght : ");
            Serial.print(m_data.bitLengt);
            
            Serial.print(" protocol : ");
            Serial.println(m_data.protocol);
            
            Serial.print(" Add to array : {");
            Serial.print(m_data.value);
            Serial.print(", ");
            Serial.print(m_data.bitLengt);
            Serial.print(", ");
            Serial.print(m_data.protocol);
            Serial.println("}");
        }
    }
#endif