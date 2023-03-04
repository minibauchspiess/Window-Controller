#include "AzureCommunication/AzureCommunication.h"

// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.


AzureCommunication::AzureCommunication()
{
}

AzureCommunication::~AzureCommunication()
{
}


void AzureCommunication::Setup() {

  _connection.ConnectWifi(WIFI_SSID, WIFI_PASSWORD);
  _connection.ConnectClient(SCOPE_ID, DEVICE_ID, DEVICE_KEY);

  if (_connection.GetContext() != NULL) {
    _connection.SetLastTick(0);  // set timer in the past to enable first telemetry a.s.a.p
  }
}

void AzureCommunication::Loop() {

float t = 23.4;

  
  if (_connection.IsConnected()) {
    String rawCommand = Connection::GetLastCommandJson();
    if(rawCommand == "") Serial.printf("Waiting %lu\r", millis());
    else Serial.print("\nReceived command inside AC: " + rawCommand + "\n");

    unsigned long ms = millis();
    if (ms - _connection.GetLastTick() > 10000) {  // send telemetry every 10 seconds
      char msg[64] = {0};
      int pos = 0, errorCode = 0;

      _connection.SetLastTick(ms);

      unsigned long newLoopId = _connection.GetLoopId() + 1;
      _connection.SetLoopId(newLoopId);
      if (newLoopId % 2 == 0) {  // send telemetry
        // _connection.SendTelemetry(String("{\"Temperature\": "+String(t)+"}"));
          
      } else {  // send property
        
      } 
  
      msg[pos] = 0;

      if (errorCode != 0) {
        LOG_ERROR("Sending message has failed with error code %d", errorCode);
      }
    }

    iotc_do_work(_connection.GetContext());  // do background work for iotc
  } else {
    iotc_free_context(_connection.GetContext());
    _connection.SetContext(NULL);
    _connection.ConnectClient(SCOPE_ID, DEVICE_ID, DEVICE_KEY);
  }

}
