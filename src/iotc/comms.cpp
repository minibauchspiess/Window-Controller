// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.
#include <Arduino.h>
#include <SPI.h>
#include <stdarg.h>
#include "iotc/iotc_internal.h"
#include "iotc/iotc_platform.h"
#include "iotc/iotc_json.h"

int mqtt_publish(IOTContextInternal* internal, const char* topic,
                 unsigned long topic_length, const char* msg,
                 unsigned long msg_length) {
  if (!internal->mqttClient->publish(topic, (const uint8_t*)msg, msg_length,
                                     false)) {
    return 1;
  }
  return 0;
}
