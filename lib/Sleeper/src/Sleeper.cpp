#include "Sleeper.h"

SleepMem Sleeper::sleepMem;

void Sleeper::nap()
{
    memSave();
    uint32_t passed = 220 + millis();
    if (2000000 > passed)
        ESP.deepSleep(2000000 - passed);
    else
        ESP.deepSleep(1);
}
