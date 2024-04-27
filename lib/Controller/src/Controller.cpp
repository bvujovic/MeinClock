#include "Controller.h"

Controller::Controller()
{
    menu = new MenuItem(MI_ROOT, NULL);

    menu->Items = new LinkedList<MenuItem *>();
    {
        MenuItem *miCountdown = new MenuItem(MI_COUNTDOWN, menu);
        // miCountdown->Items = new LinkedList<MenuItem *>();
        // miCountdown->Items->add(new MenuItem("test", miCountdown));
        menu->Items->add(miCountdown);
    }
    menu->Items->add(new MenuItem(MI_TIMEWATCH, menu));
    menu->Items->add(new MenuItem(MI_STOPWATCH, menu));
    {
        MenuItem *mi = new MenuItem(MI_TURNOFFSCR, menu);
        LinkedList<MenuItem *> *items = new LinkedList<MenuItem *>();
        items->add(new MenuItem(MI_AFTER5SEC, mi));
        items->add(new MenuItem(MI_AFTER5MIN, mi));
        items->add(new MenuItem(MI_NEVER, mi));
        mi->Items = items;
        menu->Items->add(mi);
    }
    goToRoot();
}

String Controller::getMenuItemName(int idx)
{
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
        n = 3;
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
