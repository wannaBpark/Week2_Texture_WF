#include "UClassManager.h"
#include "UObject.h"
#include "Actor/Actor.h"
#include "Actor/Sphere.h"
#include "Actor/Cube.h"
#include "Actor/Arrow.h"
#include "Actor/BillBoard.h"
#include "Actor/Camera.h"
#include "Actor/Circle.h"
#include "Actor/Cone.h"
#include "Actor/Cylinder.h"
#include "Actor/Picker.h"
#include "Actor/SubUV.h"
#include "Actor/Triangle.h"
#include "Actor/WorldGrid.h"
#include "Actor/WorldText.h"



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
            PushUClass(typeid(AArrow).name(), GetClass<AActor>());
            PushUClass(typeid(ABillBoard).name(), GetClass<AActor>());
            PushUClass(typeid(ACamera).name(), GetClass<AActor>());
            PushUClass(typeid(ACircle).name(), GetClass<AActor>());
            PushUClass(typeid(ACone).name(), GetClass<AActor>());
            PushUClass(typeid(ACylinder).name(), GetClass<AActor>());
            PushUClass(typeid(APicker).name(), GetClass<AActor>());
            PushUClass(typeid(ASubUV).name(), GetClass<AActor>());
            PushUClass(typeid(ATriangle).name(), GetClass<AActor>());
            PushUClass(typeid(AWorldGrid).name(), GetClass<AActor>());
            PushUClass(typeid(AWorldText).name(), GetClass<AActor>());
        }
    }
}