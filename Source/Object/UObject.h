#pragma once
#include <memory>

// TODO: RTTI 구현하면 enable_shared_from_this 제거
class UObject : public std::enable_shared_from_this<UObject>
{
public:
	UObject();
	~UObject();

	virtual void Tick(float DeltaTime) {};


	bool IsTickEnabled() const { return bCanEverTick; }

protected:
	bool bCanEverTick = false;
};

