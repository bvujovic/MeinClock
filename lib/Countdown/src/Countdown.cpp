#include "Countdown.h"
// #include <Sleeper.h>
// #include <Common.h>

void Countdown::addMenuItem(const CdItem &it)
{
    items.add(it);
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

int Countdown::refresh(uint32_t ms, Time &t)
{
    if (state == CdMenu)
        return 0;
    else
    {
        //B ulong itv = currentItem.CDownTime.toMilliSeconds() - (ms - msStartTime);
        uint32_t itv = getSleepInterval(ms);
        t.fromMilliSeconds(itv + 1000);
        // if countdown is still ongoing, itv represents number of msecs left and it will be small positive number
        // when msecs passed are greater then msecs of selected item, since itv is unsigned and can't be negative,
        // itv will be some very large number
        return itv < __LONG_MAX__ ? 0 : 1;
    }
}

void Countdown::buttons(uint32_t ms, int idxBtn, ClickType click)
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
    // B
    // if (click == ShortClick && idxBtn == CenterButton)
    // {
    //     ulong itv = currentItem.CDownTime.toMilliSeconds() - (ms - msStartTime);
    //     Sleeper::setMem(SleepMem(AppCountdown, idxPage, 0));
    //     Sleeper::sleep(itv);
    // }
}
