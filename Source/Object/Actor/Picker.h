#pragma once

#include "Actor.h"

class APicker : public AActor
{
    using Super = AActor;
public:
    APicker();
    ~APicker() = default;
    
    static FVector4 EncodeUUID(unsigned int UUID);
    static uint32_t DecodeUUID(FVector4 color);
    
    virtual void Tick(float DeltaTime) override;
    virtual void LateTick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
    
    static bool SetSelectActor(const UActorComponent* actorComponent);
private:
    static POINT GetMousePoint();
    UActorComponent* GetAcotrByPixelPicking(const POINT& pt);
    static void PickLocalGizmo(UActorComponent* actor);
    static void PickWorldGizmo();
};
