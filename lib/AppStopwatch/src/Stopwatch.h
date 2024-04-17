#pragma once

#include <Arduino.h>
#include "Time.h"

/// @brief Measuring time. Methods: start(), stop(), reset().
class Stopwatch
{
private:
    // /// @brief Should milliseconds be displayed or not.
    // bool displayMS;
    bool isPaused;
    /// @brief Time when stopwatch is started (in milliseconds).
    ulong msStartTime;
    /// @brief Time previously measured from start() to pause() - maybe multiple times.
    ulong msTimePrev;

public:
    Stopwatch();
    void start(ulong ms) { msStartTime = ms; isPaused = false; }
    void pause(ulong ms) { isPaused = true; msTimePrev += ms - msStartTime; }
    void reset()
    {
        msTimePrev = 0;
        isPaused = true;
    }
    /// @brief Calculate measured time in milliseconds.
    /// @param ms Current time
    ulong getTime(ulong ms);
    /// @brief Write current time to Time structure.
    /// @param ms Current time
    void writeTime(ulong ms, Time *time);
};
