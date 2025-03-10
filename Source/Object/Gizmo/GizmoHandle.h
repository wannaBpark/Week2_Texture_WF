#pragma once
#include "Object/Actor/Actor.h"

class AGizmoHandle : public AActor
{
public:
	AGizmoHandle();
	virtual ~AGizmoHandle() = default;

public:
	virtual void Tick(float DeltaTime) override;
	void SetScaleByDistance();
	void SetActive(bool bActive);
private:
	bool bIsActive = false;
	TArray<class UCylinderComp*> CylinderComponents;

	virtual const char* GetTypeName() override;
};

