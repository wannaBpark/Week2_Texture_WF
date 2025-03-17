#pragma once
#include "Actor.h"
#include "Core/Container/Array.h"
#include <string>

class ASubUV : public AActor
{
    using Super = AActor;
public:
    ASubUV();
    virtual ~ASubUV() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
    void SetFrame(int32 frame);

    void SetAtlas(std::string InAtlasName);

private:
    USubUVComponent* SubUVComponent;
    std::string AtlasName;
};
