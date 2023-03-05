#include <Arduino.h>

#include "AzureCommunication/AzureCommunication.h"
#include "Commands/Commands.h"

AzureCommunication azure = AzureCommunication();
Commands commands = Commands();


void setup() {
  Serial.begin(115200);

  azure.Setup();

  azure.SetCommandFunctionsMap(commands.GetCommandFunctionsMap());
}

void loop() {
  azure.Loop();
}
