#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class MyDisplay
{
private:
    U8G2_SSD1306_64X48_ER_1_HW_I2C *u8g2;

public:
    MyDisplay();
    void menu(int page);

};
