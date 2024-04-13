#include "MyDisplay.h"

MyDisplay::MyDisplay()
{
    u8g2 = new U8G2_SSD1306_64X48_ER_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
    u8g2->begin();
    isItOn = true;
    msLastDisplay = millis();
}

void MyDisplay::menu(LinkedList<String> *items)
{
    Serial.println("menu");
    if (items == NULL)
        return;
    u8g2->setFont(u8g2_font_7x14_tr);
    u8g2->firstPage();
    do
    {
        if (items->size() > 0)
            u8g2->drawStr(0, 14, items->get(0).c_str());
        if (items->size() > 1)
            u8g2->drawStr(0, 30, items->get(1).c_str());
        if (items->size() > 2)
            u8g2->drawStr(0, 46, items->get(2).c_str());
    } while (u8g2->nextPage());
    msLastDisplay = millis();
}

void MyDisplay::turnOff()
{
    u8g2->clear();
    u8g2->noDisplay();
    isItOn = false;
}

void MyDisplay::turnOn()
{
    u8g2->display();
    msLastDisplay = millis();
    isItOn = true;
}

void MyDisplay::autoTurnOff(ulong ms)
{
    if (isItOn && itvTurnOffDisplay != 0 && ms > msLastDisplay + itvTurnOffDisplay)
        turnOff();
}
