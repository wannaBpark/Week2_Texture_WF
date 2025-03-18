#pragma once
#include "Actor.h"
#include "Object/ObjectMacro.h"

class ACube : public AActor
{
	using Super = AActor;
	DECLARE_CLASS(ACube, Super)


public:
	ACube();
	virtual ~ACube() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual const char* GetTypeName() override;

};

