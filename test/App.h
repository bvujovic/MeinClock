#pragma once

#include "Time.h"
#include "ButtonEnums.h"

typedef unsigned long ulong;

class App
{

public:
    virtual void refresh(ulong ms, Time &t) = 0;
    virtual void buttons(ulong ms, int idxBtn, ClickType click) = 0;
};
