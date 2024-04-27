#pragma once

typedef unsigned long ulong;
typedef unsigned char byte;

struct Time
{
    byte hours;
    byte minutes;
    byte seconds;

    Time()
    {
        minutes = 0;
        seconds = 0;
    }
    Time(byte min, byte sec)
    {
        minutes = min;
        seconds = sec;
    }
    // Time(byte h, byte m, byte s)
    // {
    //     hours = h;
    //     minutes = m;
    //     seconds = s;
    // }

    ulong toMilliSeconds() { return (((hours * 60) + minutes * 60) + seconds) * 1000; }
    void fromMilliSeconds(ulong itv)
    {
        ulong sec = itv / 1000;
        minutes = sec / 60;
        seconds = sec % 60;
    }
};

enum DisplayTime
{
    HourMin,
    MinSec
};
