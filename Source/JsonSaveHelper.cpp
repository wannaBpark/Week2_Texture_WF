#include "JsonSaveHelper.h"

#include <fstream>
#include <string>

UUScene* JsonSaveHelper::LoadScene(const char* SceneName)
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

    JSON JsonData = JSON::Load(Contents);

    UUScene* Scene = new UUScene();
     
    Scene->Version = JsonData["Version"].ToInt();
    Scene->sceneName = JsonData["SceneName"].ToString();
    Scene->NextUUID = JsonData["NextUUID"].ToInt();
    Scene->Objcts = new UUObject*[Scene->NextUUID];
    for (int i = 0; i < Scene->NextUUID; i++)
    {
        UUObject* Object = new UUObject();
        Scene->Objcts[i] = Object;
        std::string Uuid = std::to_string(Object->UUID);
        JSON Location = JsonData["Primitives"][Uuid]["Location"];
        JSON Rotation = JsonData["Primitives"][Uuid]["Rotation"];
        JSON Scale = JsonData["Primitives"][Uuid]["Scale"];
        Object->Location = FVector(Location[0].ToFloat(), Location[1].ToFloat(), Location[2].ToFloat());
        Object->Rotation = FVector(Rotation[0].ToFloat(), Rotation[1].ToFloat(), Rotation[2].ToFloat());
        Object->Scale = FVector(Scale[0].ToFloat(), Scale[1].ToFloat(), Scale[2].ToFloat());

        std::string type = JsonData["Primitives"][Uuid]["Type"].ToString();
        if (type == "Sphere")
        {
            Object->ObjectType = UUObjectType::Type::Sphere;
        }
        else if (type == "Cube")
        {
            Object->ObjectType = UUObjectType::Type::Cube;
        }
        Object->UUID = i;
    }
    return Scene;
}

 void JsonSaveHelper::SaveScene()
{
    UUScene Scene;

    Scene.Objcts = new UUObject*[5];
    Scene.sceneName = "Scene Name";
    Scene.NextUUID = 5;
    for (int i = 0; i < 5; i++)
    {
        Scene.Objcts[i] = new UUObject();
        Scene.Objcts[i]->UUID = i;
        Scene.Objcts[i]->Location = FVector(rand() % 100, rand() % 100, rand() % 100);
        Scene.Objcts[i]->Rotation = FVector(rand() % 100, rand() % 100, rand() % 100);
        Scene.Objcts[i]->Scale = FVector(rand() % 100, rand() % 100, rand() % 100);
        auto random = rand() % 2;
        if (random == 0)
        {
            Scene.Objcts[i]->ObjectType = UUObjectType::Type::Cube;   
        }else
        {
            Scene.Objcts[i]->ObjectType = UUObjectType::Type::Sphere;
        }
    }

    SaveScene(Scene);
}

void JsonSaveHelper::SaveScene(const UUScene& Scene)
{
    JSON json;

    json["Version"] = Scene.Version;
    json["NextUUID"] = Scene.NextUUID;
    json["SceneName"] = Scene.sceneName;
    json["A"] = "a";
    json["B"] = "a";
    json["C"] = "a";
    json["D"] = "a";
    json["E"] = "a";
    json["F"] = "a";
    json["G"] = "a";
     
    for (int i = 0; i < 5; i++)
    {
        UUObject* object = Scene.Objcts[i];
        std::string Uuid = std::to_string(object->UUID);
        json["Primitives"][Uuid]["Location"].append(object->Location.X, object->Location.Y, object->Location.Z);
        json["Primitives"][Uuid]["Rotation"].append(object->Rotation.X, object->Rotation.Y, object->Rotation.Z);
        json["Primitives"][Uuid]["Scale"].append(object->Scale.X, object->Scale.Y, object->Scale.Z);
        json["Primitives"][Uuid]["Type"] = object->GetType();
    }
     
    std::ofstream output(Scene.sceneName + ".scene");

    if (output.is_open())
    {
        output << json;
    }
}

const char* UUObject::GetType() const
{
     switch (ObjectType)
     {
     case UUObjectType::Type::Sphere:
         return "Sphere";
     case UUObjectType::Type::Cube:
         return "Cube";
     default:
         return  "default";
     }
 }
