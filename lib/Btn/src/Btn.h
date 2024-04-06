#pragma once

#include <Arduino.h>

enum ClickType
{
    None,
    ShortClick,
    LongClick
};

class Btn
{
private:
    byte pin;
    bool state;            // the current reading from the input pin
    bool lastState = true; // the previous reading from the input pin

    const ulong itvShort = 50; // minimal interval in ms between state changes for short click
    const ulong itvLong = 500; // minimal interval in ms between state changes for long click
    ulong msLastDebounce = 0;  // the last time the output pin was toggled

public:
    Btn(byte pin);

    ClickType check(ulong ms);
};
