//* test deep sleep with read/write to RTC memory using Sleeper class

#include <Arduino.h>
#include "Sleeper.h"

const byte pinBtnLeft = D7;

void setup()
{
    pinMode(pinBtnLeft, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.println("\n***");

    Sleeper::memLoad();
    SleepMem& mem = Sleeper::getMem();
    Serial.printf("counter: %d\n", mem.counter);

    if (mem.counter >= 100 && mem.counter < 105)
    {
        Sleeper::counterInc();
        // mem.counter++;
        Serial.printf("passed: %lu msecs\n", millis());
        Sleeper::nap();
    }
    else
    {
        Serial.println("Sleep ended.");
        mem.counter = 100;
        Sleeper::memSave();
    }
}

void loop()
{
    delay(100);
}
