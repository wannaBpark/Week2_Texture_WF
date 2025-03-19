#pragma once
#include "Object/USceneComponent.h"
#include "Object/ObjectMacro.h"
#include "Core/Container/Array.h"

class UCharComp;

class UStringComponent : public USceneComponent 
{
	DECLARE_CLASS(UStringComponent, USceneComponent)

public:
	UStringComponent();
	virtual ~UStringComponent() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ClearCharComps();
	void SetCharComps(std::string InText);

	float GetLetterSpacing();
	void SetLetterSpacing(float InLetterSpacing);

	void SetActive(bool bActive);
	TArray<UCharComp> CharComps;

private:
	bool bIsActive = false;
	float LetterSpacing{ 0.0f };

public:
	void SetUseBillboardUtil(bool bUse);
	bool IsUseBillboardUtil() const { return bUseBillboardUtil; }

private:
	bool bUseBillboardUtil = false;
};