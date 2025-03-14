#include "UClass.h"

UClass::UClass(std::string InName, UClass* InParentClass)
	:Name(InName), ParentClass(InParentClass) { }

UClass::~UClass()
{

}

bool UClass::IsA(UClass* OtherClass)
{
	if (this->Name == OtherClass->GetName()) 
	{
		return true;
	}

	if (ParentClass != nullptr) 
	{
		return ParentClass->IsA(OtherClass);
	}
	return false;
}

