#include "AzureCommunication/Connection.h"


bool Connection::_isConnected = false;

Connection::Connection()
{
}

Connection::~Connection()
{
}

void Connection::ConnectWifi(const char* wifi_ssid, const char* wifi_password) {
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void Connection::ConnectClient(const char* scopeId, const char* deviceId,const char* deviceKey) {
  // initialize iotc _context (per device client)
  int errorCode = iotc_init_context(&_context);
  if (errorCode != 0) {
    LOG_ERROR("Error initializing IOTC. Code %d", errorCode);
    return;
  }

  iotc_set_logging(IOTC_LOGGING_API_ONLY);

  // set up event callbacks. they are all declared under the ESP8266.ino file
  // for simplicity, track all of them from the same callback function
  iotc_on(_context, MESSAGE_SENT, OnEvent, NULL);
  iotc_on(_context, COMMAND, OnEvent, NULL);
  iotc_on(_context, CONNECTION_STATUS, OnEvent, NULL);
  iotc_on(_context, SETTINGS_UPDATED, OnEvent, NULL);

  // connect to Azure IoT
  errorCode = iotc_connect(_context, scopeId, deviceKey, deviceId,
                           IOTC_CONNECT_SYMM_KEY);
  if (errorCode != 0) {
    LOG_ERROR("Error @ iotc_connect. Code %d", errorCode);
    return;
  }
}

void Connection::OnEvent(IOTContext ctx, IOTCallbackInfo* callbackInfo) {
  // ConnectionStatus
  if (strcmp(callbackInfo->eventName, CONNECTION_STATUS) == 0) {
    _isConnected = callbackInfo->statusCode == IOTC_CONNECTION_OK;
    if(_isConnected) Serial.println("Connected to Azure");
    else Serial.println("Not connected to Azure");

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

  if (strcmp(callbackInfo->eventName, COMMAND) == 0) {
    LOG_VERBOSE("- Command name was => %s\r\n", callbackInfo->tag);
  }
}

bool Connection::IsConnected(){
  return _isConnected;
}

unsigned long Connection::GetLastTick(){
  return _lastTick;
}

unsigned long Connection::GetLoopId(){
  return _loopId;
}

IOTContext Connection::GetContext(){
  return _context;
}

void Connection::SetLastTick(unsigned long newValue){
  _lastTick = newValue;
}

void Connection::SetLoopId(unsigned long newValue){
  _loopId = newValue;
}

void Connection::SetContext(IOTContext newValue){
  _context = newValue;
}