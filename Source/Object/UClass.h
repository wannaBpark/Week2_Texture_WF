#pragma once
#include <string>

class UClass {
public:
	UClass() = delete;
	UClass(std::string InName, UClass* InParentClass);
	~UClass();

	std::string GetName() const { return Name; }
	UClass* GetParentClass() const { return ParentClass; }

private:
	std::string Name;
	UClass* ParentClass;

public:
	bool IsA(UClass* OtherClass);

};