#pragma once

#include <Blinky.h> // https://github.com/bvujovic/ArduinoLibs/tree/main/Blinky
#include "ESP8266WiFi.h"
#include "CredWiFi.h"
#include <SNTPtime.h>
#include "Time.h"

// bool isTimeSet;
// ulong cntTrySetTime = 0;
// const ulong maxTrySetTime = 3;

// typedef unsigned char byte;
// typedef unsigned long ulong;

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
    // TODO ovde je ponovo definisan bazer u projektu - srediti da postoji samo jedna definicija
    Blinky buzzer = Blinky(D3, true);

    bool getCurrentTime();
    void buzzGetTime(bool success);
    void wiFiOff();

public:
    TimeWatcher();

    bool initTime();
    int refresh(ulong ms, Time &t);
    void buzzIN();
};
