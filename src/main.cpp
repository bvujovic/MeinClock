#include <Arduino.h>

#include "Btn.h"
Btn btnLeft(D7);
Btn btnCenter(D6);
Btn btnRight(D5);

#include "MyDisplay.h"
MyDisplay disp;

void setup()
{
    disp.menu(1);
}

void loop()
{
    delay(10);
    ulong ms = millis();
    ClickType click;

    click = btnRight.check(ms);
    if(click == LongClick)
        disp.menu(2);
    click = btnLeft.check(ms);
    if(click == LongClick)
        disp.menu(1);
}
