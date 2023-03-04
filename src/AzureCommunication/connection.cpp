#include "AzureCommunication/connection.h"


bool connection::isConnected = false;

connection::connection(/* args */)
{
}

connection::~connection()
{
}

void connection::on_event(IOTContext ctx, IOTCallbackInfo* callbackInfo) {
  // ConnectionStatus
  if (strcmp(callbackInfo->eventName, "ConnectionStatus") == 0) {
    LOG_VERBOSE("Is connected ? %s (%d)",
                callbackInfo->statusCode == IOTC_CONNECTION_OK ? "YES" : "NO",
                callbackInfo->statusCode);
    isConnected = callbackInfo->statusCode == IOTC_CONNECTION_OK;
    return;
  }

  // payload buffer doesn't have a null ending.
  // add null ending in another buffer before print
  AzureIOT::StringBuffer buffer;
  if (callbackInfo->payloadLength > 0) {
    buffer.initialize(callbackInfo->payload, callbackInfo->payloadLength);
  }

  LOG_VERBOSE("- [%s] event was received. Payload => %s\n",
              callbackInfo->eventName, buffer.getLength() ? *buffer : "EMPTY");

  if (strcmp(callbackInfo->eventName, "Command") == 0) {
    LOG_VERBOSE("- Command name was => %s\r\n", callbackInfo->tag);
  }
}


void connection::connect_client(const char* scopeId, const char* deviceId,const char* deviceKey) {
  // initialize iotc context (per device client)
  int errorCode = iotc_init_context(&context);
  if (errorCode != 0) {
    LOG_ERROR("Error initializing IOTC. Code %d", errorCode);
    return;
  }

  iotc_set_logging(IOTC_LOGGING_API_ONLY);

  // set up event callbacks. they are all declared under the ESP8266.ino file
  // for simplicity, track all of them from the same callback function
  iotc_on(context, "MessageSent", on_event, NULL);
  iotc_on(context, "Command", on_event, NULL);
  iotc_on(context, "ConnectionStatus", on_event, NULL);
  iotc_on(context, "SettingsUpdated", on_event, NULL);

  // connect to Azure IoT
  errorCode = iotc_connect(context, scopeId, deviceKey, deviceId,
                           IOTC_CONNECT_SYMM_KEY);
  if (errorCode != 0) {
    LOG_ERROR("Error @ iotc_connect. Code %d", errorCode);
    return;
  }
}

void connection::connect_wifi(const char* wifi_ssid, const char* wifi_password) {
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

bool connection::IsConnected(){
  return isConnected;
}