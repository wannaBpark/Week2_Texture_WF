#pragma once

#include "Core/Math/Vector.h"
#include "SimpleJSON/Json.hpp"

using json::JSON;

namespace UUObjectType{
    enum class Type
    {
        Sphere,
        Cube
    };
}

class UUObject
{
public:
    FVector Location; 
    FVector Rotation;
    FVector Scale;
    UUObjectType::Type ObjectType;

    int UUID;
    const char* GetType() const;
};

class UUScene
{
public:
    UUObject** Objcts;
    int NextUUID;
    int Version;
    std::string sceneName;
};

class JsonSaveHelper
{
public:
    static UUScene* LoadScene(const char* SceneName);    // SceneName에 해당하는 파일을 읽어오고 Clear() 후 LoadData
    static void SaveScene();                         // 현재 SceneName과 SceneData를 저장 후 Write
    static void SaveScene(const UUScene& Scene);
};
