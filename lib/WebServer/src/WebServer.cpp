#include "WebServer.h"

ESP8266WebServer server(80);
bool isRunning = true;

#include <ArduinoOTA.h>
bool isOtaOn = false;

void handleTestJson()
{
    server.send(200, "application/json", "{ 'app': 'MeinClock' }");
}

void handleIndex()
{
    HandleDataFile(server, "/text_editor.html", "text/html");
}

void handleStop()
{
    isRunning = false;
    SendEmptyText(server);
    server.stop();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
}

String textFileName;

void handleLoadTextFile()
{
    textFileName = server.arg("name");
    HandleDataFile(server, textFileName, "text/csv");
}

void handleSaveTextFile()
{
    //   LittleFsUtils::WriteFile(textFileName, server.arg("plain"));
    File fp = LittleFS.open(textFileName, "w");
    if (fp)
    {
        fp.print(server.arg("plain"));
        fp.close();
    }
    SendEmptyText(server);
}

bool WebServer::start()
{
    if (ConnectToWiFi(WIFI_SSID, WIFI_PASS))
    {
        SetupIPAddress(70);
        server.on("/test", handleTestJson);
        server.on("/", []()
                  { handleIndex(); });
        server.on("/stopServer", []()
                  { handleStop(); });
        server.on("/loadTextFile", handleLoadTextFile);
        server.on("/saveTextFile", handleSaveTextFile);
        server.on("/otaUpdate", []()
                  {
              server.send(200, "text/plain", "ESP is waiting for OTA updates...");
              isOtaOn = true;
              ArduinoOTA.begin(); });
        server.begin();
        return isRunning = true;
    }
    else
        return false;
}

bool WebServer::refresh()
{
    if (isOtaOn)
        ArduinoOTA.handle();
    else if (isRunning)
        server.handleClient();
    return isRunning;
}
