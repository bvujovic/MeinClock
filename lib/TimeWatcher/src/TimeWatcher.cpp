#include "TimeWatcher.h"

TimeWatcher::TimeWatcher()
{
    pinMode(buzzer.getPin(), OUTPUT);
    buzzer.off();
}

bool TimeWatcher::initTime()
{
    buzzGetTime(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
        delay(250);
    delay(100);
    if (WiFi.status() == WL_CONNECTED)
    {
        bool res = getCurrentTime();
        wiFiOff();
        buzzGetTime(res);
        return res;
    }
    buzzGetTime(false);
    return false;
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
  if (now.second == 0)
  {
    for (BuzzData b : buzzes)
      if(b.minutes == now.minute)
        buzzer.blink(b.itvBuzz, b.countBuzz);
  }
}

void TimeWatcher::buzzGetTime(bool success)
{
    if (success)
        buzzer.blink(100, 2);
    else
        buzzer.blink(1000, 1);
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
