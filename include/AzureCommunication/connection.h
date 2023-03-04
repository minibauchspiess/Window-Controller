#pragma once
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.

#include <ESP8266WiFi.h>
#include "iotc/string_buffer.h"
#include "iotc/iotc.h"

class Connection
{
public:
  
  Connection();
  ~Connection();

  void ConnectWifi(const char* wifi_ssid, const char* wifi_password);
  void ConnectClient(const char* scopeId, const char* deviceId, const char* deviceKey);

  static void OnEvent(IOTContext ctx, IOTCallbackInfo* callbackInfo);
  
  bool IsConnected();
  unsigned long GetLastTick();
  unsigned long GetLoopId();
  IOTContext GetContext();

  void SetLastTick(unsigned long newValue);
  void SetLoopId(unsigned long newValue);
  void SetContext(IOTContext newValue);

private:
  unsigned long _lastTick = 0, _loopId = 0;
  IOTContext _context = NULL;
  static bool _isConnected;
};






