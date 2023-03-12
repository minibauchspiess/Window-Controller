#pragma once

#include <Arduino.h>

class Motor
{
public:
    Motor(uint16_t pinA, uint16_t pinB);
    ~Motor();

    void SpinForward();
    void SpinBackward();
    void Stop();
private:
    uint16_t _pinA, _pinB;
};

