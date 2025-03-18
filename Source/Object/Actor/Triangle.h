#pragma once
#include "Object/Actor/Actor.h"

class ATriangle : public AActor
{
    using Super = AActor;
public:
    ATriangle();
    virtual ~ATriangle() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;

public:
    static UClass* GetClass();
};