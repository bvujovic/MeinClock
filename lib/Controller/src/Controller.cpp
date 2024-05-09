#include "Controller.h"

Controller::Controller()
{
    menu = new MenuItem(MI_ROOT, NULL);

    menu->Items = new LinkedList<MenuItem *>();
    menu->Items->add(new MenuItem(MI_COUNTDOWN, menu));
    menu->Items->add(new MenuItem(MI_TIMEWATCH, menu));
    menu->Items->add(new MenuItem(MI_STOPWATCH, menu));
    {
        MenuItem *mi = new MenuItem(MI_TURNOFFSCR, menu);
        LinkedList<MenuItem *> *items = new LinkedList<MenuItem *>();
        items->add(new MenuItem("After 5s", mi));
        items->add(new MenuItem("After 10s", mi));
        items->add(new MenuItem("After 20s", mi));
        items->add(new MenuItem("After 1m", mi));
        items->add(new MenuItem("After 3m", mi));
        items->add(new MenuItem("After 10m", mi));
        mi->Items = items;
        menu->Items->add(mi);
    }
    {
        MenuItem *mi = new MenuItem(MI_GOTOSLEEP, menu);
        LinkedList<MenuItem *> *items = new LinkedList<MenuItem *>();
        items->add(new MenuItem("After 1m", mi));
        items->add(new MenuItem("After 3m", mi));
        items->add(new MenuItem("After 5m", mi));
        mi->Items = items;
        menu->Items->add(mi);
    }
    goToRoot();
}

String Controller::getMenuItemName(int idx)
{
    idx = idxPage * 3 + idx;
    if (miCurrent == NULL || miCurrent->Items == NULL || idx >= miCurrent->Items->size())
        return "";
    else
        return miCurrent->Items->get(idx)->Name;
}

LinkedList<String> *Controller::getMenuPage()
{
    if (miCurrent == NULL || miCurrent->Items == NULL || miCurrent->Items->size() == 0)
        return NULL;
    LinkedList<String> *items = new LinkedList<String>();
    int n = miCurrent->Items->size();
    int i = idxPage * 3;
    if (n - i > 3)
        n = i + 3;
    for (; i < n; i++)
        items->add(miCurrent->Items->get(i)->Name);
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
    if (miCurrent == NULL || miCurrent->Items == NULL || miCurrent->Items->size() <= idxItem)
        return;
    miCurrent = miCurrent->Items->get(idxItem);
    idxPage = 0;
}

int Controller::timeStrToSec(const String &s)
{
    // example for s: "After 1m" or "After 20s"
    int idx = s.lastIndexOf(' ');
    if (idx == -1)
        return 0;
    String t = s.substring(idx + 1);
    return t.toInt() * (*(s.end() - 1) == 'm' ? 60 : 1);
}
