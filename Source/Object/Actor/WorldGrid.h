#pragma once
#include "Actor.h"
#include "Object/ObjectMacro.h"


class AWorldGrid : public AActor
{
	using Super = AActor;
	DECLARE_CLASS(AWorldGrid, Super)
public:
	AWorldGrid();
	virtual ~AWorldGrid() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual const char* GetTypeName() override;

};

