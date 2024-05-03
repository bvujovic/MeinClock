#pragma once

// #include <Arduino.h>
#include "Time.h"
#include "ButtonEnums.h"
typedef unsigned long ulong;

/// @brief Measuring time from 00:00.
class Stopwatch
{
private:
    /// @brief Is the stopwatch paused.
    bool isPaused;
    /// @brief Time when stopwatch is started (in milliseconds).
    ulong msStartTime;
    /// @brief Time previously measured from start() to pause() - maybe multiple times.
    ulong msTimePrev;

    /// @brief Pause the stopwatch if it's started or start/resume if it's not.
    /// @param ms Current time in milliseconds.
    void toggleStartPause(ulong ms) { isPaused ? start(ms) : pause(ms); }
    /// @brief Start the stopwatch.
    /// @param ms Current time in milliseconds.
    void start(ulong ms) { msStartTime = ms; isPaused = false; }
    /// @brief Pause the stopwatch.
    /// @param ms Current time in milliseconds.
    void pause(ulong ms) { isPaused = true; msTimePrev += ms - msStartTime; }
    /// @brief Set the time to 00:00 and stop/pause.
    void reset() { msTimePrev = 0; isPaused = true; }
    /// @brief Calculate measured time in milliseconds.
    /// @param ms Current time
    ulong getTime(ulong ms);
    /// @brief Write current time to Time structure.
    /// @param ms Current time
    void writeTime(ulong ms, Time &time);

public:
    Stopwatch();

    /// @brief Is the stopwatch paused.
    bool IsPaused() { return isPaused; }

    /// @brief Set the time (t) to correct value based on current time, start time etc.
    /// @param ms Current time in milliseconds.
    /// @param t Time structure: h, min, sec.
    void refresh(ulong ms, Time &t) { writeTime(ms, t); }
    /// @brief Handle button clicks.
    /// @param ms Current time in milliseconds.
    /// @param idxBtn Index of a button - which button is clicked.
    /// @param click Short/long click.
    void buttons(ulong ms, int idxBtn, ClickType click);
};
