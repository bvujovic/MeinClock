//* test deep sleep with read/write to RTC memory

#include <Arduino.h>

const byte pinBtnLeft = D7;

// uint32_t counter;

struct SleepMem
{
    byte app;
    uint16_t counter;
} sleepMem;

void setup()
{
    pinMode(pinBtnLeft, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.println("\n***");
    // Serial.println(millis());

    ESP.rtcUserMemoryRead(0, (uint32_t *)&sleepMem, sizeof(SleepMem));

    // if (!ESP.rtcUserMemoryRead(0, &sleepMem, sizeof(SleepMem)))
    // {
    //     Serial.println("RTC read failed!");
    //     // ESP.deepSleep(0);
    // }
    // else
    // {

    // counter++;
    sleepMem.counter++;
    Serial.printf("app %d\n", sleepMem.app);
    Serial.printf("counter++: %d\n", sleepMem.counter);
    if (digitalRead(pinBtnLeft) == LOW)
    {
        Serial.printf("counter: %d\n", sleepMem.counter);
    }
    else
    {
        if (sleepMem.counter < 105)
        {
            if (!ESP.rtcUserMemoryWrite(0, (uint32_t *)&sleepMem, sizeof(SleepMem)))
            {
                Serial.println("RTC write failed!");
            }
            else
                ESP.deepSleep(2000000);
        }
        else if (sleepMem.counter > 1000000)
        {
            sleepMem.counter = 100;
            if (!ESP.rtcUserMemoryWrite(0, (uint32_t *)&sleepMem, sizeof(SleepMem)))
            {
                Serial.println("RTC write failed!");
            }
            else
            {
                Serial.println("Counting started");
                ESP.deepSleep(2000000);
            }
        }
    }
    // }
    Serial.println("Setup end");
}

void loop()
{
    delay(100);
    if (digitalRead(pinBtnLeft) == LOW)
    {
        sleepMem.app++;
        sleepMem.counter = 100;
        ESP.rtcUserMemoryWrite(0, (uint32_t *)&sleepMem, sizeof(SleepMem));
    }
}