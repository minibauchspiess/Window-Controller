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

  conn.connect_wifi(WIFI_SSID, WIFI_PASSWORD);
  conn.connect_client(SCOPE_ID, DEVICE_ID, DEVICE_KEY);

  if (conn.context != NULL) {
    conn.lastTick = 0;  // set timer in the past to enable first telemetry a.s.a.p
  }
}

void AzureCommunication::Loop() {

float t = 23.4;

  
  if (conn.IsConnected()) {

    unsigned long ms = millis();
    if (ms - conn.lastTick > 10000) {  // send telemetry every 10 seconds
      char msg[64] = {0};
      int pos = 0, errorCode = 0;

      conn.lastTick = ms;
      if (conn.loopId++ % 2 == 0) {  // send telemetry
        pos = snprintf(msg, sizeof(msg) - 1, "{\"Temperature\": %f}",
                       t);
        errorCode = iotc_send_telemetry(conn.context, String("{\"Temperature\": "+String(t)+"}").c_str(), pos);
        
        // pos = snprintf(msg, sizeof(msg) - 1, "{\"Humidity\":%f}",
        //                h);
        // errorCode = iotc_send_telemetry(context, msg, pos);
          
      } else {  // send property
        
      } 
  
      msg[pos] = 0;

      if (errorCode != 0) {
        LOG_ERROR("Sending message has failed with error code %d", errorCode);
      }
    }

    iotc_do_work(conn.context);  // do background work for iotc
  } else {
    iotc_free_context(conn.context);
    conn.context = NULL;
    conn.connect_client(SCOPE_ID, DEVICE_ID, DEVICE_KEY);
  }

}
