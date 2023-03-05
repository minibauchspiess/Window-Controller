#include "Commands/Commands.h"

void dummyFunctionOne(String value){
    Serial.printf("In first dummy function with value %s\n", value.c_str());
}

void dummyFunctionTwo(String value){
    Serial.printf("In second dummy function with value %s\n", value.c_str());
}

void dummyFunctionThree(String value){
    Serial.printf("In third dummy function with value %s\n", value.c_str());
}


Commands::Commands()
{
    _commandFunctionsMap["One"] = dummyFunctionOne;
    _commandFunctionsMap["Two"] = dummyFunctionTwo;
    _commandFunctionsMap["Three"] = dummyFunctionThree;
}

Commands::~Commands()
{
}

std::map<String, void(*)(String)> Commands::GetCommandFunctionsMap(){
    return _commandFunctionsMap;
}