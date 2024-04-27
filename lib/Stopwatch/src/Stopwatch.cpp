#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    reset();
}

void Stopwatch::buttons(ulong ms, int idxBtn, ClickType click)
{
    if (idxBtn == BtnCenter)
    {
        if (click == ShortClick)
            togglePlayPause(ms);
        if (click == LongClick)
            reset();
    }
}

ulong Stopwatch::getTime(ulong ms)
{
    return msTimePrev + (!isPaused ? ms - msStartTime : 0);
}

void Stopwatch::writeTime(ulong ms, Time &time)
{
    ms = getTime(ms);
    time.fromMilliSeconds(ms);
}
