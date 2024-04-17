#include <Arduino.h>
#include <LinkedList.h>

#include "Btn.h"
Btn btnLeft(D7);
Btn btnCenter(D6);
Btn btnRight(D5);
Btn buttons[] = {btnLeft, btnCenter, btnRight};

#include "Controller.h"
Controller ctrl;

#include "MyDisplay.h"
MyDisplay disp;

#include "Stopwatch.h"
Stopwatch sw;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n*** MEIN CLOCK ***");
    disp.setItvAutoTurnOff(10 * 1000);
    disp.menu(ctrl.getMenuPage());
}

bool isAppActive = false;
ClickType click;
int idxBtn;

//* STOPWATCH TEST
ulong msStart;
Time t;

void loop()
{
    delay(10);
    ulong ms = millis();
    disp.autoTurnOff(ms);

    idxBtn = -1;
    for (size_t i = 0; i < 3; i++)
        if ((click = buttons[i].check(ms)) != None)
        {
            idxBtn = i;
            break;
        }

    if (isAppActive)
    {
        int sec = (ms - msStart) / 1000;
        t.seconds = sec % 60;
        t.minutes = sec / 60;
        disp.time(&t);

        if (idxBtn == 1)
            isAppActive = false;
        return;
    }

    if (idxBtn != -1)
    {
        if (!disp.IsItOn())
        {
            disp.turnOn();
            disp.menu(ctrl.getMenuPage());
            return;
        }
        // Serial.printf("%d, %s\n", idxBtn, ctrl.getCurrentMenuName().c_str());

        if (click == ShortClick && ctrl.getCurrentMenuName() == MI_TURNOFFSCR)
        {
            if (ctrl.getMenuItemName(idxBtn) == MI_AFTER5SEC)
                disp.setItvAutoTurnOff(5 * 1000);
            if (ctrl.getMenuItemName(idxBtn) == MI_AFTER5MIN)
                disp.setItvAutoTurnOff(5 * 60 * 1000);
            if (ctrl.getMenuItemName(idxBtn) == MI_NEVER)
                disp.setItvAutoTurnOff(0);
            ctrl.goToParentMenu();
            disp.menu(ctrl.getMenuPage());
            return;
        }
        if (click == ShortClick && ctrl.getMenuItemName(idxBtn) == MI_STOPWATCH)
        {
            disp.setItvAutoTurnOff(0);
            msStart = ms;
            isAppActive = true;
            return;
        }
    }

    if (idxBtn == 0)
    {
        if (click == LongClick) // dugi klik
        {
            ctrl.goToParentMenu();
            // disp.menu(ctrl.getMenuPage());
        }
        if (click == ShortClick) // kratki klik
        {
            ctrl.goToItem(0);
        }
        disp.menu(ctrl.getMenuPage());
    }
    if (idxBtn == 1)
    {
        if (click == LongClick)
            ctrl.goToRoot();
        if (click == ShortClick)
            ctrl.goToItem(1);
        disp.menu(ctrl.getMenuPage());
    }
    if (idxBtn == 2)
    {
        if (click == LongClick)
            ctrl.goToNextPage();
        if (click == ShortClick)
            ctrl.goToItem(2);
        disp.menu(ctrl.getMenuPage());
    }
}
