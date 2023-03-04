#pragma once
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.

// src/connection.h

#include <ESP8266WiFi.h>
#include "iotc/string_buffer.h"
#include "iotc/iotc.h"

class connection
{
public:
  
  connection(/* args */);
  ~connection();

  void connect_client(const char* scopeId, const char* deviceId, const char* deviceKey);
  void connect_wifi(const char* wifi_ssid, const char* wifi_password);
  static void on_event(IOTContext ctx, IOTCallbackInfo* callbackInfo);

  bool IsConnected();

  unsigned long lastTick = 0, loopId = 0;
  IOTContext context = NULL;
  static bool isConnected;
private:
  /* data */
};






