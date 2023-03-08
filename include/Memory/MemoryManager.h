#pragma once

#include "LittleFS.h"

class MemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();

    static void StartFileSystem();
    
    static void WriteStringOnFile(String filename, String fileContent);
    static String ReadStringFromFile(String fileName);

    static const constexpr char *WIFI_SSID_FILENAME = "/WifiSSID.txt";
    static const constexpr char *WIFI_PASSWORD_FILENAME = "/WifiPassword.txt";
    static const constexpr char *SCOPE_FILENAME = "/Scope.txt";
    static const constexpr char *DEVICE_FILENAME = "/Device.txt";
    static const constexpr char *KEY_FILENAME = "/Key.txt";
private:
};

