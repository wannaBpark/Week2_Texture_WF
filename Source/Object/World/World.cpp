#include "World.h"
#include <cassert>
#include "JsonSavehelper.h"
#include "Object/Actor/Actor.h"
#include "Object/Actor/Sphere.h"
#include "Object/Actor/Cube.h"
#include "Object/Actor/Arrow.h"
#include "Object/Gizmo/Axis.h"
#include "Core/EngineStatics.h"
#include "Core/Container/Map.h"

void UWorld::ClearWorld()
{
	//Actors.Empty();
}



void UWorld::BeginPlay()
{
	AAxis* Axis = SpawnActor<AAxis>();

	//AArrow* TestArrow = FObjectFactory::ConstructActor<AArrow>();
	//TestArrow->SetTransform(FTransform(FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 90.0f, 0.0f), FVector(0.2f, 0.2f, 0.5f)));
	//ASphere* TestSphere = FObjectFactory::ConstructActor<ASphere>();
	//FTransform tr = TestArrow->GetActorTransform();
	//TestArrow->SetTransform(tr);
	//TestArrow->SetTransform(FTransform(FVector(0.0f, 0.0f, 2.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.1f, 0.1f, 0.5f)));


	for (const auto& Actor : Actors)
	{
		Actor->BeginPlay();
	}
}

void UWorld::Tick(float DeltaTime)
{
	for (const auto& Actor : ActorsToSpawn)
	{
		Actor->BeginPlay();
	}
	ActorsToSpawn.Empty();

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

void UWorld::ClearWorld()
{
	
}

void UWorld::SaveWorld()
{
	const UWorldInfo& WorldInfo = GetWorldInfo();
	JsonSaveHelper::SaveScene(WorldInfo);
}

void UWorld::LoadWorld(const char* SceneName)
{
	ClearWorld();
	
	UWorldInfo* WorldInfo = JsonSaveHelper::LoadScene(SceneName);

	Version = WorldInfo->Version;
	this->SceneName = WorldInfo->SceneName;
	uint32 ActorCount = WorldInfo->ActorCount;

	// Type 확인
	for (uint32 i = 0; i < ActorCount; i++)
	{
		UObjectInfo* ObjectInfo = WorldInfo->ObjctInfos[i];
		FTransform Transform = FTransform(ObjectInfo->Location, ObjectInfo->Rotation, ObjectInfo->Scale);

		AActor* Actor = nullptr;
		
		if (ObjectInfo->ObjectType == "Actor")
		{
			Actor = FObjectFactory::ConstructActor<AActor>();
		}
		else if (ObjectInfo->ObjectType == "Sphere")
		{
			Actor = FObjectFactory::ConstructActor<ASphere>();
		}
		else if (ObjectInfo->ObjectType == "Cube")
		{
			Actor = FObjectFactory::ConstructActor<ACube>();
		}
		else if (ObjectInfo->ObjectType == "Arrow")
		{
			Actor = FObjectFactory::ConstructActor<AArrow>();
		}
		else if (ObjectInfo->ObjectType == "Axis")
		{
			Actor = FObjectFactory::ConstructActor<AAxis>();
		}
			
		Actor->SetTransform(Transform);
	}
}

UWorldInfo UWorld::GetWorldInfo() const
{
	UWorldInfo WorldInfo;
	WorldInfo.ActorCount = Actors.Num();
	WorldInfo.ObjctInfos = new UObjectInfo*[WorldInfo.ActorCount];
	WorldInfo.SceneName = SceneName;
	WorldInfo.Version = 1;
	uint32 i = 0;
	for (auto& actor : Actors)
	{
		WorldInfo.ObjctInfos[i] = new UObjectInfo();
		const FTransform& Transform = actor->GetActorTransform();
		WorldInfo.ObjctInfos[i]->Location = Transform.GetPosition();
		WorldInfo.ObjctInfos[i]->Rotation = Transform.GetRotation();
		WorldInfo.ObjctInfos[i]->Scale = Transform.GetScale();
		WorldInfo.ObjctInfos[i]->ObjectType = actor->GetTypeName();

		WorldInfo.ObjctInfos[i]->UUID = actor->GetUUID();
		i++;
	}
	return WorldInfo;
}