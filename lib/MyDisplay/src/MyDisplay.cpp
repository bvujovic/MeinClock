#include "MyDisplay.h"

MyDisplay::MyDisplay()
{
    u8g2 = new U8G2_SSD1306_64X48_ER_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
    u8g2->begin();
}

void MyDisplay::menu(int page)
{
    u8g2->setFont(u8g2_font_7x14_tr);
    u8g2->firstPage();
    do
    {
        if (page == 1)
        {
            u8g2->drawStr(0, 14, "Countdown");
            u8g2->drawStr(0, 30, "TimeWatch");
            u8g2->drawStr(0, 46, "Stopwatch");
        }
        else
        {
            u8g2->drawStr(0, 14, "Screen");
        }
    } while (u8g2->nextPage());
}
