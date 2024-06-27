#pragma once

#include <Blinky.h> // https://github.com/bvujovic/ArduinoLibs/tree/main/Blinky
#include "ESP8266WiFi.h"
#include "CredWiFi.h"
#include <SNTPtime.h>
#include "Time.h"

struct BuzzData
{
    BuzzData(byte minutes, byte countBuzz, ulong itvBuzz)
        : minutes(minutes), countBuzz(countBuzz), itvBuzz(itvBuzz)
    {
    }
    byte minutes;
    byte countBuzz;
    ulong itvBuzz;
};

class TimeWatcher
{
private:
    SNTPtime ntp;
    StrDateTime now;
    BuzzData buzzes[6] = {
        BuzzData(0, 2, 1000),
        BuzzData(10, 1, 333),
        BuzzData(20, 2, 333),
        BuzzData(30, 1, 1000),
        BuzzData(40, 1, 333),
        BuzzData(50, 2, 333)};
    Blinky *buzzer = NULL;
    byte prevMinutesBuzzIN = 123;

    bool getCurrentTime();
    void buzzGetTime(bool success);
    void wiFiOff();

public:
    bool initTime();
    int refresh(ulong ms, Time &t);
    void buzzIN();
    void setBuzzer(Blinky *b) { buzzer = b; }
};
