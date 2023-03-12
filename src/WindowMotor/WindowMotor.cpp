#include "WindowMotor/WindowMotor.h"

WindowMotor::WindowMotor() : _motor(Motor(D0, D1))
{
}

WindowMotor::~WindowMotor()
{
}

void WindowMotor::OpenWindow(void* selfRefference, String){
    WindowMotor *self = (WindowMotor*) selfRefference;
    self->OpenWindow();
}

void WindowMotor::OpenWindow(){
    Serial.println("Opening window");
    _motor.SpinForward();
    delay(10000);
    Serial.println("Stop");
    _motor.Stop();
}

void WindowMotor::CloseWindow(void* selfRefference, String){
    WindowMotor *self = (WindowMotor*) selfRefference;
    self->CloseWindow();
}

void WindowMotor::CloseWindow(){
    Serial.println("Closing window");
    _motor.SpinBackward();
    delay(10000);
    Serial.println("Stop");
    _motor.Stop();
}