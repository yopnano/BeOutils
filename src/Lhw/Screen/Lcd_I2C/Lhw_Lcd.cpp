#ifdef UsingLib_LcdI2c

    #include <Lhw\Screen\Lcd_I2C\Lhw_Lcd.h>

    Lhw_Lcd::Lhw_Lcd(const uint8_t lcd_Addr, const uint8_t lcd_cols, const uint8_t lcd_rows)
    :
        LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows),
        _cols(lcd_cols),
        _rows(lcd_rows)
        {}

    const size_t Lhw_Lcd::printCenter(const uint8_t row, const String &s)
    { 
        const uint8_t xPos = ((_cols) / 2) - (s.length() / 2);
        setCursor(xPos, row);
        return print(s);
    }
        
    const size_t Lhw_Lcd::printPos(const uint8_t col, const uint8_t row, const String &s)
    { 
        setCursor(col, row);
        return print(s);
    }

    const char* Lhw_Lcd::toggleText(const String &str1, const String &str2, const bool selector)
    {
        return (selector ? str2.c_str() : str1.c_str());
    }
#endif