#pragma once

#include "LittleFS.h"

class MemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();

    static void StartFileSystem();
    
    static void WriteStringOnFile(String filename, String fileContent);
    static String ReadStringFromFile(String fileName);
private:
};

