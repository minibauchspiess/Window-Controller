#include "Commands/Commands.h"

Commands::Commands()
{   
    Serial.setTimeout(50);

    _commandFunctionsMap["WifiSSID"] = AzureCommunication::SetWifiSsid;
    _commandFunctionsMap["WifiPassword"] = AzureCommunication::SetWifiPassword;
    _commandFunctionsMap["Scope"] = AzureCommunication::SetScopeId;
    _commandFunctionsMap["Device"] = AzureCommunication::SetDeviceId;
    _commandFunctionsMap["Key"] = AzureCommunication::SetDeviceKey;
}

Commands::~Commands()
{
}

void Commands::Update(){
    String newLine = _ReadLineWithVerbose();
    if(newLine != ""){
        String command, payload;
        _ExtractCommandAndPayload(newLine, command, payload);
        _ExecuteCommand(command, payload);
    }
}

std::map<String, void(*)(String)> Commands::GetCommandFunctionsMap(){
    return _commandFunctionsMap;
}

String Commands::_ReadLineWithVerbose(){
    String newLine = "";
    if(Serial.available()){
        bool timeout = false;
        uint32_t timerStart = millis();

        do{
            String recentText = Serial.readString();

            if(recentText != ""){
                timerStart = millis();
                if(recentText == "\b"){
                    newLine = newLine.substring(0, newLine.length()-1);

                    Serial.print("\b \b");
                    Serial.print(" ");
                    Serial.print("\b");
                    recentText = "";
                }
                Serial.print(recentText);
                newLine += recentText;
            }
            timeout = (millis() - timerStart) > READ_LINE_TIMEOUT_MS;

        }while((newLine.indexOf("\n") == -1) && !timeout);
    }
    return newLine;
}

void Commands::_ExtractCommandAndPayload(String rawLine, String &command, String &payload){
    int carriageReturnPosition, divisor;
    
    // Lines end with "\r\n". Removing eveything from \r and after
    carriageReturnPosition = rawLine.indexOf("\r");
    if(carriageReturnPosition != -1){
        rawLine = rawLine.substring(0, carriageReturnPosition);
    }
    else{
        Serial.println("\nNo carriage return in this raw command");
    }

    divisor = rawLine.indexOf(" ");
    if(divisor == -1){
        command = rawLine;
        payload = "";
    }
    else{
        command = rawLine.substring(0, divisor);
        payload = rawLine.substring(divisor+1);
    }
}

void Commands::_ExecuteCommand(String command, String payload){
    if(_commandFunctionsMap.find(command) != _commandFunctionsMap.end()){
        _commandFunctionsMap[command](payload);
    }
    else{
        Serial.println("Command not found");
    }
}
