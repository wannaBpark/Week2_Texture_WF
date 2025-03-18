#pragma once
#include "unordered_map"
#include "Core/AbstractClass/Singleton.h"
#include "../EEnum.h"
#include "Core/HAL/PlatformType.h"

class UWorld;
class FSceneManager : public TSingleton<FSceneManager>
{
public:
	void AddScene(UWorld* world);
	void ToggleShowFlag(EShowFlag showFlag) { showFlagMasking ^= showFlag; }
private:
	std::unordered_map<uint32, UWorld*> worldMap;
	inline static uint32 showFlagMasking = 0xFFFFFFFF;
};