#include "UClassManager.h"
#include "UObject.h"
#include "Actor/Actor.h"
#include "Actor/Sphere.h"
#include "Actor/Cube.h"

UClassManager::UClassManager()
{
    Initialize();
}

UClassManager::~UClassManager()
{
    // map에 저장된 모든 UClass 포인터를 해제합니다.
    for (auto& pair : ClassMap)
    {
        delete pair.second;
    }
}

UClassManager& UClassManager::Get()
{
    static UClassManager instance;
    return instance;
}

void UClassManager::PushUClass(const std::string& InName, UClass* ParentClass)
{
    if (ClassMap.find(InName) != ClassMap.end())
    {
        return;
    }
    // UClass의 생성자 호출 (UClass는 기본 생성자가 삭제되어 있으므로, 반드시 InName과 ParentClass를 인자로 받아야 함)
    UClass* NewClass = new UClass(InName, ParentClass);
    ClassMap[InName] = NewClass;
}

void UClassManager::Initialize()
{
    PushUClass(typeid(UObject).name(), nullptr);

    {
        PushUClass(typeid(AActor).name(), GetClass<UObject>());
        {
            PushUClass(typeid(ASphere).name(), GetClass<AActor>());
            PushUClass(typeid(ACube).name(), GetClass<AActor>());
        }
    }
}
