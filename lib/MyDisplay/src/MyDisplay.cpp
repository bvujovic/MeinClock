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
    secondsPrev = secondsPrevDef;
}

void MyDisplay::time(Time &t, DisplayTime dt)
{
    if (t.seconds == secondsPrev && dt != MinSecCent)
        return;
    secondsPrev = t.seconds;
    char a[3], b[3], cs[3];
    strcpy(a, u8x8_u8toa(dt != HourMin ? t.minutes : t.hours, 2));
    strcpy(b, u8x8_u8toa(dt != HourMin ? t.seconds : t.minutes, 2));
    strcpy(cs, u8x8_u8toa(t.centSec, 2));
    u8g2->firstPage();
    byte bottom = dt == MinSecCent ? 32 : 40;
    do
    {
        u8g2->setFont(u8g2_font_logisoso24_tn);
        u8g2->drawStr(0, bottom, a);
        u8g2->drawStr(29, bottom, ":");
        u8g2->drawStr(35, bottom, b);
        if (dt == MinSecCent)
        {
            u8g2->setFont(u8g2_font_7x14_tr);
            u8g2->drawStr(45, 47, cs);
        }
    } while (u8g2->nextPage());
}

void MyDisplay::turnOff()
{
    u8g2->clear();
    u8g2->noDisplay();
    secondsPrev = secondsPrevDef;
    isItOn = false;
}

void MyDisplay::turnOn()
{
    u8g2->display();
    isItOn = true;
    msLastDisplay = millis();
}

void MyDisplay::setItvAutoTurnOff(ulong itv)
{
    itvTurnOffDisplayPrev = itvTurnOffDisplay;
    itvTurnOffDisplay = itv;
    msLastDisplay = millis();
}

bool MyDisplay::autoTurnOffIN(ulong ms)
{
    bool res = isItOn && itvTurnOffDisplay != 0 && ms > msLastDisplay + itvTurnOffDisplay;
    if (res)
        turnOff();
    return res;
}
