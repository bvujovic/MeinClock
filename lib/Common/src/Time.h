#pragma once

typedef unsigned long ulong;
typedef unsigned char byte;

struct Time
{
    byte hours;
    byte minutes;
    byte seconds;
    byte centSec;

    Time()
    {
        hours = minutes = seconds = centSec = 0;
    }

    Time(byte min, byte sec)
    {
        minutes = min;
        seconds = sec;
    }

    ulong toMilliSeconds() { return (((hours * 60) + minutes * 60) + seconds) * 1000; }

    void fromMilliSeconds(ulong itv)
    {
        ulong sec = itv / 1000;
        minutes = sec / 60;
        seconds = sec % 60;
        centSec = itv / 10 % 100;
    }
};

enum DisplayTime
{
    /// @brief Hours, minutes
    HourMin,
    /// @brief Minutes, seconds
    MinSec,
    /// @brief Minutes, seconds, centiseconds
    MinSecCent
};
