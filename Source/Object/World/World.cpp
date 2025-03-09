#include "World.h"
#include "Object/Actor/Actor.h"
#include "JsonSavehelper.h"
#include <Object/Actor/Sphere.h>
#include <Object/Actor/Cube.h>
#include <Object/Gizmo/Axis.h>
#include <Object/Actor/Arrow.h>

void UWorld::ClearWorld()
{
	//Actors.Empty();
}

UWorldInfo& UWorld::GetWorldInfo()
{
	UWorldInfo WorldInfo;
	// WorldInfo.Objcts = new UObjectInfo*[10];
	// WorldInfo.sceneName = SceneName;
	// WorldInfo.Version = 1;
	// WorldInfo.NextUUID = UEngineStatics::GetNextUUID();
	// for (auto& actor : Actors)
	// {
	// 	FTransform& Transform = actor->GetTransform();
	// 	WorldInfo.Objcts[i]->Location =Transform.GetPosition();
	// 	WorldInfo.Objcts[i]->Rotation =Transform.GetRotation();
	// 	WorldInfo.Objcts[i]->Scale =Transform.GetScale();
	// 	WorldInfo.Objcts[i]->ObjectType = ObjectType;
	// 	WorldInfo.Objcts[i]->UUID = 1;
	// 	for (auto component : actor->Components)
	// 	{
	// 		WorldInfo.Objcts[i]->ComponentUUIDs.push_back(component->uuid);
	// 	} 
	//	}
	return WorldInfo;
}

void UWorld::SaveWorld()
{
	//UWorldInfo& WorldInfo = GetWorldInfo();
	//JsonSaveHelper::SaveScene(WorldInfo);
}

void UWorld::LoadWorld(const char* Name)
{
	ClearWorld();
	// !TODO : WorldInfo에 맞게 오브젝트들 Instantiate
	//UWorldInfo* WorldInfo = JsonSaveHelper::LoadScene(Name);
}

void UWorld::BeginPlay()
{
	AAxis* Axis = FObjectFactory::ConstructActor<AAxis>();

	//ACube* TestCube1 = FObjectFactory::ConstructActor<ACube>();
	//TestCube1->SetTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));

	//ACube* TestCube2 = FObjectFactory::ConstructActor<ACube>();
	//TestCube2->SetTransform(FTransform(FVector(.5f, .5f, .5f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));

	AArrow* TestArrow = FObjectFactory::ConstructActor<AArrow>();
	TestArrow->SetTransform(FTransform(FVector(0.0f, 0.0f, 1.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.2f, 0.2f, 0.5f)));
	//ASphere* TestSphere = FObjectFactory::ConstructActor<ASphere>();
	//FTransform tr = TestArrow->GetActorTransform();
	//TestArrow->SetTransform(tr);

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
