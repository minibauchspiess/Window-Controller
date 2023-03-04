#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include "iotc/string_buffer.h"
#include "iotc/iotc.h"

#include "connection.h"

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
    const char* SCOPE_ID = "********";
    const char* DEVICE_ID = "***********";
    const char* DEVICE_KEY = "**********************************";

    connection conn = connection();
};


