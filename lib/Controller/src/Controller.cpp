#include "Controller.h"

Controller::Controller()
{
    menu = new MenuItem("root", NULL);
    MenuItem *mi;
    menu->Items = new LinkedList<MenuItem *>();
    MenuItem *miCountdown = new MenuItem("Countdown", menu);
    miCountdown->Items = new LinkedList<MenuItem *>();
    miCountdown->Items->add(new MenuItem("test", miCountdown));
    menu->Items->add(miCountdown);
    menu->Items->add(new MenuItem("TimeWatch", menu));
    menu->Items->add(new MenuItem("Stopwatch", menu));
    mi = new MenuItem("TurnOffScr", menu);
    LinkedList<MenuItem *> *items = new LinkedList<MenuItem *>();
    items->add(new MenuItem("After5sec", mi));
    items->add(new MenuItem("After5min", mi));
    items->add(new MenuItem("Never", mi));
    mi->Items = items;
    menu->Items->add(mi);
    goToRoot();
}

LinkedList<String> *Controller::getMenuPage()
{
    if (miCurrent == NULL || miCurrent->Items == NULL || miCurrent->Items->size() == 0)
        return NULL;
    LinkedList<String> *items = new LinkedList<String>();
    int n = miCurrent->Items->size();
    int i = idxPage * 3;
    if (n - i > 3)
        n = 3;
    Serial.println(i);
    Serial.println(n);
    for (; i < n; i++)
    {
        Serial.println(i);
        items->add(miCurrent->Items->get(i)->Name);
    }
    return items;
}

void Controller::goToNextPage()
{
    int nItems = miCurrent->Items->size();
    int nPages = (nItems - 1) / 3;
    if (idxPage < nPages)
        idxPage++;
    else
        idxPage = 0;
}

void Controller::goToParentMenu()
{
    if (miCurrent->Parent != NULL)
    {
        miCurrent = miCurrent->Parent;
        idxPage = 0;
    }
}

void Controller::goToRoot()
{
    miCurrent = menu;
    idxPage = 0;
}

void Controller::goToItem(int idxItem)
{
    idxItem = idxItem + idxPage * 3;
    if (miCurrent->Items == nullptr || miCurrent->Items->size() <= idxItem)
        return;
    miCurrent = miCurrent->Items->get(idxItem);
    idxPage = 0;
}
