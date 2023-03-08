#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>

#include <ESP8266WiFi.h>
#include "iotc/string_buffer.h"
#include "iotc/iotc.h"

#include "Connection.h"
#include "Memory/MemoryManager.h"

class AzureCommunication
{
public:
    AzureCommunication();
    ~AzureCommunication();

    void Setup();
    void Loop();

    void SetCommandFunctionsMap(std::map<String, void(*)(String)> functionsMap);
    static void SetWifiSsid(String ssid);
    static void SetWifiPassword(String password);
    static void SetScopeId(String scopeId);
    static void SetDeviceId(String deviceId);
    static void SetDeviceKey(String deviceKey);
private:
    StaticJsonDocument<300> _GetCommandAsJson(String rawCommands);

    void _ExecuteCommands(StaticJsonDocument<300> commandsJson);

    static char _wifiSsid[50];
    static char _wifiPassword[50];

    static char _scopeId[50];
    static char _deviceId[50];
    static char _deviceKey[100];

    Connection _connection = Connection();

    std::map<String, void(*)(String)> _commandFunctionsMap;
};


