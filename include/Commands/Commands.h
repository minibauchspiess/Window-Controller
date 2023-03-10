#pragma once

#define FUNCTION_TARGET void(*)(void*, String)

#include <Arduino.h>
#include <map>

#include "AzureCommunication/AzureCommunication.h"
#include "WindowMotor/WindowMotor.h"

class Commands
{
public:
    Commands(AzureCommunication *azureRefference, WindowMotor *windowMotorRefference);
    ~Commands();

    void Update();

    std::map<String, std::pair<FUNCTION_TARGET, void*>> GetCommandFunctionsMap();
private:
    String _ReadLineWithVerbose();
    void _ExtractCommandAndPayload(String rawLine, String &command, String &payload);
    void _ExecuteCommand(String command, String payload);

    std::map<String, std::pair<FUNCTION_TARGET, void*>> _commandFunctionsMap;
    const uint32_t READ_LINE_TIMEOUT_MS = 30000;
};