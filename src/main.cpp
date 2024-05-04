#include <Arduino.h>
#include <LinkedList.h>

#include "Btn.h"
Btn btnLeft(D7);
Btn btnCenter(D6);
Btn btnRight(D5);
Btn buttons[] = {btnLeft, btnCenter, btnRight};

#include "Common.h"
Apps activeApp = NoApp;
#include "Controller.h"
Controller ctrl;
#include "MyDisplay.h"
MyDisplay disp;
#include "Blinky.h"
Blinky buzzer = Blinky(D3, true);

#include "Stopwatch.h"
Stopwatch sw;
#include "Countdown.h"
Countdown cd;

// Milliseconds in 1 second.
#define SEC (1000)
// Milliseconds in 1 minute.
#define MIN (60 * SEC)

void setup()
{
    Serial.begin(115200);
    pinMode(buzzer.getPin(), OUTPUT);
    Serial.println("\n*** MEIN CLOCK ***");
    disp.setItvAutoTurnOff(10 * SEC);
    disp.menu(ctrl.getMenuPage());
}

ClickType click;
int idxBtn;
Time t;
/// @brief How many msec from the last time something is displayed device should go to sleep.
ulong itvGoToSleep = 3 * MIN;

/// @brief Go to sleep if the time is not currently measured.
/// @param ms Current time.
void goToSleepIN(ulong ms)
{
    bool stopwatchOk = activeApp == AppStopwatch && sw.IsPaused();
    bool countdownOk = activeApp == AppCountdown && cd.getState() == CdMenu;
    ulong awakeTime = disp.getItvTurnOffDisplay() + itvGoToSleep;
    if (ms - disp.getMsLastDisplay() > awakeTime && (activeApp == NoApp || stopwatchOk || countdownOk))
    {
        buzzer.blink(1);
        disp.turnOff();
        ESP.deepSleep(0);
    }
}

void loop()
{
    delay(10);
    ulong ms = millis();
    disp.autoTurnOff(ms);
    goToSleepIN(ms);

    idxBtn = -1;
    for (size_t i = 0; i < 3; i++)
        if ((click = buttons[i].check(ms)) != None)
        {
            idxBtn = i;
            break;
        }

    // APPS
    if (activeApp == AppStopwatch)
    {
        sw.refresh(ms, t);
        disp.time(t, MinSec);
        sw.buttons(ms, idxBtn, click);
        if (idxBtn == CenterButton)
            disp.ItIsOn(ms);
        if (idxBtn == LeftButton)
        {
            activeApp = NoApp;
            // disp.setItvAutoTurnOffPrev();
            disp.menu(ctrl.getMenuPage());
        }
        return;
    }
    if (activeApp == AppCountdown)
    {
        if (idxBtn != -1)
        {
            if (!disp.IsItOn())
            {
                disp.turnOn();
                disp.menu(cd.getMenuPage());
                return;
            }
            else
                disp.ItIsOn(ms);
        }
        int res = cd.refresh(ms, t);
        if (cd.getState() == CdCountdown)
        {
            if (res == 1 && !disp.IsItOn())
                disp.turnOn();
            disp.time(t, MinSec);
        }
        if (res == 1) // TODO uvesti enum za rezultate refresh/buttons
        {
            buzzer.blink(3);
            cd.setState(CdMenu);
            disp.menu(cd.getMenuPage());
        }
        cd.buttons(ms, idxBtn, click);
        if (idxBtn == RightButton && click == LongClick && cd.getState() == CdMenu)
            disp.menu(cd.getMenuPage());
        if (idxBtn == LeftButton && click == LongClick)
        {
            if (cd.getState() == CdMenu)
            {
                activeApp = NoApp;
                // disp.setItvAutoTurnOffPrev();
                disp.menu(ctrl.getMenuPage());
            }
            if (cd.getState() == CdCountdown)
            {
                cd.setState(CdMenu);
                disp.menu(cd.getMenuPage());
            }
        }
        return;
    }

    // MENU
    if (idxBtn != -1)
    {
        // click & display is off -> turn on display
        if (!disp.IsItOn())
        {
            disp.turnOn();
            disp.menu(ctrl.getMenuPage());
            return;
        }
        // Serial.printf("%d, %s\n", idxBtn, ctrl.getCurrentMenuName().c_str());

        if (click == ShortClick && ctrl.getCurrentMenuName() == MI_TURNOFFSCR)
        {
            int sec = Controller::timeStrToSec(ctrl.getMenuItemName(idxBtn));
            if (sec > 0)
            {
                disp.setItvAutoTurnOff(sec * SEC);
                ctrl.goToParentMenu();
                disp.menu(ctrl.getMenuPage());
            }
            return;
        }
        if (click == ShortClick && ctrl.getCurrentMenuName() == MI_GOTOSLEEP)
        {
            int sec = Controller::timeStrToSec(ctrl.getMenuItemName(idxBtn));
            if (sec > 0)
            {
                itvGoToSleep = sec * SEC;
                ctrl.goToParentMenu();
                disp.menu(ctrl.getMenuPage());
            }
            return;
        }
        // starting apps
        if (click == ShortClick)
        {
            if (ctrl.getMenuItemName(idxBtn) == MI_STOPWATCH)
            {
                activeApp = AppStopwatch;
                return;
            }
            if (ctrl.getMenuItemName(idxBtn) == MI_COUNTDOWN)
            {
                activeApp = AppCountdown;
                disp.menu(cd.getMenuPage());
                return;
            }
        }

        if (click == LongClick)
        {
            if (idxBtn == LeftButton)
                ctrl.goToParentMenu();
            if (idxBtn == CenterButton)
                ctrl.goToRoot();
            if (idxBtn == RightButton)
                ctrl.goToNextPage();
        }

        if (click == ShortClick)
            ctrl.goToItem(idxBtn);
        disp.menu(ctrl.getMenuPage());
    }
}
