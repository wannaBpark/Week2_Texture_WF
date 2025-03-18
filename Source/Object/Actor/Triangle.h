#pragma once
#include "Object/Actor/Actor.h"
#include "Object/ObjectMacro.h"

class ATriangle : public AActor
{
    using Super = AActor;
    DECLARE_CLASS(ATriangle, Super)
public:
    ATriangle();
    virtual ~ATriangle() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;

};