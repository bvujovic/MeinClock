#include "Btn.h"
Btn btnCenter(D6);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    delay(10);
    ulong ms = millis();
    ClickType click = btnCenter.check(ms);

    if (click == ShortClick)
        Serial.println("Short");
    if (click == LongClick)
        Serial.println("Long");
}
