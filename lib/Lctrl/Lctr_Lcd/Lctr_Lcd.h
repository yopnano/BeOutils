#ifndef Lctrl_lcd_h
#define Lctrl_lcd_h

#include <Arduino.h>
#include <Lctrl.h>
#include <LiquidCrystal_I2C.h>
#include <Lsys_Fimpulse\Lsys_Fimpulse.h>

class Lctrl_Lcd : /*public Lctrl,*/ public LiquidCrystal_I2C
{
public:
    //void setup(void) {};
    //void main(void) {};

    Lctrl_Lcd(const uint8_t lcd_Addr, const uint8_t lcd_cols, const uint8_t lcd_rows);

    const size_t printCenter(const uint8_t row, const String &s);
    const size_t printPos(const uint8_t col, const uint8_t row, const String &s);
    const char* toggleText(const String &str1, const String &str2, const bool selector);
    
private:
  const uint8_t _cols;
  const uint8_t _rows;
  
};

#endif