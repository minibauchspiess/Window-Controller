#include <Arduino.h>

#include "AzureCommunication/AzureCommunication.h"

AzureCommunication azure = AzureCommunication();

void setup() {
  Serial.begin(115200);

  azure.Setup();
}

void loop() {
  azure.Loop();
}
