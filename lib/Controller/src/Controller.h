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
#define MI_GOTOSLEEP "GoToSleep"

class Controller
{
private:
    MenuItem *menu;
    MenuItem *miCurrent;
    int idxPage;

public:
    Controller();

    String getMenuItemName(int idx);
    LinkedList<String> *getMenuPage();
    String getCurrentMenuName() { return miCurrent->Name; }

    void goToRoot();
    void goToNextPage();
    void goToParentMenu();
    void goToItem(int idxItem);

    static int timeStrToSec(const String &s);
};
