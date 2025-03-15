#pragma once
#include "Actor.h"
class ABillBoard : public AActor
{
	using Super = AActor;
public:
	ABillBoard();
	virtual ~ABillBoard() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual const char* GetTypeName() override;
};

