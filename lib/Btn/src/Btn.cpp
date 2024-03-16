#include "Btn.h"

Btn::Btn(byte pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool Btn::check(ulong ms)
{
    bool result = false;
    bool reading = digitalRead(pin);
    if (reading != lastState)
        msLastDebounce = millis();

    if ((ms - msLastDebounce) > itvDebounce)
    {
        if (reading != state)
        {
            state = reading;
            if (state == false)
                result = true;
        }
    }
    lastState = reading;
    return result;
}
