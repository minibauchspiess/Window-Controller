#pragma once

#include <Arduino.h>

#include "Motor.h"

class WindowMotor
{
public:
    WindowMotor();
    ~WindowMotor();

    void OpenWindow();
    static void OpenWindow(void* selfRefference, String);

    void CloseWindow();
    static void CloseWindow(void* selfRefference, String);

    bool isWindowOpen();
private:
    bool _isOpen;
    Motor _motor;
};

