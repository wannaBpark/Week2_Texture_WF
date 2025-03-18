#pragma once
#include "Actor.h"
#include "Core/Container/Array.h"
#include <string>
#include "Object/ObjectMacro.h"


class UWorldTextComponent;

class AWorldText : public AActor
{
    DECLARE_CLASS(AWorldText, AActor)
    using Super = AActor;
    
public:
    AWorldText();
    virtual ~AWorldText() = default;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;

    void ClearCharComps();
    void SetCharComps(std::string InText);

    float GetLetterSpacing();
    void SetLetterSpacing(float InLetterSpacing);

    void SetActive(bool bActive);

private:
    bool bIsActive = false;
	TArray<UWorldCharComp> CharComps;
	float LetterSpacing{ 0.0f };

public:
	void SetUseBillboardUtil(bool bUse);
	bool IsUseBillboardUtil() const { return bUseBillboardUtil; }

private:
    bool bUseBillboardUtil = false;

};
