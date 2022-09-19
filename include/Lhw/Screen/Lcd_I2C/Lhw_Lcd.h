#ifndef Lhw_lcd_h
#define Lhw_lcd_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Lhw\Screen\Lcd_I2C\Lhw_Lcd.h>

class Lhw_Lcd : public LiquidCrystal_I2C
{
public:

    Lhw_Lcd(const uint8_t lcd_Addr, const uint8_t lcd_cols, const uint8_t lcd_rows);

    void setup(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS ) {begin(cols, rows, charsize = LCD_5x8DOTS );}
   
    const size_t printCenter(const uint8_t row, const String &s);
    const size_t printPos(const uint8_t col, const uint8_t row, const String &s);
    const char* toggleText(const String &str1, const String &str2, const bool selector);
    
private:
  const uint8_t _cols;
  const uint8_t _rows;
  
};

#endif