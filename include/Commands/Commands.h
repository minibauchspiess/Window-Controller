#pragma once

#include <Arduino.h>
#include <map>

#include "AzureCommunication/AzureCommunication.h"

class Commands
{
public:
    Commands();
    ~Commands();

    void Update();

    std::map<String, void(*)(String)> GetCommandFunctionsMap();
private:
    String _ReadLineWithVerbose();
    void _ExtractCommandAndPayload(String rawLine, String &command, String &payload);
    void _ExecuteCommand(String command, String payload);

    std::map<String, void(*)(String)> _commandFunctionsMap;

    const uint32_t READ_LINE_TIMEOUT_MS = 30000;
};