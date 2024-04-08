#include "TimeWatcher.h"

TimeWatcher::TimeWatcher()
{
    pinMode(buzzer.getPin(), OUTPUT);
    buzzer.off();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        // Serial.print(".");
    }
    // Serial.println("");
    // Serial.print("Connected to network: ");
    // Serial.println(WIFI_SSID);
    delay(100);
    getCurrentTime();
    wiFiOff();
}

void TimeWatcher::getCurrentTime()
{
    isTimeSet = false;
    cntTrySetTime = 0;
    while (!ntp.setSNTPtime() && cntTrySetTime++ < maxTrySetTime)
        ; // Serial.print("*");
    //   Serial.println();
    if (cntTrySetTime < maxTrySetTime)
    {
        isTimeSet = true;
        // Serial.println("Time set");
    }
    else
    {
        // Serial.println("Time NOT set");
        // noTimeError();
    }
}

void wiFiOff()
{
    //   Serial.println("Turning WiFi OFF...");
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(100);
    //   Serial.println("WiFi OFF");
    //   led.off();
}
