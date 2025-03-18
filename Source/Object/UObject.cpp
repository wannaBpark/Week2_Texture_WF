#include "UObject.h"
#include "UClassManager.h"


UObject::UObject()
{
	EquipUClass(UObject, ClassType);
}

UObject::~UObject()
{
}

UClass* UObject::GetClass()
{
	return UClassManager::Get().GetClass<UObject>();
}

bool UObject::IsA(UClass* OtherClass)
{
	if (ClassType == nullptr)
	{
		UE_LOG("ClassType is Null");
		return false;
	}
	if (OtherClass == nullptr)
	{
		UE_LOG("OtherClass is Null!");
		return false;
	}

	if (ClassType->GetName() == OtherClass->GetName())
	{
		return true;
	}

	if (ClassType->GetParentClass())
	{
		return ClassType->GetParentClass()->IsA(OtherClass);
	}

	return false;
}
