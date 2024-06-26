//* Mein Clock - Time Watcher
//* Device beeps every hour (2 long beeps), half an hour (1 long beep), 10min (1 or 2 short beeps)

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "CredWiFi.h"

#include <Blinky.h> // https://github.com/bvujovic/ArduinoLibs/tree/main/Blinky
Blinky led = Blinky::create();
Blinky buzzer = Blinky(D3, true);

#include <SNTPtime.h>
SNTPtime ntp;
StrDateTime now;

bool isTimeSet;
ulong cntTrySetTime = 0;
const ulong maxTrySetTime = 3;

// Signal that time is not set so device can't run properly.
void noTimeError()
{
  buzzer.blinkErrorMajor();
  led.on();
}

void getCurrentTime()
{
  isTimeSet = false;
  cntTrySetTime = 0;
  while (!ntp.setSNTPtime() && cntTrySetTime++ < maxTrySetTime)
    Serial.print("*");
  Serial.println();
  if (cntTrySetTime < maxTrySetTime)
  {
    isTimeSet = true;
    Serial.println("Time set");
  }
  else
  {
    Serial.println("Time NOT set");
    noTimeError();
  }
}

void wiFiOff()
{
  Serial.println("Turning WiFi OFF...");
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(100);
  Serial.println("WiFi OFF");
  led.off();
}

void setup()
{
  pinMode(buzzer.getPin(), OUTPUT);
  pinMode(led.getPin(), OUTPUT);
  buzzer.off();
  led.on();
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to network: ");
  Serial.println(WIFI_SSID);
  delay(100);

  getCurrentTime();
  wiFiOff();
}

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

BuzzData buzzes[] = {
    BuzzData(0, 2, 1000),
    BuzzData(10, 1, 333),
    BuzzData(20, 2, 333),
    BuzzData(30, 1, 1000),
    BuzzData(40, 1, 333),
    BuzzData(50, 2, 333),
};

void loop()
{
  delay(1000);
  now = ntp.getTime(1.0, 1);
  // now.Println();

  if (now.second == 0)
  {
    for (BuzzData b : buzzes)
      if(b.minutes == now.minute)
        buzzer.blink(b.msBuzz, b.countBuzz);
  }
}
