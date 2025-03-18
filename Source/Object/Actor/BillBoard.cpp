#include "Object/Actor/BillBoard.h"

#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

#include "Object/UClassManager.h"

ABillBoard::ABillBoard()
{
    EquipUClass(ABillBoard, ClassType);

    bCanEverTick = true;

    UBillBoardComp* BillBoardComponent = AddComponent<UBillBoardComp>();
    RootComponent = BillBoardComponent;

    SetActorTransform(FTransform());
}

void ABillBoard::BeginPlay()
{
    Super::BeginPlay();
}

void ABillBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

const char* ABillBoard::GetTypeName()
{
    return "BillBoard";
}

UClass* ABillBoard::GetClass()
{
    return UClassManager::Get().GetClass<ABillBoard>();
}
