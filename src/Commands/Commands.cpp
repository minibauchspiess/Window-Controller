#include "Commands/Commands.h"


Commands::Commands()
{
}

Commands::~Commands()
{
}

std::map<String, void(*)(String)> Commands::GetCommandFunctionsMap(){
    return _commandFunctionsMap;
}