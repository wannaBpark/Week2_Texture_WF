#pragma once
#include "Object/Actor/Actor.h"

class AWorldText : public AActor
{
    using Super = AActor;
public:
    AWorldText();
    virtual ~AWorldText() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
};
