#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>

#include <ESP8266WiFi.h>
#include "iotc/string_buffer.h"
#include "iotc/iotc.h"

#include "Connection.h"

#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11


#define WIFI_SSID "*******"
#define WIFI_PASSWORD "*******"

class AzureCommunication
{
public:
    AzureCommunication();
    ~AzureCommunication();

    void Setup();
    void Loop();
private:
    StaticJsonDocument<300> _GetCommandAsJson(String rawCommands);

    void _ExecuteCommands(StaticJsonDocument<300> commandsJson);

    const char* SCOPE_ID = "********";
    const char* DEVICE_ID = "***********";
    const char* DEVICE_KEY = "**********************************";

    Connection _connection = Connection();

    std::map<String, void(*)(String)> _commandFunctionsMap;
};


