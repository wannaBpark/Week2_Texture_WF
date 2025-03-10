#pragma once
#include "Object/Actor/Actor.h"

enum class ESelectedAxis : uint8
{
	None,
	X,
	Y,
	Z
};

class AGizmoHandle : public AActor
{
public:
	AGizmoHandle();

public:
	virtual void Tick(float DeltaTime) override;
	void SetScaleByDistance();
	void SetActive(bool bActive);
	void SetSelectedAxis(ESelectedAxis NewAxis) { SelectedAxis = NewAxis; }
	ESelectedAxis GetSelectedAxis() const { return SelectedAxis; }

private:
	bool bIsActive = false;
	TArray<class UCylinderComp*> CylinderComponents;

	ESelectedAxis SelectedAxis = ESelectedAxis::None;

	virtual const char* GetTypeName() override;
};

