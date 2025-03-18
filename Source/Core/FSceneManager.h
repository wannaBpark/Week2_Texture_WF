#pragma once
#include "unordered_map"
#include "Core/AbstractClass/Singleton.h"
#include "Object/World/World.h"
#include "../EEnum.h"


class FSceneManager : public TSingleton<FSceneManager>
{
public:
	std::unordered_map<FString, UWorld> worldMap;

	void ToggleShowFlag(EShowFlag showFlag) { showFlagMasking ^= showFlag; }
private:
	uint32 showFlagMasking = 0xFFFFFFFF;
};