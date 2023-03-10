#pragma once

#define FUNCTION_TARGET void(*)(void*, String)

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

    void SetCommandFunctionsMap(std::map<String, std::pair<FUNCTION_TARGET, void*>> functionsMap);

    void SetWifiSsid(String ssid);
    static void SetWifiSsid(void* selfRefference, String ssid);

    void SetWifiPassword(String password);
    static void SetWifiPassword(void* selfRefference, String password);

    void SetScopeId(String scopeId);
    static void SetScopeId(void* selfRefference, String scopeId);

    void SetDeviceId(String deviceId);
    static void SetDeviceId(void* selfRefference, String deviceId);

    void SetDeviceKey(String deviceKey);
    static void SetDeviceKey(void* selfRefference, String deviceKey);
private:
    StaticJsonDocument<300> _GetCommandAsJson(String rawCommands);

    void _ExecuteCommands(StaticJsonDocument<300> commandsJson);

    char _wifiSsid[50];
    char _wifiPassword[50];

    char _scopeId[50];
    char _deviceId[50];
    char _deviceKey[100];

    Connection _connection = Connection();

    std::map<String, std::pair<FUNCTION_TARGET, void*>> _commandFunctionsMap;
};


