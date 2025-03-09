#pragma once

#include <string>
#include <vector>

#include "Core/Math/Vector.h"

// (TEMP) 각 모든 컴포넌트 타입 
namespace UObjectTypeInfo{
    enum class Type
    {
        Sphere,
        Cube
    };
}

struct UObjectInfo
{
    FVector Location; 
    FVector Rotation;
    FVector Scale;
    UObjectTypeInfo::Type ObjectType;

    int UUID;
    std::vector<int> ComponentUUIDs;
    static const char* GetType(const UObjectInfo* ObjectType);
};

struct UWorldInfo
{
    UObjectInfo** Objcts;
    int NextUUID;
    int Version;
    std::string SceneName;
};

class JsonSaveHelper
{
public:
    // SceneName - 확장자 제외
    static UWorldInfo* LoadScene(const char* SceneName);
    static void SaveScene(const UWorldInfo& WorldInfo);
};
