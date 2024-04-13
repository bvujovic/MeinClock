#include <Arduino.h>
#include <LinkedList.h>

#include "Btn.h"
Btn btnLeft(D7);
Btn btnCenter(D6);
Btn btnRight(D5);

#include "Controller.h"
Controller ctrl;

#include "MyDisplay.h"
MyDisplay disp;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n*** MEIN CLOCK ***");
    disp.setItvTurnOffDisplay(5 * 1000);
    disp.menu(ctrl.getMenuPage());
}

void loop()
{
    delay(10);
    ulong ms = millis();
    disp.autoTurnOff(ms);

    ClickType click;

    // LEVO DUGME
    click = btnLeft.check(ms);
    if (click != None)
    {
        if (click == LongClick) // dugi klik
        {
            ctrl.goToParentMenu();
            disp.menu(ctrl.getMenuPage());
        }
        if (click == ShortClick) // kratki klik
        {
            Serial.println(ctrl.getCurrentMenu());
            if (ctrl.getCurrentMenu() == "TurnOffScr")
            {
                disp.setItvTurnOffDisplay(10 * 1000);
            }
            else
            {
                ctrl.goToItem(0);
                disp.menu(ctrl.getMenuPage());
            }
        }
    }
    // SREDNJE DUGME
    click = btnCenter.check(ms);
    if (click != None)
    {
        if (!disp.IsItOn())
        {
            disp.turnOn();
            disp.menu(ctrl.getMenuPage());
        }
        else
        {
            if (click == LongClick) // dugi klik
            {
                ctrl.goToRoot();
                disp.menu(ctrl.getMenuPage());
            }
            if (click == ShortClick) // kratki klik
            {
                ctrl.goToItem(1);
                disp.menu(ctrl.getMenuPage());
            }
        }
    }
    // DESNO DUGME
    click = btnRight.check(ms);
    if (click != None)
    {
        if (click == LongClick) // dugi klik
        {
            ctrl.goToNextPage();
            disp.menu(ctrl.getMenuPage());
        }
        if (click == ShortClick) // kratki klik
        {
            ctrl.goToItem(2);
            disp.menu(ctrl.getMenuPage());
        }
    }
}
