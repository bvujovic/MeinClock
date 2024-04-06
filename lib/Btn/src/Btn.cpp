#include "Btn.h"

Btn::Btn(byte pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

ClickType Btn::check(ulong ms)
{
    ClickType result = None;
    bool reading = digitalRead(pin);
    ulong itvPress = ms - msLastDebounce;
    if (reading != lastState)
    {
        if (reading)
        {
            // T Serial.println(itvPress);
            state = reading;
            if (itvPress > itvLong)
                result = LongClick;
            else if (itvPress > itvShort)
                result = ShortClick;
        }
        msLastDebounce = millis();
    }
    lastState = reading;
    return result;
}
