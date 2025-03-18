#pragma once
#include "Actor.h"
#include "Core/Container/Array.h"
#include "Object/ObjectMacro.h"


class ASubUV : public AActor
{
    DECLARE_CLASS(ASubUV, AActor)
    using Super = AActor;
    
public:
    ASubUV();
    virtual ~ASubUV() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
    void SetFrame(int32 frame);
private:
    USubUVComponent* SubUVComponent;

};
