#pragma once

#include <Blinky.h> // https://github.com/bvujovic/ArduinoLibs/tree/main/Blinky

#include "ESP8266WiFi.h"
#include "CredWiFi.h"
#include <SNTPtime.h>
SNTPtime ntp;
StrDateTime now;

bool isTimeSet;
ulong cntTrySetTime = 0;
const ulong maxTrySetTime = 3;

// typedef unsigned char byte;
// typedef unsigned long ulong;

struct BuzzData
{
    BuzzData(byte minutes, byte countBuzz, ulong msBuzz)
        : minutes(minutes), countBuzz(countBuzz), msBuzz(msBuzz)
    {
    }
    byte minutes;
    byte countBuzz;
    ulong msBuzz;
};

class TimeWatcher
{
private:
    bool on = false;
    BuzzData buzzes[6] = {
        BuzzData(0, 2, 1000),
        BuzzData(10, 1, 333),
        BuzzData(20, 2, 333),
        BuzzData(30, 1, 1000),
        BuzzData(40, 1, 333),
        BuzzData(50, 2, 333)};
    Blinky buzzer = Blinky(D3, true);

    void getCurrentTime();
    void wiFiOff();

public:
    bool IsItOn() { return on; }
    void turnOn() { on = true; }
    void turnOff() { on = false; }

    TimeWatcher();
};
