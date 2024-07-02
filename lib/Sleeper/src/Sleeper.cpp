#include "Sleeper.h"

Sleeper::Sleeper()
{
}

void Sleeper::nap()
{
    ESP.deepSleep(2000000);
}
