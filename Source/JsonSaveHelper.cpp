#include "JsonSaveHelper.h"

#include <fstream>

using json::JSON;

// SceneName - 확장자 제외
UWorldInfo* JsonSaveHelper::LoadScene(const char* SceneName)
{
    std::ifstream Input(SceneName);

    if (!Input.is_open())
    {
        throw std::exception("Scene file not found"); 
    }
    std::string Contents;
    Input.seekg( 0, std::ios::end );
    Contents.reserve( Input.tellg() );
    Input.seekg( 0, std::ios::beg );

    Contents.assign( std::istreambuf_iterator<char>( Input ), std::istreambuf_iterator<char>() );

    JSON Json = JSON::Load(Contents);

    UWorldInfo* WorldInfo = new UWorldInfo();
     
    WorldInfo->Version = Json["Version"].ToInt();
    WorldInfo->sceneName = Json["SceneName"].ToString();
    WorldInfo->NextUUID = Json["NextUUID"].ToInt();
    WorldInfo->Objcts = new UObjectInfo*[WorldInfo->NextUUID];
    for (int i = 0; i < WorldInfo->NextUUID; i++)
    {
        UObjectInfo* ObjectInfo = new UObjectInfo();
        WorldInfo->Objcts[i] = ObjectInfo;
        std::string Uuid = std::to_string(ObjectInfo->UUID);
        JSON Location = Json["Primitives"][Uuid]["Location"];
        JSON Rotation = Json["Primitives"][Uuid]["Rotation"];
        JSON Scale = Json["Primitives"][Uuid]["Scale"];
        ObjectInfo->Location = FVector(Location[0].ToFloat(), Location[1].ToFloat(), Location[2].ToFloat());
        ObjectInfo->Rotation = FVector(Rotation[0].ToFloat(), Rotation[1].ToFloat(), Rotation[2].ToFloat());
        ObjectInfo->Scale = FVector(Scale[0].ToFloat(), Scale[1].ToFloat(), Scale[2].ToFloat());

        int ComponentCount = Json["Primitives"][Uuid]["Components"].length();
        for (int i = 0; i < ComponentCount; i++)
        {
            ObjectInfo->ComponentUUIDs.push_back(Json["Primitives"][Uuid]["Components"][i].ToInt());   
        }
        
        
        std::string UObjectInfoType = Json["Primitives"][Uuid]["Type"].ToString();
        if (UObjectInfoType == "Sphere")
        {
            ObjectInfo->ObjectType = UObjectTypeInfo::Type::Sphere;
        }
        else if (UObjectInfoType == "Cube")
        {
            ObjectInfo->ObjectType = UObjectTypeInfo::Type::Cube;
        }
        // Type 추가에 따라 추가
        
        ObjectInfo->UUID = i;
    }
    return WorldInfo;
}

void JsonSaveHelper::SaveScene(const UWorldInfo& WorldInfo)
{
    JSON Json;
    
    Json["Version"] = WorldInfo.Version;
    Json["NextUUID"] = WorldInfo.NextUUID;
    Json["SceneName"] = WorldInfo.sceneName;

    for (int i = 0; i < 5; i++)
    {
        UObjectInfo* ObjectInfo = WorldInfo.Objcts[i];
        std::string Uuid = std::to_string(ObjectInfo->UUID);
        Json["Primitives"][Uuid]["Location"].append(ObjectInfo->Location.X, ObjectInfo->Location.Y, ObjectInfo->Location.Z);
        Json["Primitives"][Uuid]["Rotation"].append(ObjectInfo->Rotation.X, ObjectInfo->Rotation.Y, ObjectInfo->Rotation.Z);
        Json["Primitives"][Uuid]["Scale"].append(ObjectInfo->Scale.X, ObjectInfo->Scale.Y, ObjectInfo->Scale.Z);
        Json["Primitives"][Uuid]["Type"] = UObjectInfo::GetType(ObjectInfo);
        for (int uuid : ObjectInfo->ComponentUUIDs)
        { 
            Json["Primitives"][Uuid]["Components"].append(uuid);
        }
    }
     
    std::ofstream Output(WorldInfo.sceneName + ".scene");
    
    if (Output.is_open())
    {
        Output << Json;
    }
}

const char* UObjectInfo::GetType(const UObjectInfo* ObjectType)
{
     switch (ObjectType->ObjectType)
     {
     case UObjectTypeInfo::Type::Sphere:
         return "Sphere";
     case UObjectTypeInfo::Type::Cube:
         return "Cube";
     default:
         return  "default";
     }
 }

