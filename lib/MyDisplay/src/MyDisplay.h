#pragma once

// #include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "WString.h"
#include <LinkedList.h>
#include "Time.h"

class MyDisplay
{
private:
    U8G2_SSD1306_64X48_ER_1_HW_I2C *u8g2;
    /// @brief The last time something is displayed.
    ulong msLastDisplay;
    /// @brief Is the display turned on.
    bool isItOn;
    /// @brief Default/fake value for previous displayed seconds 
    const byte secondsPrevDef = 123;
    /// @brief Previous displayed seconds 
    byte secondsPrev = secondsPrevDef;

    /// @brief (ms) display will be turned off automatically after this interval
    ulong itvTurnOffDisplay = 0;
    /// @brief (ms) previous value for itvTurnOffDisplay
    ulong itvTurnOffDisplayPrev = 0;

public:
    void init();
    /// @brief Displays up to 3 items from the list items.
    /// @param items List of items (strings) that will be displayed.
    void menu(LinkedList<String> *items);
    /// @brief Displays time in format hh:mm or mm:ss
    /// @param t Time that will be displayed.
    void time(Time &t, DisplayTime dt);

    /// @brief Is the display turned on.
    bool IsItOn() { return isItOn; }
    /// @brief Sets msLastDisplay to ms (current time).
    void ItIsOn(ulong ms) { msLastDisplay = ms; }
    /// @brief Turn on display.
    void turnOn();
    /// @brief Turn off display.
    void turnOff();
    /// @brief Gets the last time something is displayed.
    ulong getMsLastDisplay() { return msLastDisplay; }
    /// @brief Set time interval in msec after which display will turn off if there is no activity.
    /// @param itv Time interval in milliseconds. 0 - don't turn off display.
    void setItvAutoTurnOff(ulong itv);
    /// @brief Gets time interval in msec after which display will turn off if there is no activity.
    ulong getItvTurnOffDisplay() { return itvTurnOffDisplay; }
    /// @brief Use the last version of itvTurnOffDisplay.
    void setItvAutoTurnOffPrev() { setItvAutoTurnOff(itvTurnOffDisplayPrev); }
    /// @brief Turn off display if there were no actions - menu() - for more than itvTurnOffDisplay msecs.
    /// @param ms Current time in milliseconds.
    /// @return true if the display is turned off.
    bool autoTurnOffIN(ulong ms);
};
