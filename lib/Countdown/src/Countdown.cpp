#include "Countdown.h"

Countdown::Countdown()
{
    items.add(CdItem{Time(0, 50), "Kafa"});
    items.add(CdItem{Time(4, 0), "Jaja"});
    items.add(CdItem{Time(7, 0), "Bleja"});

    items.add(CdItem{Time(5, 0), "5min"});
    items.add(CdItem{Time(10, 0), "10min"});
    items.add(CdItem{Time(15, 0), "15min"});

    items.add(CdItem{Time(30, 0), "30min"});
    items.add(CdItem{Time(2, 00), "Gym S"});
    items.add(CdItem{Time(5, 00), "Gym L"});
}

LinkedList<String> *Countdown::getMenuPage()
{
    LinkedList<String> *page = new LinkedList<String>();
    int n = items.size();
    int i = idxPage * 3;
    if (n - i > 3)
        n = i + 3;
    for (; i < n; i++)
        page->add(items.get(i).Name);
    return page;
}

void Countdown::goToNextPage()
{
    int nItems = items.size();
    int nPages = (nItems - 1) / 3;
    if (idxPage < nPages)
        idxPage++;
    else
        idxPage = 0;
}

int Countdown::refresh(ulong ms, Time &t)
{
    if (state == CdMenu)
        return 0;
    else
    {
        ulong itv = currentItem.CDownTime.toMilliSeconds() - (ms - msStartTime);
        t.fromMilliSeconds(itv + 1000);
        // if countdown is still ongoing itv represends number of msecs left and it will be small positive number
        // when msecs passed are greater then msecs of selected item, since itv is unsigned and can't be negative,
        // itv will be some very large number 
        return itv < __LONG_MAX__ ? 0 : 1;
    }
}

void Countdown::buttons(ulong ms, int idxBtn, ClickType click)
{
    if (click == ShortClick)
    {
        if (state == CdMenu) // start countdown for selected item
        {
            msStartTime = ms;
            currentItem = items.get(idxPage * 3 + idxBtn);
            state = CdCountdown;
        }
    }
    if (click == LongClick && idxBtn == RightButton && state == CdMenu)
        goToNextPage();
}
