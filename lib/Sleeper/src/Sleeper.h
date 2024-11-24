#pragma once

#include <Esp.h>

/// @brief Data that will be saved/loaded before/after deep sleep.
struct SleepMem
{
    SleepMem()
    {
        counter = data = app = 0;
    }
    SleepMem(uint8_t app, uint8_t data, uint16_t counter)
    {
        this->app = app;
        this->data = data;
        this->counter = counter;
    }

    /// @brief ID of an app that asked for a nap/sleep.
    uint8_t app;
    /// @brief Data that writes/reads an app that asked for a nap/sleep.
    uint8_t data;
    /// @brief Nap counter.
    uint16_t counter;
};

/// @brief Handling deep sleep, save/load data before/after 2sec "nap"
class Sleeper
{
private:
    /// @brief Data that will be saved/loaded before/after deep sleep.
    static SleepMem sleepMem;

public:
    /// @brief Gets sleepMem structure.
    static SleepMem &getMem() { return sleepMem; }
    static void setMem(SleepMem mem) {}
    /// @brief Increments counter in sleepMem structure.
    static void counterInc() { sleepMem.counter++; }

    /// @brief Save sleepMem structure to RTC memory.
    static void memSave() { ESP.rtcUserMemoryWrite(0, (uint32_t *)&sleepMem, sizeof(SleepMem)); }
    /// @brief Load sleepMem structure from RTC memory.
    static void memLoad() { ESP.rtcUserMemoryRead(0, (uint32_t *)&sleepMem, sizeof(SleepMem)); }

    /// @brief DeepSleep for a 2 seconds minus time for wakeup and setup().
    static void nap();
    /// @brief Deep sleep for itv milliseconds.
    /// @param itv Deep sleep interval in milliseconds.
    static void sleep(uint32_t itv);
};
