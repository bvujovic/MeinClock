#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    reset();
}

ulong Stopwatch::getTime(ulong ms)
{
    return msTimePrev + (!isPaused ? ms - msStartTime : 0);
}

void Stopwatch::writeTime(ulong ms, Time *time)
{
    ms = getTime(ms);
    ulong sec = ms / 1000;
    time->minutes = sec / 60;
    time->seconds = sec % 60;
}
