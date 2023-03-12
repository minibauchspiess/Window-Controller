#include "WindowMotor/Motor.h"

Motor::Motor(uint16_t pinA, uint16_t pinB)
{
    _pinA = pinA;
    _pinB = pinB;

    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
}

Motor::~Motor()
{
}

void Motor::SpinForward(){
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, LOW);
}

void Motor::SpinBackward(){
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, HIGH);
}

void Motor::Stop(){
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, LOW);
}