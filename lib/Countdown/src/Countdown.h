#pragma once

// #include <Arduino.h>
#include "Time.h"
#include "ButtonEnums.h"
#include "WString.h"
#include <LinkedList.h>

typedef unsigned long ulong;

/// @brief Countdown app states: Menu, Countdown
enum CdAppState
{
    /// @brief Countdown app displays menu
    CdMenu,
    /// @brief Countdown app is in countdown mode
    CdCountdown
};

struct CdItem
{
    Time CDownTime;
    String Name;
    // CdItem *Next;
    //CdItem (String name, Time time) { Name = name; CDownTime = time; };
};

class Countdown
{
private:
    CdAppState state = CdMenu;
    // LinkedList<CdItem> *items = new LinkedList<CdItem>();
    LinkedList<CdItem> items;
    /// @brief Time when Countdown is started (in milliseconds).
    ulong msStartTime;
    CdItem currentItem;

public:
    Countdown();

    CdAppState getState() { return state; } 
    void setState(CdAppState state) { this->state = state; } 
    // void start(ulong ms) { msStartTime = ms; }
    
    LinkedList<String> *getMenuPage();

    int refresh(ulong ms, Time &t);
    void buttons(ulong ms, int idxBtn, ClickType click);
};
