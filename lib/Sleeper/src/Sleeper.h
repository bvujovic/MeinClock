#pragma once

// #include <sys/_stdint.h>
#include <Esp.h>

/// @brief Data that will be saved/loaded before/after deep sleep.
struct SleepMem
{
    /// @brief ID of an app that asked for a nap.
    uint8_t app;
    /// @brief Nap counter.
    uint16_t counter;
};

class Sleeper
{
private:
    SleepMem sleepMem;

public:
    Sleeper(/* args */);

    SleepMem& GetMem() { return sleepMem; }
    void CounterInc() { sleepMem.counter++; }

    /// @brief DeepSleep for a 2 seconds minus time for wakeup and setup()
    void nap();
};
