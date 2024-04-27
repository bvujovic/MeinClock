#pragma once

// #include <Arduino.h>
#include "Time.h"
#include "ButtonEnums.h"
typedef unsigned long ulong;

/// @brief Measuring time. Methods: start(), stop(), reset().
class Stopwatch
{
private:
    bool isPaused;
    /// @brief Time when stopwatch is started (in milliseconds).
    ulong msStartTime;
    /// @brief Time previously measured from start() to pause() - maybe multiple times.
    ulong msTimePrev;

    void togglePlayPause(ulong ms) { isPaused ? start(ms) : pause(ms); }
    void start(ulong ms) { msStartTime = ms; isPaused = false; }
    void pause(ulong ms) { isPaused = true; msTimePrev += ms - msStartTime; }
    void reset() { msTimePrev = 0; isPaused = true; }
    /// @brief Calculate measured time in milliseconds.
    /// @param ms Current time
    ulong getTime(ulong ms);
    /// @brief Write current time to Time structure.
    /// @param ms Current time
    void writeTime(ulong ms, Time &time);

public:
    Stopwatch();

    void refresh(ulong ms, Time &t) { writeTime(ms, t); }
    void buttons(ulong ms, int idxBtn, ClickType click);
};
