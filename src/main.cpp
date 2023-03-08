#include <Arduino.h>

#include "AzureCommunication/AzureCommunication.h"
#include "Commands/Commands.h"
#include "Memory/MemoryManager.h"

AzureCommunication azure = AzureCommunication();
Commands commands = Commands();


void setup() {
  Serial.begin(115200);
  delay(1000);
  MemoryManager::StartFileSystem();

  azure.Setup();

  azure.SetCommandFunctionsMap(commands.GetCommandFunctionsMap());
}

void loop() {
  azure.Loop();
  commands.Update();
}
