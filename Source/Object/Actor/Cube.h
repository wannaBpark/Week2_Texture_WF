#pragma once
#include "Actor.h"



class ACube : public AActor
{
	using Super = AActor;

public:
	static UClass* GetClass();

public:
	ACube();
	virtual ~ACube() = default;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual const char* GetTypeName() override;
};

