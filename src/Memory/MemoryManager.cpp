#include "Memory/MemoryManager.h"

MemoryManager::MemoryManager()
{
    LittleFS.begin();
}

MemoryManager::~MemoryManager()
{
}

void MemoryManager::StartFileSystem(){
    Serial.println("Mounting file system...");
    if(!LittleFS.begin()){
        Serial.println("Failed mounting filesystem");
    }
}

void MemoryManager::WriteStringOnFile(String fileName, String fileContent){
    File file;

    file = LittleFS.open(fileName, "w");
    if(!file){
        Serial.printf("Failed opening file %s to write\n", fileName.c_str());
        return;
    }

    file.write(fileContent.c_str());

    file.close();
}

String MemoryManager::ReadStringFromFile(String fileName){
    File file;
    String fileContent;

    file = LittleFS.open(fileName, "r");
    if(!file){
        Serial.printf("Failed opening file %s to read\n", fileName.c_str());
        return "";
    }

    fileContent = file.readString();

    file.close();

    return fileContent;
}