#pragma once
#include "Actor.h"
#include "Object/ObjectMacro.h"

class ACylinder : public AActor
{
    using Super = AActor;
    DECLARE_CLASS(ACylinder, Super)
public:
    ACylinder();
    virtual ~ACylinder() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;

};

