#pragma once
#include "Object/Actor/Actor.h"

class AGizmoHandle : public AActor
{
public:
	AGizmoHandle();
	virtual ~AGizmoHandle() = default;

public:
	void SetActive(bool bActive) { bIsActive = bActive; }
private:
	bool bIsActive = false;
	TArray<class UCylinderComp*> ArrowComponents;

	virtual const char* GetTypeName() override;
};

