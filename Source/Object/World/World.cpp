#include "World.h"
#include "Object/Actor/Actor.h"
#include "JsonSavehelper.h"
#include <Object/Actor/Sphere.h>
#include <Object/Actor/Cube.h>
#include <Object/Gizmo/Axis.h>


void UWorld::LoadWorld(const UWorldInfo& WorldInfo)
{
	// !TODO : WorldInfo에 맞게 오브젝트들 Instantiate
}

void UWorld::BeginPlay()
{
	AAxis* Axis = FObjectFactory::ConstructActor<AAxis>();

	ASphere* TestSphere = FObjectFactory::ConstructActor<ASphere>();
	TestSphere->SetTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));

	ACube* TestCube = FObjectFactory::ConstructActor<ACube>();
	TestCube->SetTransform(FTransform(FVector(0.0f, 1.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));

	for (auto& Actor : Actors)
	{
		Actor->BeginPlay();
	}
}

void UWorld::Tick(float DeltaTime)
{
	for (auto& Actor : Actors)
	{
		if (Actor->CanEverTick())
		{
			Actor->Tick(DeltaTime);
		}
	}
}
