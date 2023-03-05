#pragma once

#include <Arduino.h>
#include <map>

class Commands
{
public:
    Commands();
    ~Commands();

    std::map<String, void(*)(String)> GetCommandFunctionsMap();
private:
    std::map<String, void(*)(String)> _commandFunctionsMap;
};