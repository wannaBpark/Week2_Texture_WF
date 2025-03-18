#pragma once
#include "Object/Actor/Actor.h"
#include "Object/ObjectMacro.h"

class ACircle : public AActor
{
    using Super = AActor;
    DECLARE_CLASS(ACircle, Super)
public:
    ACircle();
    virtual ~ACircle() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;


};

