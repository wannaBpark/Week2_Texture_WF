#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include "UClass.h"
#include "Debug/DebugConsole.h"

#define EquipUClass(ObjectClass, ClassPtr)  do { \
    ClassPtr = UClassManager::Get().GetClass<ObjectClass>(); \
} while(0)

class UClassManager {
private:
    UClassManager();
    ~UClassManager();
    UClassManager(const UClassManager&) = delete;
    UClassManager& operator=(const UClassManager&) = delete;

    std::unordered_map<std::string, UClass*> ClassMap;

public:
	static UClassManager& Get();
    void Initialize();
    void PushUClass(const std::string& InName, UClass* ParentClass);

    template <typename T>
    UClass* GetClass()
    {
        auto it = ClassMap.find(typeid(T).name());
        if (it != ClassMap.end())
        {
            UClass* foundClass = it->second;
            return foundClass;
        }
        else
        {
            UE_LOG("ClassMap don't have %s", typeid(T).name());
            return nullptr;
        }
    }

};