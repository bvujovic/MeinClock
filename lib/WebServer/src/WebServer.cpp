#include "WebServer.h"

ESP8266WebServer server(80);
bool isRunning = true;

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
    SendEmptyText(server);
    server.stop();
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
        server.on("/stop", []()
                  { handleStop(); });
        server.on("/loadTextFile", handleLoadTextFile);
        server.on("/saveTextFile", handleSaveTextFile);
        server.begin();
        return true;
    }
    else
        return false;
}

bool WebServer::refresh()
{
    server.handleClient();
    return isRunning;
}

void WebServer::stop()
{
    server.stop();
}
