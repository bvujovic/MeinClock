#pragma once

// #include <Arduino.h>
#include "Time.h"
#include "ButtonEnums.h"
#include "WString.h"
#include <LinkedList.h>

//B typedef unsigned long ulong;

/// @brief Countdown app states: Menu, Countdown
enum CdAppState
{
    CdMenu,      /// @brief Countdown app displays menu
    CdCountdown, /// @brief Countdown app is in countdown mode
};

/// @brief Item in Countdown menu
struct CdItem
{
    Time CDownTime;
    String Name;
    // CdItem *Next;
};

class Countdown
{
private:
    CdAppState state = CdMenu;
    // LinkedList<CdItem> *items = new LinkedList<CdItem>();
    LinkedList<CdItem> items;
    /// @brief Time when Countdown is started (in milliseconds).
    uint32_t msStartTime;
    CdItem currentItem;
    int idxPage = 0;

public:
    void addMenuItem(const CdItem &it);
    CdAppState getState() { return state; }
    void setState(CdAppState state) { this->state = state; }
    int getIdxPage() { return idxPage; }
    uint32_t getSleepInterval(uint32_t ms) { return currentItem.CDownTime.toMilliSeconds() - (ms - msStartTime); }
    void goToNextPage();

    LinkedList<String> *getMenuPage();

    int refresh(uint32_t ms, Time &t);
    void buttons(uint32_t ms, int idxBtn, ClickType click);
};
