#pragma once
#include "Object/Actor/Actor.h"

class ACircle : public AActor
{
    using Super = AActor;
public:
    ACircle();
    virtual ~ACircle() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;


};

