#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "WString.h"
#include <LinkedList.h>
#include "Time.h"

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
    /// @brief Displays up to 3 items from the list items.
    /// @param items List of items (strings) that will be displayed.
    void menu(LinkedList<String> *items);
    /// @brief Displays time in format hh:mm or mm:ss
    /// @param t Time that will be displayed.
    void time(Time *t);

    bool IsItOn() { return isItOn; }
    void turnOff();
    void turnOn();
    ulong getMsLastDisplay() { return msLastDisplay; }
    /// @brief Set time interval in msec after which display will turn off if there is no activity.
    /// @param itv Time interval in milliseconds. 0 - don't turn off display.
    void setItvAutoTurnOff(ulong itv) { itvTurnOffDisplay = itv; msLastDisplay = millis(); }
    /// @brief Turn off display if there were no actions - menu() - for more than itvTurnOffDisplay msecs.
    /// @param ms Current time in milliseconds.
    void autoTurnOff(ulong ms);

};
