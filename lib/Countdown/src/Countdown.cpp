#include "Countdown.h"

Countdown::Countdown()
{
    items.add(CdItem{Time(0, 50), "Kafa"});
    items.add(CdItem{Time(4, 0), "Jaja"});
    items.add(CdItem{Time(7, 0), "Bleja"});
}

LinkedList<String> *Countdown::getMenuPage()
{
    LinkedList<String> *page = new LinkedList<String>();
    for (int i = 0; i < items.size(); i++)
        page->add(items.get(i).Name);
    return page;
}

int Countdown::refresh(ulong ms, Time &t)
{
    if (state == CdMenu)
        return 0;
    else
    {
        ulong itv = currentItem.CDownTime.toMilliSeconds() - (ms - msStartTime);
        if (itv < __LONG_MAX__)
        {
            t.fromMilliSeconds(itv);
            return 0;
        }
        else
            return 1;
    }
}

void Countdown::buttons(ulong ms, int idxBtn, ClickType click)
{
    if (click == ShortClick)
    {
        if (state == CdMenu)
        {
            msStartTime = ms;
            currentItem = items.get(idxBtn);
            state = CdCountdown;
        }
    }
}
