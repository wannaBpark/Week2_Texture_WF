#pragma once
#include <string>

#include "ContainerAllocator.h"


class FString
{
private:
    using BaseStringType = TCHAR;
    std::basic_string<
        BaseStringType,
        std::char_traits<BaseStringType>,
        FDefaultAllocator<BaseStringType>
    > PrivateString;

    explicit FString(const std::string& InString) : PrivateString(InString) {}

public:
    FString() : PrivateString() {}
    FString(const ANSICHAR* InString) : PrivateString(InString) {}
    
    static FString FromInt(int32 Num);

public:
    // bool Equals(const FString& Other) const;
};
