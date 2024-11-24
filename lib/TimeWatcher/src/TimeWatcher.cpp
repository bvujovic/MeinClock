#include "TimeWatcher.h"

bool TimeWatcher::initTime()
{
    buzzGetTime(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    auto msStart = millis();
    while (WiFi.status() != WL_CONNECTED && millis() < msStart + 10000) // wait max 10 secs
        delay(250);
    //? delay(100);
    if (WiFi.status() == WL_CONNECTED)
    {
        bool res = getCurrentTime();
        wiFiOff();
        return buzzGetTime(res);
        // buzzGetTime(res);
        // return res;
    }
    else
        return buzzGetTime(false);
    // {
    //     buzzGetTime(false);
    //     return false;
    // }
}

bool TimeWatcher::getCurrentTime()
{
    const ulong maxTrySetTime = 3;
    ulong cntTrySetTime = 0;
    while (!ntp.setSNTPtime() && cntTrySetTime++ < maxTrySetTime)
        ;
    return cntTrySetTime < maxTrySetTime;
}

void TimeWatcher::wiFiOff()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
}

int TimeWatcher::refresh(ulong ms, Time &t)
{
    now = ntp.getTime(1.0, 1);
    t.minutes = now.hour;
    t.seconds = now.minute;
    return 0;
}

void TimeWatcher::buzzIN()
{
    if (now.second == 0 && prevMinutesBuzzIN != now.minute)
    {
        prevMinutesBuzzIN = now.minute;
        for (BuzzData b : buzzes)
            if (b.minutes == now.minute)
                buzzer->blink(b.itvBuzz, b.countBuzz);
    }
}

bool TimeWatcher::buzzGetTime(bool success)
{
    if (success)
        buzzer->blink(100, 2);
    else
        buzzer->blink(1000, 1);
    return success;
}
