#pragma once

#include "Arduino.h"
#include "WString.h"
#include <LinkedList.h>

struct MenuItem
{
    String Name;
    LinkedList<MenuItem *> *Items;
    MenuItem *Parent;
    MenuItem(String name, MenuItem *parent) { Name = name; Parent = parent; }
};

class Controller
{
private:
    MenuItem *menu;
    MenuItem *miCurrent;
    int idxPage;

public:
    Controller();

    // MenuItem getMenuItem(int idx) { return menu->Items->get(idx); }
    String getMenuItem(int idx) { return menu->Items->get(idx)->Name; }
    LinkedList<String> *getMenuPage();
    String getCurrentMenu() { return miCurrent->Name; }

    void goToRoot();
    void goToNextPage();
    void goToParentMenu();
    void goToItem(int idxItem);
};
