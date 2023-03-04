#include "AzureCommunication/Connection.h"


bool Connection::_isConnected = false;

Connection::Connection(/* args */)
{
}

Connection::~Connection()
{
}

void Connection::OnEvent(IOTContext ctx, IOTCallbackInfo* callbackInfo) {
  // ConnectionStatus
  if (strcmp(callbackInfo->eventName, "ConnectionStatus") == 0) {
    LOG_VERBOSE("Is connected ? %s (%d)",
                callbackInfo->statusCode == IOTC_CONNECTION_OK ? "YES" : "NO",
                callbackInfo->statusCode);
    _isConnected = callbackInfo->statusCode == IOTC_CONNECTION_OK;
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
  iotc_on(_context, "MessageSent", OnEvent, NULL);
  iotc_on(_context, "Command", OnEvent, NULL);
  iotc_on(_context, "ConnectionStatus", OnEvent, NULL);
  iotc_on(_context, "SettingsUpdated", OnEvent, NULL);

  // connect to Azure IoT
  errorCode = iotc_connect(_context, scopeId, deviceKey, deviceId,
                           IOTC_CONNECT_SYMM_KEY);
  if (errorCode != 0) {
    LOG_ERROR("Error @ iotc_connect. Code %d", errorCode);
    return;
  }
}

void Connection::ConnectWifi(const char* wifi_ssid, const char* wifi_password) {
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
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