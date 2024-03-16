#pragma once

#include <Arduino.h>

class Btn
{
private:
    byte pin;
    bool state;             // the current reading from the input pin
    bool lastState = false; // the previous reading from the input pin

    // TODO treba da bude static i da moze da se promeni vrednost: get set
    ulong itvDebounce = 50;   // the debounce time; increase if the output flickers
    ulong msLastDebounce = 0; // the last time the output pin was toggled

public:
    Btn(byte pin);

    bool check(ulong ms);
};
