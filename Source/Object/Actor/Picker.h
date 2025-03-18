#pragma once

#include "Actor.h"
#include "Object/ObjectMacro.h"


class APicker : public AActor
{
    DECLARE_CLASS(APicker, AActor)
    using Super = AActor;
    
public:
    APicker();
    ~APicker() = default;
    
    static FVector4 EncodeUUID(unsigned int UUID);
    static uint32_t DecodeUUID(FVector4 color);
    
    virtual void Tick(float DeltaTime) override;
    virtual void LateTick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
private:
    POINT GetMousePoint();


};
