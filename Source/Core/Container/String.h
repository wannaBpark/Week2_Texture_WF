#pragma once

#define _TCHAR_DEFINED
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include "ContainerAllocator.h"
#include "Core/HAL/PlatformType.h"


class FString
{
private:
    using BaseStringType = std::basic_string<
        TCHAR,
        std::char_traits<TCHAR>,
        FDefaultAllocator<TCHAR>
    >;

    BaseStringType PrivateString;

public:
    FString() {}

#if IS_WIDECHAR
private:
    static std::wstring ConvertWideChar(const ANSICHAR*NarrowStr);

    FString(const std::wstring& InString) : PrivateString(InString) {}
    FString(const std::string& InString) : PrivateString(ConvertWideChar(InString.c_str())) {}

public:
    FString(const WIDECHAR* InString) : PrivateString(InString) {}
    FString(const ANSICHAR* InString) : PrivateString(ConvertWideChar(InString)) {}
#else
private:
    FString(const std::string& InString) : PrivateString(InString) {}
public:
    FString(const ANSICHAR* InString) : PrivateString(InString) {}
#endif

    static FString FromInt(int32 Num);

public:
    // bool Equals(const FString& Other) const;
};
