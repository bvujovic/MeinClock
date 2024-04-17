#pragma once

#include "Arduino.h"
#include "WString.h"
#include <LinkedList.h>

struct MenuItem
{
    String Name;
    MenuItem *Parent;
    LinkedList<MenuItem *> *Items;
    MenuItem(String name, MenuItem *parent) { Name = name; Parent = parent; Items = NULL; }
};

#define MI_ROOT "root"
#define MI_COUNTDOWN "Countdown"
#define MI_TIMEWATCH "TimeWatch"
#define MI_STOPWATCH "Stopwatch"
#define MI_TURNOFFSCR "TurnOffScr"
#define MI_AFTER5SEC "After5sec"
#define MI_AFTER5MIN "After5min"
#define MI_NEVER "Never"

class Controller
{
private:
    MenuItem *menu;
    MenuItem *miCurrent;
    int idxPage;

public:
    Controller();

    // MenuItem getMenuItem(int idx) { return menu->Items->get(idx); }
    // String getMenuItem(int idx) { return menu->Items->get(idx)->Name; }

    String getMenuItemName(int idx);
    LinkedList<String> *getMenuPage();
    String getCurrentMenuName() { return miCurrent->Name; }

    void goToRoot();
    void goToNextPage();
    void goToParentMenu();
    void goToItem(int idxItem);
};
