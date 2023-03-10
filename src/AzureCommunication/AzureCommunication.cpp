#include "AzureCommunication/AzureCommunication.h"

// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

char AzureCommunication::_wifiSsid[50];
char AzureCommunication::_wifiPassword[50];
char AzureCommunication::_scopeId[50];
char AzureCommunication::_deviceId[50];
char AzureCommunication::_deviceKey[100];

AzureCommunication::AzureCommunication()
{
}

AzureCommunication::~AzureCommunication()
{
}


void AzureCommunication::Setup() {

  SetWifiSsid(MemoryManager::ReadStringFromFile(MemoryManager::WIFI_SSID_FILENAME));
  SetWifiPassword(MemoryManager::ReadStringFromFile(MemoryManager::WIFI_PASSWORD_FILENAME));
  SetScopeId(MemoryManager::ReadStringFromFile(MemoryManager::SCOPE_FILENAME));
  SetDeviceId(MemoryManager::ReadStringFromFile(MemoryManager::DEVICE_FILENAME));
  SetDeviceKey(MemoryManager::ReadStringFromFile(MemoryManager::KEY_FILENAME));

  Serial.printf("_wifiSsid: %s\n", _wifiSsid);
  Serial.printf("_wifiPassword: %s\n", _wifiPassword);
  Serial.printf("_scopeId: %s\n", _scopeId);
  Serial.printf("_deviceId: %s\n", _deviceId);
  Serial.printf("_deviceKey: %s\n", _deviceKey);

  _connection.ConnectWifi(_wifiSsid, _wifiPassword);
  if(_connection.isConnectedToWifi())
    _connection.ConnectClient(_scopeId, _deviceId, _deviceKey);
  
  if (_connection.GetContext() != NULL) {
    _connection.SetLastTick(0);  // set timer in the past to enable first telemetry a.s.a.p
  }
}


void AzureCommunication::Loop() {

  if(!_connection.isConnectedToWifi()){
    _connection.ConnectWifi(_wifiSsid, _wifiPassword);
  }
  else{
    if (_connection.IsConnected()) {
      
      String rawCommand = Connection::GetLastCommandJson();
      if(rawCommand != "") _ExecuteCommands(_GetCommandAsJson(rawCommand));

      iotc_do_work(_connection.GetContext());  // do background work for iotc
    } else {
        iotc_free_context(_connection.GetContext());
        _connection.SetContext(NULL);
        _connection.ConnectClient(_scopeId, _deviceId, _deviceKey);
    }
  }

}

void AzureCommunication::SetCommandFunctionsMap(std::map<String, void(*)(String)> functionsMap){
  _commandFunctionsMap = functionsMap;
}

void AzureCommunication::SetWifiSsid(String ssid){
  strcpy(_wifiSsid, ssid.c_str());
  MemoryManager::WriteStringOnFile(MemoryManager::WIFI_SSID_FILENAME, ssid);
  Serial.printf("Updated wifi ssid to %s\n", _wifiSsid);
}

void AzureCommunication::SetWifiPassword(String password){
  strcpy(_wifiPassword, password.c_str());
  MemoryManager::WriteStringOnFile(MemoryManager::WIFI_PASSWORD_FILENAME, password);
  Serial.printf("Updated wifi password to %s\n", _wifiPassword);
}

void AzureCommunication::SetScopeId(String scopeId){
  strcpy(_scopeId, scopeId.c_str());
  MemoryManager::WriteStringOnFile(MemoryManager::SCOPE_FILENAME, scopeId);
  Serial.printf("Updated scope id to %s\n", _scopeId);
}

void AzureCommunication::SetDeviceId(String deviceId){
  strcpy(_deviceId, deviceId.c_str());
  MemoryManager::WriteStringOnFile(MemoryManager::DEVICE_FILENAME, deviceId);
  Serial.printf("Updated device id to %s\n", _deviceId);
}

void AzureCommunication::SetDeviceKey(String deviceKey){
  strcpy(_deviceKey, deviceKey.c_str());
  MemoryManager::WriteStringOnFile(MemoryManager::KEY_FILENAME, deviceKey);
  Serial.printf("Updated device key to %s\n", _deviceKey);
}

StaticJsonDocument<300> AzureCommunication::_GetCommandAsJson(String rawCommands){
  StaticJsonDocument<300> commandsJson;

  deserializeJson(commandsJson, rawCommands);

  return commandsJson;
}

void AzureCommunication::_ExecuteCommands(StaticJsonDocument<300> commandsJson){

  JsonObject commandsJsonObject = commandsJson.as<JsonObject>();
  for(JsonPair commandPair : commandsJsonObject){
    String command, payload;

    command = String(commandPair.key().c_str());
    payload = commandPair.value().as<String>();
    Serial.printf("Command: %s. Payload: %s\n", command.c_str(), payload.c_str());

    if(_commandFunctionsMap.find(command) != _commandFunctionsMap.end()){
      _commandFunctionsMap[command](payload);
    }
    else{
      Serial.println("Command not found");
    }
  }
}