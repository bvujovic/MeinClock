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
#include "Blinky.h" // https://github.com/bvujovic/ArduinoLibs/tree/main/Blinky
Blinky buzzer = Blinky(D3, true);
#include "EasyINI.h" // https://github.com/bvujovic/ArduinoLibs/tree/main/EasyINI
EasyINI ei("/setts.ini");

#include "Stopwatch.h"
Stopwatch sw;
#include "Countdown.h"
Countdown cd;
#include "TimeWatcher.h"
TimeWatcher tw;
#include "CsvReader.h"

// Milliseconds in 1 second.
#define SEC (1000)
// Milliseconds in 1 minute.
#define MIN (60 * SEC)

ClickType click;
int idxBtn;
Time t;
/// @brief How many msec from the last time something is displayed device should go to sleep.
ulong itvGoToSleep = 3 * MIN;

void readCountdownCSV()
{
    CsvReader csv("/countdown.csv", 2);
    if (csv.fileOpenSuccess())
    {
        while (true)
        {
            String *ss = csv.readLine();
            if (ss == NULL)
                break;
            int idx = ss[1].indexOf(':');
            if (idx == -1)
                continue;
            int min = ss[1].substring(0, idx).toInt();
            int sec = ss[1].substring(idx + 1).toInt();
            CdItem item = CdItem{Time(min, sec), ss[0]};
            cd.addMenuItem(item);
        }
    }
    else
        Serial.println("no CSV file.");
}

void readIni()
{
    const int turnOffScrDef = 10 * SEC;
    const int goToSleepDef = 180 * SEC;
    if (ei.open(FMOD_READ))
    {
        disp.setItvAutoTurnOff(ei.getInt(MI_TURNOFFSCR, turnOffScrDef));
        itvGoToSleep = ei.getInt(MI_GOTOSLEEP, goToSleepDef);
        ei.close();
    }
    else
    {
        disp.setItvAutoTurnOff(turnOffScrDef);
        itvGoToSleep = goToSleepDef;
    }
}

void saveIni()
{
    if (ei.open(FMOD_WRITE))
    {
        ei.setInt(MI_TURNOFFSCR, disp.getItvTurnOffDisplay());
        ei.setInt(MI_GOTOSLEEP, itvGoToSleep);
        ei.close();
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\n*** MEIN CLOCK ***");
    pinMode(buzzer.getPin(), OUTPUT);
    buzzer.off();
    tw.setBuzzer(&buzzer);
    ctrl.init();
    disp.init();
    // LittleFS.begin();
    readIni();
    readCountdownCSV();
    disp.menu(ctrl.getMenuPage());
}

/// @brief Go to sleep if the time is not currently measured.
/// @param ms Current time.
void goToSleepIN(ulong ms)
{
    bool stopwatchOk = activeApp == AppStopwatch && sw.IsPaused();
    bool countdownOk = activeApp == AppCountdown && cd.getState() == CdMenu;
    // TODO add bool timewatcherOk = ...
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
    disp.autoTurnOffIN(ms);
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
        if (idxBtn != -1)
        {
            if (!disp.IsItOn())
            {
                disp.turnOn();
                disp.time(t, MinSecCent);
                return;
            }
            else
                disp.ItIsOn(ms);
        }
        sw.refresh(ms, t);
        disp.time(t, MinSecCent);
        sw.buttons(ms, idxBtn, click);
        if (idxBtn == CenterButton)
            disp.ItIsOn(ms);
        if (idxBtn == LeftButton)
        {
            activeApp = NoApp;
            disp.setItvAutoTurnOffPrev();
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
    if (activeApp == AppTimeWatcher)
    {
        //* COPY/PASTE CODE
        // wake up display
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
        tw.refresh(ms, t);
        disp.time(t, MinSec);
        // TODO budjenje displeja pre pistanja
        tw.buzzIN();

        // tw.buttons(ms, idxBtn, click);
        if (idxBtn == LeftButton && click == LongClick)
        {
            activeApp = NoApp;
            disp.menu(ctrl.getMenuPage());
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

        // handling options/settings: Turn off display and Go to sleep
        if (click == ShortClick && ctrl.getCurrentMenuName() == MI_TURNOFFSCR)
        {
            int sec = Controller::timeStrToSec(ctrl.getMenuItemName(idxBtn));
            if (sec > 0)
            {
                disp.setItvAutoTurnOff(sec * SEC);
                saveIni();
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
                saveIni();
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
                disp.setItvAutoTurnOff(0);
                return;
            }
            if (ctrl.getMenuItemName(idxBtn) == MI_COUNTDOWN)
            {
                activeApp = AppCountdown;
                disp.menu(cd.getMenuPage());
                return;
            }
            if (ctrl.getMenuItemName(idxBtn) == MI_TIMEWATCH)
            {
                activeApp = AppTimeWatcher;
                disp.turnOff();
                tw.initTime();
                disp.turnOn();
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
        // short click -> go to item (starting app/selecting some option)
        if (click == ShortClick)
            ctrl.goToItem(idxBtn);
        disp.menu(ctrl.getMenuPage());
    }
}
