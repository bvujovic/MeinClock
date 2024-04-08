#include <Arduino.h>

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_64X48_ER_1_HW_I2C display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    display.begin();
    // display.setFont(u8g2_font_t0_16_tr); // dobro je, samo su slova malo siroka
    display.setFont(u8g2_font_7x14_tr); // dobro je, da li moze malo krupnije?
}

int i = 0;

void loop()
{
    i++;
    // if (i++ % 2)
    //     display.setFont(u8g2_font_t0_16_tr);
    // else
    //     display.setFont(u8g2_font_7x14_tr);

    if (i > 3)
    {
        display.clear();
        display.noDisplay();
        // TODO ispitati potrosnju aparata pre i posle noDisplay()
    }
    else
    {
        display.firstPage();
        do
        {
            display.drawStr(0, 16, "Countdown");
            display.drawStr(0, 32, "TimeWatch");
            display.drawStr(0, 48, "Screen");
            
            //* prikaz teksta u 2 fonta
            // display.setFont(u8g2_font_7x14_tr);
            // display.drawStr(0, 16, "Countdown");
            // display.setFont(u8g2_font_10x20_tr);
            // display.drawStr(0, 48, "Scre");
        } while (display.nextPage());
    }
    delay(2000);
}
