#pragma once

#include <WiFiServerBasics.h> // https://github.com/bvujovic/ArduinoLibs/tree/main/WiFiServerBasics

class WebServer
{
public:
    friend void handleTestJson();
    friend void handleIndex();
    friend void handleStop();
    friend void handleLoadTextFile();
    friend void handleLoadTextFile();

    bool start();
    bool refresh();
};
