#include "World.h"
#include <cassert>
#include "Object/Actor/Actor.h"
#include "JsonSavehelper.h"
#include "Object/Actor/Sphere.h"
#include "Object/Actor/Cube.h"
#include "Object/Gizmo/Axis.h"

void UWorld::ClearWorld()
{
	//Actors.Empty();
}

UWorldInfo UWorld::GetWorldInfo()
{
	UWorldInfo WorldInfo{};
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
	AAxis* Axis = SpawnActor<AAxis>();
	ASphere* TestSphere = SpawnActor<ASphere>();
	ACube* TestCube = SpawnActor<ACube>();

	for (const auto& Actor : Actors)
	{
		Actor->BeginPlay();
	}
}

void UWorld::Tick(float DeltaTime)
{
	for (const auto& Actor : Actors)
	{
		if (Actor->CanEverTick())
		{
			Actor->Tick(DeltaTime);
		}
	}

	for (const auto& PendingActor : PendingDestroyActors)
	{
		// Engine에서 제거
		UEngine::Get().GObjects.Remove(PendingActor->shared_from_this());
	}
	PendingDestroyActors.Empty();
}

bool UWorld::DestroyActor(AActor* InActor)
{
	// 나중에 Destroy가 실패할 일이 있다면 return false; 하기
	assert(InActor);

	if (PendingDestroyActors.Find(InActor) != -1)
	{
		return true;
	}

	// 삭제될 때 Destroyed 호출
	InActor->Destroyed();

	// World에서 제거
	Actors.Remove(InActor);

	// 제거 대기열에 추가
	PendingDestroyActors.Add(InActor);
	return true;
}
