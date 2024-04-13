#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "WString.h"
#include <LinkedList.h>

class MyDisplay
{
private:
    U8G2_SSD1306_64X48_ER_1_HW_I2C *u8g2;
    ulong msLastDisplay;
    bool isItOn;

    /// @brief (ms) display will be turned off automatically after this interval
    ulong itvTurnOffDisplay = 0;

public:
    MyDisplay();
    void menu(LinkedList<String> *items);
    bool IsItOn() { return isItOn; }
    void turnOff();
    void turnOn();
    ulong getMsLastDisplay() { return msLastDisplay; }
    void setItvTurnOffDisplay(ulong itv) { itvTurnOffDisplay = itv; }
    /// @brief Turn off display if there were no actions - menu() - for more than itvTurnOffDisplay msecs
    /// @param ms Current time in milliseconds
    void autoTurnOff(ulong ms);

};
