#pragma once

#include <Arduino.h>

#include "Motor.h"

class WindowMotor
{
public:
    WindowMotor();
    ~WindowMotor();
    bool isWindowOpen();
private:
    bool _isOpen;
    Motor _motor;
};

