#pragma once
#include "Object/Actor/Actor.h"
#include "Object/ObjectMacro.h"

class ASphere : public AActor
{
	using Super = AActor;
public:
	DECLARE_CLASS(ASphere, AActor)

	ASphere();
	virtual ~ASphere() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual const char* GetTypeName() override;

};

