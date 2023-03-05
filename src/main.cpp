#include <Arduino.h>

#include "AzureCommunication/AzureCommunication.h"

AzureCommunication azure = AzureCommunication();

void dummyFunctionOne(String value){
  Serial.printf("In first dummy function with value %s\n", value.c_str());
}

void dummyFunctionTwo(String value){
  Serial.printf("In second dummy function with value %s\n", value.c_str());
}

void dummyFunctionThree(String value){
  Serial.printf("In third dummy function with value %s\n", value.c_str());
}

void setup() {
  Serial.begin(115200);

  azure.Setup();
  
  std::map<String, void(*)(String)> dummyFunctionsMap;
  dummyFunctionsMap["One"] = dummyFunctionOne;
  dummyFunctionsMap["Two"] = dummyFunctionTwo;
  dummyFunctionsMap["Three"] = dummyFunctionThree;

  azure.SetCommandFunctionsMap(dummyFunctionsMap);
}

void loop() {
  azure.Loop();
}
